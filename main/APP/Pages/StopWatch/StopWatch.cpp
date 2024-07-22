#include "StopWatch.h"
#include <stdio.h>

using namespace Page;

uint16_t Min = 0, Sec = 0, Msec = 0;

StopWatch::StopWatch()
    : timer(nullptr)
{
}

StopWatch::~StopWatch()
{

}
void StopWatch::SW_ShowTime(uint32_t ms)
{

    Min = ms / 60000;
    Sec = (ms - (Min * 60000)) / 1000;
    Msec = ms - (Sec * 1000) - (Min * 60000);
}


void StopWatch::SW_Pause()
{
    if (SW_IsPause)
    {
        SW_IntervalTime = lv_tick_get() - SW_LastTime;
        //lv_timer_resume(timer);
        // lv_task_set_prio(taskStopwatch, LV_TASK_PRIO_MID);
    }
    else
    {
        SW_LastTime = SW_CurrentTime;
        //lv_timer_pause(timer);
        // lv_task_set_prio(taskStopwatch, LV_TASK_PRIO_OFF);
    }
    SW_IsPause = !SW_IsPause;
}

void StopWatch::SW_Reset()
{
    SW_LastTime = 0;
    SW_CurrentTime = 0;
    SW_IntervalTime = 0;
    SW_IsPause = true;
    HistoryRecCnt = 0;
    // lv_task_set_prio(taskStopwatch, LV_TASK_PRIO_OFF);
    SW_ShowTime(SW_CurrentTime);
     //lv_list_clean(listHistory);
}



void StopWatch::onCustomAttrConfig()
{
    LV_LOG_USER("begin");
    // SetCustomCacheEnable(true);
    // SetCustomLoadAnimType(PageManager::LOAD_ANIM_FADE_ON, 300, lv_anim_path_ease_out);
}

void StopWatch::onViewLoad()
{
    LV_LOG_USER("begin");
    View.Create(_root);
    AttachEvent(_root, onEvent, LV_EVENT_ALL);
    AttachEvent(View.ui.button_reset, onEvent, LV_EVENT_CLICKED);
    AttachEvent(View.ui.button_pause, onEvent, LV_EVENT_CLICKED);
    AttachEvent(View.ui.button_add, onEvent, LV_EVENT_CLICKED);
    timer = lv_timer_create(onTimerUpdate, 1, this);
    lv_timer_pause(timer);
}

void StopWatch::onViewDidLoad()
{
    LV_LOG_USER("begin");
}

void StopWatch::onViewWillAppear()
{
    LV_LOG_USER("begin");

    View.AppearAnimStart(false);

}

void StopWatch::onViewDidAppear()
{
    LV_LOG_USER("begin");
}

void StopWatch::onViewWillDisappear()
{
    LV_LOG_USER("begin");  
    View.AppearAnimStart(true);

}

void StopWatch::onViewDidDisappear()
{
    LV_LOG_USER("begin");
    //lv_timer_del(timer);

}

void StopWatch::onViewUnload()
{
    LV_LOG_USER("begin");
}

void StopWatch::onViewDidUnload()
{
    LV_LOG_USER("begin");
}

void StopWatch::AttachEvent(lv_obj_t* obj, lv_event_cb_t event_cb, lv_event_code_t filter)
{
    //lv_obj_set_user_data(obj, this);
    lv_obj_add_event_cb(obj, event_cb, filter, this);
}

void StopWatch::Update()
{
    SW_CurrentTime = lv_tick_get() - SW_IntervalTime;
    SW_ShowTime(SW_CurrentTime);
    lv_label_set_text_fmt(View.ui.time, "%02d:%02d.%03d", Min, Sec, Msec);
}

void StopWatch::onTimerUpdate(lv_timer_t* timer)
{
    StopWatch* instance = (StopWatch*)timer->user_data;

    instance->Update();

}


void StopWatch::onEvent(lv_event_t* event)
{
    StopWatch* instance = (StopWatch*)lv_event_get_user_data(event);
    LV_ASSERT_NULL(instance);

    lv_obj_t* obj = lv_event_get_current_target_obj(event);
    lv_event_code_t code = lv_event_get_code(event);

    if (code == LV_EVENT_GESTURE)
    {
        LV_LOG_USER("LV_EVENT_GESTURE %d", code);

        if (lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_RIGHT) {
            instance->_Manager->Pop();
        }
    }
    if (code == LV_EVENT_CLICKED)
    {
        LV_LOG_USER("LV_EVENT_CLICKED %d", code);

        if (obj == instance->View.ui.button_reset)
        {
            LV_LOG_USER("BtnReset");

            if (SW_IsPause)
            {
                SW_Reset();
                lv_obj_clean(instance->View.ui.listHistory);
                lv_obj_add_state(instance->View.ui.button_reset, LV_STATE_DISABLED);
                lv_label_set_text_fmt(instance->View.ui.time, "%02d:%02d.%03d", 0, 0, 0);
                HistoryRecCnt = 0;
                LV_LOG_USER("clear history");

            }
        }
        else if (obj == instance->View.ui.button_pause)
        {
            SW_Pause();
            if (SW_IsPause)
            {
                lv_img_set_src(instance->View.ui.button_img, ResourcePool::GetImage("stopwatch_start"));
                lv_obj_clear_state(instance->View.ui.button_reset, LV_STATE_DISABLED);
                lv_timer_pause(instance->timer);

            }
            else
            {
                lv_img_set_src(instance->View.ui.button_img, ResourcePool::GetImage("stopwatch_pause"));
                lv_obj_add_state(instance->View.ui.button_reset, LV_STATE_DISABLED); 
                lv_timer_resume(instance->timer);
            }
            LV_LOG_USER("SW_IsPause: %d", SW_IsPause);

        }
        else if (obj == instance->View.ui.button_add)
        {
            lv_obj_t* list_btn;
            // lv_obj_t* label;
            uint16_t Min = 0, Sec = 0, Msec = 0;

            if (HistoryRecCnt < 10 && !SW_IsPause)
            {
                Min = SW_CurrentTime / 60000;
                Sec = (SW_CurrentTime - (Min * 60000)) / 1000;
                Msec = SW_CurrentTime - (Sec * 1000) - (Min * 60000);

                char buf[64];
                lv_snprintf(buf, sizeof(buf), " %d. %02d:%02d.%03d", HistoryRecCnt + 1, Min, Sec, Msec);

                list_btn = lv_list_add_btn(instance->View.ui.listHistory, NULL, buf);
                // label = lv_obj_get_child(list_btn, NULL);

                // lv_label_set_recolor(label, true);
                lv_obj_scroll_to_view(list_btn, LV_ANIM_ON);
                lv_obj_set_style_text_decor(list_btn, LV_TEXT_DECOR_UNDERLINE, LV_STATE_DEFAULT);
                HistoryRecCnt++;
            }
        }
    }
}
