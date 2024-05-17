#include "DialplateView.h"
#include <stdarg.h>
#include <stdio.h>

using namespace Page;

void DialplateView::Create(lv_obj_t* root)
{
    Dialplate_Create(root);
        //TopInfo_Create(root);
        //BtnCont_Create(root);

    ui.anim_timeline = lv_anim_timeline_create();

#define ANIM_DEF(start_time, obj, attr, start, end) \
    {start_time, obj, LV_ANIM_EXEC(attr), start, end, 500, lv_anim_path_ease_out, true}

#define ANIM_OPA_DEF(start_time, obj) \
    ANIM_DEF(start_time, obj, opa_scale, LV_OPA_TRANSP, LV_OPA_COVER)

        //lv_coord_t y_tar_top = lv_obj_get_y(ui.topInfo.cont);
    lv_coord_t y_tar_bottom = lv_obj_get_y(ui.dialplate.labelClockhour);
    lv_coord_t y_tar_min = lv_obj_get_y(ui.dialplate.labelClockmin);

        //lv_coord_t h_tar_btn = lv_obj_get_height(ui.dialplate.labelClockhour);

    lv_anim_timeline_wrapper_t wrapper[] =
    {
                //ANIM_DEF(0, ui.topInfo.cont, y, -lv_obj_get_height(ui.topInfo.cont), y_tar_top),

               ANIM_DEF(200, ui.dialplate.labelClockhour, y, -lv_obj_get_height(ui.dialplate.labelClockhour), y_tar_bottom),
                //ANIM_OPA_DEF(200, ui.dialplate.labelClockhour),
                ANIM_DEF(200, ui.dialplate.labelClockmin, y, lv_obj_get_height(ui.dialplate.labelClockmin)+400, y_tar_min),

                        //ANIM_DEF(500, ui.dialplate.labelClockhour, height, 0, h_tar_btn),
          /*              ANIM_DEF(600, ui.btnCont.btnRec, height, 0, h_tar_btn),
                        ANIM_DEF(700, ui.btnCont.btnMenu, height, 0, h_tar_btn),*/
                        LV_ANIM_TIMELINE_WRAPPER_END
    };
    lv_anim_timeline_add_wrapper(ui.anim_timeline, wrapper);
}

void DialplateView::Delete()
{
    if (ui.anim_timeline)
    {
        lv_anim_timeline_delete(ui.anim_timeline);
        ui.anim_timeline = nullptr;
    }
}

