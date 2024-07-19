#include "Video_Player.h"
#include "stdio.h"
using namespace Page;

// #include <FFat.h>
// #include <LittleFS.h>
// #include <SPIFFS.h>
// #include <SD.h>
// #include <SD_MMC.h>
// #include "MjpegClass.h"
// #include "JPEGDEC.h"
// #include <LovyanGFX.hpp>
#include "lvgl_port/lv_port_disp.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
// #include <ESP32_JPEG_Library.h>

// #define MJPEG_FILENAME "/earth.mjpeg"
// #define MJPEG_OUTPUT_SIZE (368 * 448 * 2)          // memory for a output image frame
// #define MJPEG_BUFFER_SIZE (MJPEG_OUTPUT_SIZE) // memory for a single JPEG frame

// // static MjpegClass mjpeg;

// /* variables */
// static int total_frames = 0;
// static unsigned long total_read_video = 0;
// static unsigned long total_decode_video = 0;
// static unsigned long total_show_video = 0;
// static unsigned long start_ms, curr_ms;
// static int16_t x = -1, y = -1, w = -1, h = -1;

// File mjpegFile;
// uint8_t *mjpeg_buf;
// uint16_t *output_buf;
// TaskHandle_t Task1Task_Handler;

// pixel drawing callback
// static int jpegDrawCallback(JPEGDRAW *pDraw)
// {
//    //printf("Draw pos = %d,%d. size = %d x %d\n", pDraw->x, pDraw->y, pDraw->iWidth, pDraw->iHeight);
//     unsigned long start = millis();
//     memcpy(&output_buf[pDraw->y* pDraw->iWidth], pDraw->pPixels, pDraw->iWidth * pDraw->iHeight * 2);
//     total_show_video += millis() - start;
//     return 1;
// }

// static void show_video_task(void *arg)
// {
//     while(1)
//     {
//         printf("show_video_task begin \n");
//         vTaskDelay(10);
//     }
// }

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
    View.Create(_root);
    AttachEvent(_root);
    AttachEvent(View.ui.cont);
    AttachEvent(View.ui.canvas);

    // if (!LittleFS.begin())
    // {
    //     println(F("ERROR: File System Mount Failed!"));
    // }
    // else
    // {
    //       println(F("File System Mount OKKKK!"));
    // }
    // mjpeg_buf = (uint8_t *)heap_caps_malloc(MJPEG_BUFFER_SIZE, MALLOC_CAP_SPIRAM);
    // output_buf = (uint16_t *)heap_caps_aligned_alloc(16, MJPEG_OUTPUT_SIZE, MALLOC_CAP_8BIT);
    // printf("PSRAM free size: %d\n", heap_caps_get_free_size(MALLOC_CAP_SPIRAM));
    // if (output_buf!=NULL && mjpeg_buf!=NULL)
    // {    
    //     lv_canvas_set_buffer(View.ui.canvas, (uint8_t*)output_buf, 368, 448, LV_COLOR_FORMAT_RGB565);
    //     println(F("input/output_buf malloc successful!"));
    // }
    // else
    // {
    //     println(F("input/output_buf malloc fail!"));
    // }
}

void Video_Player::onViewDidLoad()
{
    LV_LOG_USER("begin");
}


void Video_Player::onViewWillAppear()
{
    LV_LOG_USER("begin");
    // mjpegFile = LittleFS.open(MJPEG_FILENAME, "r");
    // if (!mjpegFile || mjpegFile.isDirectory())
    // {
    //     println(F("ERROR: Failed to open " MJPEG_FILENAME " file for reading"));
    // }
    // else
    // {
    //     println(F("MJPEG start"));

    //     start_ms = millis();
    //     curr_ms = millis();
    //     // if (!mjpeg.setup(
    //     //         &mjpegFile, mjpeg_buf,
    //     //         output_buf, MJPEG_OUTPUT_SIZE, true /* useBigEndian */))
    //     // {
    //     //     println(F("mjpeg.setup() failed!"));
    //     // }
    //     mjpeg.setup(&mjpegFile, mjpeg_buf, jpegDrawCallback, false , 0 , 0 , 368, 448 );

    // }
    // timer = lv_timer_create(onTimerUpdate, 10, this);
    // vTaskResume(Task1Task_Handler);	//恢复任务1
}

void Video_Player::onViewDidAppear()
{
    LV_LOG_USER("begin");
    //  xTaskCreate(show_video_task, "video task", 8196, NULL, 4, &Task1Task_Handler);
}

void Video_Player::onViewWillDisappear()
{
    LV_LOG_USER("begin");
}

void Video_Player::onViewDidDisappear()
{
    LV_LOG_USER("begin");
    lv_timer_del(timer);
    // mjpegFile.close();
    // int time_used = millis() - start_ms;
    // println(F("MJPEG end"));

    // float fps = 1000.0 * total_frames / time_used;
    // printf("Arduino_GFX ESP32 SIMD MJPEG decoder\n\n");
    // // printf("Frame size: %d x %d\n", mjpeg.getWidth(), mjpeg.getHeight());
    // printf("Total frames: %d\n", total_frames);
    // printf("Time used: %d ms\n", time_used);
    // printf("Average FPS: %0.1f\n", fps);
    // printf("Read MJPEG: %lu ms (%0.1f %%)\n", total_read_video, 100.0 * total_read_video / time_used);
    // printf("Decode video: %lu ms (%0.1f %%)\n", total_decode_video, 100.0 * total_decode_video / time_used);
    // printf("Show video: %lu ms (%0.1f %%)\n", total_show_video, 100.0 * total_show_video / time_used);
    // // vTaskSuspend(Task1Task_Handler);
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
    
    // if (mjpegFile.available())
    // { 
    //     mjpeg.readMjpegBuf();
    //     // Read video
    //     total_read_video += millis() - curr_ms;
    //     curr_ms = millis();

    //     // Play video
    //     // mjpeg.decodeJpg();
    //     mjpeg.drawJpg();
    //     total_decode_video += millis() - curr_ms;
    //     curr_ms = millis();

        // if (x == -1)
        // {
        //     w = mjpeg.getWidth();
        //     h = mjpeg.getHeight();
        //     x = (w > 368) ? 0 : ((368 - w) / 2);
        //     y = (h > 448) ? 0 : ((448 - h) / 2);
        //     printf("Draw pos = %d,%d. size = %d x %d\n", x, y, w, h);
        // }
        // display.startWrite();
        // display.setWindow(0, 0, 368, 448); 
        // display.pushPixels(output_buf, 368 * 448, false);
        // display.endWrite();

    //     lv_obj_invalidate(View.ui.canvas);

    //     total_show_video += millis() - curr_ms;
    //     curr_ms = millis();
    //     total_frames++;
    // }
    // else
    // {
    //     printf("finish start looping\n\n");
    //     mjpegFile = LittleFS.open(MJPEG_FILENAME, "r"); 
    //     mjpeg.setup(&mjpegFile, mjpeg_buf, jpegDrawCallback, false , 0 , 0 , 368, 448 );
    // }
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

    if (code == LV_EVENT_PRESSED)
    {    

        instance->_Manager->Push("Pages/Dialplate");
    }

}
