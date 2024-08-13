#include "Dialplate.h"

using namespace Page;

static void StatusBar_AnimCreate(lv_obj_t* contBatt);

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
}

void Dialplate::onViewDidLoad()
{

}

void Dialplate::onViewWillAppear()
{
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

static void StatusBar_ConBattSetOpa(lv_obj_t* obj, int32_t opa)
{
    lv_obj_set_style_opa(obj, opa, 0);
}

static void StatusBar_onAnimOpaFinish(lv_anim_t* a)
{
    lv_obj_t* obj = (lv_obj_t*)a->var;
    StatusBar_ConBattSetOpa(obj, LV_OPA_COVER);
    StatusBar_AnimCreate(obj);
}

static void StatusBar_onAnimHeightFinish(lv_anim_t* a)
{
    lv_anim_t a_opa;
    lv_anim_init(&a_opa);
    lv_anim_set_var(&a_opa, a->var);
    lv_anim_set_exec_cb(&a_opa, (lv_anim_exec_xcb_t)StatusBar_ConBattSetOpa);
    lv_anim_set_ready_cb(&a_opa, StatusBar_onAnimOpaFinish);
    lv_anim_set_values(&a_opa, LV_OPA_COVER, LV_OPA_TRANSP);
    lv_anim_set_early_apply(&a_opa, true);
    lv_anim_set_delay(&a_opa, 500);
    lv_anim_set_time(&a_opa, 500);
    lv_anim_start(&a_opa);
}

static void StatusBar_AnimCreate(lv_obj_t* contBatt)
{
    lv_anim_t a;
    lv_anim_init(&a);
    lv_anim_set_var(&a, contBatt);
    lv_anim_set_exec_cb(&a, [](void* var, int32_t v)
    {
        lv_obj_set_height((lv_obj_t*)var, v);
    });
    lv_anim_set_values(&a, 0, 9);
    lv_anim_set_time(&a, 1000);
    lv_anim_set_ready_cb(&a, StatusBar_onAnimHeightFinish);
    lv_anim_start(&a);
}

void Dialplate::Update()
{
    HAL::Clock_Info_t clockInfo;
    Model.GetClockinfo(&clockInfo);
    
    HAL::Power_Info_t PowerInfo;
    Model.GetPowerInfo(&PowerInfo);
    // printf("PowerInfo: %d \n", PowerInfo.Percentage);

    lv_label_set_text_fmt(View.ui.dialplate.labelClockmin, "%02d", clockInfo.minute);
    lv_label_set_text_fmt(View.ui.dialplate.labelClockhour, "%02d", clockInfo.hour);
    lv_label_set_text_fmt(View.ui.battery.label, "%d%%", PowerInfo.Percentage);

    bool Is_BattCharging = PowerInfo.isCharging;
    printf("Is_BattCharging: %d \n", PowerInfo.isCharging);
    lv_obj_t* contBatt = View.ui.battery.objUsage;
    static bool Is_BattChargingAnimActive = false;
    if(Is_BattCharging)
    {
        if(!Is_BattChargingAnimActive)
        {
            StatusBar_AnimCreate(contBatt);
            Is_BattChargingAnimActive = true;
        }
    }
    else
    {
        if(Is_BattChargingAnimActive)
        {
            lv_anim_del(contBatt, nullptr);
            lv_obj_set_style_opa(contBatt, LV_OPA_COVER, 0);
            Is_BattChargingAnimActive = false;
        }
        lv_coord_t height = lv_map(PowerInfo.Percentage, 0, 100, 0, 9);
        lv_obj_set_height(contBatt, height);
    }
    // lv_obj_set_height(contBatt, 5);
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
        // if (lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_RIGHT) {
        //     instance->_Manager->Replace("Pages/Watch_analog");
        // }
    }
    else if (code == LV_EVENT_LONG_PRESSED)
    {
        instance->_Manager->Replace("Pages/WatchFace_Select");

    }
}