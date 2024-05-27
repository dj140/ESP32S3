#include "Watch_cxk_View.h"
#include <stdarg.h>
#include <stdio.h>

using namespace Page;


void Watch_cxk_View::Create(lv_obj_t* root)
{
    Watch_Create(root);

    ui.anim_timeline = lv_anim_timeline_create();

#define ANIM_DEF(start_time, obj, attr, start, end) \
    {start_time, obj, LV_ANIM_EXEC(attr), start, end, 500, lv_anim_path_ease_out, true}

#define ANIM_IMG_DEF(start_time, obj, attr, start, end) \
    {start_time, obj, LV_ANIM_IMG(attr), start, end, 2000, lv_anim_path_ease_out, true}

#define ANIM_OPA_DEF(start_time, obj) \
    ANIM_DEF(start_time, obj, opa_scale, LV_OPA_TRANSP, LV_OPA_COVER)

    //lv_coord_t y_tar_top = lv_obj_get_y(ui.topInfo.cont);
    lv_coord_t angle_sec = lv_img_get_angle(ui.ui_sec);
    lv_coord_t angle_min = lv_img_get_angle(ui.ui_min);
    lv_coord_t angle_hour = lv_img_get_angle(ui.ui_hour);

    //lv_coord_t h_tar_btn = lv_obj_get_height(ui.bottomInfo.labelweek);

    lv_anim_timeline_wrapper_t wrapper[] =
    {
        //ANIM_DEF(0, ui.topInfo.cont, y, -lv_obj_get_height(ui.topInfo.cont), y_tar_top),

       //ANIM_IMG_DEF(200, ui.ui_sec, angle, -lv_img_get_angle(ui.ui_sec), angle_sec+3600),
       ANIM_IMG_DEF(200, ui.ui_min, angle, -lv_img_get_angle(ui.ui_min), angle_min + 3600),
       ANIM_IMG_DEF(200, ui.ui_hour, angle, -lv_img_get_angle(ui.ui_hour), angle_hour + 3600),

       //ANIM_OPA_DEF(500, ui.bottomInfo.labelweek),
/*              ANIM_DEF(600, ui.btnCont.btnRec, height, 0, h_tar_btn),
              ANIM_DEF(700, ui.btnCont.btnMenu, height, 0, h_tar_btn),*/
              LV_ANIM_TIMELINE_WRAPPER_END
    };
    lv_anim_timeline_add_wrapper(ui.anim_timeline, wrapper);



}
//static lv_obj_t* img;

//static void set_angle(void* img, int32_t v)
//{
//    lv_img_set_angle(img, v);
//}
void Watch_cxk_View::Watch_Create(lv_obj_t* par)
{
    lv_obj_t* ui_Watch_cxk = lv_obj_create(par);
    lv_obj_remove_style_all(ui_Watch_cxk);
    lv_obj_clear_flag(ui_Watch_cxk, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_clear_flag(ui_Watch_cxk, LV_OBJ_FLAG_GESTURE_BUBBLE);      /// Flags
    lv_obj_set_style_bg_color(ui_Watch_cxk, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Watch_cxk, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_size(ui_Watch_cxk, TFT_HOR_RES, TFT_VER_RES);
    lv_obj_set_align(ui_Watch_cxk, LV_ALIGN_CENTER);
    ui.cont = ui_Watch_cxk;
  
    lv_obj_t* ui_bg_cxk = lv_img_create(ui_Watch_cxk);
    lv_obj_remove_style_all(ui_bg_cxk);
    lv_img_set_src(ui_bg_cxk, "0:sdcard/watch_faces/cxk/cxk_bg.bin");
    lv_obj_set_width(ui_bg_cxk, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_bg_cxk, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_bg_cxk, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_bg_cxk, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_bg_cxk, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    ui.ui_bg = ui_bg_cxk;
  
    lv_obj_t* ui_clock_group = lv_obj_create(ui_Watch_cxk);
    lv_obj_set_width(ui_clock_group, 350);
    lv_obj_set_height(ui_clock_group, 350);
    lv_obj_set_align(ui_clock_group, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_clock_group, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_clock_group, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_clock_group, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t* ui_min = lv_img_create(ui_clock_group);
    lv_img_set_src(ui_min,  ResourcePool::GetImage("cxk_min"));
    lv_obj_set_width(ui_min, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_min, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_min, 0);
    lv_obj_set_y(ui_min, 0);
    lv_obj_set_align(ui_min, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_min, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_min, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    //lv_img_set_pivot(ui_min, 9, 153);
    lv_img_set_angle(ui_min, 2600);

    ui.ui_min = ui_min;

    lv_obj_t* ui_hour = lv_img_create(ui_clock_group);
    lv_img_set_src(ui_hour,  ResourcePool::GetImage("cxk_hour"));
    lv_obj_set_width(ui_hour, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_hour, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_hour, 0);
    lv_obj_set_y(ui_hour, 0);
    lv_obj_set_align(ui_hour, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_hour, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_hour, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    //lv_img_set_pivot(ui_hour, 0, 0);
    lv_img_set_angle(ui_hour, 1000);

    ui.ui_hour = ui_hour;

    lv_obj_t* ui_sec = lv_img_create(ui_clock_group);
    lv_img_set_src(ui_sec,  ResourcePool::GetImage("cxk_sec"));
    lv_obj_set_width(ui_sec, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_sec, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_sec, 0);
    lv_obj_set_y(ui_sec, 0);
    lv_obj_set_align(ui_sec, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_sec, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_sec, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    //lv_img_set_pivot(ui_sec, 15, 155);
    lv_img_set_angle(ui_sec, 0);
    ui.ui_sec = ui_sec;

    ///*Create an animation to set the value*/
    lv_anim_t a;
    lv_anim_init(&a);
    lv_anim_set_exec_cb(&a, (lv_anim_exec_xcb_t)lv_img_set_angle);
    lv_anim_set_values(&a, 0, 3600);
    lv_anim_set_repeat_count(&a, LV_ANIM_REPEAT_INFINITE);
    lv_anim_set_time(&a, 30000);     /*2 sec for 1 turn of the minute hand (1 hour)*/
    lv_anim_set_var(&a, ui_sec);
    lv_anim_start(&a);

    //lv_anim_set_var(&a, ui_hour);
    //lv_anim_set_time(&a, 2000);    /*24 sec for 1 turn of the hour hand*/
    //lv_anim_set_values(&a, 0, 3600);
    //lv_anim_start(&a);
}
void Watch_cxk_View::Delete()
{
    if (ui.anim_timeline)
    {
        lv_anim_timeline_del(ui.anim_timeline);
        ui.anim_timeline = nullptr;
    }
}
void Watch_cxk_View::AppearAnimStart(bool reverse)
{
    lv_anim_timeline_set_reverse(ui.anim_timeline, reverse);
    lv_anim_timeline_start(ui.anim_timeline);
}
