#include "HAL.h"
#include "LSM6DSM.h"

static LSM6DSM imu;
static HAL::CommitFunc_t CommitFunc = nullptr;
static void* UserData = nullptr;

bool HAL::IMU_Init()
{
    Serial.print("IMU: init...");
    // Force INT1 of LSM6DSR low in order to enable I2C
    pinMode(38, OUTPUT);

    digitalWrite(38, LOW);

    Wire.begin(HAL_PIN_I2C_SDA, HAL_PIN_I2C_SCL);
    imu.begin(Wire, LSM6DSM_I2C_ADDRESS);
    bool success = imu.Init();

    Serial.println(success ? "success" : "failed");

    return success;
}

void HAL::IMU_SetCommitCallback(CommitFunc_t func, void* userData)
{
    CommitFunc = func;
    UserData = userData;
}

void HAL::IMU_Update()
{
    IMU_Info_t imuInfo;
    imu.GetMotion6(
        &imuInfo.ax, &imuInfo.ay, &imuInfo.az,
        &imuInfo.gx, &imuInfo.gy, &imuInfo.gz
    );
   Serial.printf(
       "ax = %d, ay = %d, az = %d, gx = %d, gy = %d, gz = %d\r\n",
       imuInfo.ax, imuInfo.ay, imuInfo.az, imuInfo.gx, imuInfo.gy, imuInfo.gz
   );

    imuInfo.steps = imu.GetCurrentStep();

    if(CommitFunc)
    {
        CommitFunc(&imuInfo, UserData);
    }
}
