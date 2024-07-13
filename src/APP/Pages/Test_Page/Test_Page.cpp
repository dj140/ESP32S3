#include "Test_Page.h"
#include "lvgl_port/lv_port_disp.h"
#include <stdio.h>

using namespace Page;

// extern LGFX display;

Test_Page::Test_Page()
    : timer(nullptr)
{
}

Test_Page::~Test_Page()
{

}

void Test_Page::onCustomAttrConfig()
{
    LV_LOG_USER("begin");
    SetCustomCacheEnable(true);
    SetCustomLoadAnimType(PageManager::LOAD_ANIM_OVER_LEFT, 300, lv_anim_path_linear);
}

void Test_Page::onViewLoad()
{
    LV_LOG_USER("begin");
    View.Create(_root);
    AttachEvent(_root, onEvent, LV_EVENT_ALL);
    AttachEvent(View.ui.cont, onEvent, LV_EVENT_ALL);
    AttachEvent(View.ui.menu, onEvent, LV_EVENT_ALL);
    AttachEvent(View.ui.sidebar, switch_handler, LV_EVENT_VALUE_CHANGED);
    AttachEvent(View.ui.Brightness, brightness_handler, LV_EVENT_VALUE_CHANGED);

}

void Test_Page::onViewDidLoad()
{
    LV_LOG_USER("begin");
}

void Test_Page::onViewWillAppear()
{
    LV_LOG_USER("begin");
    timer = lv_timer_create(onTimerUpdate, 1000, this);
//    lv_obj_set_style_opa(_root, LV_OPA_TRANSP, 0);
//    lv_obj_fade_in(_root, 300, 0);
}

void Test_Page::onViewDidAppear()
{
    LV_LOG_USER("begin");
}

void Test_Page::onViewWillDisappear()
{
    LV_LOG_USER("begin");
//    lv_obj_fade_out(_root, 300, 0);
}

void Test_Page::onViewDidDisappear()
{
    LV_LOG_USER("begin");
    lv_timer_del(timer);
}

void Test_Page::onViewUnload()
{
    LV_LOG_USER("begin");
}

void Test_Page::onViewDidUnload()
{
    LV_LOG_USER("begin");
}

void Test_Page::AttachEvent(lv_obj_t* obj, lv_event_cb_t event_cb, lv_event_code_t filter)
{
    //lv_obj_set_user_data(obj, this);
    lv_obj_add_event_cb(obj, event_cb, filter, this);
}

void Test_Page::Update()
{


}

void Test_Page::onTimerUpdate(lv_timer_t* timer)
{
    Test_Page* instance = (Test_Page*)timer->user_data;

    instance->Update();
}

void Test_Page::switch_handler(lv_event_t* event)
{
    Test_Page* instance = (Test_Page*)lv_event_get_user_data(event);
    LV_ASSERT_NULL(instance);

    lv_event_code_t code = lv_event_get_code(event);
    // lv_obj_t * menu = (lv_obj_t*)lv_event_get_user_data(event);
    lv_obj_t * obj = (lv_obj_t*)lv_event_get_target(event);
    if(code == LV_EVENT_VALUE_CHANGED) {
        if(lv_obj_has_state(obj, LV_STATE_CHECKED)) {
            lv_menu_set_page(instance->View.ui.menu, NULL);
            lv_menu_set_sidebar_page(instance->View.ui.menu, instance->View.ui.rootPage);
            lv_obj_send_event(lv_obj_get_child(lv_obj_get_child(lv_menu_get_cur_sidebar_page(instance->View.ui.menu), 0), 0), LV_EVENT_CLICKED,
                              NULL);
        }
        else {
            lv_menu_set_sidebar_page(instance->View.ui.menu, NULL);
            lv_menu_clear_history(instance->View.ui.menu); /* Clear history because we will be showing the root page later */
            lv_menu_set_page(instance->View.ui.menu, instance->View.ui.rootPage);
        }
    }
}
void Test_Page::brightness_handler(lv_event_t* event)
{
    Test_Page* instance = (Test_Page*)lv_event_get_user_data(event);
    LV_ASSERT_NULL(instance);

    lv_event_code_t code = lv_event_get_code(event);
    lv_obj_t * obj = (lv_obj_t*)lv_event_get_target(event);

    if(code == LV_EVENT_VALUE_CHANGED) {
          printf("slider: %d \n", (uint8_t)lv_slider_get_value(obj));
        //   display.setBrightness((uint8_t)lv_slider_get_value(obj));
    }
}
void Test_Page::onEvent(lv_event_t* event)
{
    Test_Page* instance = (Test_Page*)lv_event_get_user_data(event);
    LV_ASSERT_NULL(instance);

    lv_obj_t* obj = lv_event_get_current_target_obj(event);
    lv_event_code_t code = lv_event_get_code(event);

    if (code == LV_EVENT_GESTURE)
    {
        LV_LOG_USER("LV_EVENT_GESTURE %d", code);

        if (lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_RIGHT) {
            instance->_Manager->Pop();
        }
    }
    // if (code = LV_EVENT_CLICKED)
    // {
    //     if(lv_menu_back_button_is_root(instance->View.ui.menu, obj)) {
    //         lv_obj_t * mbox1 = lv_msgbox_create(NULL);
    //         lv_msgbox_add_title(mbox1, "Hello");
    //         lv_msgbox_add_text(mbox1, "Root back btn click.");
    //         lv_msgbox_add_close_button(mbox1);
    //     }
    // }

}
