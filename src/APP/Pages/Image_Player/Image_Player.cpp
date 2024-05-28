#include "Image_Player.h"
#include "stdio.h"
using namespace Page;

Image_Player::Image_Player()
    : timer(nullptr)
{
}

Image_Player::~Image_Player()
{

}

void Image_Player::onCustomAttrConfig()
{
    LV_LOG_USER("begin");
    // SetCustomCacheEnable(true);
    // SetCustomLoadAnimType(PageManager::LOAD_ANIM_OVER_BOTTOM, 1000, lv_anim_path_bounce);
}

void Image_Player::onViewLoad()
{
    printf("Image_Player begin \n");
    View.Create(_root);
    AttachEvent(_root);
    AttachEvent(View.ui.cont);
    AttachEvent(View.ui.lottie);

}

void Image_Player::onViewDidLoad()
{
    LV_LOG_USER("begin");
}


void Image_Player::onViewWillAppear()
{
    LV_LOG_USER("begin");
    timer = lv_timer_create(onTimerUpdate, 10, this);
}

void Image_Player::onViewDidAppear()
{
    LV_LOG_USER("begin");
    //  xTaskCreate(show_video_task, "video task", 8196, NULL, 4, &Task1Task_Handler);
}

void Image_Player::onViewWillDisappear()
{
    LV_LOG_USER("begin");
}

void Image_Player::onViewDidDisappear()
{
    LV_LOG_USER("begin");
    lv_timer_del(timer);
}

void Image_Player::onViewUnload()
{
    LV_LOG_USER("begin");
}

void Image_Player::onViewDidUnload()
{
    LV_LOG_USER("begin");
}

void Image_Player::AttachEvent(lv_obj_t* obj)
{
    lv_obj_set_user_data(obj, this);
    lv_obj_add_event_cb(obj, onEvent, LV_EVENT_ALL, this);
}

void Image_Player::Update()
{

}

void Image_Player::onTimerUpdate(lv_timer_t* timer)
{
    Image_Player* instance = (Image_Player*)timer->user_data;

    instance->Update();
}

void Image_Player::onEvent(lv_event_t* event)
{
    Image_Player* instance = (Image_Player*)lv_event_get_user_data(event);
    LV_ASSERT_NULL(instance);

    lv_obj_t* obj = lv_event_get_current_target_obj(event);
    lv_event_code_t code = lv_event_get_code(event);
    // printf("lv_event_code_t: %d ", code);

    if (code == LV_EVENT_PRESSED)
    {    

        instance->_Manager->Pop();
    }

//     if (code == LV_EVENT_GESTURE)
//     {
// //      LV_LOG_USER("LV_EVENT_GESTURE %d", code);

//       if (lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_LEFT) {
//           instance->_Manager->Push("Pages/Dialplate");
//       }
//     }

}
