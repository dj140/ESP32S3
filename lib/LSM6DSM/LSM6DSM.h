#ifndef __LSM6DSM_H
#define __LSM6DSM_H

#ifdef ARDUINO
#include <Arduino.h>
#include <Wire.h>
#else
#include <stdint.h>
#include <string.h>
#endif
#define LSM6DSM_I2C_ADDRESS    0x6B

class LSM6DSM
{
public:
    LSM6DSM(){}
    ~LSM6DSM(){}
#ifdef ARDUINO
    int begin(TwoWire &port = Wire, uint8_t addr = LSM6DSM_I2C_ADDRESS);
#endif
    bool Init(uint8_t addr = LSM6DSM_I2C_ADDRESS);

    bool IsConnected();
    void ConfigAcc(uint8_t acc_odr, uint8_t acc_scale);
    void ConfigGyr(uint8_t gyr_odr, uint8_t gyr_scale);
    void GetMotion6(
        int16_t* acc_x,
        int16_t* acc_y,
        int16_t* acc_z,
        int16_t* gyr_x,
        int16_t* gyr_y,
        int16_t* gyr_z
    );
    int16_t GetTemperature();
    void SoftReset();
    void EnableEMbeddedFunc();
    void DisableEMbeddedFunc();
    void EnableAWT(int16_t angle, int16_t Delay);
    void DisableAWT();
    void EnableTapDetection();
    void DisableTapDetection();
    void EnablePedometer(uint16_t debounce_time, uint8_t debounce_step);
    uint16_t GetCurrentStep();
    void ResetStepCounter();
    void DisablePedometer();

private:
#ifdef ARDUINO
    TwoWire *_i2cPort;
#endif
    uint8_t Address;
    void WriteReg(uint8_t reg, uint8_t dat);
    uint8_t ReadReg(uint8_t reg);
    void ReadRegs(uint8_t reg, uint8_t* buf, uint16_t len);
    void SetRegisterBits(uint8_t reg, uint8_t data, bool setBits);
};

#endif
