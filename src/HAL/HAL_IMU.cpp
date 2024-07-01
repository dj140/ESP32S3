#include "HAL.h"
#include <LSM6DSRSensor.h>

#define DEV_I2C Wire

static HAL::CommitFunc_t CommitFunc = nullptr;
static void* UserData = nullptr;

LSM6DSRSensor AccGyr(&DEV_I2C, LSM6DSR_I2C_ADD_H);
int32_t accelerometer[3]; // Alternatively, use float accelerometer[3]
int32_t gyroscope[3];
uint8_t step[2];

bool HAL::IMU_Init()
{
    Serial.print("IMU: init...");
    // Force INT1 of LSM6DSR low in order to enable I2C
    gpio_reset_pin(GPIO_NUM_38);
    gpio_set_direction(GPIO_NUM_38, GPIO_MODE_OUTPUT);
    gpio_set_pull_mode(GPIO_NUM_38, GPIO_PULLUP_PULLDOWN);
    gpio_set_level(GPIO_NUM_38, 0);

    DEV_I2C.begin(HAL_PIN_I2C_SDA, HAL_PIN_I2C_SCL);
    AccGyr.begin();
    AccGyr.Enable_X();
    AccGyr.Enable_G();
    return 1;
}

void HAL::IMU_SetCommitCallback(CommitFunc_t func, void* userData)
{
    CommitFunc = func;
    UserData = userData;
}

void HAL::IMU_Update()
{
    IMU_Info_t imuInfo;
    // Read accelerometer and gyroscope.

    AccGyr.Get_X_Axes(accelerometer);
    AccGyr.Get_G_Axes(gyroscope);
    imuInfo.ax = accelerometer[0];
    imuInfo.ay = accelerometer[1];
    imuInfo.az = accelerometer[2];
    imuInfo.gx = gyroscope[0];
    imuInfo.gy = gyroscope[1];
    imuInfo.gz = gyroscope[2];

    AccGyr.GetCurrentStep(step);
    imuInfo.steps = (step[1] << 8) | step[0];

    Serial.printf(
        "ax = %d, ay = %d, az = %d, gx = %d, gy = %d, gz = %d, step = %d\r\n",
        imuInfo.ax, imuInfo.ay, imuInfo.az, imuInfo.gx, imuInfo.gy, imuInfo.gz, imuInfo.steps
    );
    if(CommitFunc)
    {
        CommitFunc(&imuInfo, UserData);
    }
}
