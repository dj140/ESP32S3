/*
 * MIT License
 * Copyright (c) 2021 _VIFEXTech
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#ifndef __HAL_CONFIG_H
#define __HAL_CONFIG_H

/*=========================
   Hardware Configuration
 *=========================*/

/* Board */
#define CONFIG_Watch_Board        1

#if CONFIG_Watch_Board

#define AMOLED_HOR_RES       410
#define AMOLED_VER_RES       502

/* AMOLED */
#define AMOLED_RESET_PIN      GPIO_NUM_4
#define AMOLED_VCI_EN_PIN     GPIO_NUM_3
#define AMOLED_TE_PIN         GPIO_NUM_7
#define AMOLED_CS_PIN         GPIO_NUM_9
#define AMOLED_CLK_PIN        GPIO_NUM_14
#define AMOLED_D0_PIN         GPIO_NUM_11
#define AMOLED_D1_PIN         GPIO_NUM_12
#define AMOLED_D2_PIN         GPIO_NUM_2
#define AMOLED_D3_PIN         GPIO_NUM_13  

/* I2C peripheral */
#define HAL_PIN_I2C_PORT    0
#define HAL_PIN_I2C_SCL     GPIO_NUM_8
#define HAL_PIN_I2C_SDA     GPIO_NUM_6

/* Touch pad */
#define HAL_PIN_TP_RST      GPIO_NUM_10
#define HAL_PIN_TP_INTR     GPIO_NUM_5

/* SD CARD */
#define CONFIG_SD_CS               GPIO_NUM_11
#define CONFIG_SD_CLK              GPIO_NUM_12
#define CONFIG_SD_D0               GPIO_NUM_13
#define CONFIG_SD_D1               GPIO_NUM_14
#define CONFIG_SD_D2               GPIO_NUM_9
#define CONFIG_SD_D3               GPIO_NUM_10

#endif

#if CONFIG_Demo_Board

#define AMOLED_HOR_RES       410
#define AMOLED_VER_RES       494

/* AMOLED */
#define AMOLED_RESET_PIN      GPIO_NUM_2
#define AMOLED_VCI_EN_PIN     GPIO_NUM_48
#define AMOLED_TE_PIN         GPIO_NUM_1
#define AMOLED_CS_PIN         GPIO_NUM_4
#define AMOLED_CLK_PIN        GPIO_NUM_5
#define AMOLED_D0_PIN         GPIO_NUM_6
#define AMOLED_D1_PIN         GPIO_NUM_7
#define AMOLED_D2_PIN         GPIO_NUM_15
#define AMOLED_D3_PIN         GPIO_NUM_16

/* I2C peripheral */
#define HAL_PIN_I2C_PORT    0
#define HAL_PIN_I2C_SCL     17
#define HAL_PIN_I2C_SDA     18

/* Touch pad */
#define HAL_PIN_TP_RST      10
#define HAL_PIN_TP_INTR     5

/* SD CARD */
#define CONFIG_SD_CS               GPIO_NUM_11
#define CONFIG_SD_CLK              GPIO_NUM_12
#define CONFIG_SD_D0               GPIO_NUM_13
#define CONFIG_SD_D1               GPIO_NUM_14
#define CONFIG_SD_D2               GPIO_NUM_9
#define CONFIG_SD_D3               GPIO_NUM_10

#endif


/* Battery */
#define CONFIG_BAT_DET_PIN          PA1
#define CONFIG_BAT_CHG_DET_PIN      PA11

/* Buzzer */
#define CONFIG_BUZZ_PIN             PA0  // TIM2

/* GPS */
#define CONFIG_GPS_SERIAL           Serial2
#define CONFIG_GPS_USE_TRANSPARENT  0
#define CONFIG_GPS_BUF_OVERLOAD_CHK 0
#define CONFIG_GPS_TX_PIN           PA3
#define CONFIG_GPS_RX_PIN           PA2

/* IMU */
#define CONFIG_IMU_INT1_PIN         PB10
#define CONFIG_IMU_INT2_PIN         PB11

#endif
