#include "Watch_analog.h"

using namespace Page;

Watch_analog::Watch_analog()
    : timer(nullptr)
{
}

Watch_analog::~Watch_analog()
{

}

void Watch_analog::onCustomAttrConfig()
{
    LV_LOG_USER("begin");
    SetCustomCacheEnable(true);
    SetCustomLoadAnimType(PageManager::LOAD_ANIM_FADE_ON, 1000, lv_anim_path_ease_in);
}

void Watch_analog::onViewLoad()
{
    LV_LOG_USER("begin");
    View.Create(_root);
    AttachEvent(_root);
    AttachEvent(View.ui.cont);
}

void Watch_analog::onViewDidLoad()
{
    LV_LOG_USER("begin");
}

void Watch_analog::onViewWillAppear()
{
    LV_LOG_USER("begin");
    View.AppearAnimStart();
//    lv_obj_set_style_opa(_root, LV_OPA_TRANSP, 0);
//    lv_obj_fade_in(_root, 500, 0);
}

void Watch_analog::onViewDidAppear()
{
    LV_LOG_USER("begin"); 
  timer = lv_timer_create(onTimerUpdate, 3000, this);

}

void Watch_analog::onViewWillDisappear()
{
    LV_LOG_USER("begin");
}

void Watch_analog::onViewDidDisappear()
{
    LV_LOG_USER("begin");
    lv_timer_del(timer);
      View.Delete();

}

void Watch_analog::onViewUnload()
{
    LV_LOG_USER("begin");
    View.Delete();
}

void Watch_analog::onViewDidUnload()
{
    LV_LOG_USER("begin");
}

void Watch_analog::AttachEvent(lv_obj_t* obj)
{
    //lv_obj_set_user_data(obj, this);
    lv_obj_add_event_cb(obj, onEvent, LV_EVENT_ALL, this);
}

void Watch_analog::Update()
{


}

void Watch_analog::onTimerUpdate(lv_timer_t* timer)
{
    Watch_analog* instance = (Watch_analog*)timer->user_data;

    instance->Update();
}

void Watch_analog::onEvent(lv_event_t* event)
{
    Watch_analog* instance = (Watch_analog*)lv_event_get_user_data(event);
    LV_ASSERT_NULL(instance);

    lv_obj_t* obj = lv_event_get_current_target_obj(event);
    lv_event_code_t code = lv_event_get_code(event);


 /*       if (code == LV_EVENT_PRESSED)
        {    

            instance->_Manager->Pop();
        }*/
    
    if (code == LV_EVENT_GESTURE)
    {
        LV_LOG_USER("LV_EVENT_GESTURE %d", code);

        if (lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_LEFT) {
            instance->_Manager->Push("Pages/SystemInfos");
        }
//        if (lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_TOP) {
//            instance->_Manager->Push("Pages/Blood_oxy");
//        }
        if (lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_BOTTOM) {
            instance->_Manager->Push("Pages/Setting");
        }
        if (lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_RIGHT) {
            instance->_Manager->Replace("Pages/Watch_cxk");
        }
    }
//    if (code == LV_EVENT_LONG_PRESSED)
//    {
//        instance->_Manager->Replace("Pages/Watch_cxk");

//    }
}
