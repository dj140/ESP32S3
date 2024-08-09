/**
 * @file lv_port_indev_templ.c
 *
 */

/*Copy this file as "lv_port_indev.c" and set this value to "1" to enable content*/
#if 1

/*********************
 *      INCLUDES
 *********************/
#include "lv_port_indev.h"
#include "HAL_Config.h"
#include "esp_log.h"
#include "HAL/HAL.h"

#define TOUCH_MODULES_CST_SELF
#include "TouchLib.h"
extern "C" {

#include "i2c_port.h"

}

TouchLib touch;

static const char *TAG = "CST820";

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/

static void touchpad_init(void);
static void touchpad_read(lv_indev_t * indev, lv_indev_data_t * data);
static bool touchpad_is_pressed(void);
static void touchpad_get_xy(lv_coord_t * x, lv_coord_t * y);

static void button_init(void);
static void button_read(lv_indev_t * indev, lv_indev_data_t * data);
static int8_t button_get_pressed_id(void);
static bool button_is_pressed(uint8_t id);
/**********************
 *  STATIC VARIABLES
 **********************/
lv_indev_t * indev_touchpad;
lv_indev_t * indev_button;

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

void lv_port_indev_init(void)
{
    /**
     * Here you will find example implementation of input devices supported by LittelvGL:
     *  - Touchpad
     *  - Mouse (with cursor support)
     *  - Keypad (supports GUI usage only with key)
     *  - Encoder (supports GUI usage only with: left, right, push)
     *  - Button (external buttons to press points on the screen)
     *
     *  The `..._read()` function are only examples.
     *  You should shape them according to your hardware
     */

    /*------------------
     * Touchpad
     * -----------------*/

    /*Initialize your touchpad if you have*/
    touchpad_init();

    /*Register a touchpad input device*/
    indev_touchpad = lv_indev_create();
    lv_indev_set_type(indev_touchpad, LV_INDEV_TYPE_POINTER);
    lv_indev_set_read_cb(indev_touchpad, touchpad_read);

    /*Initialize your button if you have*/
    button_init();

    /*Register a button input device*/
    indev_button = lv_indev_create();
    lv_indev_set_type(indev_button, LV_INDEV_TYPE_BUTTON);
    lv_indev_set_read_cb(indev_button, button_read);

    
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

/*------------------
 * Touchpad
 * -----------------*/

/*Initialize your touchpad*/
static void touchpad_init(void)
{
    /*Your code comes here*/
    gpio_reset_pin(GPIO_NUM_10);
    gpio_set_direction(GPIO_NUM_10, GPIO_MODE_OUTPUT);
    gpio_set_pull_mode(GPIO_NUM_10, GPIO_PULLUP_PULLDOWN);
    gpio_set_level(GPIO_NUM_10, 0);
    vTaskDelay(pdMS_TO_TICKS(200));
    gpio_set_level(GPIO_NUM_10, 1);
    vTaskDelay(pdMS_TO_TICKS(200));
    touch.begin(CTS820_SLAVE_ADDRESS, -1, twi_read, twi_write);
}

/*Will be called by the library to read the touchpad*/
static void touchpad_read(lv_indev_t * indev, lv_indev_data_t * data)
{
    // static int32_t last_x = 0;
    // static int32_t last_y = 0;

    if(touch.read()) { 
        TP_Point tp_data = touch.getPoint(0);
        data->point.x = tp_data.x;
        data->point.y = tp_data.y;
        data->state = LV_INDEV_STATE_PR;
        // ESP_LOGI(TAG,"x:%d, y:%d\n", tp_data.x, tp_data.y);
    }
    else {
        data->state = LV_INDEV_STATE_REL;
    }


}

/*Return true is the touchpad is pressed*/
static bool touchpad_is_pressed(void)
{
    /*Your code comes here*/

    return false;
}

/*Get the x and y coordinates if the touchpad is pressed*/
static void touchpad_get_xy(lv_coord_t * x, lv_coord_t * y)
{
    /*Your code comes here*/

    // (*x) = 0;
    // (*y) = 0;
}

/*------------------
 * Button
 * -----------------*/

/*Initialize your buttons*/
static void button_init(void)
{
    /*Your code comes here*/
}

/*Will be called by the library to read the button*/
static void button_read(lv_indev_t * indev_drv, lv_indev_data_t * data)
{
    static bool lastState;
    // data->enc_diff = HAL::Encoder_GetDiff();
    
    bool isPush = HAL::Button_GetIsPush();
    
    data->state = isPush ? LV_INDEV_STATE_PRESSED : LV_INDEV_STATE_RELEASED;
    
    if(isPush != lastState)
    {
        // HAL::Buzz_Tone(isPush ? 500 : 700, 20);
        ESP_LOGI(TAG,"state:%d \n", isPush);
        lastState = isPush;
    }
    // static uint8_t last_btn = 0;
    // HAL::Button_Info_t Button;
    // HAL::Button_GetInfo(&Button);
    // /*Get the pressed button's ID*/
    // int8_t btn_act = Button.PRESS;

    // if(btn_act > 0) {
    //     data->state = LV_INDEV_STATE_PRESSED;
    //     ESP_LOGI(TAG,"state:%d \n", btn_act);
    //     last_btn = btn_act;
    // }
    // else {
    //     // ESP_LOGI(TAG,"state:%d \n", btn_act);
    //     data->state = LV_INDEV_STATE_RELEASED;
    // }

    // /*Save the last pressed button's ID*/
    // data->btn_id = last_btn;
}

/*Get ID  (0, 1, 2 ..) of the pressed button*/
static int8_t button_get_pressed_id(void)
{
    uint8_t i;

    /*Check to buttons see which is being pressed (assume there are 2 buttons)*/
    for(i = 0; i < 2; i++) {
        /*Return the pressed button's ID*/
        if(button_is_pressed(i)) {
            return i;
        }
    }

    /*No button pressed*/
    return -1;
}

/*Test if `id` button is pressed or not*/
static bool button_is_pressed(uint8_t id)
{

    /*Your code comes here*/

    return false;
}
/*This dummy typedef exists purely to silence -Wpedantic.*/
typedef int keep_pedantic_happy;
#endif
