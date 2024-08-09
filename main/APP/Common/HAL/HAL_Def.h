#ifndef __HAL_DEF_H
#define __HAL_DEF_H

#include <stdint.h>
#include <driver/i2c.h>

namespace HAL
{

/* Clock */
typedef struct
{
    uint16_t year;
    uint8_t month;
    uint8_t day;
    uint8_t week;
    uint8_t hour;
    uint8_t minute;
    uint8_t second;
    uint16_t millisecond;
} Clock_Info_t;

/* GPS */
typedef struct
{
    double longitude;
    double latitude;
    float altitude;
    float course;
    float speed;
    int16_t satellites;
    bool isVaild;
    Clock_Info_t clock;
} GPS_Info_t;

/* MAG */
typedef struct
{
    int16_t x;
    int16_t y;
    int16_t z;
} MAG_Info_t;

/* IMU */
typedef struct
{
    int16_t ax;
    int16_t ay;
    int16_t az;
    int16_t gx;
    int16_t gy;
    int16_t gz;
    int16_t steps;
} IMU_Info_t;

/* Button */
typedef struct
{
    bool PRESS;
    bool RELEASED;
} Button_Info_t;

/* SportStatus */
typedef struct
{
    uint32_t lastTick;

    float weight;

    float speedKph;
    float speedMaxKph;
    float speedAvgKph;

    union
    {
        uint32_t totalTimeUINT32[2];
        uint64_t totalTime;
    };

    float totalDistance;

    union
    {
        uint32_t singleTimeUINT32[2];
        uint64_t singleTime;
    };

    float singleDistance;
    float singleCalorie;
    
} SportStatus_Info_t;

/* Power */
typedef struct
{
    uint16_t voltage;
    uint8_t Percentage;
    bool isCharging;
} Power_Info_t;

// typedef struct{
//     int pin_scl     = -1;
//     int pin_sda     = -1;
//     int pin_rst     = -1;
//     int pin_int     = -1;
//     bool pull_up_en = true;

//     i2c_port_t i2c_port = 0;
//     uint32_t clk_speed = 100000;

//     uint8_t dev_addr = 0x38;
// }TP_Config;


// typedef struct{
//     uint8_t event = 0;
//     uint8_t id = 0;
//     int x = -1;
//     int y = -1;
// }TouchPoint_t;

}



#endif
