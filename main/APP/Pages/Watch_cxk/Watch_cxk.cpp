#include "Watch_cxk.h"

using namespace Page;

Watch_cxk::Watch_cxk()
    : timer(nullptr)
{
}

Watch_cxk::~Watch_cxk()
{

}

void Watch_cxk::onCustomAttrConfig()
{
    LV_LOG_USER("begin");
    SetCustomCacheEnable(true);
    SetCustomLoadAnimType(PageManager::LOAD_ANIM_OVER_RIGHT, 200, lv_anim_path_ease_in);
}

void Watch_cxk::onViewLoad()
{
    LV_LOG_USER("begin");
    View.Create(_root);
    AttachEvent(_root);
    AttachEvent(View.ui.cont);
//    AttachEvent(View.ui.ui_bg);

}

void Watch_cxk::onViewDidLoad()
{
    LV_LOG_USER("begin");
}

void Watch_cxk::onViewWillAppear()
{
    LV_LOG_USER("begin");
    timer = lv_timer_create(onTimerUpdate, 3000, this);
    View.AppearAnimStart();

}

void Watch_cxk::onViewDidAppear()
{
    LV_LOG_USER("begin");
}

void Watch_cxk::onViewWillDisappear()
{
    LV_LOG_USER("begin");
}

void Watch_cxk::onViewDidDisappear()
{
    LV_LOG_USER("begin");
    lv_timer_del(timer);
}

void Watch_cxk::onViewUnload()
{
    LV_LOG_USER("begin");
    View.Delete();

}

void Watch_cxk::onViewDidUnload()
{
    LV_LOG_USER("begin");
}

void Watch_cxk::AttachEvent(lv_obj_t* obj)
{
    //lv_obj_set_user_data(obj, this);
    lv_obj_add_event_cb(obj, onEvent, LV_EVENT_ALL, this);
}

void Watch_cxk::Update()
{
    //lv_img_set_src(View.ui.image, ResourcePool::GetImage("app_icon_hdpi_boxing_png"));
    //lv_obj_fade_in(View.ui.image, 2000, 100);
}

void Watch_cxk::onTimerUpdate(lv_timer_t* timer)
{
    Watch_cxk* instance = (Watch_cxk*)timer->user_data;

    instance->Update();
}

void Watch_cxk::onEvent(lv_event_t* event)
{
    Watch_cxk* instance = (Watch_cxk*)lv_event_get_user_data(event);
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
       if (lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_TOP) {
           instance->_Manager->Push("Pages/Blood_oxy");
       }
        if (lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_BOTTOM) {
            instance->_Manager->Push("Pages/Setting");
        }
        // if (lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_RIGHT) {
        //     instance->_Manager->Replace("Pages/Dialplate");
        // }
    }
    else if (code == LV_EVENT_LONG_PRESSED)
    {
        instance->_Manager->Replace("Pages/WatchFace_Select");

    }
}
