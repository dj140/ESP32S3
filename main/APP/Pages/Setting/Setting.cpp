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
    SetCustomLoadAnimType(PageManager::LOAD_ANIM_OVER_BOTTOM, 500, lv_anim_path_overshoot);
}

void Setting::onViewLoad()
{
    LV_LOG_USER("begin");
    View.Create(_root);
    AttachEvent(_root);
    AttachEvent(View.ui.cont);
    AttachEvent(View.ui.icon2);

}

void Setting::onViewDidLoad()
{
    LV_LOG_USER("begin");
}

void Setting::onViewWillAppear()
{
    LV_LOG_USER("begin");
    timer = lv_timer_create(onTimerUpdate, 3000, this);
    lv_obj_set_style_opa(_root, LV_OPA_TRANSP, 0);
    lv_obj_fade_in(_root, 300, 0);
}

void Setting::onViewDidAppear()
{
    LV_LOG_USER("begin");
}

void Setting::onViewWillDisappear()
{
    LV_LOG_USER("begin");
    lv_obj_fade_out(_root, 300, 0);

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

    lv_obj_t* obj = lv_event_get_current_target_obj(event);
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
    if (code == LV_EVENT_CLICKED)
    {
        LV_LOG_USER("LV_EVENT_CLICKED %d", code);

        if (obj == instance->View.ui.icon2)
        {
            //LV_LOG_USER("icon2");
            //if ((lv_obj_get_state(instance->View.ui.icon2) | LV_STATE_CHECKED) == 1)
            //{
            //    LV_LOG_USER("LV_STATE_CHECKED");

                lv_obj_t* img0 = lv_img_create(instance->View.ui.icon1);
                lv_img_set_src(img0, ResourcePool::GetImage("wifi_icon"));
                lv_img_set_zoom(img0, 80);
                lv_obj_set_style_img_recolor_opa(img0, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_obj_set_style_img_recolor(img0, lv_palette_main(LV_PALETTE_LIGHT_BLUE), LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_obj_align(img0, LV_ALIGN_CENTER, 0, 0);
            //}
            //else if (lv_obj_get_state(instance->View.ui.icon2) == LV_STATE_DEFAULT)
            //{
            //    LV_LOG_USER("icon55");

            //}


            //lv_obj_add_state(instance->View.ui.icon2, LV_STATE_PRESSED);
        }
    }
    //if (code == LV_EVENT_LONG_PRESSED)
    //{
    //    instance->_Manager->Replace("Pages/Dialplate");

    //}
}
