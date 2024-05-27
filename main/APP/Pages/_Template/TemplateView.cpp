#include "TemplateView.h"
#include <stdarg.h>
#include <stdio.h>



using namespace Page;

// FILINFO fno;
// DIR dir;
// FIL F;

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

    lv_obj_t* image = lv_img_create(cont);
   // lv_img_set_src(image, "0:sdcard/boot_anim/shm_logo.bin");
    lv_obj_set_width(image, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(image, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(image, LV_ALIGN_CENTER);
    lv_obj_add_flag(image, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(image, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    ui.image = image;
  
//    lv_obj_t* ui_Spinner = lv_spinner_create(image, 1000, 90);
//    lv_obj_set_width(ui_Spinner, 100);
//    lv_obj_set_height(ui_Spinner, 100);
//    lv_obj_set_x(ui_Spinner, 0);
//    lv_obj_set_y(ui_Spinner, -70);
//    lv_obj_set_align(ui_Spinner, LV_ALIGN_OUT_BOTTOM_MID);
//    lv_obj_clear_flag(ui_Spinner, LV_OBJ_FLAG_CLICKABLE);      /// Flags
//    lv_obj_set_style_arc_color(ui_Spinner, lv_color_hex(0x3E413E), LV_PART_MAIN | LV_STATE_DEFAULT);
//    lv_obj_set_style_arc_opa(ui_Spinner, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
//    lv_obj_set_style_arc_width(ui_Spinner, 6, LV_PART_MAIN | LV_STATE_DEFAULT);

//    lv_obj_set_style_arc_color(ui_Spinner, lv_color_hex(0xEE1C18), LV_PART_INDICATOR | LV_STATE_DEFAULT);
//    lv_obj_set_style_arc_opa(ui_Spinner, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);
//    lv_obj_set_style_arc_rounded(ui_Spinner, true, LV_PART_INDICATOR | LV_STATE_DEFAULT);
//    ui.Spinner = ui_Spinner;
}
/**
  * @brief  List up to 25 file on the root directory with extension .BMP
  * @param  None
  * @retval The number of the found files
  */
uint32_t TemplateView::Storage_GetDirectoryBitmapFiles (const char* DirName, char* Files[])
{
  uint32_t index = 0;

 
//  /* Open filesystem */
//  if(f_mount(&fs, (TCHAR const*)"",0) != FR_OK)
//  {
//    return 0;
//  }

  /* Start to search for wave files */
//   res = f_findfirst(&dir, &fno, DirName, "*.bin");
//   printf("f_findfir stutas: %d \n", res);
//   /* Repeat while an item is found */
//   while (fno.fname[0])
//   {
//     if(res == FR_OK)
//     {
//       if(index < 25)
//       {
// //        printf("index: %d Max files: %d\r\n", index, MAX_BMP_FILES);								//����ļ���	
//         sprintf (Files[index++], "%s", fno.fname);
// //        printf("index: %d %s\r\n",index,Files[index]);								//����ļ���	

//       } 

//       /* Search for next item */
//       res = f_findnext(&dir, &fno);
//     }
//     else
//     {
//       printf("no files left\r\n");								//����ļ���	
//       index = 0;
//       break;
//     }
//   }

//   f_closedir(&dir);

  return index;
}



