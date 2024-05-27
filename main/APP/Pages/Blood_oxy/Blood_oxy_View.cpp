#include "Blood_oxy_View.h"
#include <stdarg.h>
#include <stdio.h>

using namespace Page;


lv_obj_t* ui_titlegroup_create(lv_obj_t* comp_parent)
{

    lv_obj_t* cui_titlegroup;
    cui_titlegroup = lv_obj_create(comp_parent);
    lv_obj_remove_style_all(cui_titlegroup);

    lv_obj_set_width(cui_titlegroup, 200);
    lv_obj_set_height(cui_titlegroup, 50);
    lv_obj_set_x(cui_titlegroup, 13);
    lv_obj_set_y(cui_titlegroup, -83);
    lv_obj_set_align(cui_titlegroup, LV_ALIGN_CENTER);
    lv_obj_clear_flag(cui_titlegroup, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(cui_titlegroup, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(cui_titlegroup, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t* cui_title;
    cui_title = lv_label_create(cui_titlegroup);
    lv_obj_set_width(cui_title, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(cui_title, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(cui_title, LV_ALIGN_TOP_MID);
    lv_label_set_text(cui_title, "SpO2");

    lv_obj_set_style_text_color(cui_title, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(cui_title, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(cui_title, ResourcePool::GetFont("bahnschrift_17"), LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t* cui_subtitle;
    cui_subtitle = lv_label_create(cui_titlegroup);
    lv_obj_set_width(cui_subtitle, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(cui_subtitle, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(cui_subtitle, LV_ALIGN_BOTTOM_MID);
    lv_label_set_text(cui_subtitle, "Blood Oxygen");
    lv_obj_set_style_text_color(cui_subtitle, lv_color_hex(0x6D6D6D), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(cui_subtitle, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(cui_subtitle, ResourcePool::GetFont("bahnschrift_17"), LV_PART_MAIN | LV_STATE_DEFAULT);

    //lv_obj_set_style_text_font(ui_comp_get_child(ui_title_group_1, UI_COMP_TITLEGROUP_TITLE), &ui_font_Subtitle,
    //    LV_PART_MAIN | LV_STATE_DEFAULT);

    //lv_obj_t** children = lv_mem_alloc(sizeof(lv_obj_t*) * _UI_COMP_TITLEGROUP_NUM);
    //children[UI_COMP_TITLEGROUP_TITLEGROUP] = cui_titlegroup;
    //children[UI_COMP_TITLEGROUP_TITLE] = cui_title;
    //children[UI_COMP_TITLEGROUP_SUBTITLE] = cui_subtitle;
    //lv_obj_add_event_cb(cui_titlegroup, get_component_child_event_cb, LV_EVENT_GET_COMP_CHILD, children);
    //lv_obj_add_event_cb(cui_titlegroup, del_component_child_event_cb, LV_EVENT_DELETE, children);
    //ui_comp_titlegroup_create_hook(cui_titlegroup);
    return cui_titlegroup;
}
lv_obj_t* ui_pulsegroup_create(lv_obj_t* comp_parent)
{

    lv_obj_t* cui_pulsegroup;
    cui_pulsegroup = lv_obj_create(comp_parent);
    lv_obj_set_width(cui_pulsegroup, 181);
    lv_obj_set_height(cui_pulsegroup, 50);
    lv_obj_set_x(cui_pulsegroup, 0);
    lv_obj_set_y(cui_pulsegroup, 70);
    lv_obj_set_align(cui_pulsegroup, LV_ALIGN_CENTER);
    lv_obj_set_flex_flow(cui_pulsegroup, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(cui_pulsegroup, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_clear_flag(cui_pulsegroup, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(cui_pulsegroup, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(cui_pulsegroup, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_row(cui_pulsegroup, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_column(cui_pulsegroup, 8, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t* cui_heart;
    cui_heart = lv_img_create(cui_pulsegroup);
    lv_img_set_src(cui_heart, ResourcePool::GetImage("bicycle"));
    lv_obj_set_width(cui_heart, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(cui_heart, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(cui_heart, LV_ALIGN_CENTER);
    lv_obj_add_flag(cui_heart, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(cui_heart, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    lv_obj_t* cui_pulse_number;
    cui_pulse_number = lv_label_create(cui_pulsegroup);
    lv_obj_set_width(cui_pulse_number, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(cui_pulse_number, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(cui_pulse_number, LV_ALIGN_CENTER);
    lv_label_set_text(cui_pulse_number, "63");
    lv_obj_set_style_text_color(cui_pulse_number, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(cui_pulse_number, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(cui_pulse_number, ResourcePool::GetFont("bahnschrift_32"), LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t* cui_bpm;
    cui_bpm = lv_label_create(cui_pulsegroup);
    lv_obj_set_width(cui_bpm, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(cui_bpm, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(cui_bpm, LV_ALIGN_CENTER);
    lv_label_set_text(cui_bpm, "bpm");
    lv_obj_set_style_text_color(cui_bpm, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(cui_bpm, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(cui_bpm, ResourcePool::GetFont("bahnschrift_17"), LV_PART_MAIN | LV_STATE_DEFAULT);

    //lv_obj_t** children = lv_mem_alloc(sizeof(lv_obj_t*) * _UI_COMP_PULSEGROUP_NUM);
    //children[UI_COMP_PULSEGROUP_PULSEGROUP] = cui_pulsegroup;
    //children[UI_COMP_PULSEGROUP_HEART] = cui_heart;
    //children[UI_COMP_PULSEGROUP_PULSE_NUMBER] = cui_pulse_number;
    //children[UI_COMP_PULSEGROUP_BPM] = cui_bpm;
    //lv_obj_add_event_cb(cui_pulsegroup, get_component_child_event_cb, LV_EVENT_GET_COMP_CHILD, children);
    //lv_obj_add_event_cb(cui_pulsegroup, del_component_child_event_cb, LV_EVENT_DELETE, children);
    //ui_comp_pulsegroup_create_hook(cui_pulsegroup);
    return cui_pulsegroup;
}
lv_obj_t* ui_buttonround_create(lv_obj_t* comp_parent)
{

    lv_obj_t* cui_buttonround;
    cui_buttonround = lv_btn_create(comp_parent);
    lv_obj_set_width(cui_buttonround, 65);
    lv_obj_set_height(cui_buttonround, 65);
    lv_obj_set_x(cui_buttonround, 0);
    lv_obj_set_y(cui_buttonround, -45);
    lv_obj_set_align(cui_buttonround, LV_ALIGN_BOTTOM_MID);
    lv_obj_add_flag(cui_buttonround, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(cui_buttonround, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(cui_buttonround, 100, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(cui_buttonround, lv_color_hex(0xEE1C18), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(cui_buttonround, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(cui_buttonround, ResourcePool::GetImage("sd_card"), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_color(cui_buttonround, lv_color_hex(0xEE1C18), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_outline_opa(cui_buttonround, 255, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_outline_width(cui_buttonround, 3, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_outline_pad(cui_buttonround, 0, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_shadow_color(cui_buttonround, lv_color_hex(0xEE1C18), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_shadow_opa(cui_buttonround, 255, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(cui_buttonround, 50, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_shadow_spread(cui_buttonround, 2, LV_PART_MAIN | LV_STATE_PRESSED);

    //lv_obj_t** children = lv_mem_alloc(sizeof(lv_obj_t*) * _UI_COMP_BUTTONROUND_NUM);
    //children[UI_COMP_BUTTONROUND_BUTTONROUND] = cui_buttonround;
    //lv_obj_add_event_cb(cui_buttonround, get_component_child_event_cb, LV_EVENT_GET_COMP_CHILD, children);
    //lv_obj_add_event_cb(cui_buttonround, del_component_child_event_cb, LV_EVENT_DELETE, children);
    //ui_comp_buttonround_create_hook(cui_buttonround);
    return cui_buttonround;
}
void Blood_oxy_View::Create(lv_obj_t* root)
{

    lv_obj_t* ui_blood_oxy = lv_obj_create(root);
    lv_obj_remove_style_all(ui_blood_oxy);
    lv_obj_clear_flag(ui_blood_oxy, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_clear_flag(ui_blood_oxy, LV_OBJ_FLAG_GESTURE_BUBBLE);      /// Flags
    lv_obj_set_style_bg_color(ui_blood_oxy, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_blood_oxy, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_size(ui_blood_oxy, TFT_HOR_RES, TFT_VER_RES);
    lv_obj_set_align(ui_blood_oxy, LV_ALIGN_CENTER);
    ui.cont = ui_blood_oxy;

    lv_obj_t* ui_bg6 = lv_img_create(ui_blood_oxy);
    lv_img_set_src(ui_bg6, ResourcePool::GetImage("bg1_png"));
    lv_obj_set_width(ui_bg6, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_bg6, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_bg6, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_bg6, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_bg6, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    lv_obj_t* ui_title_group_1 = ui_titlegroup_create(ui_blood_oxy);
//    lv_obj_remove_style_all(ui_title_group_1);
    lv_obj_set_x(ui_title_group_1, 0);
    lv_obj_set_y(ui_title_group_1, -303);
    lv_obj_set_align(ui_title_group_1, LV_ALIGN_BOTTOM_MID);


    //lv_obj_t* ui_button_down5 = ui_buttondown_create(ui_blood_oxy);
    //lv_obj_set_x(ui_button_down5, 146);
    //lv_obj_set_y(ui_button_down5, 102);

    //lv_img_set_src(ui_comp_get_child(ui_button_down5, UI_COMP_BUTTONDOWN_BUTTON_DOWN_ICON), &ui_img_house_png);

    lv_obj_t* ui_button_round = ui_buttonround_create(ui_blood_oxy);
    lv_obj_set_x(ui_button_round, 0);
    lv_obj_set_y(ui_button_round, -45);
    ui.button = ui_button_round;

    lv_obj_t* ui_blood_presure_group = lv_obj_create(ui_blood_oxy);
    lv_obj_remove_style_all(ui_blood_presure_group);
    lv_obj_set_height(ui_blood_presure_group, 106);
    lv_obj_set_width(ui_blood_presure_group, LV_SIZE_CONTENT);   /// 186
    lv_obj_set_x(ui_blood_presure_group, 0);
    lv_obj_set_y(ui_blood_presure_group, -15);
    lv_obj_set_align(ui_blood_presure_group, LV_ALIGN_CENTER);
    lv_obj_set_flex_flow(ui_blood_presure_group, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(ui_blood_presure_group, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_END, LV_FLEX_ALIGN_START);
    lv_obj_clear_flag(ui_blood_presure_group, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_blood_presure_group, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_blood_presure_group, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t* ui_blood_oxygen = lv_label_create(ui_blood_presure_group);
    lv_obj_set_height(ui_blood_oxygen, lv_pct(80));
    lv_obj_set_width(ui_blood_oxygen, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_align(ui_blood_oxygen, LV_ALIGN_CENTER);
    lv_label_set_text(ui_blood_oxygen, "91");
    lv_obj_set_style_text_color(ui_blood_oxygen, lv_color_hex(0xEE1E1E), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_blood_oxygen, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_blood_oxygen, ResourcePool::GetFont("bahnschrift_65"), LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t* ui_percent = lv_label_create(ui_blood_presure_group);
    lv_obj_set_width(ui_percent, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_percent, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_percent, LV_ALIGN_CENTER);
    lv_label_set_text(ui_percent, "%");
    lv_obj_set_style_text_color(ui_percent, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_percent, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_percent, &lv_font_montserrat_26, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t* ui_pulse_group = ui_pulsegroup_create(ui_blood_oxy);
    lv_obj_set_x(ui_pulse_group, 0);
    lv_obj_set_y(ui_pulse_group, 53);
    lv_obj_set_style_border_color(ui_pulse_group, lv_color_hex(0x545454), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_pulse_group, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_pulse_group, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui_pulse_group, LV_BORDER_SIDE_TOP, LV_PART_MAIN | LV_STATE_DEFAULT);



    lv_obj_t* ui_arc_spo2 = lv_arc_create(ui_blood_oxy);
    lv_obj_set_width(ui_arc_spo2, 370);
    lv_obj_set_height(ui_arc_spo2, 370);
    lv_obj_set_align(ui_arc_spo2, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_arc_spo2, LV_OBJ_FLAG_CLICKABLE);      /// Flags
    lv_arc_set_value(ui_arc_spo2, 91);
    lv_arc_set_bg_angles(ui_arc_spo2, 145, 335);
    lv_obj_set_style_arc_color(ui_arc_spo2, lv_color_hex(0x414141), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_opa(ui_arc_spo2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_rounded(ui_arc_spo2, true, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_arc_color(ui_arc_spo2, lv_color_hex(0x41A1E6), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_opa(ui_arc_spo2, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_rounded(ui_arc_spo2, true, LV_PART_INDICATOR | LV_STATE_DEFAULT);

    lv_obj_set_style_bg_color(ui_arc_spo2, lv_color_hex(0xFFFFFF), LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_arc_spo2, 0, LV_PART_KNOB | LV_STATE_DEFAULT);

    lv_obj_t* ui_precent_70 = lv_label_create(ui_blood_oxy);
    lv_obj_set_width(ui_precent_70, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_precent_70, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_precent_70, 53);
    lv_obj_set_y(ui_precent_70, -65);
    lv_obj_set_align(ui_precent_70, LV_ALIGN_BOTTOM_LEFT);
    lv_label_set_text(ui_precent_70, "70%");
    lv_obj_set_style_text_color(ui_precent_70, lv_color_hex(0x6A6D6A), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_precent_70, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_precent_70, ResourcePool::GetFont("bahnschrift_17"), LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t* ui_precent_100 = lv_label_create(ui_blood_oxy);
    lv_obj_set_width(ui_precent_100, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_precent_100, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_precent_100, -19);
    lv_obj_set_y(ui_precent_100, -58);
    lv_obj_set_align(ui_precent_100, LV_ALIGN_RIGHT_MID);
    lv_label_set_text(ui_precent_100, "100%");
    lv_obj_set_style_text_color(ui_precent_100, lv_color_hex(0x6A6D6A), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_precent_100, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_precent_100, ResourcePool::GetFont("bahnschrift_17"), LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t* ui_health_dots_group = lv_obj_create(ui_blood_oxy);
    lv_obj_remove_style_all(ui_health_dots_group);
    lv_obj_set_width(ui_health_dots_group, 102);
    lv_obj_set_height(ui_health_dots_group, 18);
    lv_obj_set_x(ui_health_dots_group, 0);
    lv_obj_set_y(ui_health_dots_group, -15);
    lv_obj_set_align(ui_health_dots_group, LV_ALIGN_BOTTOM_MID);
    lv_obj_set_flex_flow(ui_health_dots_group, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(ui_health_dots_group, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_clear_flag(ui_health_dots_group, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_health_dots_group, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_health_dots_group, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_row(ui_health_dots_group, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_column(ui_health_dots_group, 10, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t* ui_dot7 = lv_obj_create(ui_health_dots_group);
    lv_obj_set_width(ui_dot7, 10);
    lv_obj_set_height(ui_dot7, 10);
    lv_obj_set_align(ui_dot7, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_dot7, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_dot7, 10, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t* ui_dot6 = lv_obj_create(ui_health_dots_group);
    lv_obj_set_width(ui_dot6, 6);
    lv_obj_set_height(ui_dot6, 6);
    lv_obj_set_align(ui_dot6, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_dot6, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_dot6, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_dot6, lv_color_hex(0x676767), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_dot6, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t* ui_dot5 = lv_obj_create(ui_health_dots_group);
    lv_obj_set_width(ui_dot5, 6);
    lv_obj_set_height(ui_dot5, 6);
    lv_obj_set_align(ui_dot5, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_dot5, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_dot5, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_dot5, lv_color_hex(0x676767), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_dot5, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t* ui_dots_group1 = lv_obj_create(ui_blood_oxy);
    lv_obj_remove_style_all(ui_dots_group1);

    lv_obj_set_width(ui_dots_group1, 20);
    lv_obj_set_height(ui_dots_group1, 50);
    lv_obj_set_x(ui_dots_group1, -10);
    lv_obj_set_y(ui_dots_group1, 0);
    lv_obj_set_align(ui_dots_group1, LV_ALIGN_RIGHT_MID);
    lv_obj_set_flex_flow(ui_dots_group1, LV_FLEX_FLOW_COLUMN_REVERSE);
    lv_obj_set_flex_align(ui_dots_group1, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_clear_flag(ui_dots_group1, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_dots_group1, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_dots_group1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_row(ui_dots_group1, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_column(ui_dots_group1, 10, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t* ui_dot18 = lv_obj_create(ui_dots_group1);
    lv_obj_set_width(ui_dot18, 10);
    lv_obj_set_height(ui_dot18, 10);
    lv_obj_set_align(ui_dot18, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_dot18, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_dot18, 10, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t* ui_dot19 = lv_obj_create(ui_dots_group1);
    lv_obj_set_width(ui_dot19, 6);
    lv_obj_set_height(ui_dot19, 6);
    lv_obj_set_align(ui_dot19, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_dot19, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_dot19, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_dot19, lv_color_hex(0x676767), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_dot19, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    //lv_obj_add_event_cb(ui_button_down5, ui_event_button_down5_buttondown, LV_EVENT_ALL, NULL);
    //lv_obj_add_event_cb(ui_button_round, ui_event_button_round_buttonround, LV_EVENT_ALL, NULL);
    //lv_obj_add_event_cb(ui_blood_oxy, ui_event_blood_oxy, LV_EVENT_ALL, NULL);

}
