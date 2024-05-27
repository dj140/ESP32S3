#include "Setting.h"

using namespace Page;

Setting::Setting()
    : timer(nullptr)
{
}

Setting::~Setting()
{

}

void Setting::onCustomAttrConfig()
{
    LV_LOG_USER("begin");
    SetCustomCacheEnable(true);
    SetCustomLoadAnimType(PageManager::LOAD_ANIM_OVER_BOTTOM, 1000, lv_anim_path_bounce);
}

void Setting::onViewLoad()
{
    LV_LOG_USER("begin");
    View.Create(_root);
    AttachEvent(_root);
    AttachEvent(View.ui.cont);

}

void Setting::onViewDidLoad()
{
    LV_LOG_USER("begin");
}

void Setting::onViewWillAppear()
{
    LV_LOG_USER("begin");
    timer = lv_timer_create(onTimerUpdate, 3000, this);
}

void Setting::onViewDidAppear()
{
    LV_LOG_USER("begin");
}

void Setting::onViewWillDisappear()
{
    LV_LOG_USER("begin");
}

void Setting::onViewDidDisappear()
{
    LV_LOG_USER("begin");
    lv_timer_del(timer);
}

void Setting::onViewUnload()
{
    LV_LOG_USER("begin");
}

void Setting::onViewDidUnload()
{
    LV_LOG_USER("begin");
}

void Setting::AttachEvent(lv_obj_t* obj)
{
    //lv_obj_set_user_data(obj, this);
    lv_obj_add_event_cb(obj, onEvent, LV_EVENT_ALL, this);
}

void Setting::Update()
{
    //lv_img_set_src(View.ui.image, ResourcePool::GetImage("app_icon_hdpi_boxing_png"));
    //lv_obj_fade_in(View.ui.image, 2000, 100);


}

void Setting::onTimerUpdate(lv_timer_t* timer)
{
    Setting* instance = (Setting*)timer->user_data;

    instance->Update();
}

void Setting::onEvent(lv_event_t* event)
{
    Setting* instance = (Setting*)lv_event_get_user_data(event);
    LV_ASSERT_NULL(instance);

    lv_obj_t* obj = lv_event_get_current_target(event);
    lv_event_code_t code = lv_event_get_code(event);


 /*       if (code == LV_EVENT_PRESSED)
        {    

            instance->_Manager->Pop();
        }*/
    
    if (code == LV_EVENT_GESTURE)
    {
        LV_LOG_USER("LV_EVENT_GESTURE %d", code);

        if (lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_TOP) {
            instance->_Manager->Pop();
        }
    }

    //if (code == LV_EVENT_LONG_PRESSED)
    //{
    //    instance->_Manager->Replace("Pages/Dialplate");

    //}
}
