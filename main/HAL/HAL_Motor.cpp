#include "HAL.h"
#include "Adafruit_DRV2605.h"
#include <stdio.h>
#include "esp_log.h"
#include "driver/i2c.h"
#include "i2c_port.h"

static const char *TAG = "DRV2605";


Adafruit_DRV2605 Motor;

void create_touchVibrates_func(uint8_t effect)
{
    // set the effect to play
    // printf("effect: ");
    // Motor.effect_name(effect);
    // printf("\n");
    Motor.setWaveform(0, effect); // play effect
    Motor.setWaveform(1, 0);      // end waveform
    // play the effect!
    Motor.go();
}
void HAL::Motor_Init()
{
    ESP_LOGI(TAG, "Motor: init...");
    // Serial.print("Motor: init...");
    // Force INT1 of LSM6DSR low in order to enable I2C
    gpio_reset_pin(GPIO_NUM_47);
    gpio_set_direction(GPIO_NUM_47, GPIO_MODE_OUTPUT);
    gpio_set_pull_mode(GPIO_NUM_47, GPIO_PULLUP_PULLDOWN);
    gpio_set_level(GPIO_NUM_47, 1);
    if (Motor.begin(twi_read, twi_write, DRV2605_ADDR)) //
    {
        ESP_LOGE(TAG, "Error init drv2605 !!!");
        // Serial.print("Error init drv2605 !!!");
    }
    ESP_LOGI(TAG, "Success init drv2605 !!!");
    // Serial.print("Success init drv2605 !!!");

    // Use LRA (Linear Resonance Actuator) mode.
    Motor.useLRA();
    // Motor.useERM();

    // Select the waveform Library to use
    // 0 = Empty, 1-5 are ERM, 6 is LRA.
    Motor.selectLibrary(6);

    // I2C trigger by sending 'go' command
    // default, internal trigger when sending GO command
    Motor.setMode(DRV2605_MODE_INTTRIG);

    // 开机振动
    create_touchVibrates_func(14);

}



void HAL::Motor_Update()
{
    create_touchVibrates_func(15);
}
