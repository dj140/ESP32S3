#include "HAL.h"
#include "App/Version.h"
#include "MillisTaskManager.h"

static MillisTaskManager taskManager;

#if CONFIG_SENSOR_ENABLE

static void HAL_Sensor_Init()
{
//    if(HAL::I2C_Scan() <= 0)
//    {
//        Serial.println("I2C: disable sensors");
//        return;
//    }

//#if CONFIG_SENSOR_IMU_ENABLE
   if(HAL::IMU_Init())
   {
       taskManager.Register(HAL::IMU_Update, 1000);
   }
//#endif

//#if CONFIG_SENSOR_MAG_ENABLE
//    if(HAL::MAG_Init())
//    {
//        taskManager.Register(HAL::MAG_Update, 1000);
//    }
//#endif
}

#endif


void HAL::HAL_Init()
{
//    Serial.begin(115200);
    Serial.println(VERSION_FIRMWARE_NAME);
    Serial.println("Version: " VERSION_SOFTWARE);
    Power_Init();
    Clock_Init();
    HAL_Sensor_Init();
    taskManager.Register(Power_Update, 2000);
}

void HAL::HAL_Update()
{
    taskManager.Running(millis());
}
