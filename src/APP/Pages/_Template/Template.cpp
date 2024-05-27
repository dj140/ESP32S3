#include "Template.h"
#include "stdio.h"
using namespace Page;

#include <FFat.h>
#include <LittleFS.h>
#include <SPIFFS.h>
#include <SD.h>
#include <SD_MMC.h>
#include "MjpegClass.h"
// #include "JPEGDEC.h"
#include <LovyanGFX.hpp>
#include "lvgl_port/lv_port_disp.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <ESP32_JPEG_Library.h>

#define MJPEG_FILENAME "/earth.mjpeg"
#define MJPEG_OUTPUT_SIZE (368 * 448 * 2)          // memory for a output image frame
#define MJPEG_BUFFER_SIZE (MJPEG_OUTPUT_SIZE) // memory for a single JPEG frame

static MjpegClass mjpeg;

/* variables */
static int total_frames = 0;
static unsigned long total_read_video = 0;
static unsigned long total_decode_video = 0;
static unsigned long total_show_video = 0;
static unsigned long start_ms, curr_ms;
static int16_t x = -1, y = -1, w = -1, h = -1;

File mjpegFile;
extern LGFX display;
uint8_t *mjpeg_buf;
uint16_t *output_buf;
TaskHandle_t Task1Task_Handler;
static lv_obj_t * camera_canvas = NULL;

// pixel drawing callback
// static int jpegDrawCallback(JPEGDRAW *pDraw)
// {
//    //Serial.printf("Draw pos = %d,%d. size = %d x %d\n", pDraw->x, pDraw->y, pDraw->iWidth, pDraw->iHeight);
//     unsigned long start = millis();
//     display.startWrite();
//     display.setWindow(pDraw->x, pDraw->y, pDraw->iWidth+pDraw->x, pDraw->iHeight+pDraw->y);
//     display.pushPixels((uint16_t *)pDraw->pPixels, pDraw->iWidth * pDraw->iHeight, true);
//     display.endWrite();
// //   gfx->draw16bitBeRGBBitmap(pDraw->x, pDraw->y, pDraw->pPixels, pDraw->iWidth, pDraw->iHeight);
//   total_show_video += millis() - start;
//   return 1;
// }
static void show_video_task(void *arg)
{
while(1)
{
    printf("show_video_task begin \n");
    vTaskDelay(10);
}

}

Template::Template()
    : timer(nullptr)
{
}

Template::~Template()
{

}

void Template::onCustomAttrConfig()
{
    LV_LOG_USER("begin");
    // SetCustomCacheEnable(true);
    // SetCustomLoadAnimType(PageManager::LOAD_ANIM_OVER_BOTTOM, 1000, lv_anim_path_bounce);
}

void Template::onViewLoad()
{
    printf("Template begin \n");
    View.Create(_root);
    AttachEvent(_root);
    AttachEvent(View.ui.cont);
    camera_canvas = lv_canvas_create(View.ui.cont);
    // lv_obj_center(camera_canvas);

    if (!LittleFS.begin())
    {
        Serial.println(F("ERROR: File System Mount Failed!"));
    // gfx->println(F("ERROR: File System Mount Failed!"));
    }
    else
    {
          Serial.println(F("File System Mount OKKKK!"));
    }
    mjpeg_buf = (uint8_t *)malloc(MJPEG_BUFFER_SIZE);

}

void Template::onViewDidLoad()
{
    LV_LOG_USER("begin");
}


void Template::onViewWillAppear()
{
    LV_LOG_USER("begin");
    mjpegFile = LittleFS.open(MJPEG_FILENAME, "r");
    if (!mjpegFile || mjpegFile.isDirectory())
    {
        Serial.println(F("ERROR: Failed to open " MJPEG_FILENAME " file for reading"));
    //   gfx->println(F("ERROR: Failed to open " MJPEG_FILENAME " file for reading"));
    }
    output_buf = (uint16_t *)heap_caps_aligned_alloc(16, MJPEG_OUTPUT_SIZE, MALLOC_CAP_8BIT);
    lv_canvas_set_buffer(camera_canvas, (uint8_t*)output_buf, 368, 448, LV_COLOR_FORMAT_RGB565);
    if (!output_buf)
    {
        Serial.println(F("output_buf malloc failed!"));
    }
    else
    {
        Serial.println(F("MJPEG start"));

        start_ms = millis();
        curr_ms = millis();
        if (!mjpeg.setup(
                &mjpegFile, mjpeg_buf,
                output_buf, MJPEG_OUTPUT_SIZE, true /* useBigEndian */))
        {
        Serial.println(F("mjpeg.setup() failed!"));
        }

    }
    timer = lv_timer_create(onTimerUpdate, 10, this);
    // vTaskResume(Task1Task_Handler);	//恢复任务1
}

