#include "Setting_View.h"
#include <stdarg.h>
#include <stdio.h>

using namespace Page;

void Setting_View::Create(lv_obj_t* root)
{   
    lv_obj_set_style_bg_color(root, lv_color_hex(0x202020), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(root, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t* cont = lv_obj_create(root);
    lv_obj_clear_flag(cont, LV_OBJ_FLAG_GESTURE_BUBBLE);      /// Flags

    static lv_coord_t col_dsc[] = { 180, 180, LV_GRID_TEMPLATE_LAST };
    static lv_coord_t row_dsc[] = { 100, 100, 100, LV_GRID_TEMPLATE_LAST };

    /*Create a container with grid*/
    lv_obj_set_style_grid_column_dsc_array(cont, col_dsc, 0);
    lv_obj_set_style_grid_row_dsc_array(cont, row_dsc, 0);
    lv_obj_set_size(cont, 400, 350);
    lv_obj_align(cont, LV_ALIGN_CENTER, 0, 20);
    lv_obj_set_layout(cont, LV_LAYOUT_GRID);
    lv_obj_set_grid_align(cont, LV_GRID_ALIGN_SPACE_EVENLY, LV_GRID_ALIGN_SPACE_EVENLY);
    lv_obj_clear_flag(cont, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_t* obj;

    static lv_style_t style;
    lv_style_init(&style);
    lv_style_set_radius(&style, 60);
    lv_style_set_border_color(&style, lv_palette_main(LV_PALETTE_LIGHT_BLUE));
    lv_style_set_bg_color(&style, lv_palette_main(LV_PALETTE_LIGHT_BLUE));
    lv_style_set_border_width(&style, 2);
    lv_style_set_img_recolor_opa(&style, LV_OPA_30);
    lv_style_set_img_recolor(&style, lv_palette_main(LV_PALETTE_LIGHT_BLUE));

    ui.icon1 = lv_btn_create(root);  
    lv_obj_set_size(ui.icon1, 100, 30);
    lv_obj_align(ui.icon1, LV_ALIGN_TOP_MID, 0, 10);
    lv_obj_add_style(ui.icon1, &style, LV_STATE_PRESSED);
    lv_obj_add_flag(ui.icon1, LV_OBJ_FLAG_CHECKABLE);
    lv_obj_set_style_radius(ui.icon1, 50, LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui.icon1, lv_color_hex(0x404040), LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui.icon1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);


    ui.icon2 = lv_btn_create(cont);
    lv_obj_add_style(ui.icon2, &style, LV_STATE_CHECKED);
    lv_obj_set_style_radius(ui.icon2, 50, LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui.icon2, lv_color_black(), LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui.icon2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_grid_cell(ui.icon2, LV_GRID_ALIGN_STRETCH, 0, 1, LV_GRID_ALIGN_STRETCH, 0, 1);
    lv_obj_add_flag(ui.icon2, LV_OBJ_FLAG_CHECKABLE);

    lv_obj_t* img1 = lv_img_create(ui.icon2);
    lv_img_set_src(img1, ResourcePool::GetImage("wifi_icon"));
    lv_obj_align(img1, LV_ALIGN_CENTER, 0, 0);

    ui.icon3 = lv_btn_create(cont);
    lv_obj_add_style(ui.icon3, &style, LV_STATE_PRESSED);
    lv_obj_set_style_radius(ui.icon3, 50, LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui.icon3, lv_color_black(), LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui.icon3, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_grid_cell(ui.icon3, LV_GRID_ALIGN_STRETCH, 1, 1, LV_GRID_ALIGN_STRETCH, 0, 1);

    lv_obj_t* img2 = lv_img_create(ui.icon3);
    lv_img_set_src(img2, ResourcePool::GetImage("wifi_icon"));
    lv_obj_align(img2, LV_ALIGN_CENTER, 0, 0);

    ui.icon4 = lv_btn_create(cont);
    lv_obj_add_style(ui.icon4, &style, LV_STATE_PRESSED);
    lv_obj_set_style_radius(ui.icon4, 50, LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui.icon4, lv_color_black(), LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui.icon4, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_grid_cell(ui.icon4, LV_GRID_ALIGN_STRETCH, 0, 1, LV_GRID_ALIGN_STRETCH, 1, 1);

    lv_obj_t* img3 = lv_img_create(ui.icon4);
    lv_img_set_src(img3, ResourcePool::GetImage("wifi_icon"));
    lv_obj_align(img3, LV_ALIGN_CENTER, 0, 0);

    ui.icon5 = lv_btn_create(cont);
    lv_obj_add_style(ui.icon5, &style, LV_STATE_PRESSED);
    lv_obj_set_style_radius(ui.icon5, 50, LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui.icon5, lv_color_black(), LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui.icon5, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_grid_cell(ui.icon5, LV_GRID_ALIGN_STRETCH, 1, 1, LV_GRID_ALIGN_STRETCH, 1, 1);

    lv_obj_t* img4 = lv_img_create(ui.icon5);
    lv_img_set_src(img4, ResourcePool::GetImage("wifi_icon"));
    lv_obj_align(img4, LV_ALIGN_CENTER, 0, 0);


    ui.cont = cont;

   

}
