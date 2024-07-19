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


/**********************
 *  STATIC VARIABLES
 **********************/
lv_indev_t * indev_touchpad;

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
    static int32_t last_x = 0;
    static int32_t last_y = 0;

    if(touch.read()) { 
        TP_Point tp_data = touch.getPoint(0);
        data->point.x = tp_data.x;
        data->point.y = tp_data.y;
        data->state = LV_INDEV_STATE_PR;
        ESP_LOGI(TAG,"x:%d, y:%d\n", tp_data.x, tp_data.y);
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



/*This dummy typedef exists purely to silence -Wpedantic.*/
typedef int keep_pedantic_happy;
#endif