void Template::onViewDidAppear()
{
    LV_LOG_USER("begin");
//    lv_obj_del(View.ui.Spinner);
    //  xTaskCreate(show_video_task, "video task", 8196, NULL, 4, &Task1Task_Handler);

}

void Template::onViewWillDisappear()
{
    LV_LOG_USER("begin");
}

void Template::onViewDidDisappear()
{
    LV_LOG_USER("begin");
    lv_timer_del(timer);
    mjpegFile.close();
    int time_used = millis() - start_ms;
    Serial.println(F("MJPEG end"));

    float fps = 1000.0 * total_frames / time_used;
    Serial.printf("Arduino_GFX ESP32 SIMD MJPEG decoder\n\n");
    Serial.printf("Frame size: %d x %d\n", mjpeg.getWidth(), mjpeg.getHeight());
    Serial.printf("Total frames: %d\n", total_frames);
    Serial.printf("Time used: %d ms\n", time_used);
    Serial.printf("Average FPS: %0.1f\n", fps);
    Serial.printf("Read MJPEG: %lu ms (%0.1f %%)\n", total_read_video, 100.0 * total_read_video / time_used);
    Serial.printf("Decode video: %lu ms (%0.1f %%)\n", total_decode_video, 100.0 * total_decode_video / time_used);
    Serial.printf("Show video: %lu ms (%0.1f %%)\n", total_show_video, 100.0 * total_show_video / time_used);
    // vTaskSuspend(Task1Task_Handler);
}

void Template::onViewUnload()
{
    LV_LOG_USER("begin");
}

void Template::onViewDidUnload()
{
    LV_LOG_USER("begin");
}

void Template::AttachEvent(lv_obj_t* obj)
{
    lv_obj_set_user_data(obj, this);
    lv_obj_add_event_cb(obj, onEvent, LV_EVENT_ALL, this);
}

void Template::Update()
{
        if (mjpegFile.available() && mjpeg.readMjpegBuf())
        {
            // Read video
            total_read_video += millis() - curr_ms;
            curr_ms = millis();

            // Play video
            mjpeg.decodeJpg();
            total_decode_video += millis() - curr_ms;
            curr_ms = millis();

            // if (x == -1)
            // {
            //     w = mjpeg.getWidth();
            //     h = mjpeg.getHeight();
            //     x = (w > 368) ? 0 : ((368 - w) / 2);
            //     y = (h > 448) ? 0 : ((448 - h) / 2);
            //     Serial.printf("Draw pos = %d,%d. size = %d x %d\n", x, y, w, h);
            // }
            // gfx->draw16bitBeRGBBitmap(x, y, output_buf, w, h);
            // display.startWrite();
            // display.setWindow(0, 0, 368, 448); 
            // // Serial.printf("Draw pos = %d,%d. size = %d x %d\n", x, y, w, h);

            // display.pushPixels(output_buf, 368 * 448, false);
            // display.endWrite();
            lv_obj_invalidate(camera_canvas);

            total_show_video += millis() - curr_ms;

            curr_ms = millis();
            total_frames++;
        }
   
}

void Template::onTimerUpdate(lv_timer_t* timer)
{
    Template* instance = (Template*)timer->user_data;

    instance->Update();
}

void Template::onEvent(lv_event_t* event)
{
    Template* instance = (Template*)lv_event_get_user_data(event);
    LV_ASSERT_NULL(instance);

    lv_obj_t* obj = lv_event_get_current_target_obj(event);
    lv_event_code_t code = lv_event_get_code(event);
//  printf("lv_event_code_t: %d ", code);

    if (code == LV_EVENT_PRESSED)
    {    

        instance->_Manager->Push("Pages/Dialplate");
    }

//     if (code == LV_EVENT_GESTURE)
//     {
// //      LV_LOG_USER("LV_EVENT_GESTURE %d", code);

//       if (lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_LEFT) {
//           instance->_Manager->Push("Pages/Dialplate");
//       }
//     }

}
