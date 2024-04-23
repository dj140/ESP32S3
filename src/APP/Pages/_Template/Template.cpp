#include "Template.h"
#include "stdio.h"
using namespace Page;

#include <FFat.h>
#include <LittleFS.h>
#include <SPIFFS.h>
#include <SD.h>
#include <SD_MMC.h>
#include "MjpegClass.h"
#include "JPEGDEC.h"
#include <Arduino_GFX_Library.h>

static MjpegClass mjpeg;
extern Arduino_GFX *gfx;
typedef struct
{
    uint8_t     *out_buff;
    /* LVGL objects */
    lv_obj_t    *main;
    lv_obj_t    *canvas;

} player_ctx_t;
static player_ctx_t player_ctx;
//lv_obj_t *img_obj;
lv_obj_t * img_obj = lv_img_create(lv_scr_act());

#define MJPEG_FILENAME "/earth3.mjpeg"
#define MJPEG_BUFFER_SIZE (240 * 240 * 2 ) // memory for a single JPEG frame
/* variables */
static int total_frames = 0;
static unsigned long total_read_video = 0;
static unsigned long total_decode_video = 0;
static unsigned long total_show_video = 0;
static unsigned long start_ms, curr_ms;
File mjpegFile;



static int jpegDrawCallback(JPEGDRAW *pDraw)
{
  // Serial.printf("Draw pos = %d,%d. size = %d x %d\n", pDraw->x, pDraw->y, pDraw->iWidth, pDraw->iHeight);
  unsigned long start = millis();
  //gfx->draw16bitBeRGBBitmap(pDraw->x, pDraw->y, pDraw->pPixels, pDraw->iWidth, pDraw->iHeight);
      //lv_obj_invalidate(player_ctx.canvas);
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
// pixel drawing callback
void Template::update_img(uint8_t *downloaded_jpeg_buf, size_t buf_size)
 {
    static lv_img_dsc_t jpeg_dsc = {
        LV_IMG_CF_TRUE_COLOR_ALPHA,
        0,
        0,
        240,
        240,
    };
    /* Set the buffer location and size each time in case it changes */
    jpeg_dsc.data = downloaded_jpeg_buf;
    jpeg_dsc.data_size = buf_size;
    lv_img_cache_invalidate_src(&jpeg_dsc); /* invalidate JPEG so it gets decoded again */
    lv_img_set_src(View.ui.image, &jpeg_dsc);
}
void Template::onCustomAttrConfig()
{
    LV_LOG_USER("begin");
    SetCustomCacheEnable(true);
    SetCustomLoadAnimType(PageManager::LOAD_ANIM_OVER_BOTTOM, 1000, lv_anim_path_bounce);
}

void Template::onViewLoad()
{
    printf("Template begin \n");
    View.Create(_root);
//    lv_label_set_text(View.ui.labelTitle, _Name);

    AttachEvent(_root);
    AttachEvent(View.ui.cont);

//    Model.TickSave = Model.GetData();
}

void Template::onViewDidLoad()
{
    LV_LOG_USER("begin");
}

void Template::onViewWillAppear()
{
    LV_LOG_USER("begin");
    timer = lv_timer_create(onTimerUpdate, 16, this);
//     player_ctx.canvas = lv_canvas_create(lv_scr_act());
//   lv_canvas_set_buffer(player_ctx.canvas, player_ctx.out_buff, 240, 240, LV_IMG_CF_RGB565);
//   lv_obj_center(player_ctx.canvas);
//   lv_canvas_fill_bg(player_ctx.canvas, lv_palette_lighten(LV_PALETTE_GREY, 3), LV_OPA_COVER);
     if (!LittleFS.begin())
  {
    Serial.println(F("ERROR: File System Mount Failed!"));
    gfx->println(F("ERROR: File System Mount Failed!"));
  }
  else
  {

     mjpegFile = LittleFS.open(MJPEG_FILENAME, "r");

    if (!mjpegFile || mjpegFile.isDirectory())
    {
      Serial.println(F("ERROR: Failed to open " MJPEG_FILENAME " file for reading"));
      gfx->println(F("ERROR: Failed to open " MJPEG_FILENAME " file for reading"));
    }
    else
    {
      player_ctx.out_buff = (uint8_t *)malloc(MJPEG_BUFFER_SIZE);
      if (!player_ctx.out_buff)
      {
        Serial.println(F("mjpeg_buf malloc failed!"));
      }
      else
      {
        Serial.println(F("MJPEG start"));

        start_ms = millis();
        curr_ms = millis();
        mjpeg.setup(
            &mjpegFile, player_ctx.out_buff, jpegDrawCallback, true /* useBigEndian */,
            0 /* x */, 0 /* y */, gfx->width() /* widthLimit */, gfx->height() /* heightLimit */);
      }
    }
  }
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
   
        // Play video
        mjpeg.drawJpg();
        total_decode_video += millis() - curr_ms;

    //lv_img_set_src(img_obj, &jpeg_dsc);
    update_img(player_ctx.out_buff,MJPEG_BUFFER_SIZE);
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

    lv_obj_t* obj = lv_event_get_current_target(event);
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
