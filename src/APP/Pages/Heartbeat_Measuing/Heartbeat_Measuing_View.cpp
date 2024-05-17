#include "Heartbeat_Measuing_View.h"
#include <stdarg.h>
#include <stdio.h>

using namespace Page;

lv_obj_t* ui_pulsegroupA_create(lv_obj_t* comp_parent)
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
void Heartbeat_Measuing_View::Create(lv_obj_t* root)
{

    lv_obj_t* ui_measuing = lv_obj_create(root);
    lv_obj_remove_style_all(ui_measuing);
    lv_obj_clear_flag(ui_measuing, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_clear_flag(ui_measuing, LV_OBJ_FLAG_GESTURE_BUBBLE);      /// Flags
    lv_obj_set_style_bg_color(ui_measuing, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_measuing, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_size(ui_measuing, TFT_HOR_RES, TFT_VER_RES);
    lv_obj_set_align(ui_measuing, LV_ALIGN_CENTER);
    ui.cont = ui_measuing;

    lv_obj_t* ui_bg7 = lv_img_create(ui_measuing);
    lv_img_set_src(ui_bg7, ResourcePool::GetImage("bg1_png"));
    lv_obj_set_width(ui_bg7, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_bg7, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_bg7, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_bg7, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_bg7, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    lv_obj_t* ui_pulse_group3 = ui_pulsegroupA_create(ui_measuing);
    lv_obj_set_x(ui_pulse_group3, 0);
    lv_obj_set_y(ui_pulse_group3, 70);
    lv_obj_set_style_border_color(ui_pulse_group3, lv_color_hex(0x545454), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_pulse_group3, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_pulse_group3, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui_pulse_group3, LV_BORDER_SIDE_BOTTOM, LV_PART_MAIN | LV_STATE_DEFAULT);



    lv_obj_t* ui_measuring = lv_label_create(ui_measuing);
    lv_obj_set_width(ui_measuring, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_measuring, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_measuring, 0);
    lv_obj_set_y(ui_measuring, 120);
    lv_obj_set_align(ui_measuring, LV_ALIGN_CENTER);
    lv_label_set_text(ui_measuring, "Measuring...");
    lv_obj_set_style_text_color(ui_measuring, lv_color_hex(0x6A6D6A), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_measuring, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_measuring, ResourcePool::GetFont("bahnschrift_17"), LV_PART_MAIN | LV_STATE_DEFAULT);

//    lv_obj_t* ui_Spinner2 = lv_spinner_create(ui_measuing);
//    lv_obj_set_width(ui_Spinner2, 200);
//    lv_obj_set_height(ui_Spinner2, 200);
//    lv_obj_set_x(ui_Spinner2, 0);
//    lv_obj_set_y(ui_Spinner2, -70);
//    lv_obj_set_align(ui_Spinner2, LV_ALIGN_CENTER);
//    lv_obj_clear_flag(ui_Spinner2, LV_OBJ_FLAG_CLICKABLE);      /// Flags
//    lv_obj_set_style_arc_color(ui_Spinner2, lv_color_hex(0x3E413E), LV_PART_MAIN | LV_STATE_DEFAULT);
//    lv_obj_set_style_arc_opa(ui_Spinner2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
//    lv_obj_set_style_arc_width(ui_Spinner2, 6, LV_PART_MAIN | LV_STATE_DEFAULT);

//    lv_obj_set_style_arc_color(ui_Spinner2, lv_color_hex(0xEE1C18), LV_PART_INDICATOR | LV_STATE_DEFAULT);
//    lv_obj_set_style_arc_opa(ui_Spinner2, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);
//    lv_obj_set_style_arc_rounded(ui_Spinner2, true, LV_PART_INDICATOR | LV_STATE_DEFAULT);

//    lv_obj_t* ui_blood_group = lv_obj_create(ui_measuing);
//    lv_obj_remove_style_all(ui_blood_group);

//    lv_obj_set_width(ui_blood_group, 160);
//    lv_obj_set_height(ui_blood_group, 160);
//    lv_obj_set_x(ui_blood_group, 0);
//    lv_obj_set_y(ui_blood_group, -70);
//    lv_obj_set_align(ui_blood_group, LV_ALIGN_CENTER);
//    lv_obj_clear_flag(ui_blood_group, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
//    lv_obj_set_style_radius(ui_blood_group, 160, LV_PART_MAIN | LV_STATE_DEFAULT);
//    lv_obj_set_style_bg_color(ui_blood_group, lv_color_hex(0x390800), LV_PART_MAIN | LV_STATE_DEFAULT);
//    lv_obj_set_style_bg_opa(ui_blood_group, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
//    lv_obj_set_style_clip_corner(ui_blood_group, true, LV_PART_MAIN | LV_STATE_DEFAULT);
//    lv_obj_set_style_outline_color(ui_blood_group, lv_color_hex(0x4E2725), LV_PART_MAIN | LV_STATE_DEFAULT);
//    lv_obj_set_style_outline_opa(ui_blood_group, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
//    lv_obj_set_style_outline_width(ui_blood_group, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
//    lv_obj_set_style_outline_pad(ui_blood_group, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

//    lv_obj_t* ui_blood1 = lv_img_create(ui_blood_group);
//    lv_img_set_src(ui_blood1, ResourcePool::GetImage("wave2_png"));
//    lv_obj_set_width(ui_blood1, 400);
//    lv_obj_set_height(ui_blood1, LV_SIZE_CONTENT);    /// 1
//    lv_obj_set_x(ui_blood1, -97);
//    lv_obj_set_y(ui_blood1, -6);
//    lv_obj_set_align(ui_blood1, LV_ALIGN_CENTER);
//    lv_obj_add_flag(ui_blood1, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
//    lv_obj_clear_flag(ui_blood1, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

//    lv_obj_t* ui_blood_fill = lv_obj_create(ui_blood_group);
//    lv_obj_remove_style_all(ui_blood_fill);
//    lv_obj_set_height(ui_blood_fill, 71);
//    lv_obj_set_width(ui_blood_fill, lv_pct(100));
//    lv_obj_set_align(ui_blood_fill, LV_ALIGN_BOTTOM_MID);
//    lv_obj_clear_flag(ui_blood_fill, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
//    lv_obj_set_style_bg_color(ui_blood_fill, lv_color_hex(0xDE615A), LV_PART_MAIN | LV_STATE_DEFAULT);
//    lv_obj_set_style_bg_opa(ui_blood_fill, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
//    lv_obj_set_style_bg_grad_color(ui_blood_fill, lv_color_hex(0xDE1810), LV_PART_MAIN | LV_STATE_DEFAULT);
//    lv_obj_set_style_bg_grad_dir(ui_blood_fill, LV_GRAD_DIR_VER, LV_PART_MAIN | LV_STATE_DEFAULT);

//    lv_obj_t* ui_blood2 = lv_img_create(ui_blood_group);
//    lv_img_set_src(ui_blood2, ResourcePool::GetImage("wave1_png"));
//    lv_obj_set_width(ui_blood2, 402);
//    lv_obj_set_height(ui_blood2, LV_SIZE_CONTENT);    /// 1
//    lv_obj_set_x(ui_blood2, -50);
//    lv_obj_set_y(ui_blood2, -3);
//    lv_obj_set_align(ui_blood2, LV_ALIGN_CENTER);
//    lv_obj_add_flag(ui_blood2, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
//    lv_obj_clear_flag(ui_blood2, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

//    lv_obj_t* ui_x_button = lv_btn_create(ui_measuing);
//    lv_obj_remove_style_all(ui_x_button);
//    lv_obj_set_width(ui_x_button, 50);
//    lv_obj_set_height(ui_x_button, 65);
//    lv_obj_set_align(ui_x_button, LV_ALIGN_BOTTOM_MID);
//    lv_obj_add_flag(ui_x_button, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
//    lv_obj_clear_flag(ui_x_button, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
//    lv_obj_set_style_radius(ui_x_button, 50, LV_PART_MAIN | LV_STATE_DEFAULT);
//    lv_obj_set_style_bg_color(ui_x_button, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
//    lv_obj_set_style_bg_opa(ui_x_button, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

//    lv_obj_t* ui_x = lv_img_create(ui_x_button);
//    lv_img_set_src(ui_x, ResourcePool::GetImage("sd_card"));
//    lv_obj_set_width(ui_x, LV_SIZE_CONTENT);   /// 1
//    lv_obj_set_height(ui_x, LV_SIZE_CONTENT);    /// 1
//    lv_obj_set_align(ui_x, LV_ALIGN_CENTER);
//    lv_obj_add_flag(ui_x, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
//    lv_obj_clear_flag(ui_x, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

}

void Heartbeat_Measuing_View::Delete()
{
  lv_obj_del(ui.cont);

}