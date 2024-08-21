#include "Image_Player_View.h"
#include <stdarg.h>
#include <stdio.h>
#include "esp_heap_caps.h"


using namespace Page;

void Image_Player_View::Create(lv_obj_t* root)
{
    lv_obj_t* cont = lv_obj_create(root);
    lv_obj_remove_style_all(cont);
    lv_obj_set_size(cont, TFT_HOR_RES, TFT_VER_RES);
    lv_obj_clear_flag(cont, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_clear_flag(cont, LV_OBJ_FLAG_GESTURE_BUBBLE);
    lv_obj_set_style_bg_color(cont, LV_COLOR_MAKE(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(cont, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_align(cont, LV_ALIGN_CENTER);
    ui.cont = cont;

    lv_obj_t* image = lv_img_create(cont);
    lv_img_set_src(image, ResourcePool::GetImage("image1"));
    lv_obj_set_align(image, LV_ALIGN_CENTER);
    lv_obj_fade_in(image, 2000, 0);
    ui.image = image;

    // lv_obj_t * lottie = lv_lottie_create(cont);
    // lv_lottie_set_buffer(lottie, 50, 50, lottile_buf); //Will be the size of the canvas too
    // lv_lottie_set_src_data(lottie, settings_lottie, sizeof(settings_lottie),10);
    // lv_obj_set_align(lottie, LV_ALIGN_CENTER);
    // ui.lottie = lottie;
    // printf("PSRAM free size: %d\n", heap_caps_get_free_size(MALLOC_CAP_SPIRAM));
}
/**
  * @brief  List up to 25 file on the root directory with extension .BMP
  * @param  None
  * @retval The number of the found files
  */
uint32_t Image_Player_View::Storage_GetDirectoryBitmapFiles (const char* DirName, char* Files[])
{
  uint32_t index = 0;

  return index;
}



