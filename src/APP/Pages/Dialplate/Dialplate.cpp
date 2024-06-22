#include "Dialplate.h"

using namespace Page;

Dialplate::Dialplate()
{
}

Dialplate::~Dialplate()
{
}

void Dialplate::onCustomAttrConfig()
{
    SetCustomLoadAnimType(PageManager::LOAD_ANIM_NONE);
}

void Dialplate::onViewLoad()
{
    Model.Init();
    View.Create(_root);
    AttachEvent(_root);

    AttachEvent(View.ui.dialplate.cont);
    AttachEvent(View.ui.dialplate.bg);

//    AttachEvent(View.ui.btnCont.btnRec);
//    AttachEvent(View.ui.btnCont.btnMenu);
}

void Dialplate::onViewDidLoad()
{

}

void Dialplate::onViewWillAppear()
{
//    lv_indev_wait_release(lv_indev_get_act());
//    lv_group_t* group = lv_group_get_default();
//    LV_ASSERT_NULL(group);

//    lv_group_set_wrap(group, false);

//    lv_group_add_obj(group, View.ui.btnCont.btnMap);
//    lv_group_add_obj(group, View.ui.btnCont.btnRec);
//    lv_group_add_obj(group, View.ui.btnCont.btnMenu);

//    if (lastFocus)
//    {
//        lv_group_focus_obj(lastFocus);
//    }
//    else
//    {
//        lv_group_focus_obj(View.ui.btnCont.btnRec);
//    }

//    Model.SetStatusBarStyle(DataProc::STATUS_BAR_STYLE_TRANSP);

    Update();

    View.AppearAnimStart();
//    lv_obj_set_style_opa(_root, LV_OPA_TRANSP, 0);
//    lv_obj_fade_in(_root, 500, 0);
}

void Dialplate::onViewDidAppear()
{
    timer = lv_timer_create(onTimerUpdate, 1000, this);
}

void Dialplate::onViewWillDisappear()
{
//    lv_group_t* group = lv_group_get_default();
//    LV_ASSERT_NULL(group);
//    lastFocus = lv_group_get_focused(group);
//    lv_group_remove_all_objs(group);
    lv_timer_del(timer);
    //View.AppearAnimStart(true);
}

void Dialplate::onViewDidDisappear()
{
}

void Dialplate::onViewUnload()
{
    Model.Deinit();
    View.Delete();
}

void Dialplate::onViewDidUnload()
{

}

void Dialplate::AttachEvent(lv_obj_t* obj)
{
    lv_obj_add_event_cb(obj, onEvent, LV_EVENT_ALL, this);
}

void Dialplate::Update()
{
    HAL::Clock_Info_t clockInfo;
    Model.GetClockinfo(&clockInfo);

    lv_label_set_text_fmt(View.ui.dialplate.labelClockmin, "%02d", clockInfo.minute);
    lv_label_set_text_fmt(View.ui.dialplate.labelClockhour, "%02d", clockInfo.hour);

}

void Dialplate::onTimerUpdate(lv_timer_t* timer)
{
    Dialplate* instance = (Dialplate*)timer->user_data;

    instance->Update();
}


void Dialplate::onEvent(lv_event_t* event)
{
    Dialplate* instance = (Dialplate*)lv_event_get_user_data(event);
    LV_ASSERT_NULL(instance);

    lv_obj_t* obj = lv_event_get_current_target_obj(event);
    lv_event_code_t code = lv_event_get_code(event);

    if (code == LV_EVENT_GESTURE)
    {
//        LV_LOG_USER("LV_EVENT_GESTURE %d", code);

        if (lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_LEFT) {
            instance->_Manager->Push("Pages/SystemInfos");
        }
        if (lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_TOP) {
            instance->_Manager->Push("Pages/Blood_oxy");
        }
        if (lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_BOTTOM) {
            instance->_Manager->Push("Pages/Setting");
        }
        if (lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_RIGHT) {
            instance->_Manager->Replace("Pages/Watch_analog");
        }
    }

}