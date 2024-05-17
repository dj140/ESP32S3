#include "TemplateView.h"
#include <stdarg.h>
#include <stdio.h>



using namespace Page;

// FILINFO fno;
// DIR dir;
// FIL F;
// lv_color_t * cam_buffer = NULL;
// lv_color_t cbuf[LV_CANVAS_BUF_SIZE_TRUE_COLOR(240, 16)];
#define CANVAS_WIDTH  240
#define CANVAS_HEIGHT  16
void TemplateView::Create(lv_obj_t* root)
{
    lv_obj_t* cont = lv_obj_create(root);
    lv_obj_remove_style_all(cont);
    lv_obj_set_size(cont, 240, 240);
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



