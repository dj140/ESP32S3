#include "Image_Player.h"
#include "stdio.h"
#include "esp_lcd_sh8601.h"
#include "freertos/FreeRTOS.h"

using namespace Page;

uint32_t counter = 0;
uint8_t  ubNumberOfFiles = 50;
uint8_t str[30];
#define MAX_BMP_FILES     10
#define MAX_BMP_FILE_NAME 10
char* pDirectoryFiles[MAX_BMP_FILES];
uint8_t num = 1;

esp_lcd_panel_handle_t panel_handle = NULL;
lv_display_t * disp;

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
    AttachEvent(View.ui.image);
    // AttachEvent(View.ui.lottie);

    disp = lv_disp_get_default();
    panel_handle = (esp_lcd_panel_handle_t)lv_display_get_user_data(disp);
}

void Image_Player::onViewDidLoad()
{
    LV_LOG_USER("begin");
}


void Image_Player::onViewWillAppear()
{
    LV_LOG_USER("begin");
    timer = lv_timer_create(onTimerUpdate, 4000, this);
}

void Image_Player::onViewDidAppear()
{
    LV_LOG_USER("begin");
}

void Image_Player::onViewWillDisappear()
{
    LV_LOG_USER("begin");
}

void Image_Player::onViewDidDisappear()
{
    LV_LOG_USER("begin");
    lv_timer_del(timer);
    panel_sh8601_disp_set_Brightness(panel_handle, 0x80);
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
    if (num > ubNumberOfFiles)
    {
        num = 0;
    }
    sprintf((char*)str, "A:sdcard/image/888/UI_%02d.bin",num); 
    printf("%d: %s\r\n", num, (char*)str);
    num++;
    lv_img_set_src(View.ui.image, (char*)str);
    for(uint8_t i = 0; i < 255; i++)
    {
        //TRANSP -> Bright
        panel_sh8601_disp_set_Brightness(panel_handle, i);
        vTaskDelay(pdMS_TO_TICKS(10));

    }
    for(uint8_t i = 255; i > 0; i--)
    {
        //Bright -> TRANSP
        panel_sh8601_disp_set_Brightness(panel_handle, i);
        vTaskDelay(pdMS_TO_TICKS(15));
    }
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
        instance->_Manager->BackHome();
    }

    if (code == LV_EVENT_LONG_PRESSED)
    {    
        instance->_Manager->BackHome();
    }

}
