#include "HAL.h"
#include "Adafruit_DRV2605.h"
#include <stdio.h>
#include "esp_log.h"
#include "driver/i2c.h"
#include "sdkconfig.h"

#define I2C_MASTER_SCL_IO           10//CONFIG_I2C_MASTER_SCL                   /*!< gpio number for I2C master clock */
#define I2C_MASTER_SDA_IO           11//CONFIG_I2C_MASTER_SDA                   /*!< gpio number for I2C master data  */
#define I2C_MASTER_NUM              I2C_NUM_0//I2C_NUMBER(I2C_NUM_0)  /*!< I2C port number for master dev */
#define I2C_MASTER_FREQ_HZ          400*1000             /*!< I2C master clock frequency */
#define I2C_MASTER_TX_BUF_DISABLE   0                                       /*!< I2C master doesn't need buffer */
#define I2C_MASTER_RX_BUF_DISABLE   0                                       /*!< I2C master doesn't need buffer */

#define WRITE_BIT                   I2C_MASTER_WRITE                        /*!< I2C master write */
#define READ_BIT                    I2C_MASTER_READ                         /*!< I2C master read */
#define ACK_CHECK_EN                0x1                                     /*!< I2C master will check ack from slave*/
#define ACK_CHECK_DIS               0x0                                     /*!< I2C master will not check ack from slave */
#define ACK_VAL                     (i2c_ack_type_t)0x0                     /*!< I2C ack value */
#define NACK_VAL                    (i2c_ack_type_t)0x1                     /*!< I2C nack value */

esp_err_t i2c_master_init(void);
uint32_t twi_read(uint8_t dev_addr, uint8_t reg_addr, uint8_t *data, uint8_t len);   //! 类型错误：uint16_t
uint32_t twi_write(uint8_t dev_addr, uint8_t reg_addr, uint8_t *data, uint8_t len);  //! 类型错误：uint16_t

Adafruit_DRV2605 Motor;

/**
 * @brief i2c master initialization
 */
esp_err_t i2c_master_init(void)
{
    int i2c_master_port = I2C_MASTER_NUM;
    static i2c_config_t conf;   //! i2c_config_t conf;
    /* 
     * 报错原因：因为 conf 是函数内的局部变量，导致 conf 有成员未初始化，会从 stack 里分配内存空间，值未知
     * 解决方法：将 conf 声明为静态局部变量解决
     */
    conf.mode = I2C_MODE_MASTER;
    conf.sda_io_num = I2C_MASTER_SDA_IO;
    conf.sda_pullup_en = GPIO_PULLUP_ENABLE;
    conf.scl_io_num = I2C_MASTER_SCL_IO;
    conf.scl_pullup_en = GPIO_PULLUP_ENABLE;
    conf.master.clk_speed = I2C_MASTER_FREQ_HZ;
    i2c_param_config(i2c_master_port, &conf);
    return i2c_driver_install(i2c_master_port, conf.mode, I2C_MASTER_RX_BUF_DISABLE, I2C_MASTER_TX_BUF_DISABLE, 0);
}

/**
 * @brief apx library i2c read callback
 * 
 */
uint32_t twi_read(uint8_t dev_addr, uint8_t reg_addr, uint8_t *data, uint8_t len)   //! 类型错误：uint16_t
{
    if (len == 0) {
        return ESP_OK;
    }
    if (data == NULL) {
        return ESP_FAIL;
    }
    i2c_cmd_handle_t cmd;

    cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (dev_addr << 1) | WRITE_BIT, ACK_CHECK_EN);
    i2c_master_write_byte(cmd, reg_addr, ACK_CHECK_EN);
    i2c_master_stop(cmd);
    esp_err_t ret =  i2c_master_cmd_begin(I2C_MASTER_NUM, cmd, 1000 / portTICK_PERIOD_MS);
    i2c_cmd_link_delete(cmd);
    if (ret != ESP_OK) {
        return ESP_FAIL;
    }
    cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (dev_addr << 1) | READ_BIT, ACK_CHECK_EN);
    if (len > 1) {
        i2c_master_read(cmd, data, len - 1, ACK_VAL);
    }
    i2c_master_read_byte(cmd, &data[len - 1], NACK_VAL);
    i2c_master_stop(cmd);
    ret = i2c_master_cmd_begin(I2C_MASTER_NUM, cmd, 1000 / portTICK_PERIOD_MS);
    i2c_cmd_link_delete(cmd);
    return ret;
}

/**
 * @brief apx library i2c write callback
 */
uint32_t twi_write(uint8_t dev_addr, uint8_t reg_addr, uint8_t *data, uint8_t len)  //! 类型错误：uint16_t
{
    if (data == NULL) {
        return ESP_FAIL;
    }
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (dev_addr << 1) | WRITE_BIT, ACK_CHECK_EN);
    i2c_master_write_byte(cmd, reg_addr, ACK_CHECK_EN);
    i2c_master_write(cmd, data, len, ACK_CHECK_EN);
    i2c_master_stop(cmd);
    esp_err_t ret = i2c_master_cmd_begin(I2C_MASTER_NUM, cmd, 1000 / portTICK_PERIOD_MS);
    i2c_cmd_link_delete(cmd);
    return ret;
}
void create_touchVibrates_func(uint8_t effect)
{
    // set the effect to play
    // printf("effect: ");
    // Motor.effect_name(effect);
    // printf("\n");
    Motor.setWaveform(0, effect); // play effect
    Motor.setWaveform(1, 0);      // end waveform
    // play the effect!
    Motor.go();
}
void HAL::Motor_Init()
{
    Serial.print("Motor: init...");
    // Force INT1 of LSM6DSR low in order to enable I2C
    gpio_reset_pin(GPIO_NUM_47);
    gpio_set_direction(GPIO_NUM_47, GPIO_MODE_OUTPUT);
    gpio_set_pull_mode(GPIO_NUM_47, GPIO_PULLUP_PULLDOWN);
    gpio_set_level(GPIO_NUM_47, 1);
    if (Motor.begin(twi_read, twi_write, DRV2605_ADDR)) //
    {
        Serial.print("Error init drv2605 !!!");
        while (1);
    }
    Serial.print("Success init drv2605 !!!");

    // Use LRA (Linear Resonance Actuator) mode.
    Motor.useLRA();
    // Motor.useERM();

    // Select the waveform Library to use
    // 0 = Empty, 1-5 are ERM, 6 is LRA.
    Motor.selectLibrary(6);

    // I2C trigger by sending 'go' command
    // default, internal trigger when sending GO command
    Motor.setMode(DRV2605_MODE_INTTRIG);

    // 开机振动
    create_touchVibrates_func(14);

}



void HAL::Motor_Update()
{
    create_touchVibrates_func(15);
}
