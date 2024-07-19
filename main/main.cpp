#include "lvgl.h"
#include "APP/APP.h"
#include "APP/Common/HAL/HAL.h"
#include "lvgl_port/lv_port_disp.h"
#include "lvgl_port/lv_port_indev.h"
#include "lvgl/demos/lv_demos.h"
#include "esp_timer.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"

static uint32_t my_tick_get_cb(void) { return (esp_timer_get_time() / 1000LL); }
static const char *TAG = "main";
SemaphoreHandle_t xGuiSemaphore;

TaskHandle_t xTouchVibrates = NULL;

void uiTask(void *pvParameters)
{
    xGuiSemaphore = xSemaphoreCreateMutex();
    ESP_LOGI(TAG, "lvgl ui task");
    //lv_demo_benchmark();
    // lv_demo_widgets();      /* A widgets example. This is what you get out of the box */
    //lv_demo_music();        /* A modern, smartphone-like music player demo. */
    // lv_demo_stress();       /* A stress test for LVGL. */
    // lv_demo_benchmark();    /* A demo to measure the performance of LVGL or to compare different settings. */
   while (1)
   {
      /* Delay 1 tick (assumes FreeRTOS tick is 10ms */
      vTaskDelay(pdMS_TO_TICKS(10));

      /* Try to take the semaphore, call lvgl related function on success */
      if (pdTRUE == xSemaphoreTake(xGuiSemaphore, portMAX_DELAY))
      {
         lv_timer_handler();
         xSemaphoreGive(xGuiSemaphore);
      }
   }
}

extern "C" void app_main(void)
{  
  HAL::HAL_Init();
  lv_init(); 
  lv_port_disp_init();
  lv_port_indev_init();
  // lv_demo_music();
  lv_tick_set_cb(my_tick_get_cb);
  //App_Init();
  // while (1) {
  //   lv_timer_handler(); /* let the GUI do its work */
  //   // HAL::HAL_Update();
  //   vTaskDelay(pdMS_TO_TICKS(2));
  // }
  xTaskCreatePinnedToCore(uiTask, "lv_ui_Task", 1024 * 48, NULL, 5, NULL, 1);
}