#include "TemplateView.h"
#include <stdarg.h>
#include <stdio.h>

using namespace Page;

void TemplateView::Create(lv_obj_t* root)
{
    lv_obj_t* cont = lv_obj_create(root);
    lv_obj_remove_style_all(cont);
    lv_obj_set_size(cont, TFT_HOR_RES, TFT_VER_RES);
    lv_obj_clear_flag(cont, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_clear_flag(cont, LV_OBJ_FLAG_GESTURE_BUBBLE);
    lv_obj_set_style_bg_color(cont, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(cont, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_align(cont, LV_ALIGN_CENTER);
    ui.cont = cont;
}
/**
  * @brief  List up to 25 file on the root directory with extension .BMP
  * @param  None
  * @retval The number of the found files
  */
uint32_t TemplateView::Storage_GetDirectoryBitmapFiles (const char* DirName, char* Files[])
{
  uint32_t index = 0;

  return index;
}



