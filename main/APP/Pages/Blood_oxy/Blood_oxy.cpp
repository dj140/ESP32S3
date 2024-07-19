#include "Blood_oxy.h"

using namespace Page;

Blood_oxy::Blood_oxy()
    : timer(nullptr)
{
}

Blood_oxy::~Blood_oxy()
{

}

void Blood_oxy::onCustomAttrConfig()
{
    LV_LOG_USER("begin");
    SetCustomCacheEnable(true);
    SetCustomLoadAnimType(PageManager::LOAD_ANIM_OVER_TOP, 300, lv_anim_path_overshoot);
}

void Blood_oxy::onViewLoad()
{
    LV_LOG_USER("begin");
    View.Create(_root);
    AttachEvent(_root);
    AttachEvent(View.ui.cont);
    AttachEvent(View.ui.button);

}

void Blood_oxy::onViewDidLoad()
{
    LV_LOG_USER("begin");
}

void Blood_oxy::onViewWillAppear()
{
    LV_LOG_USER("begin");
    timer = lv_timer_create(onTimerUpdate, 3000, this);
}

void Blood_oxy::onViewDidAppear()
{
    LV_LOG_USER("begin");
}

void Blood_oxy::onViewWillDisappear()
{
    LV_LOG_USER("begin");
}

void Blood_oxy::onViewDidDisappear()
{
    LV_LOG_USER("begin");
    lv_timer_del(timer);
}

void Blood_oxy::onViewUnload()
{
    LV_LOG_USER("begin");
}

void Blood_oxy::onViewDidUnload()
{
    LV_LOG_USER("begin");
      View.Delete();
}

void Blood_oxy::AttachEvent(lv_obj_t* obj)
{
    //lv_obj_set_user_data(obj, this);
    lv_obj_add_event_cb(obj, onEvent, LV_EVENT_ALL, this);
}

void Blood_oxy::Update()
{
    //lv_img_set_src(View.ui.image, ResourcePool::GetImage("app_icon_hdpi_boxing_png"));
    //lv_obj_fade_in(View.ui.image, 2000, 100);


}

void Blood_oxy::onTimerUpdate(lv_timer_t* timer)
{
    Blood_oxy* instance = (Blood_oxy*)timer->user_data;

    instance->Update();
}

void Blood_oxy::onEvent(lv_event_t* event)
{
    Blood_oxy* instance = (Blood_oxy*)lv_event_get_user_data(event);
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

        if (lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_BOTTOM) {
            instance->_Manager->Pop();
        }
    }
    if (code == LV_EVENT_SHORT_CLICKED)
    {
        if (obj == instance->View.ui.button)
        {
            instance->_Manager->Push("Pages/Heartbeat_Measuing");
        }
    }
    //if (code == LV_EVENT_LONG_PRESSED)
    //{
    //    instance->_Manager->Replace("Pages/Dialplate");

    //}
}
