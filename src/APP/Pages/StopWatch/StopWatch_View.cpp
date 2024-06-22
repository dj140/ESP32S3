#include "StopWatch_View.h"
#include <stdarg.h>
#include <stdio.h>

using namespace Page;

static const lv_coord_t Btn_Width = 70;
static const lv_coord_t Btn_Height = 45;

void StopWatch_View::LabelTime_Create(lv_obj_t* par)
{

    lv_obj_t* label = lv_label_create(par);

    lv_obj_set_style_text_font(label, &lv_font_montserrat_40, LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(label, LV_COLOR_MAKE(0x87, 0xFF, 0xCE), LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(label, lv_color_black(), LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(label, LV_OPA_TRANSP, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_label_set_text(label, "00:00.000");
    lv_obj_set_size(label, 210, 40);
    //lv_obj_set_size(label, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_align(label, LV_ALIGN_TOP_MID, 0, 50);

    //labelTime = label;
    ui.time = label;
}

void StopWatch_View::listHistory_Create(lv_obj_t* par)
{
    lv_obj_t* list = lv_list_create(par);
    //lv_obj_remove_style_all(list);                          /*Remove the style coming from the theme*/

    lv_obj_set_style_text_font(list, &lv_font_montserrat_36, LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(list, lv_color_white(), LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(list, 2, LV_STATE_DEFAULT);
    lv_obj_set_style_radius(list, 5, LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(list, lv_palette_main(LV_PALETTE_BLUE), LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(list, lv_color_black(), LV_STATE_DEFAULT);
    lv_obj_set_size(list, 300, 200);
    lv_obj_align(list,LV_ALIGN_CENTER, 0, 0);
    // lv_obj_set_auto_realign(list, true);
    ui.listHistory = list;

}

void StopWatch_View::BtnGrp_Create(lv_obj_t* par)
{
    static lv_style_t style;
    lv_style_init(&style);
    lv_style_set_radius(&style, 8);
    lv_style_set_border_color(&style, lv_color_black());
    lv_style_set_border_width(&style, 2);
    lv_style_set_bg_color(&style, lv_palette_main(LV_PALETTE_GREY));

    ui.button_reset = lv_btn_create(par);
    lv_obj_set_size(ui.button_reset, Btn_Width, Btn_Height);
    lv_obj_align(ui.button_reset, LV_ALIGN_BOTTOM_LEFT, 60 + (0 * Btn_Width), -10);
    lv_obj_add_style(ui.button_reset, &style, LV_STATE_PRESSED);
    lv_obj_set_style_radius(ui.button_reset, 8, LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui.button_reset, LV_COLOR_MAKE(0x00, 0xFF, 0xD7), LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui.button_reset, lv_palette_main(LV_PALETTE_GREY), LV_STATE_DISABLED);
    lv_obj_set_style_bg_opa(ui.button_reset, 255, LV_STATE_DEFAULT);

    lv_obj_t* img_reset = lv_img_create(ui.button_reset);
    lv_img_set_src(img_reset, ResourcePool::GetImage("stopwatch_reset"));
    lv_obj_align(img_reset, LV_ALIGN_CENTER, 0, 0);

    ui.button_pause = lv_btn_create(par);
    lv_obj_set_size(ui.button_pause, Btn_Width, Btn_Height);
    lv_obj_align(ui.button_pause, LV_ALIGN_BOTTOM_LEFT, 60 + (1 * Btn_Width + 10), -10);
    lv_obj_add_style(ui.button_pause, &style, LV_STATE_PRESSED);
    lv_obj_set_style_radius(ui.button_pause, 8, LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui.button_pause, LV_COLOR_MAKE(0x46, 0xF4, 0xB0), LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui.button_pause, 255, LV_STATE_DEFAULT);

    lv_obj_t* img_pause = lv_img_create(ui.button_pause);
    lv_img_set_src(img_pause, ResourcePool::GetImage("stopwatch_pause"));
    lv_obj_align(img_pause, LV_ALIGN_CENTER, 0, 0);
    ui.button_img = img_pause;

    ui.button_add = lv_btn_create(par);
    lv_obj_set_size(ui.button_add, Btn_Width, Btn_Height);
    lv_obj_align(ui.button_add, LV_ALIGN_BOTTOM_LEFT, 60 + (2 * Btn_Width + 20), -10);
    lv_obj_add_style(ui.button_add, &style, LV_STATE_PRESSED);
    lv_obj_set_style_radius(ui.button_add, 8, LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui.button_add, LV_COLOR_MAKE(0x51, 0xFF, 0x9C), LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui.button_add, 255, LV_STATE_DEFAULT);

    lv_obj_t* img_add = lv_img_create(ui.button_add);
    lv_img_set_src(img_add, ResourcePool::GetImage("stopwatch_add"));
    lv_obj_align(img_add, LV_ALIGN_CENTER, 0, 0);

    lv_obj_add_state(ui.button_reset, LV_STATE_DISABLED);
}

void StopWatch_View::CreateAnim()
{
    static lv_coord_t time_y_end = lv_obj_get_y(ui.time);
    static lv_coord_t btn_y_end = lv_obj_get_y(ui.button_reset);
    lv_coord_t btn_y_start = 300 + lv_obj_get_height(ui.button_reset);

    static lv_coord_t list_width_end = lv_obj_get_width(ui.listHistory);
    static lv_coord_t list_height_end = lv_obj_get_height(ui.listHistory);

    ui.anim_timeline = lv_anim_timeline_create();

    lv_anim_timeline_wrapper_t wrapper[] =
    {
            {0, ui.time, (lv_anim_exec_xcb_t)lv_obj_set_y, -lv_obj_get_height(ui.time), time_y_end, 300, lv_anim_path_ease_out, true},
            {0, ui.time, LV_ANIM_EXEC(opa_scale), LV_OPA_TRANSP, LV_OPA_COVER, 300, lv_anim_path_ease_out, true},
            {100, ui.button_reset, LV_ANIM_EXEC(y), btn_y_start, btn_y_end, 300, lv_anim_path_ease_out, true},
            {150, ui.button_pause, LV_ANIM_EXEC(y), btn_y_start, btn_y_end, 300, lv_anim_path_ease_out, true},
            {200, ui.button_add, LV_ANIM_EXEC(y), btn_y_start, btn_y_end, 300, lv_anim_path_ease_out, true},
            {100, ui.listHistory, LV_ANIM_EXEC(width), 0, list_width_end, 200, lv_anim_path_ease_out, true},
            {300, ui.listHistory, LV_ANIM_EXEC(height), 2, list_height_end, 200, lv_anim_path_ease_out, true},
            LV_ANIM_TIMELINE_WRAPPER_END
    };
    lv_anim_timeline_add_wrapper(ui.anim_timeline, wrapper);
    // uint32_t playtime = lv_anim_timeline_start(ui.anim_timeline);
    // PageDelay(playtime);
}


void StopWatch_View::Create(lv_obj_t* root)
{
    //lv_obj_t* cont = lv_obj_create(root);
    lv_obj_clear_flag(root, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_clear_flag(root, LV_OBJ_FLAG_GESTURE_BUBBLE);      /// Flags
    listHistory_Create(root);
    LabelTime_Create(root);
    BtnGrp_Create(root);
    CreateAnim();
}
void StopWatch_View::AppearAnimStart(bool reverse)
{
    lv_anim_timeline_set_reverse(ui.anim_timeline, reverse);
    lv_anim_timeline_start(ui.anim_timeline);
}