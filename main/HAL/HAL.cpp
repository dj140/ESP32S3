#include "HAL.h"
#include "App/Version.h"
#include "MillisTaskManager.h"
#include "esp_timer.h"
#include "i2c_port.h"

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
    ESP_ERROR_CHECK(i2c_master_init());
    I2C_Scan();
    Power_Init();
    Clock_Init();
    SD_Init();
    Button_Init();
    taskManager.Register(Power_Update, 500);
    taskManager.Register(Button_Update, 100);
}

void HAL::HAL_Update()
{
    taskManager.Running((esp_timer_get_time() / 1000LL));
}
