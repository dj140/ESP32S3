#include "HAL.h"
#include "App/Version.h"
#include "MillisTaskManager.h"
#include "esp_timer.h"

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
//    if(HAL::IMU_Init())
//    {
//        taskManager.Register(HAL::IMU_Update, 1000);
//    }
//#endif

//#if CONFIG_SENSOR_MAG_ENABLE
//    if(HAL::MAG_Init())
//    {
//        taskManager.Register(HAL::MAG_Update, 1000);
//    }
//#endif
}

#endif

static void HAL_TimerInterrputUpdate()
{
//    HAL::Power_Update();
//    HAL::Encoder_Update();
//    HAL::Audio_Update();
}

void HAL::HAL_Init()
{
    Power_Init();
    Clock_Init();
    taskManager.Register(Power_Update, 1500);
}

void HAL::HAL_Update()
{
    taskManager.Running((esp_timer_get_time() / 1000LL));
}
