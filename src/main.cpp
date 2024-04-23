
#include "Arduino.h"
#include "lvgl.h"
#include "APP/APP.h"
#include "lvgl_port/lv_port_disp.h"
#include "demos/benchmark/lv_demo_benchmark.h"


void setup(void)
{
  Serial.begin(115200);
  // Serial.setDebugOutput(true);
  // while(!Serial);
  Serial.println("Arduino_GFX Hello World example");
  lv_init(); 
  lv_port_disp_init();
  //lv_demo_benchmark();
  App_Init();
}

void loop()
{
  lv_timer_handler(); /* let the GUI do its work */
  delay(5);
}
