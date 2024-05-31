
#include "Arduino.h"
#include "lvgl.h"
#include "APP/APP.h"
#include "APP/Common/HAL/HAL.h"
#include "lvgl_port/lv_port_disp.h"
#include "lvgl_port/lv_port_indev.h"
#include "lvgl_demo/demos/benchmark/lv_demo_benchmark.h"
static uint32_t my_tick_get_cb(void) { return millis(); }

//increase loop task stack to 48kb for prevent rlottie crash
SET_LOOP_TASK_STACK_SIZE( 48 * 1024 ); // 48KB

void setup(void)
{
  Serial.begin(115200);
  // Serial.setDebugOutput(true);
  // while(!Serial);
  Serial.println("Usart enable");
  Serial.printf("Deafult free size: %d\n", heap_caps_get_free_size(MALLOC_CAP_DEFAULT));
  Serial.printf("PSRAM free size: %d\n", heap_caps_get_free_size(MALLOC_CAP_SPIRAM));
  Serial.printf("Flash size: %d bytes\n", ESP.getFlashChipSize());
  HAL::HAL_Init();
  lv_init(); 
  lv_port_disp_init();
  lv_port_indev_init();
  //lv_demo_benchmark();
  //lv_demo_music();
  //lv_demo_vector_graphic();
  // lv_demo_multilang();
  lv_tick_set_cb(my_tick_get_cb);
  App_Init();
  
}

void loop()
{ 
  lv_timer_handler(); /* let the GUI do its work */
  vTaskDelay(pdMS_TO_TICKS(2));
}
