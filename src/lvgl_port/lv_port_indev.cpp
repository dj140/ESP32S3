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
#include "HAL/HAL.h"
#include "Arduino.h"

#define TOUCH_MODULES_CST_SELF

#include "TouchLib.h"
#include "Wire.h"

TouchLib touch(Wire, HAL_PIN_I2C_SDA, HAL_PIN_I2C_SCL, CTS820_SLAVE_ADDRESS);

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
static void touchpad_get_xy(int32_t * x, int32_t * y);


/**********************
 *  STATIC VARIABLES
 **********************/
lv_indev_t * indev_touchpad;



struct TouchPoint_t {
    uint8_t event = 0;
    uint8_t id = 0;
    int x = -1;
    int y = -1;
};


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
    Serial.println("TP_init start");
    pinMode(HAL_PIN_TP_RST, OUTPUT);
    digitalWrite(HAL_PIN_TP_RST, 0);
    delay(200);
    digitalWrite(HAL_PIN_TP_RST, 1);
    delay(200);
    Wire.begin(HAL_PIN_I2C_SDA, HAL_PIN_I2C_SCL);
    touch.init();
}

/*Will be called by the library to read the touchpad*/
static void touchpad_read(lv_indev_t * indev_drv, lv_indev_data_t * data)
{
    static int32_t last_x = 0;
    static int32_t last_y = 0;
    /*Your code comes here*/

    /*Save the pressed coordinates and the state*/
    if(touch.read()) { 
        TP_Point tp_data = touch.getPoint(0);
        data->point.x = tp_data.x;
        data->point.y = tp_data.y;
        data->state = LV_INDEV_STATE_PR;
            //   Serial.printf("x:%d, y:%d \n", tp_data.x, tp_data.y);
    }
    else {
        data->state = LV_INDEV_STATE_REL;
    }
    // /*Set the last pressed coordinates*/
    // data->point.x = last_x;
    // data->point.y = last_y;
}

/*Return true is the touchpad is pressed*/
static bool touchpad_is_pressed(void)
{
    /*Your code comes here*/
    // if(FT3168.isTouched())
    // {
    //     Serial.println("touch detect");
    //     return true;
    // }
    return false;
}

/*Get the x and y coordinates if the touchpad is pressed*/
static void touchpad_get_xy(int32_t * x, int32_t * y)
{
    // TouchPoint_t tp_data;
    // /*Your code comes here*/
    // FT3168.getTouchRaw(tp_data);
    // (*x) = tp_data.x;
    // (*y) = tp_data.y;

}



/*This dummy typedef exists purely to silence -Wpedantic.*/
typedef int keep_pedantic_happy;
#endif
