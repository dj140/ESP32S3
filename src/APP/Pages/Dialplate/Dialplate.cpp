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
    lv_indev_wait_release(lv_indev_get_act());
    lv_group_t* group = lv_group_get_default();
    LV_ASSERT_NULL(group);

    lv_group_set_wrap(group, false);

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

    Model.SetStatusBarStyle(DataProc::STATUS_BAR_STYLE_TRANSP);

    Update();

    View.AppearAnimStart();
}

void Dialplate::onViewDidAppear()
{
    timer = lv_timer_create(onTimerUpdate, 1000, this);
}

void Dialplate::onViewWillDisappear()
{
    lv_group_t* group = lv_group_get_default();
    LV_ASSERT_NULL(group);
    lastFocus = lv_group_get_focused(group);
    lv_group_remove_all_objs(group);
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
//    char buf[16];
//    lv_label_set_text_fmt(View.ui.topInfo.labelSpeed, "%02d", (int)Model.GetSpeed());

//    lv_label_set_text_fmt(View.ui.dialplate.labelInfoGrp[0].lableValue, "%0.1f km/h", Model.GetAvgSpeed());
////    lv_label_set_text(
////        View.ui.dialplate.labelInfoGrp[1].lableValue,
////        DataProc::MakeTimeString(Model.sportStatusInfo.singleTime, buf, sizeof(buf))
////    );
//    lv_label_set_text_fmt(
//        View.ui.dialplate.labelInfoGrp[2].lableValue,
//        "%0.1f km",
//        Model.sportStatusInfo.singleDistance / 1000
//    );
//    lv_label_set_text_fmt(
//        View.ui.dialplate.labelInfoGrp[3].lableValue,
//        "%d k",
//        int(Model.sportStatusInfo.singleCalorie)
//    );
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

    lv_obj_t* obj = lv_event_get_current_target(event);
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
    if (code == LV_EVENT_LONG_PRESSED)
    {
        instance->_Manager->Replace("Pages/Watch_analog");

    }
//    if (code == LV_EVENT_SHORT_CLICKED)
//    {
//        instance->onBtnClicked(obj);
//    }

//    if (obj == instance->View.ui.btnCont.btnRec)
//    {
//        if (code == LV_EVENT_SHORT_CLICKED)
//        {
//            instance->onRecord(false);
//        }
//        else if (code == LV_EVENT_LONG_PRESSED)
//        {
//            instance->onRecord(true);
//        }
//    }
}
