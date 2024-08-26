#include "Video_Player.h"
#include "stdio.h"
using namespace Page;

#include "esp_chip_info.h"
#include "spi_flash_mmap.h"
#include "esp_littlefs.h"
#include "lvgl_port/lv_port_disp.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_err.h"
#include "esp_log.h"
#include "esp_flash.h"
#include "JPEGDEC.h"
#include "MjpegClass.h"
#include "esp_lcd_sh8601.h"
#include "esp_lcd_panel_io.h"
#include "esp_lcd_panel_io_interface.h"
// #include <ESP32_JPEG_Library.h>
static const char *TAG = "Video_Player";

#define MJPEG_FILENAME "/sdcard/video0.mjpeg"
// #define MJPEG_FILENAME "/littlefs/earth.mjpeg"
#define MJPEG_OUTPUT_SIZE ((TFT_HOR_RES + 6) * TFT_VER_RES * 2)          // memory for a output image frame
#define MJPEG_BUFFER_SIZE (MJPEG_OUTPUT_SIZE) // memory for a single JPEG frame

static MjpegClass mjpeg;

/* variables */
// static int total_frames = 0;
// static unsigned long total_read_video = 0;
// static unsigned long total_decode_video = 0;
// static unsigned long total_show_video = 0;
// static unsigned long start_ms, curr_ms;
// static int16_t x = -1, y = -1, w = -1, h = -1;

FILE *mjpegFile;
uint8_t *mjpeg_buf;
uint16_t *output_buf;
bool status;
uint8_t video_str[20];
uint8_t video_num = 1;
uint8_t video_max = 7;

esp_lcd_panel_handle_t panel_handle = NULL;
lv_display_t * disp;

// pixel drawing callback
static int jpegDrawCallback(JPEGDRAW *pDraw)
{
    /*Draw pos = 0,0. size = 416 x 16
    Draw pos = 0,16. size = 416 x 16
    .....
    Draw pos = 0,464. size = 416 x 16
    Draw pos = 0,480. size = 416 x 14*/
    // printf("Draw pos = %d,%d. size = %d x %d\n", pDraw->x, pDraw->y, pDraw->iWidth, pDraw->iHeight);
    // unsigned long start = millis();
    memcpy(&output_buf[pDraw->y * pDraw->iWidth], pDraw->pPixels, pDraw->iWidth * pDraw->iHeight * 2);
    // total_show_video += millis() - start;
    return 1;
}


Video_Player::Video_Player()
    : timer(nullptr)
{
}

Video_Player::~Video_Player()
{

}

void Video_Player::onCustomAttrConfig()
{
    LV_LOG_USER("begin");
    // SetCustomCacheEnable(true);
    // SetCustomLoadAnimType(PageManager::LOAD_ANIM_OVER_BOTTOM, 1000, lv_anim_path_bounce);
}

void Video_Player::onViewLoad()
{
    printf("Video_Player begin \n");
    Model.Init();
    View.Create(_root);
    AttachEvent(_root);
    AttachEvent(View.ui.cont);
    AttachEvent(View.ui.canvas);

    ESP_LOGI(TAG, "Initializing LittleFS");

    esp_vfs_littlefs_conf_t conf = {
        .base_path = "/littlefs",
        .partition_label = "littlefs",
        .format_if_mount_failed = true,
        .dont_mount = false,
    };

    // Use settings defined above to initialize and mount LittleFS filesystem.
    // Note: esp_vfs_littlefs_register is an all-in-one convenience function.
    esp_err_t ret = esp_vfs_littlefs_register(&conf);

    if (ret != ESP_OK)
    {
        if (ret == ESP_FAIL)
        {
            ESP_LOGE(TAG, "Failed to mount or format filesystem");
        }
        else if (ret == ESP_ERR_NOT_FOUND)
        {
            ESP_LOGE(TAG, "Failed to find LittleFS partition");
        }
        else
        {
            ESP_LOGE(TAG, "Failed to initialize LittleFS (%s)", esp_err_to_name(ret));
        }
        return;
    }

    size_t total = 0, used = 0;
    ret = esp_littlefs_info(conf.partition_label, &total, &used);
    if (ret != ESP_OK)
    {
        ESP_LOGE(TAG, "Failed to get LittleFS partition information (%s)", esp_err_to_name(ret));
    }
    else
    {
        ESP_LOGI(TAG, "Partition size: total: %d, used: %d", total, used);
    }
    // uint8_t *mjpeg_buf = (uint8_t *)aligned_alloc(16, MJPEG_BUFFER_SIZE);
    // uint16_t *output_buf = (uint16_t *)aligned_alloc(16, MJPEG_OUTPUT_SIZE);
    mjpeg_buf = (uint8_t *)heap_caps_malloc(MJPEG_BUFFER_SIZE, MALLOC_CAP_SPIRAM);
    output_buf = (uint16_t *)heap_caps_aligned_alloc(16, MJPEG_OUTPUT_SIZE, MALLOC_CAP_8BIT);
    printf("PSRAM free size: %d\n", heap_caps_get_free_size(MALLOC_CAP_SPIRAM));

    if (output_buf!=NULL && mjpeg_buf!=NULL)
    {    
        lv_canvas_set_buffer(View.ui.canvas, (uint8_t*)output_buf, TFT_HOR_RES + 6, TFT_VER_RES, LV_COLOR_FORMAT_RGB565);
        printf("input/output_buf malloc successful! \n");
    }
    else
    {
        printf("input/output_buf malloc fail!");
    }

}

