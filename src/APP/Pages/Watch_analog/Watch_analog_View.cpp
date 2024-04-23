#include "Watch_analog_View.h"
#include <stdarg.h>
#include <stdio.h>

using namespace Page;


void Watch_analog_View::Create(lv_obj_t* root)
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

       ANIM_IMG_DEF(200, ui.ui_sec, angle, -lv_img_get_angle(ui.ui_sec), angle_sec+3600),
       ANIM_IMG_DEF(200, ui.ui_min, angle, -lv_img_get_angle(ui.ui_min), angle_min+1620),
       ANIM_IMG_DEF(200, ui.ui_hour, angle, -lv_img_get_angle(ui.ui_hour), angle_hour+900),

       //ANIM_OPA_DEF(500, ui.bottomInfo.labelweek),
/*              ANIM_DEF(600, ui.btnCont.btnRec, height, 0, h_tar_btn),
              ANIM_DEF(700, ui.btnCont.btnMenu, height, 0, h_tar_btn),*/
              LV_ANIM_TIMELINE_WRAPPER_END
    };
    lv_anim_timeline_add_wrapper(ui.anim_timeline, wrapper);

}
void Watch_analog_View::Watch_Create(lv_obj_t* par)
{
    lv_obj_t* ui_watch_analog = lv_obj_create(par);
    lv_obj_remove_style_all(ui_watch_analog);
    lv_obj_clear_flag(ui_watch_analog, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_clear_flag(ui_watch_analog, LV_OBJ_FLAG_GESTURE_BUBBLE);      /// Flags
    lv_obj_set_style_bg_color(ui_watch_analog, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_watch_analog, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_size(ui_watch_analog, 397, 397);
    lv_obj_set_align(ui_watch_analog, LV_ALIGN_CENTER);
    ui.cont = ui_watch_analog;
  
    lv_obj_t* ui_bg_2 = lv_img_create(ui_watch_analog);
    lv_img_set_src(ui_bg_2, ResourcePool::GetImage("apple_watch"));
    lv_obj_set_width(ui_bg_2, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_bg_2, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_bg_2, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_bg_2, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_bg_2, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    lv_obj_t* ui_clock = lv_label_create(ui_watch_analog);
    lv_obj_set_width(ui_clock, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_clock, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_clock, 2);
    lv_obj_set_y(ui_clock, 75);
    lv_obj_set_align(ui_clock, LV_ALIGN_TOP_MID);
    lv_label_set_text(ui_clock, "03   27");
    lv_obj_set_style_text_color(ui_clock, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_clock, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_clock, ResourcePool::GetFont("bahnschrift_17"), LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t* ui_dots = lv_label_create(ui_watch_analog);
    lv_obj_set_width(ui_dots, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_dots, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_dots, 2);
    lv_obj_set_y(ui_dots, 72);
    lv_obj_set_align(ui_dots, LV_ALIGN_TOP_MID);
    lv_label_set_text(ui_dots, ":");
    lv_obj_set_style_text_color(ui_dots, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_dots, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_dots, ResourcePool::GetFont("bahnschrift_17"), LV_PART_MAIN | LV_STATE_DEFAULT);

    //lv_obj_t* ui_battery_group1 = ui_batterygroup_create(ui_watch_analog);
    //lv_obj_set_x(ui_battery_group1, 0);
    //lv_obj_set_y(ui_battery_group1, 20);



    lv_obj_t* ui_date_group2 = lv_obj_create(ui_watch_analog);
    lv_obj_remove_style_all(ui_date_group2);
    lv_obj_set_width(ui_date_group2, 100);
    lv_obj_set_height(ui_date_group2, 82);
    lv_obj_set_x(ui_date_group2, 105);
    lv_obj_set_y(ui_date_group2, 160);
    lv_obj_set_align(ui_date_group2, LV_ALIGN_TOP_MID);
    lv_obj_set_flex_flow(ui_date_group2, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(ui_date_group2, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_clear_flag(ui_date_group2, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_date_group2, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_date_group2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t* ui_day2 = lv_label_create(ui_date_group2);
    lv_obj_set_width(ui_day2, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_day2, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_day2, LV_ALIGN_CENTER);
    lv_label_set_text(ui_day2, "MON");
    lv_obj_set_style_text_color(ui_day2, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_day2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_day2, ResourcePool::GetFont("bahnschrift_17"), LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t* ui_month2 = lv_label_create(ui_date_group2);
    lv_obj_set_width(ui_month2, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_month2, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_month2, LV_ALIGN_CENTER);
    lv_label_set_text(ui_month2, "18 FEB");
    lv_obj_set_style_text_color(ui_month2, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_month2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_month2, ResourcePool::GetFont("bahnschrift_17"), LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t* ui_year2 = lv_label_create(ui_date_group2);
    lv_obj_set_width(ui_year2, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_year2, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_year2, LV_ALIGN_CENTER);
    lv_label_set_text(ui_year2, "2022");
    lv_obj_set_style_text_color(ui_year2, lv_color_hex(0x6B6B6B), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_year2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    //lv_obj_set_style_text_font(ui_year2, &ui_font_Title, LV_PART_MAIN | LV_STATE_DEFAULT);

    //lv_obj_t* ui_weather_title_group_2 = ui_titlegroup_create(ui_watch_analog);
    //lv_obj_set_x(ui_weather_title_group_2, 13);
    //lv_obj_set_y(ui_weather_title_group_2, -83);
    //lv_obj_set_align(ui_weather_title_group_2, LV_ALIGN_BOTTOM_MID);

    //lv_label_set_text(ui_comp_get_child(ui_weather_title_group_2, UI_COMP_TITLEGROUP_TITLE), "Partly Cloudy");

    //lv_label_set_text(ui_comp_get_child(ui_weather_title_group_2, UI_COMP_TITLEGROUP_SUBTITLE), "Max: 18бу Min: 12бу");

    lv_obj_t* ui_weather_group_5 = lv_obj_create(ui_watch_analog);
    lv_obj_remove_style_all(ui_weather_group_5);
    lv_obj_set_width(ui_weather_group_5, 82);
    lv_obj_set_height(ui_weather_group_5, 76);
    lv_obj_set_x(ui_weather_group_5, -90);
    lv_obj_set_y(ui_weather_group_5, 1);
    lv_obj_set_align(ui_weather_group_5, LV_ALIGN_CENTER);
    lv_obj_set_flex_flow(ui_weather_group_5, LV_FLEX_FLOW_COLUMN_REVERSE);
    lv_obj_set_flex_align(ui_weather_group_5, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_clear_flag(ui_weather_group_5, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_weather_group_5, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_weather_group_5, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_row(ui_weather_group_5, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_column(ui_weather_group_5, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t* ui_degree_7 = lv_label_create(ui_weather_group_5);
    lv_obj_set_width(ui_degree_7, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_degree_7, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_degree_7, 8);
    lv_obj_set_y(ui_degree_7, 0);
    lv_obj_set_align(ui_degree_7, LV_ALIGN_CENTER);
    lv_label_set_text(ui_degree_7, "25");
    lv_obj_set_style_text_color(ui_degree_7, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_degree_7, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    //lv_obj_set_style_text_font(ui_degree_7, &ui_font_H1, LV_PART_MAIN | LV_STATE_DEFAULT);

    //lv_obj_t* ui_cloud_fog_3 = lv_img_create(ui_weather_group_5);
    //lv_img_set_src(ui_cloud_fog_3, &ui_img_weather_sun_cloud_png);
    //lv_obj_set_width(ui_cloud_fog_3, LV_SIZE_CONTENT);   /// 1
    //lv_obj_set_height(ui_cloud_fog_3, LV_SIZE_CONTENT);    /// 1
    //lv_obj_set_align(ui_cloud_fog_3, LV_ALIGN_CENTER);
    //lv_obj_add_flag(ui_cloud_fog_3, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    //lv_obj_clear_flag(ui_cloud_fog_3, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    //lv_obj_t* ui_step_group2 = ui_stepgroup_create(ui_watch_analog);
    //lv_obj_set_x(ui_step_group2, 0);
    //lv_obj_set_y(ui_step_group2, -40);



    //lv_obj_t* ui_daily_mission_group1 = ui_dailymissiongroup_create(ui_watch_analog);
    //lv_obj_set_x(ui_daily_mission_group1, 0);
    //lv_obj_set_y(ui_daily_mission_group1, 0);





    //ui_button_top1 = ui_buttontop_create(ui_watch_analog);
    //lv_obj_set_x(ui_button_top1, 145);
    //lv_obj_set_y(ui_button_top1, -105);



    //ui_button_down1 = ui_buttondown_create(ui_watch_analog);
    //lv_obj_set_x(ui_button_down1, 146);
    //lv_obj_set_y(ui_button_down1, 102);



    lv_obj_t* ui_clock_group = lv_obj_create(ui_watch_analog);
    lv_obj_remove_style_all(ui_clock_group);
    lv_obj_set_width(ui_clock_group, 350);
    lv_obj_set_height(ui_clock_group, 350);
    lv_obj_set_align(ui_clock_group, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_clock_group, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    lv_obj_set_style_bg_color(ui_clock_group, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_clock_group, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t* ui_sec = lv_img_create(ui_clock_group);
    lv_img_set_src(ui_sec, ResourcePool::GetImage("clockwise_sec_png"));
    lv_obj_set_width(ui_sec, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_sec, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_sec, 0);
    lv_obj_set_y(ui_sec, -67);
    lv_obj_set_align(ui_sec, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_sec, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_sec, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_img_set_pivot(ui_sec, 15, 155);
    lv_img_set_angle(ui_sec, 0);
    ui.ui_sec = ui_sec;

    lv_obj_t* ui_min = lv_img_create(ui_clock_group);
    lv_img_set_src(ui_min, ResourcePool::GetImage("clockwise_min_png"));
    lv_obj_set_width(ui_min, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_min, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_min, 0);
    lv_obj_set_y(ui_min, -75);
    lv_obj_set_align(ui_min, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_min, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_min, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_img_set_pivot(ui_min, 9, 153);
    ui.ui_min = ui_min;

    lv_obj_t* ui_hour = lv_img_create(ui_clock_group);
    lv_img_set_src(ui_hour, ResourcePool::GetImage("clockwise_hour_png"));
    lv_obj_set_width(ui_hour, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_hour, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_hour, 0);
    lv_obj_set_y(ui_hour, -45);
    lv_obj_set_align(ui_hour, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_hour, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_hour, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_img_set_pivot(ui_hour, 9, 93);
    ui.ui_hour = ui_hour;

//    lv_obj_t* ui_dots_group = lv_obj_create(ui_watch_analog);
//    lv_obj_remove_style_all(ui_dots_group);
//    lv_obj_set_width(ui_dots_group, 20);
//    lv_obj_set_height(ui_dots_group, 50);
//    lv_obj_set_x(ui_dots_group, -10);
//    lv_obj_set_y(ui_dots_group, 0);
//    lv_obj_set_align(ui_dots_group, LV_ALIGN_RIGHT_MID);
//    lv_obj_set_flex_flow(ui_dots_group, LV_FLEX_FLOW_COLUMN);
//    lv_obj_set_flex_align(ui_dots_group, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
//    lv_obj_clear_flag(ui_dots_group, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);      /// Flags
//    lv_obj_set_style_bg_color(ui_dots_group, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
//    lv_obj_set_style_bg_opa(ui_dots_group, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
//    lv_obj_set_style_pad_row(ui_dots_group, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
//    lv_obj_set_style_pad_column(ui_dots_group, 10, LV_PART_MAIN | LV_STATE_DEFAULT);

//    lv_obj_t* ui_dot16 = lv_obj_create(ui_dots_group);
//    lv_obj_set_width(ui_dot16, 10);
//    lv_obj_set_height(ui_dot16, 10);
//    lv_obj_set_align(ui_dot16, LV_ALIGN_CENTER);
//    lv_obj_clear_flag(ui_dot16, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
//    lv_obj_set_style_radius(ui_dot16, 10, LV_PART_MAIN | LV_STATE_DEFAULT);

//    lv_obj_t* ui_dot17 = lv_obj_create(ui_dots_group);
//    lv_obj_set_width(ui_dot17, 6);
//    lv_obj_set_height(ui_dot17, 6);
//    lv_obj_set_align(ui_dot17, LV_ALIGN_CENTER);
//    lv_obj_clear_flag(ui_dot17, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
//    lv_obj_set_style_radius(ui_dot17, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
//    lv_obj_set_style_bg_color(ui_dot17, lv_color_hex(0x676767), LV_PART_MAIN | LV_STATE_DEFAULT);
//    lv_obj_set_style_bg_opa(ui_dot17, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
}
void Watch_analog_View::Delete()
{
    if (ui.anim_timeline)
    {
        lv_anim_timeline_del(ui.anim_timeline);
        ui.anim_timeline = nullptr;
    }
}
void Watch_analog_View::AppearAnimStart(bool reverse)
{
    lv_anim_timeline_set_reverse(ui.anim_timeline, reverse);
    lv_anim_timeline_start(ui.anim_timeline);
}
