#include "HAL/HAL.h"
#include "esp_log.h"
extern "C" {
#include "i2c_port.h"
}
#include "axp20x.hpp"

static const char *TAG = "AXP202";


static uint16_t Power_ADC_GetValue()
{
    // uint16_t retval = 0;
    // if(adc_flag_get(BATT_ADC, ADC_OCCE_FLAG))
    // {
    //     retval = adc_ordinary_conversion_data_get(BATT_ADC);
    // }
    return 0;
}

static void Power_ADC_Update()
{

}

void HAL::Power_Init()
{

 if (axp.begin(twi_read, twi_write, AXP202_SLAVE_ADDRESS))
    {
        ESP_LOGE(TAG, "Error init axp20x !!!");
        while (1);
    }
    ESP_LOGI(TAG, "Success init axp20x !!!");

    axp.adc1Enable(AXP202_VBUS_VOL_ADC1 |
                   AXP202_VBUS_CUR_ADC1 |
                   AXP202_BATT_CUR_ADC1 |
                   AXP202_BATT_VOL_ADC1 |
                   AXP202_TS_PIN_ADC1,
                   true);
    // 两个警告等级（类似于手机20%一提醒，10%一提醒）和一个关机电压（类似于手机3%关机，实际显示0%）
    axp.setVWarningLevel1(3150);
    axp.setVWarningLevel2(3000);
    axp.setPowerDownVoltage(2600);
    uint16_t level1 = axp.getVWarningLevel1();
    uint16_t level2 = axp.getVWarningLevel2();
    uint16_t level3 = axp.getPowerDownVoltage();
    ESP_LOGI(TAG, "getVWarningLevel1:%u mV", level1 );
    ESP_LOGI(TAG, "getVWarningLevel2:%u mV", level2);
    ESP_LOGI(TAG, "getPowerDonwLevel3:%u mV", level3);

    axp.setPowerOutPut(AXP202_DCDC3, AXP202_ON); // main power
    axp.setPowerOutPut(AXP202_DCDC2, AXP202_ON);

    axp.setLDO2Voltage(3300); // AMOLED_VDDI
    axp.setPowerOutPut(AXP202_LDO2, AXP202_ON);

    axp.setLDO4Voltage(AXP202_LDO4_3300MV); // TP_VDDI
    axp.setPowerOutPut(AXP202_LDO4, AXP202_ON);

    // axp.setLDO3Voltage(3500); // 触觉驱动器供电
    // axp.setPowerOutPut(AXP202_LDO3, AXP202_ON);

    axp.setPowerOutPut(AXP202_EXTEN, AXP202_ON);
    axp.EnableCoulombcounter();

    if (axp.isDCDC2Enable())
    {
        ESP_LOGI(TAG, "DC2: %u mV", axp.getDCDC2Voltage());
    }
    else
    {
        ESP_LOGI(TAG, "DC2: DISABLE");
    }

    if (axp.isDCDC3Enable())
    {
        ESP_LOGI(TAG, "DC3: %u mV", axp.getDCDC3Voltage());
    }
    else
    {
        ESP_LOGI(TAG, "DC3: DISABLE");
    }

    if (axp.isLDO2Enable())
    {
        ESP_LOGI(TAG, "LDO2: %u mV", axp.getLDO2Voltage());
    }
    else
    {
        ESP_LOGI(TAG, "LDO2: DISABLE");
    }

    if (axp.isLDO3Enable())
    {
        ESP_LOGI(TAG, "LDO3: %u mV", axp.getLDO3Voltage());
    }
    else
    {
        ESP_LOGI(TAG, "LDO3: DISABLE");
    }

    if (axp.isLDO4Enable())
    {
        ESP_LOGI(TAG, "LDO4: %u mV", axp.getLDO4Voltage());
    }
    else
    {
        ESP_LOGI(TAG, "LDO4: DISABLE");
    }

    if (axp.isExtenEnable())
    {
        ESP_LOGI(TAG, "Exten: ENABLE");
    }
    else
    {
        ESP_LOGI(TAG, "Exten: DISABLE");
    }

    if (axp.isBatteryConnect())
    {
        ESP_LOGI(TAG, "BatteryConnect!!");
    }
    // When the chip is axp192 / 173, the allowed values are 0 ~ 15,
    // corresponding to the axp1xx_charge_current_t enumeration
    //  axp.setChargeControlCur(AXP1XX_CHARGE_CUR_550MA);

    // axp202 allows maximum charging current of 1800mA, minimum 300mA
    axp.setChargeControlCur(300);

    // axp.setChgLEDContrl(AXP20X_LED_CHARGING_CTL);   // CHGLED由充电状态控制
    // axp.setChgLEDChargingMode(AXP20X_LED_LIGHT_WHEN_CHARGING);  // CHGLED由充电状态控制模式
    // axp.setChgLEDContrl(AXP20X_LED_REG_32H_CTL); // CHGLED由REG32H控制
    // axp.setChgLEDMode(AXP20X_LED_BLINK_4HZ);  // CHGLED由REG32H控制模式

    ESP_LOGI(TAG, "setChargeControlCur:%u", axp.getChargeControlCur());
    ESP_LOGI(TAG, "getCoreTemp:%.2f C", axp.getTemp());

    // Backup battery charge control
    // Backup Battery model: KTS CR2032W 3.0V 220mAh
    // axp.setBackupChargeControl(AXP202_ON);
    // axp.setBackupChargeVoltage(AXP202_BACKUP_VOLTAGE_3V0);
    // axp.setBackupChargeCurrent(AXP202_BACKUP_CURRENT_100UA);

    // axp.setGPIOMode(AXP_GPIO_0, AXP_IO_OUTPUT_HIGH_MODE); // 打开主板指示灯PIO0
    // axp.gpioWrite(AXP_GPIO_0, 1);
}


void HAL::Power_Update()
{
    ESP_LOGI(TAG, "VbusCurrent:%.2f mV", axp.getVbusCurrent());
    ESP_LOGI(TAG, "BattChargeCurrent:%.2f mV", axp.getBattChargeCurrent());
    ESP_LOGI(TAG, "BattDischargeCurrent:%.2f mV", axp.getBattDischargeCurrent());
    ESP_LOGI(TAG, "BattPercentage: %d %%", axp.getBattPercentage());
    ESP_LOGI(TAG, "BattVoltage:%.2f mV", axp.getBattVoltage());
    ESP_LOGI(TAG, "TSVoltage:%.2f mV", axp.getTSTemp());
    ESP_LOGI(TAG, "CoreTemp:%.2f C", axp.getTemp());
    ESP_LOGI(TAG, "CoulombData:%.2f mAh", axp.getCoulombData());
} 

void HAL::Power_GetInfo(Power_Info_t* info)
{
    info->voltage = axp.getBattVoltage();
    info->Percentage = axp.getBattPercentage();
    info->isCharging = axp.isChargeing();
}

