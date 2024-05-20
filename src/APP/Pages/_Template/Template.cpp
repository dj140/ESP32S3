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

#define MJPEG_FILENAME "/earth.mjpeg"
#define MJPEG_BUFFER_SIZE (240 * 240 * 2 / 10) // memory for a single JPEG frame

static MjpegClass mjpeg;

/* variables */
static int total_frames = 0;
static unsigned long total_read_video = 0;
static unsigned long total_decode_video = 0;
static unsigned long total_show_video = 0;
static unsigned long start_ms, curr_ms;

File mjpegFile;
extern LGFX display;

// pixel drawing callback
static int jpegDrawCallback(JPEGDRAW *pDraw)
{
  // Serial.printf("Draw pos = %d,%d. size = %d x %d\n", pDraw->x, pDraw->y, pDraw->iWidth, pDraw->iHeight);
  unsigned long start = millis();
    display.startWrite();
    display.setWindow(pDraw->x, pDraw->y, pDraw->iWidth, pDraw->iHeight);
    display.pushPixels((uint16_t *)pDraw->pPixels, pDraw->iWidth * pDraw->iHeight, true);
    display.endWrite();
//   gfx->draw16bitBeRGBBitmap(pDraw->x, pDraw->y, pDraw->pPixels, pDraw->iWidth, pDraw->iHeight);
  total_show_video += millis() - start;
  return 1;
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
    if (!LittleFS.begin())
    {
        Serial.println(F("ERROR: File System Mount Failed!"));
    // gfx->println(F("ERROR: File System Mount Failed!"));
    }
    else
    {
        File mjpegFile = LittleFS.open(MJPEG_FILENAME, "r");
        if (!mjpegFile || mjpegFile.isDirectory())
        {
            Serial.println(F("ERROR: Failed to open " MJPEG_FILENAME " file for reading"));
        //   gfx->println(F("ERROR: Failed to open " MJPEG_FILENAME " file for reading"));
        }
        uint8_t *mjpeg_buf = (uint8_t *)malloc(MJPEG_BUFFER_SIZE);
        Serial.println(F("MJPEG start"));
        start_ms = millis();
        curr_ms = millis();
        mjpeg.setup(&mjpegFile, mjpeg_buf, jpegDrawCallback, true , 0 , 0 , 368, 448 );
    }
}

void Template::onViewDidLoad()
{
    LV_LOG_USER("begin");
}

int Template::jpegDrawCallback(JPEGDRAW *pDraw)
{
  printf("Draw pos = %d,%d. size = %d x %d\n", pDraw->x, pDraw->y, pDraw->iWidth, pDraw->iHeight);
  unsigned long start = millis();
     //gfx->draw16bitBeRGBBitmap(pDraw->x, pDraw->y, pDraw->pPixels, pDraw->iWidth, pDraw->iHeight);
  total_show_video += millis() - start;
  return 1;
}
void Template::onViewWillAppear()
{
    LV_LOG_USER("begin");
    timer = lv_timer_create(onTimerUpdate, 16, this);

}

void Template::onViewDidAppear()
{
    LV_LOG_USER("begin");
//    lv_obj_del(View.ui.Spinner);

}

void Template::onViewWillDisappear()
{
    LV_LOG_USER("begin");
}

void Template::onViewDidDisappear()
{
    LV_LOG_USER("begin");
    lv_timer_del(timer);
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
    while (mjpegFile.available() && mjpeg.readMjpegBuf())
    {
        // Read video
        total_read_video += millis() - curr_ms;
        curr_ms = millis();

        // Play video
        mjpeg.drawJpg();
        total_decode_video += millis() - curr_ms;

        curr_ms = millis();
        total_frames++;
    }

    mjpegFile.close();
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

    if (code == LV_EVENT_GESTURE)
    {
//      LV_LOG_USER("LV_EVENT_GESTURE %d", code);

      if (lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_LEFT) {
          instance->_Manager->Push("Pages/Dialplate");
      }
    }

}
