#include "HAL/HAL.h"
#include "axp20x.h"
// AXP20X_Class axp;
const uint8_t slave_address = AXP202_SLAVE_ADDRESS;          //use axp202

void printPowerChannel()
{
    Serial.print("DC2:");
    Serial.print(axp.isDCDC2Enable() ? String(axp.getDCDC2Voltage()) + " mv" : "DISABLE");
    Serial.print("  ");

    Serial.print("DC3:");
    Serial.print(axp.isDCDC3Enable() ? String(axp.getDCDC3Voltage()) + " mv" : "DISABLE");
    Serial.print("  ");

    Serial.print("LDO2:");
    Serial.print(axp.isLDO2Enable() ? String(axp.getLDO2Voltage()) + " mv" : "DISABLE");
    Serial.print("  ");

    Serial.print("LDO3:");
    Serial.print(axp.isLDO3Enable() ? String(axp.getLDO3Voltage()) + " mv" : "DISABLE");
    Serial.print("  ");

    Serial.print("LDO4:");
    Serial.print(axp.isLDO4Enable() ? String(axp.getLDO4Voltage()) + " mv" : "DISABLE");
    Serial.print("  ");

    Serial.print("Exten:");
    Serial.print(axp.isExtenEnable() ? "ENABLE" : "DISABLE");
    Serial.print("\r\n");
}

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
    Wire.begin(HAL_PIN_I2C_SDA, HAL_PIN_I2C_SCL);

    Serial.println("AXP202 PMU Init");

    /* Initialise the pmu */
    int ret = axp.begin(Wire, slave_address);
    if (ret) {
        /* There was a problem detecting the AXP202/192 ... check your connections */
        Serial.println("Ooops, AXP202 power chip detected ... Check your wiring!");
        while (1);
    }

    /*Enable AXP ADC function*/
    axp.adc1Enable(AXP202_VBUS_VOL_ADC1 |
                   AXP202_VBUS_CUR_ADC1 |
                   AXP202_BATT_CUR_ADC1 |
                   AXP202_BATT_VOL_ADC1,
                   true);

    Serial.println("");
    axp.setShutdownTime(AXP_POWER_OFF_TIME_4S);
    axp.setVWarningLevel1(3200);
    axp.setVWarningLevel2(3100);
    axp.setChargingTargetVoltage(AXP202_TARGET_VOL_4_2V);
    axp.ClearCoulombcounter();
    axp.EnableCoulombcounter();
    uint16_t level1 = axp.getVWarningLevel1();
    uint16_t level2 = axp.getVWarningLevel2();
    Serial.printf("getVWarningLevel1:%u mV \n", level1 );
    Serial.printf("getVWarningLevel2:%u mV \n", level2);
    axp.setPowerDownVoltage(3000);
    axp.setChargeControlCur(500);
    axp.setPowerOutPut(AXP202_DCDC2, AXP202_OFF);
    axp.setPowerOutPut(AXP202_LDO3,  AXP202_OFF);
    axp.setPowerOutPut(AXP202_EXTEN, AXP202_OFF);
    axp.setDCDC3Voltage(3300);
    axp.setLDO2Voltage(1800);
    axp.setLDO4Voltage(AXP202_LDO4_3300MV);
    printPowerChannel();
}


void HAL::Power_Update()
{
    Serial.println("=========================");
    Serial.print("VBUS STATUS: ");
    // You can use isVBUSPlug to check whether the USB connection is normal
    if (axp.isVBUSPlug()) {

        Serial.println("CONNECT");

        // Get USB voltage
        Serial.print("VBUS Volate:");
        Serial.print(axp.getVbusVoltage());
        Serial.println(" mV");

        // Get USB current
        Serial.print("VBUS Current: ");
        Serial.print(axp.getVbusCurrent());
        Serial.println(" mA");

    } else {
        Serial.println("DISCONNECT");
    }

    Serial.println("=========================");

    Serial.print("BATTERY STATUS: ");

    // You can use isBatteryConnect() to check whether the battery is connected properly
    if (axp.isBatteryConnect()) {

        Serial.println("CONNECT");

        // Get battery voltage
        Serial.print("BAT Volate:");
        Serial.print(axp.getBattVoltage());
        Serial.println(" mV");

        // To display the charging status, you must first discharge the battery,
        // and it is impossible to read the full charge when it is fully charged
        if (axp.isChargeing()) {
            Serial.print("Charge:");
            Serial.print(axp.getBattChargeCurrent());
            Serial.println(" mA");
        } else {
            // Show current consumption
            Serial.print("Discharge:");
            Serial.print(axp.getBattDischargeCurrent());
            Serial.println(" mA");

            /*getBattPercentage just only support axp202 */
            if (slave_address == AXP202_SLAVE_ADDRESS) {
                Serial.print("Per: ");
                Serial.print(axp.getBattPercentage());
                Serial.println(" %");
            }
        }
    } else {
        Serial.println("DISCONNECT");
    }
    Serial.println();
    Serial.println();
    // axp.debugCharging();
}

void HAL::Power_GetInfo(Power_Info_t* info)
{

}

