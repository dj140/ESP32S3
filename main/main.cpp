#include "lvgl.h"
#include "APP/APP.h"
#include "APP/Common/HAL/HAL.h"
#include "lvgl_port/lv_port_disp.h"
#include "lvgl_port/lv_port_indev.h"
#include "demos/benchmark/lv_demo_benchmark.h"


extern "C" void app_main(void)
{  
  HAL::HAL_Init();
  lv_init(); 
  lv_port_disp_init();
  lv_port_indev_init();
  //lv_demo_benchmark();
  lv_demo_music();
  //App_Init();
  while (1) {
    lv_timer_handler(); /* let the GUI do its work */
    HAL::HAL_Update();
    vTaskDelay(pdMS_TO_TICKS(2));
  }
}