void DialplateView::Dialplate_Create(lv_obj_t* par)
{
  lv_obj_t* cont = lv_obj_create(par);
  lv_obj_remove_style_all(cont);
  lv_obj_set_size(cont, TFT_HOR_RES, TFT_VER_RES);
  lv_obj_clear_flag(cont, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
  lv_obj_clear_flag(cont, LV_OBJ_FLAG_GESTURE_BUBBLE);      /// Flags
  lv_obj_set_style_bg_color(cont, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_opa(cont, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_align(cont, LV_ALIGN_CENTER);
  ui.dialplate.cont = cont;

  //Write codes home_digital
  lv_obj_t* home_digital = lv_obj_create(cont);
  lv_obj_remove_style_all(home_digital);
  lv_obj_clear_flag(home_digital, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
  lv_obj_set_size(home_digital, TFT_HOR_RES, TFT_VER_RES);

//  lv_obj_clear_flag(home_digital, LV_OBJ_FLAG_GESTURE_BUBBLE);      /// Flags
  ui.dialplate.bg = home_digital;
  //Write style for home_digital, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
  lv_obj_set_style_bg_opa(home_digital, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_img_src(home_digital, ResourcePool::GetImage("bg_digital_392x392"), LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_image_opa(home_digital, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

  //Write codes home_digital_arc_step
  //lv_obj_t* home_digital_arc_step = lv_arc_create(home_digital);
  //lv_arc_set_mode(home_digital_arc_step, LV_ARC_MODE_NORMAL);
  //lv_arc_set_range(home_digital_arc_step, 0, 100);
  //lv_arc_set_bg_angles(home_digital_arc_step, 60, 120);
  //lv_arc_set_angles(home_digital_arc_step, 60, 110);
  //lv_arc_set_rotation(home_digital_arc_step, 0);
  //lv_obj_set_pos(home_digital_arc_step, 47, 84);
  //lv_obj_set_size(home_digital_arc_step, 323, 300);

  //Write style for home_digital_arc_step, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
  //lv_obj_set_style_bg_opa(home_digital_arc_step, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  //lv_obj_set_style_border_width(home_digital_arc_step, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  //lv_obj_set_style_arc_width(home_digital_arc_step, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
  //lv_obj_set_style_arc_opa(home_digital_arc_step, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
  //lv_obj_set_style_arc_color(home_digital_arc_step, lv_color_hex(0x777777), LV_PART_MAIN | LV_STATE_DEFAULT);
  //lv_obj_set_style_radius(home_digital_arc_step, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
  //lv_obj_set_style_pad_top(home_digital_arc_step, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  //lv_obj_set_style_pad_bottom(home_digital_arc_step, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  //lv_obj_set_style_pad_left(home_digital_arc_step, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  //lv_obj_set_style_pad_right(home_digital_arc_step, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  //lv_obj_set_style_shadow_width(home_digital_arc_step, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

  ////Write style for home_digital_arc_step, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
  //lv_obj_set_style_arc_width(home_digital_arc_step, 12, LV_PART_INDICATOR | LV_STATE_DEFAULT);
  //lv_obj_set_style_arc_opa(home_digital_arc_step, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);
  //lv_obj_set_style_arc_color(home_digital_arc_step, lv_color_hex(0xFF4818), LV_PART_INDICATOR | LV_STATE_DEFAULT);

  ////Write style for home_digital_arc_step, Part: LV_PART_KNOB, State: LV_STATE_DEFAULT.
  //lv_obj_set_style_bg_opa(home_digital_arc_step, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
  //lv_obj_set_style_pad_all(home_digital_arc_step, 0, LV_PART_KNOB | LV_STATE_DEFAULT);

  //Write codes home_digital_arc_flash
  //lv_obj_t* home_digital_arc_flash = lv_arc_create(home_digital);
  //lv_arc_set_mode(home_digital_arc_flash, LV_ARC_MODE_NORMAL);
  //lv_arc_set_range(home_digital_arc_flash, 0, 100);
  //lv_arc_set_bg_angles(home_digital_arc_flash, 238, 300);
  //lv_arc_set_angles(home_digital_arc_flash, 238, 279);
  //lv_arc_set_rotation(home_digital_arc_flash, 0);
  //lv_obj_set_pos(home_digital_arc_flash, 46, 5);
  //lv_obj_set_size(home_digital_arc_flash, 327, 300);

  ////Write style for home_digital_arc_flash, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
  //lv_obj_set_style_bg_opa(home_digital_arc_flash, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  //lv_obj_set_style_border_width(home_digital_arc_flash, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  //lv_obj_set_style_arc_width(home_digital_arc_flash, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
  //lv_obj_set_style_arc_opa(home_digital_arc_flash, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
  //lv_obj_set_style_arc_color(home_digital_arc_flash, lv_color_hex(0x777777), LV_PART_MAIN | LV_STATE_DEFAULT);
  //lv_obj_set_style_radius(home_digital_arc_flash, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
  //lv_obj_set_style_pad_top(home_digital_arc_flash, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
  //lv_obj_set_style_pad_bottom(home_digital_arc_flash, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  //lv_obj_set_style_pad_left(home_digital_arc_flash, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  //lv_obj_set_style_pad_right(home_digital_arc_flash, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  //lv_obj_set_style_shadow_width(home_digital_arc_flash, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

  ////Write style for home_digital_arc_flash, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
  //lv_obj_set_style_arc_width(home_digital_arc_flash, 12, LV_PART_INDICATOR | LV_STATE_DEFAULT);
  //lv_obj_set_style_arc_opa(home_digital_arc_flash, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);
  //lv_obj_set_style_arc_color(home_digital_arc_flash, lv_color_hex(0x1000ff), LV_PART_INDICATOR | LV_STATE_DEFAULT);

  ////Write style for home_digital_arc_flash, Part: LV_PART_KNOB, State: LV_STATE_DEFAULT.
  //lv_obj_set_style_bg_opa(home_digital_arc_flash, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
  //lv_obj_set_style_pad_all(home_digital_arc_flash, 0, LV_PART_KNOB | LV_STATE_DEFAULT);


  //Write codes home_digital_img_stepIcon
  lv_obj_t* home_digital_img_stepIcon = lv_img_create(home_digital);
  lv_obj_add_flag(home_digital_img_stepIcon, LV_OBJ_FLAG_CLICKABLE);
  lv_img_set_src(home_digital_img_stepIcon, ResourcePool::GetImage("icn_step_red_alpha_17x21"));
  lv_img_set_pivot(home_digital_img_stepIcon, 50, 50);
  lv_img_set_angle(home_digital_img_stepIcon, 0);
  lv_obj_set_pos(home_digital_img_stepIcon, 156, 338);
  lv_obj_set_size(home_digital_img_stepIcon, 17, 21);

  //Write style for home_digital_img_stepIcon, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
  lv_obj_set_style_img_opa(home_digital_img_stepIcon, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

  //Write codes home_digital_label_stepText
  lv_obj_t* home_digital_label_stepText = lv_label_create(home_digital);
  lv_label_set_text(home_digital_label_stepText, "1526");
  lv_label_set_long_mode(home_digital_label_stepText, LV_LABEL_LONG_WRAP);
  lv_obj_set_pos(home_digital_label_stepText, 186, 338);
  lv_obj_set_size(home_digital_label_stepText, 59, 21);

  //Write style for home_digital_label_stepText, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
  lv_obj_set_style_border_width(home_digital_label_stepText, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_radius(home_digital_label_stepText, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_color(home_digital_label_stepText, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_font(home_digital_label_stepText, &lv_font_montserrat_22, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_letter_space(home_digital_label_stepText, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_line_space(home_digital_label_stepText, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_align(home_digital_label_stepText, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_opa(home_digital_label_stepText, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_pad_top(home_digital_label_stepText, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_pad_right(home_digital_label_stepText, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_pad_bottom(home_digital_label_stepText, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_pad_left(home_digital_label_stepText, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_shadow_width(home_digital_label_stepText, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

  //Write codes home_digital_label_weather1Text
  lv_obj_t* home_digital_label_weather1Text = lv_label_create(home_digital);
  lv_label_set_text(home_digital_label_weather1Text, "26");
  lv_label_set_long_mode(home_digital_label_weather1Text, LV_LABEL_LONG_WRAP);
  lv_obj_set_pos(home_digital_label_weather1Text, 65, 248);
  lv_obj_set_size(home_digital_label_weather1Text, 47, 21);

  //Write style for home_digital_label_weather1Text, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
  lv_obj_set_style_border_width(home_digital_label_weather1Text, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_radius(home_digital_label_weather1Text, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_color(home_digital_label_weather1Text, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_font(home_digital_label_weather1Text, &lv_font_montserrat_22, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_letter_space(home_digital_label_weather1Text, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_line_space(home_digital_label_weather1Text, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_align(home_digital_label_weather1Text, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_opa(home_digital_label_weather1Text, 253, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_color(home_digital_label_weather1Text, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_pad_top(home_digital_label_weather1Text, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_pad_right(home_digital_label_weather1Text, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_pad_bottom(home_digital_label_weather1Text, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_pad_left(home_digital_label_weather1Text, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_shadow_width(home_digital_label_weather1Text, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

  //Write codes home_digital_label_week
  lv_obj_t* home_digital_label_week = lv_label_create(home_digital);
  lv_label_set_text(home_digital_label_week, "WED");
  lv_label_set_long_mode(home_digital_label_week, LV_LABEL_LONG_WRAP);
  lv_obj_set_pos(home_digital_label_week, 34, 143);
  lv_obj_set_size(home_digital_label_week, 67, 25);

  //Write style for home_digital_label_week, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
  lv_obj_set_style_border_width(home_digital_label_week, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_radius(home_digital_label_week, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_color(home_digital_label_week, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_font(home_digital_label_week, &lv_font_montserrat_22, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_letter_space(home_digital_label_week, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_line_space(home_digital_label_week, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_align(home_digital_label_week, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_opa(home_digital_label_week, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_pad_top(home_digital_label_week, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_pad_right(home_digital_label_week, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_pad_bottom(home_digital_label_week, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_pad_left(home_digital_label_week, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_shadow_width(home_digital_label_week, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

  //Write codes home_digital_label_date
  lv_obj_t* home_digital_label_date = lv_label_create(home_digital);
  lv_label_set_text(home_digital_label_date, "05/15");
  lv_label_set_long_mode(home_digital_label_date, LV_LABEL_LONG_WRAP);
  lv_obj_set_pos(home_digital_label_date, 34, 111);
  lv_obj_set_size(home_digital_label_date, 74, 21);

  //Write style for home_digital_label_date, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
  lv_obj_set_style_border_width(home_digital_label_date, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_radius(home_digital_label_date, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_color(home_digital_label_date, lv_color_hex(0x777777), LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_font(home_digital_label_date, &lv_font_montserrat_22, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_letter_space(home_digital_label_date, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_line_space(home_digital_label_date, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_align(home_digital_label_date, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_opa(home_digital_label_date, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_pad_top(home_digital_label_date, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_pad_right(home_digital_label_date, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_pad_bottom(home_digital_label_date, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_pad_left(home_digital_label_date, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_shadow_width(home_digital_label_date, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

  //Write codes home_digital_img_flash
  lv_obj_t* home_digital_img_flash = lv_img_create(home_digital);
  lv_obj_add_flag(home_digital_img_flash, LV_OBJ_FLAG_CLICKABLE);
  lv_img_set_src(home_digital_img_flash, ResourcePool::GetImage("icn_flash_blue_alpha_17x21"));
  lv_img_set_pivot(home_digital_img_flash, 50, 50);
  lv_img_set_angle(home_digital_img_flash, 0);
  lv_obj_set_pos(home_digital_img_flash, 162, 35);
  lv_obj_set_size(home_digital_img_flash, 17, 21);

  //Write style for home_digital_img_flash, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
  lv_obj_set_style_img_opa(home_digital_img_flash, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

  //Write codes home_digital_label_flashText
  lv_obj_t* home_digital_label_flashText = lv_label_create(home_digital);
  lv_label_set_text(home_digital_label_flashText, "86%");
  lv_label_set_long_mode(home_digital_label_flashText, LV_LABEL_LONG_WRAP);
  lv_obj_set_pos(home_digital_label_flashText, 186, 35);
  lv_obj_set_size(home_digital_label_flashText, 59, 21);

  //Write style for home_digital_label_flashText, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
  lv_obj_set_style_border_width(home_digital_label_flashText, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_radius(home_digital_label_flashText, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_color(home_digital_label_flashText, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_font(home_digital_label_flashText, &lv_font_montserrat_22, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_letter_space(home_digital_label_flashText, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_line_space(home_digital_label_flashText, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_align(home_digital_label_flashText, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_opa(home_digital_label_flashText, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_pad_top(home_digital_label_flashText, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_pad_right(home_digital_label_flashText, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_pad_bottom(home_digital_label_flashText, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_pad_left(home_digital_label_flashText, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_shadow_width(home_digital_label_flashText, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

  //Write codes home_digital_img_dialDot
  lv_obj_t* home_digital_img_dialDot = lv_img_create(home_digital);
  lv_obj_add_flag(home_digital_img_dialDot, LV_OBJ_FLAG_CLICKABLE);
  lv_img_set_src(home_digital_img_dialDot, ResourcePool::GetImage("menu_alpha_11x117"));
  lv_img_set_pivot(home_digital_img_dialDot, 50, 50);
  lv_img_set_angle(home_digital_img_dialDot, 0);
  lv_obj_set_pos(home_digital_img_dialDot, 365, 140);
  lv_obj_set_size(home_digital_img_dialDot, 11, 117);

  //Write style for home_digital_img_dialDot, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
  lv_obj_set_style_img_opa(home_digital_img_dialDot, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

  //Write codes home_digital_label_min
  lv_obj_t* home_digital_label_min = lv_label_create(home_digital);
  lv_label_set_text(home_digital_label_min, "32");
  lv_label_set_long_mode(home_digital_label_min, LV_LABEL_LONG_WRAP);
  lv_obj_set_pos(home_digital_label_min, 165, 198);
  lv_obj_set_size(home_digital_label_min, 152, 104);
  ui.dialplate.labelClockmin = home_digital_label_min;

  //Write style for home_digital_label_min, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
  lv_obj_set_style_border_width(home_digital_label_min, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_radius(home_digital_label_min, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_color(home_digital_label_min, lv_color_hex(0xFF4818), LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_font(home_digital_label_min, ResourcePool::GetFont("montserratMedium_110"), LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_letter_space(home_digital_label_min, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_line_space(home_digital_label_min, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_align(home_digital_label_min, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_opa(home_digital_label_min, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_pad_top(home_digital_label_min, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_pad_right(home_digital_label_min, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_pad_bottom(home_digital_label_min, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_pad_left(home_digital_label_min, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_shadow_width(home_digital_label_min, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

  //Write codes home_digital_label_hour
  lv_obj_t* home_digital_label_hour = lv_label_create(home_digital);
  lv_label_set_text(home_digital_label_hour, "15");
  lv_label_set_long_mode(home_digital_label_hour, LV_LABEL_LONG_WRAP);
  lv_obj_set_pos(home_digital_label_hour, 108, 76);
  lv_obj_set_size(home_digital_label_hour, 150, 122);
  ui.dialplate.labelClockhour = home_digital_label_hour;

  //Write style for home_digital_label_hour, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
  lv_obj_set_style_border_width(home_digital_label_hour, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_radius(home_digital_label_hour, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_color(home_digital_label_hour, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_font(home_digital_label_hour, ResourcePool::GetFont("montserratMedium_110"), LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_letter_space(home_digital_label_hour, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_line_space(home_digital_label_hour, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_align(home_digital_label_hour, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_opa(home_digital_label_hour, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_pad_top(home_digital_label_hour, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_pad_right(home_digital_label_hour, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_pad_bottom(home_digital_label_hour, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_pad_left(home_digital_label_hour, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_shadow_width(home_digital_label_hour, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

  //Write codes home_digital_img_messageIcon
  lv_obj_t* home_digital_img_messageIcon = lv_img_create(home_digital);
  lv_obj_add_flag(home_digital_img_messageIcon, LV_OBJ_FLAG_CLICKABLE);
  lv_img_set_src(home_digital_img_messageIcon, ResourcePool::GetImage("icn_message_alpha_25x25"));
  lv_img_set_pivot(home_digital_img_messageIcon, 50, 50);
  lv_img_set_angle(home_digital_img_messageIcon, 0);
  lv_obj_set_pos(home_digital_img_messageIcon, 306, 269);
  lv_obj_set_size(home_digital_img_messageIcon, 25, 25);

  //Write style for home_digital_img_messageIcon, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
  lv_obj_set_style_img_opa(home_digital_img_messageIcon, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

  //Write codes home_digital_img_sportIcon
  lv_obj_t* home_digital_img_sportIcon = lv_img_create(home_digital);
  lv_obj_add_flag(home_digital_img_sportIcon, LV_OBJ_FLAG_CLICKABLE);
  lv_img_set_src(home_digital_img_sportIcon, ResourcePool::GetImage("icn_sport_alpha_12x24"));
  lv_img_set_pivot(home_digital_img_sportIcon, 50, 50);
  lv_img_set_angle(home_digital_img_sportIcon, 0);
  lv_obj_set_pos(home_digital_img_sportIcon, 317, 102);
  lv_obj_set_size(home_digital_img_sportIcon, 12, 24);

  //Write style for home_digital_img_sportIcon, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
  lv_obj_set_style_img_opa(home_digital_img_sportIcon, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

  //Write codes home_digital_img_weather1Icon
  lv_obj_t* home_digital_img_weather1Icon = lv_img_create(home_digital);
  lv_obj_add_flag(home_digital_img_weather1Icon, LV_OBJ_FLAG_CLICKABLE);
  lv_img_set_src(home_digital_img_weather1Icon, ResourcePool::GetImage("icn_weather_1_alpha_41x33"));
  lv_img_set_pivot(home_digital_img_weather1Icon, 50, 50);
  lv_img_set_angle(home_digital_img_weather1Icon, 0);
  lv_obj_set_pos(home_digital_img_weather1Icon, 57, 208);
  lv_obj_set_size(home_digital_img_weather1Icon, 41, 33);

  //Write style for home_digital_img_weather1Icon, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
  lv_obj_set_style_img_recolor_opa(home_digital_img_weather1Icon, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_img_recolor(home_digital_img_weather1Icon, lv_color_hex(0x777777), LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_img_opa(home_digital_img_weather1Icon, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

  //Write codes home_digital_img_sportText
  lv_obj_t* home_digital_img_sportText = lv_img_create(home_digital);
  lv_obj_add_flag(home_digital_img_sportText, LV_OBJ_FLAG_CLICKABLE);
  lv_img_set_src(home_digital_img_sportText, ResourcePool::GetImage("text_sport_alpha_50x50"));
  lv_img_set_pivot(home_digital_img_sportText, 50, 50);
  lv_img_set_angle(home_digital_img_sportText, 30);
  lv_obj_set_pos(home_digital_img_sportText, 321, 76);
  lv_obj_set_size(home_digital_img_sportText, 50, 50);

  //Write style for home_digital_img_sportText, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
  lv_obj_set_style_img_opa(home_digital_img_sportText, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

  //Write codes home_digital_img_messageText
  lv_obj_t* home_digital_img_messageText = lv_img_create(home_digital);
  lv_obj_add_flag(home_digital_img_messageText, LV_OBJ_FLAG_CLICKABLE);
  lv_img_set_src(home_digital_img_messageText, ResourcePool::GetImage("text_message_alpha_70x70"));
  lv_img_set_pivot(home_digital_img_messageText, 50, 50);
  lv_img_set_angle(home_digital_img_messageText, -50);
  lv_obj_set_pos(home_digital_img_messageText, 306, 257);
  lv_obj_set_size(home_digital_img_messageText, 70, 70);

  //Write style for home_digital_img_messageText, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
  lv_obj_set_style_img_opa(home_digital_img_messageText, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

  //Write codes home_digital_img_dot
  lv_obj_t* home_digital_img_dot = lv_img_create(home_digital);
  lv_obj_add_flag(home_digital_img_dot, LV_OBJ_FLAG_CLICKABLE);
  lv_img_set_src(home_digital_img_dot, ResourcePool::GetImage("dot_alpha_8x8"));
  lv_img_set_pivot(home_digital_img_dot, 50, 50);
  lv_img_set_angle(home_digital_img_dot, 0);
  lv_obj_set_pos(home_digital_img_dot, 365, 140);
  lv_obj_set_size(home_digital_img_dot, 8, 8);

  //Write style for home_digital_img_dot, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
  lv_obj_set_style_img_opa(home_digital_img_dot, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

  //Update current screen layout.
  lv_obj_update_layout(home_digital);


}

void DialplateView::AppearAnimStart(bool reverse)
{
    lv_anim_timeline_set_reverse(ui.anim_timeline, reverse);
    lv_anim_timeline_start(ui.anim_timeline);
}