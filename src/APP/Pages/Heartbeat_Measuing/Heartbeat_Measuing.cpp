#include "Heartbeat_Measuing.h"

using namespace Page;

Heartbeat_Measuing::Heartbeat_Measuing()
    : timer(nullptr)
{
}

Heartbeat_Measuing::~Heartbeat_Measuing()
{

}

void Heartbeat_Measuing::onCustomAttrConfig()
{
    LV_LOG_USER("begin");
    SetCustomCacheEnable(true);
    SetCustomLoadAnimType(PageManager::LOAD_ANIM_OVER_TOP, 1000, lv_anim_path_bounce);
}

void Heartbeat_Measuing::onViewLoad()
{
    LV_LOG_USER("begin");
    View.Create(_root);
    AttachEvent(_root);
    AttachEvent(View.ui.cont);
}

void Heartbeat_Measuing::onViewDidLoad()
{
    LV_LOG_USER("begin");
}

void Heartbeat_Measuing::onViewWillAppear()
{
    LV_LOG_USER("begin");
    timer = lv_timer_create(onTimerUpdate, 3000, this);
}

void Heartbeat_Measuing::onViewDidAppear()
{
    LV_LOG_USER("begin");
}

void Heartbeat_Measuing::onViewWillDisappear()
{
    LV_LOG_USER("begin");
}

void Heartbeat_Measuing::onViewDidDisappear()
{
    LV_LOG_USER("begin");
    lv_timer_del(timer);
}

void Heartbeat_Measuing::onViewUnload()
{
    LV_LOG_USER("begin");
    View.Delete();
}

void Heartbeat_Measuing::onViewDidUnload()
{
    LV_LOG_USER("begin");
}

void Heartbeat_Measuing::AttachEvent(lv_obj_t* obj)
{
    //lv_obj_set_user_data(obj, this);
    lv_obj_add_event_cb(obj, onEvent, LV_EVENT_ALL, this);
}

void Heartbeat_Measuing::Update()
{
    //lv_img_set_src(View.ui.image, ResourcePool::GetImage("app_icon_hdpi_boxing_png"));
    //lv_obj_fade_in(View.ui.image, 2000, 100);


}

void Heartbeat_Measuing::onTimerUpdate(lv_timer_t* timer)
{
    Heartbeat_Measuing* instance = (Heartbeat_Measuing*)timer->user_data;

    instance->Update();
}

void Heartbeat_Measuing::onEvent(lv_event_t* event)
{
    Heartbeat_Measuing* instance = (Heartbeat_Measuing*)lv_event_get_user_data(event);
    LV_ASSERT_NULL(instance);

    lv_obj_t* obj = lv_event_get_current_target_obj(event);
    lv_event_code_t code = lv_event_get_code(event);


        //if (code == LV_EVENT_PRESSED)
        //{    

        //    instance->_Manager->Pop();
        //}
    
    if (code == LV_EVENT_GESTURE)
    {
        LV_LOG_USER("LV_EVENT_GESTURE %d", code);

        if (lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_BOTTOM) {
            instance->_Manager->Pop();
        }
    }

}
