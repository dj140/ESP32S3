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
player_ctx_t player_ctx;
//lv_obj_t *img_obj;
// lv_obj_t * img_obj = lv_img_create(lv_scr_act());
    lv_img_dsc_t img;

#define MJPEG_FILENAME "/earth3.mjpeg"
#define MJPEG_BUFFER_SIZE (240 * 16 * 2 ) // memory for a single JPEG frame
/* variables */
static int total_frames = 0;
static unsigned long total_read_video = 0;
static unsigned long total_decode_video = 0;
static unsigned long total_show_video = 0;
static unsigned long start_ms, curr_ms;
File mjpegFile;
// extern lv_color_t * cam_buffer;
// static size_t cam_buf_size;
// static lv_obj_t * camera_canvas = NULL;
//  extern lv_color_t cbuf[];
// lv_color_t cbuf[LV_CANVAS_BUF_SIZE_TRUE_COLOR(240, 16)];



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
//         lv_draw_rect_dsc_t rect_dsc;
//     lv_draw_rect_dsc_init(&rect_dsc);
//     rect_dsc.radius = 10;
//     rect_dsc.bg_opa = LV_OPA_COVER;
//     rect_dsc.bg_grad.dir = LV_GRAD_DIR_HOR;
//     rect_dsc.bg_grad.stops[0].color = lv_palette_main(LV_PALETTE_RED);
//     rect_dsc.bg_grad.stops[1].color = lv_palette_main(LV_PALETTE_BLUE);
//     rect_dsc.border_width = 2;
//     rect_dsc.border_opa = LV_OPA_90;
//     rect_dsc.border_color = lv_color_white();
//     rect_dsc.shadow_width = 5;
//     rect_dsc.shadow_ofs_x = 5;
//     rect_dsc.shadow_ofs_y = 5;

//    lv_draw_label_dsc_t label_dsc;
//     lv_draw_label_dsc_init(&label_dsc);
//     label_dsc.color = lv_palette_main(LV_PALETTE_ORANGE);

//    player_ctx.canvas = lv_canvas_create(View.ui.cont);
//     lv_canvas_set_buffer(player_ctx.canvas, cbuf, 240, 16, LV_IMG_CF_TRUE_COLOR);
//     lv_obj_center(player_ctx.canvas);
//         lv_canvas_fill_bg(player_ctx.canvas, lv_palette_lighten(LV_PALETTE_GREY, 3), LV_OPA_COVER);
//     lv_canvas_draw_rect(player_ctx.canvas, 70, 60, 240, 16, &rect_dsc);
//     lv_obj_invalidate(player_ctx.canvas);
//     if (!LittleFS.begin())
//     {
//         Serial.println(F("ERROR: File System Mount Failed!"));
//         gfx->println(F("ERROR: File System Mount Failed!"));
//     }
//     else
//     {

//         mjpegFile = LittleFS.open(MJPEG_FILENAME, "r");

//         if (!mjpegFile || mjpegFile.isDirectory())
//         {
//             Serial.println(F("ERROR: Failed to open " MJPEG_FILENAME " file for reading"));
//             gfx->println(F("ERROR: Failed to open " MJPEG_FILENAME " file for reading"));
//         }
//         else
//         {
//             player_ctx.out_buff = (uint8_t *)malloc(MJPEG_BUFFER_SIZE);

//             if (!player_ctx.out_buff)
//             {
//                 Serial.println(F("mjpeg_buf malloc failed!"));
//             }
//             else
//             {
//                 Serial.println(F("MJPEG start"));

//                 start_ms = millis();
//                 curr_ms = millis();
//                 mjpeg.setup(
//                 &mjpegFile, player_ctx.out_buff, jpegDrawCallback, false /* useBigEndian */,
//                 0 /* x */, 0 /* y */, gfx->width() /* widthLimit */, gfx->height() /* heightLimit */);
//             }

//         }
//     }

//    Model.TickSave = Model.GetData();
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

    // lv_canvas_fill_bg(myView.ui.image, LV_COLOR_SILVER, LV_OPA_COVER);
    //lv_canvas_transform(myView.ui.image, &img, 30, LV_IMG_ZOOM_NONE, 0, 0, 240, 16, true);



    //lv_obj_invalidate(player_ctx.canvas);
    // memcpy(cbuf, pDraw->pPixels, sizeof(cbuf));




    // TemplateView myView;
    //  lv_obj_invalidate(myView.ui.image);

    //Serial.println(F("ERROR: File System Mount Failed!"));

  total_show_video += millis() - start;
  return 1;
}
void Template::onViewWillAppear()
{
    LV_LOG_USER("begin");
    timer = lv_timer_create(onTimerUpdate, 16, this);
    // cam_buf_size = 240 * 240 * 2;
    // cam_buffer = (lv_color_t*)heap_caps_malloc(cam_buf_size, MALLOC_CAP_DEFAULT);
    // assert(cam_buffer);
    // memset(cam_buffer, 0, cam_buf_size);
    //  camera_canvas = lv_canvas_create(View.ui.cont);
    // lv_canvas_set_buffer(camera_canvas, cam_buffer, 240, 240, LV_IMG_CF_TRUE_COLOR);
    // lv_obj_center(camera_canvas);
//     player_ctx.canvas = lv_canvas_create(lv_scr_act());
//   lv_canvas_set_buffer(player_ctx.canvas, player_ctx.out_buff, 240, 240, LV_IMG_CF_RGB565);
//   lv_obj_center(player_ctx.canvas);
//   lv_canvas_fill_bg(player_ctx.canvas, lv_palette_lighten(LV_PALETTE_GREY, 3), LV_OPA_COVER);

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
    // while (mjpegFile.available() && mjpeg.readMjpegBuf())
    // {
   
    //     // Play video
    //     mjpeg.drawJpg();
    //     total_decode_video += millis() - curr_ms;


    //         //lv_img_set_src(View.ui.image, &img);

    // //   static lv_color_t cbuf_tmp[240 * 240];
    // // memcpy(cbuf_tmp, player_ctx.out_buff, sizeof(cbuf_tmp));

    // //update_img(player_ctx.out_buff,MJPEG_BUFFER_SIZE);
    // }
 
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
