#include "WatchFace_Select.h"

using namespace Page;

WatchFace_Select::WatchFace_Select()
    : timer(nullptr)
{
}

WatchFace_Select::~WatchFace_Select()
{
}

void WatchFace_Select::onCustomAttrConfig()
{
    SetCustomLoadAnimType(PageManager::LOAD_ANIM_FADE_ON, 200, lv_anim_path_ease_in);
}

void WatchFace_Select::onViewLoad()
{
    //Model.Init();
    View.Create(_root);
    AttachEvent(_root);
    AttachEvent(View.ui.faceSelect);
    for (int i = 0; i < View.numFaces; i++)
    {
        AttachEvent(View.faces[i].watchface);
    }

}

void WatchFace_Select::onViewDidLoad()
{

}

void WatchFace_Select::onViewWillAppear()
{
    lv_indev_wait_release(lv_indev_get_act());
    lv_group_t* group = lv_group_get_default();
    LV_ASSERT_NULL(group);

    lv_group_set_wrap(group, false);
}

void WatchFace_Select::onViewDidAppear()
{
    timer = lv_timer_create(onTimerUpdate, 1000, this);
}

void WatchFace_Select::onViewWillDisappear()
{
    lv_group_t* group = lv_group_get_default();
    LV_ASSERT_NULL(group);
    lastFocus = lv_group_get_focused(group);
    lv_group_remove_all_objs(group);
    lv_timer_del(timer);
    View.numFaces = 0;
    //View.AppearAnimStart(true);
}

void WatchFace_Select::onViewDidDisappear()
{
}

void WatchFace_Select::onViewUnload()
{
    //Model.Deinit();
    View.Delete();
}

void WatchFace_Select::onViewDidUnload()
{

}

void WatchFace_Select::AttachEvent(lv_obj_t* obj)
{
        lv_obj_add_event_cb(obj, onEvent, LV_EVENT_ALL, this);
}

void WatchFace_Select::Update()
{

}

void WatchFace_Select::onTimerUpdate(lv_timer_t* timer)
{
    WatchFace_Select* instance = (WatchFace_Select*)timer->user_data;

    instance->Update();
}



void WatchFace_Select::onEvent(lv_event_t* event)
{
    WatchFace_Select* instance = (WatchFace_Select*)lv_event_get_user_data(event);
    LV_ASSERT_NULL(instance);

    lv_obj_t* obj = lv_event_get_current_target_obj(event);
    lv_event_code_t code = lv_event_get_code(event);
    //PageManager manager;

    if (code == LV_EVENT_GESTURE)
    {
        LV_LOG_USER("LV_EVENT_GESTURE %d", code);

        if (lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_LEFT) {
            instance->_Manager->Pop();
        }
        //if (lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_TOP) {
        //    instance->_Manager->Push("Pages/Blood_oxy");
        //}
        //if (lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_BOTTOM) {
        //    instance->_Manager->Push("Pages/Setting");
        //}
        //if (lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_RIGHT) {
        //    instance->_Manager->Replace("Pages/Watch_analog");
        //}
    }
    if (code == LV_EVENT_CLICKED)
    {
        LV_LOG_USER("LV_EVENT_CLICKED %d", code);

        if (obj == instance->View.faces[0].watchface)
        {
            instance->_Manager->Replace("Pages/Watch_cxk");

        } 
        if (obj == instance->View.faces[1].watchface)
        {
        instance->_Manager->Replace("Pages/Watch_analog");
        }
        if (obj == instance->View.faces[2].watchface)
        {
            instance->_Manager->Replace("Pages/Dialplate");

        }
    }
  
}
