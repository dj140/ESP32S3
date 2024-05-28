#include "SystemInfos.h"
#include "App/Version.h"

using namespace Page;

SystemInfos::SystemInfos()
{
}

SystemInfos::~SystemInfos()
{

}

void SystemInfos::onCustomAttrConfig()
{

}

void SystemInfos::onViewLoad()
{
    Model.Init();
    View.Create(_root);
    //AttachEvent(_root);
    //lv_obj_add_event_cb(View.LauncherData_t.appPanel, onEvent, LV_EVENT_SCROLL, this);

    AttachEvent(View.LauncherData_t.appPanel);
    //AttachEvent(View.ui.sport.cont);

   SystemInfosView::item_t* item_grp = ((SystemInfosView::item_t*)&View.ui);

    for (int i = 0; i < sizeof(View.ui) / sizeof(SystemInfosView::item_t); i++)
    {
        AttachEvent(item_grp[i].cont);
    }
}

void SystemInfos::onViewDidLoad()
{

}

void SystemInfos::onViewWillAppear()
{
    timer = lv_timer_create(onTimerUpdate, 1000, this);
    lv_timer_ready(timer);

    //View.SetScrollToY(_root, -LV_VER_RES, LV_ANIM_OFF);
    lv_obj_set_style_opa(_root, LV_OPA_TRANSP, 0);
    lv_obj_fade_in(_root, 300, 0);
}

void SystemInfos::onViewDidAppear()
{
    //lv_group_t* group = lv_group_get_default();
    //LV_ASSERT_NULL(group);
    //View.onFocus(group);
}

void SystemInfos::onViewWillDisappear()
{
    //lv_obj_fade_out(_root, 300, 0);
}

void SystemInfos::onViewDidDisappear()
{
    lv_timer_del(timer);
}

void SystemInfos::onViewUnload()
{
    View.Delete();
    Model.Deinit();
}

void SystemInfos::onViewDidUnload()
{

}

void SystemInfos::AttachEvent(lv_obj_t* obj)
{
    lv_obj_add_event_cb(obj, onEvent, LV_EVENT_ALL, this);
}

void SystemInfos::Update()
{

}

void SystemInfos::onTimerUpdate(lv_timer_t* timer)
{
    SystemInfos* instance = (SystemInfos*)timer->user_data;

    instance->Update();
}

void SystemInfos::onEvent(lv_event_t* event)
{
    SystemInfos* instance = (SystemInfos*)lv_event_get_user_data(event);
    LV_ASSERT_NULL(instance);

    lv_obj_t* obj = lv_event_get_current_target_obj(event);
    lv_event_code_t code = lv_event_get_code(event);
    //LV_LOG_USER("LV_EVENT_GESTURE %d", code);

    if (code == LV_EVENT_GESTURE)
    {
        LV_LOG_USER("LV_EVENT_GESTURE %d", code);

//        if (lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_LEFT) {
//            instance->_Manager->Pop();
//        }
        if (lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_RIGHT) {
            instance->_Manager->Pop();
        }
    }
    if (obj != instance->View.LauncherData_t.appPanel)
    {
        /* Pressed feedback */
        if (code == LV_EVENT_PRESSED) {
            /* If pressed, smaller Icon */
            lv_img_set_zoom(lv_event_get_target_obj(event), lv_img_get_zoom(lv_event_get_target_obj(event)) - 10);
        }
        if (code == LV_EVENT_RELEASED) {
            /* If released, set it back */
            lv_img_set_zoom(lv_event_get_target_obj(event), lv_img_get_zoom(lv_event_get_target_obj(event)) + 10);
        }
    }
    /* If scrolling, update Icon zooming */
    if (code == LV_EVENT_SCROLL) {
        /* Get launcher pointer */
        instance->View.updateAppIconZoom(instance->View.LauncherData_t.appPanel);
    }
    /* Start App */
    if (code == LV_EVENT_SHORT_CLICKED) {
        if (obj == instance->View.ui.app1.cont)
        {
            instance->_Manager->BackHome();
        }
        if (obj == instance->View.ui.app2.cont)
        {
            instance->_Manager->Push("Pages/Image_Player");
        }
                if (obj == instance->View.ui.app3.cont)
        {
            instance->_Manager->BackHome();
        }
                if (obj == instance->View.ui.app4.cont)
        {
            instance->_Manager->BackHome();
        }
//                if (obj == instance->View.ui.gps.cont)
//        {
//            instance->_Manager->Push("Pages/_Template");
//        }

    }
    //if (code == LV_EVENT_PRESSED)
    //{
    //    if (lv_obj_has_state(obj, LV_STATE_FOCUSED))
    //    {
    //        instance->_Manager->Pop();
    //    }
    //}

    //if (obj == instance->_root)
    //{
    //    if (code == LV_EVENT_LEAVE)
    //    {
    //        instance->_Manager->Pop();
    //    }
    //}
}
