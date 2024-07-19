#include "Template.h"
#include "stdio.h"
using namespace Page;

#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include "esp_err.h"
#include "esp_log.h"
#include "esp_system.h"
#include "esp_heap_caps.h"
#include "multi_heap.h"


// #include <LovyanGFX.hpp>
#include "lvgl_port/lv_port_disp.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"


// pixel drawing callba

Template::Template()
    : timer(nullptr)
{
}

Template::~Template()
{

}
// pixel drawing callback
void Template::update_img(uint8_t *downloaded_jpeg_buf, size_t buf_size)
 {

}
void Template::onCustomAttrConfig()
{
    LV_LOG_USER("begin");
    SetCustomCacheEnable(true);
    SetCustomLoadAnimType(PageManager::LOAD_ANIM_OVER_BOTTOM, 1000, lv_anim_path_bounce);
}

void Template::onViewLoad()
{
    printf("Template begin \n");
    View.Create(_root);
//    lv_label_set_text(View.ui.labelTitle, _Name);

    AttachEvent(_root);
    AttachEvent(View.ui.cont);
 

}

void Template::onViewDidLoad()
{
    LV_LOG_USER("begin");
}

void Template::onViewWillAppear()
{
    LV_LOG_USER("begin");
    timer = lv_timer_create(onTimerUpdate, 16, this);
 

}

void Template::onViewDidAppear()
{
    LV_LOG_USER("begin");
//    lv_obj_del(View.ui.Spinner);

}

void Template::onViewWillDisappear()
{
    LV_LOG_USER("begin");
}

void Template::onViewDidDisappear()
{
    LV_LOG_USER("begin");
    lv_timer_del(timer);
}

void Template::onViewUnload()
{
    LV_LOG_USER("begin");
}

void Template::onViewDidUnload()
{
    LV_LOG_USER("begin");
}

void Template::AttachEvent(lv_obj_t* obj)
{
    lv_obj_set_user_data(obj, this);
    lv_obj_add_event_cb(obj, onEvent, LV_EVENT_ALL, this);
}

void Template::Update()
{
 
}

void Template::onTimerUpdate(lv_timer_t* timer)
{
    Template* instance = (Template*)timer->user_data;

    instance->Update();
}

void Template::onEvent(lv_event_t* event)
{
    Template* instance = (Template*)lv_event_get_user_data(event);
    LV_ASSERT_NULL(instance);

    lv_obj_t* obj = lv_event_get_current_target_obj(event);
    lv_event_code_t code = lv_event_get_code(event);
//  printf("lv_event_code_t: %d ", code);

    if (code == LV_EVENT_PRESSED)
    {    

        instance->_Manager->Push("Pages/Dialplate");
    }

    if (code == LV_EVENT_GESTURE)
    {
//      LV_LOG_USER("LV_EVENT_GESTURE %d", code);

      if (lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_LEFT) {
          instance->_Manager->Push("Pages/Dialplate");
      }
    }

}