void Video_Player::onViewDidLoad()
{
    LV_LOG_USER("begin");
}


void Video_Player::onViewWillAppear()
{
    disp = lv_disp_get_default();
    panel_handle = (esp_lcd_panel_handle_t)lv_display_get_user_data(disp);

    // panel_sh8601_disp_set_BGR(panel_handle, 0);

    LV_LOG_USER("begin");
    ESP_LOGI(TAG, "Opening file");
    mjpegFile = fopen(MJPEG_FILENAME, "r");
    if (mjpegFile == NULL)
    {
        ESP_LOGE(TAG, "Failed to open file");
        return;
    }
    mjpeg.setup(mjpegFile, mjpeg_buf, jpegDrawCallback, false , 0 , 0 , TFT_HOR_RES + 6, TFT_VER_RES );
    // mjpeg.setup(mjpegFile, mjpeg_buf, false , 0 , 0 , TFT_HOR_RES + 6, TFT_VER_RES );
    // mjpeg.setup(mjpegFile, mjpeg_buf, output_buf, MJPEG_OUTPUT_SIZE, true /* useBigEndian */);
    timer = lv_timer_create(onTimerUpdate, 10, this);

}

void Video_Player::onViewDidAppear()
{
    LV_LOG_USER("begin");
}

void Video_Player::onViewWillDisappear()
{
    LV_LOG_USER("begin");
}

void Video_Player::onViewDidDisappear()
{
    LV_LOG_USER("begin");
    lv_timer_del(timer);
    mjpeg.close();
    panel_sh8601_disp_set_BGR(panel_handle, 1);
    // if(mjpeg_buf)
    // {
    //     heap_caps_free(mjpeg_buf);
    // }
    // if(output_buf)
    // {
    //     heap_caps_free(output_buf);
    // }
}

void Video_Player::onViewUnload()
{
    LV_LOG_USER("begin");
}

void Video_Player::onViewDidUnload()
{
    LV_LOG_USER("begin");
}

void Video_Player::AttachEvent(lv_obj_t* obj)
{
    lv_obj_set_user_data(obj, this);
    lv_obj_add_event_cb(obj, onEvent, LV_EVENT_ALL, this);
}

void Video_Player::Update()
{
    if(mjpeg.readMjpegBuf())
    {
        mjpeg.drawJpg();
        // mjpeg.decodeJpg();
        lv_obj_invalidate(View.ui.canvas);
    }
    else
    {
        sprintf((char*)video_str, "/sdcard/video%01d.mjpeg", video_num); 
        printf("%d: %s\r\n", video_num, (char*)video_str);
        video_num++;
        if (video_num > video_max)
        {
            video_num = 0;
        }
        ESP_LOGI(TAG, "Finish Video Playing Loop \n");
        fclose(mjpegFile);
        mjpegFile = fopen((char*)video_str, "r");
        lv_canvas_set_buffer(View.ui.canvas, (uint8_t*)output_buf, TFT_HOR_RES + 6, TFT_VER_RES, LV_COLOR_FORMAT_RGB565);
        mjpeg.setup(mjpegFile, mjpeg_buf, jpegDrawCallback, false , 0 , 0 , TFT_HOR_RES + 6, TFT_VER_RES );
    }
//    ESP_LOGI(TAG, "free MALLOC_CAP_DMA: %d \n", heap_caps_get_free_size(MALLOC_CAP_DMA));

}

void Video_Player::onTimerUpdate(lv_timer_t* timer)
{
    Video_Player* instance = (Video_Player*)timer->user_data;

    instance->Update();
}

void Video_Player::onEvent(lv_event_t* event)
{
    Video_Player* instance = (Video_Player*)lv_event_get_user_data(event);
    LV_ASSERT_NULL(instance);

    lv_obj_t* obj = lv_event_get_current_target_obj(event);
    lv_event_code_t code = lv_event_get_code(event);
//  printf("lv_event_code_t: %d ", code);

    // if (code == LV_EVENT_PRESSED)
    // {    
    //     instance->_Manager->Push("Pages/Dialplate");
    // }
    if(code == LV_EVENT_SHORT_CLICKED)
    {
        sprintf((char*)video_str, "/sdcard/video%01d.mjpeg", video_num); 
        printf("%d: %s\r\n", video_num, (char*)video_str);
        video_num++;
        if (video_num > video_max)
        {
            video_num = 0;
        }
        ESP_LOGI(TAG, "Next Video Playing \n");
        fclose(mjpegFile);
        mjpegFile = fopen((char*)video_str, "r");
        lv_canvas_set_buffer(instance->View.ui.canvas, (uint8_t*)output_buf, TFT_HOR_RES + 6, TFT_VER_RES, LV_COLOR_FORMAT_RGB565);
        mjpeg.setup(mjpegFile, mjpeg_buf, jpegDrawCallback, false , 0 , 0 , TFT_HOR_RES + 6, TFT_VER_RES );
        // instance->_Manager->Push("Pages/Dialplate");
    }

    if (code == LV_EVENT_LONG_PRESSED)
    {    
        instance->_Manager->Push("Pages/Image_Player");
    }

}
