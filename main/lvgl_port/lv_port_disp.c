/**
 * @file lv_port_disp_templ.c
 *
 */

/*Copy this file as "lv_port_disp.c" and set this value to "1" to enable content*/
#if 1

/*********************
 *      INCLUDES
 *********************/
#include "lv_port_disp.h"
#include <stdbool.h>
#include <esp_log.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "driver/i2c.h"
#include "driver/spi_master.h"
#include "esp_timer.h"
#include "esp_lcd_panel_io.h"
#include "esp_lcd_panel_vendor.h"
#include "esp_lcd_panel_ops.h"
#include "esp_err.h"
#include "esp_log.h"
#include "esp_lcd_sh8601.h"

#define LCD_HOST    SPI3_HOST
static const char *TAG = "LVGL";
#define LCD_BIT_PER_PIXEL       (16)
#define EXAMPLE_LCD_H_RES              410
#define EXAMPLE_LCD_V_RES              502
/*********************
 *      DEFINES
 *********************/
#define EXAMPLE_LCD_BK_LIGHT_ON_LEVEL  1
#define EXAMPLE_LCD_BK_LIGHT_OFF_LEVEL !EXAMPLE_LCD_BK_LIGHT_ON_LEVEL
#define EXAMPLE_PIN_NUM_LCD_CS            (GPIO_NUM_9)
#define EXAMPLE_PIN_NUM_LCD_PCLK          (GPIO_NUM_14)
#define EXAMPLE_PIN_NUM_LCD_DATA0         (GPIO_NUM_11)
#define EXAMPLE_PIN_NUM_LCD_DATA1         (GPIO_NUM_12)
#define EXAMPLE_PIN_NUM_LCD_DATA2         (GPIO_NUM_2)
#define EXAMPLE_PIN_NUM_LCD_DATA3         (GPIO_NUM_13)
#define EXAMPLE_PIN_NUM_LCD_RST           (GPIO_NUM_4)
#define EXAMPLE_PIN_NUM_BK_LIGHT          (GPIO_NUM_0)


/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/
static void disp_init(void);

static void disp_flush(lv_display_t * disp, const lv_area_t * area, uint8_t * px_map);
//static void gpu_fill(lv_disp_drv_t * disp_drv, lv_color_t * dest_buf, lv_coord_t dest_width,
//        const lv_area_t * fill_area, lv_color_t color);

/**********************
 *  STATIC VARIABLES
 **********************/

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/
static bool example_notify_lvgl_flush_ready(esp_lcd_panel_io_handle_t panel_io, esp_lcd_panel_io_event_data_t *edata, void *user_ctx)
{
    lv_display_t *disp_driver = (lv_display_t *)user_ctx;
    lv_disp_flush_ready(disp_driver);
    return false;
}

static void disp_flush(lv_display_t * disp, const lv_area_t * area, uint8_t * px_map)
{
    esp_lcd_panel_handle_t panel_handle = (esp_lcd_panel_handle_t)lv_display_get_user_data(disp);

    const int offsetx1 = area->x1;
    const int offsetx2 = area->x2;
    const int offsety1 = area->y1;
    const int offsety2 = area->y2;

#if LCD_BIT_PER_PIXEL == 24
    uint8_t *to = (uint8_t *)color_map;
    uint8_t temp = 0;
    uint16_t pixel_num = (offsetx2 - offsetx1 + 1) * (offsety2 - offsety1 + 1);

    // Special dealing for first pixel
    temp = color_map[0].ch.blue;
    *to++ = color_map[0].ch.red;
    *to++ = color_map[0].ch.green;
    *to++ = temp;
    // Normal dealing for other pixels
    for (int i = 1; i < pixel_num; i++) {
        *to++ = color_map[i].ch.red;
        *to++ = color_map[i].ch.green;
        *to++ = color_map[i].ch.blue;
    }
#endif

    // copy a buffer's content to a specific area of the display
    //RRRRR GGG | GGG BBBBB  ---->  GGG BBBBB | RRRRR GGG
    lv_draw_sw_rgb565_swap(px_map, (offsetx2 - offsetx1 + 1) * (offsety2 - offsety1 + 1));
    // esp_lcd_panel_draw_bitmap(panel_handle, offsetx1 , offsety1, offsetx2 + 1, offsety2 + 1, px_map);
    esp_lcd_panel_draw_bitmap(panel_handle, 0 , 0, 410, 252, &px_map[0]);
    esp_lcd_panel_draw_bitmap(panel_handle, 0 , 252, 410, 503, &px_map[410 * 252 * 2]);
    lv_disp_flush_ready(disp);

}

void example_lvgl_rounder_cb(struct _lv_disp_drv_t *disp_drv, lv_area_t *area)
{
    uint16_t x1 = area->x1;
    uint16_t x2 = area->x2;

    uint16_t y1 = area->y1;
    uint16_t y2 = area->y2;

    // round the start of coordinate down to the nearest 2M number
    area->x1 = (x1 >> 1) << 1;
    area->y1 = (y1 >> 1) << 1;
    // round the end of coordinate up to the nearest 2N+1 number
    area->x2 = ((x2 >> 1) << 1) + 1;
    area->y2 = ((y2 >> 1) << 1) + 1;

}

void lv_port_disp_init(void)
{
    disp_init();
    lv_display_t * disp = lv_display_create(TFT_HOR_RES, TFT_VER_RES);
    lv_display_set_flush_cb(disp, disp_flush);
    ESP_LOGI(TAG,"Deafult free size: %d\n", heap_caps_get_free_size(MALLOC_CAP_DEFAULT));
    ESP_LOGI(TAG,"PSRAM free size: %d\n", heap_caps_get_free_size(MALLOC_CAP_SPIRAM));
    ESP_LOGI(TAG, "before free MALLOC_CAP_DMA: %d\r\n", heap_caps_get_free_size(MALLOC_CAP_DMA));
    ESP_LOGI(TAG, "Initialize SPI bus");

    const spi_bus_config_t buscfg = SH8601_PANEL_BUS_QSPI_CONFIG(EXAMPLE_PIN_NUM_LCD_PCLK,
                                                                EXAMPLE_PIN_NUM_LCD_DATA0,
                                                                EXAMPLE_PIN_NUM_LCD_DATA1,
                                                                EXAMPLE_PIN_NUM_LCD_DATA2,
                                                                EXAMPLE_PIN_NUM_LCD_DATA3,
                                                                EXAMPLE_LCD_H_RES * EXAMPLE_LCD_V_RES * 16 / 8);

     ESP_ERROR_CHECK(spi_bus_initialize(LCD_HOST, &buscfg, SPI_DMA_CH_AUTO));

    ESP_LOGI(TAG, "Install panel IO");
    esp_lcd_panel_io_handle_t io_handle = NULL;

    const esp_lcd_panel_io_spi_config_t io_config = SH8601_PANEL_IO_QSPI_CONFIG(EXAMPLE_PIN_NUM_LCD_CS,
                                                                                example_notify_lvgl_flush_ready,
                                                                                &disp);
    sh8601_vendor_config_t vendor_config = {
        .flags = {
            .use_qspi_interface = 1,
        },
    };

    // Attach the LCD to the SPI bus
    ESP_ERROR_CHECK(esp_lcd_new_panel_io_spi((esp_lcd_spi_bus_handle_t)LCD_HOST, &io_config, &io_handle));

    esp_lcd_panel_handle_t panel_handle = NULL;

    const esp_lcd_panel_dev_config_t panel_config = {
        .reset_gpio_num = EXAMPLE_PIN_NUM_LCD_RST,
        .rgb_ele_order = LCD_RGB_ELEMENT_ORDER_RGB,
        .bits_per_pixel = LCD_BIT_PER_PIXEL,
        .vendor_config = &vendor_config,
    };

    ESP_LOGI(TAG, "Install SH8601 panel driver");
    ESP_ERROR_CHECK(esp_lcd_new_panel_sh8601(io_handle, &panel_config, &panel_handle));

    esp_lcd_panel_set_gap(panel_handle, 0x16, 0x00);

    ESP_ERROR_CHECK(esp_lcd_panel_reset(panel_handle));
    ESP_ERROR_CHECK(esp_lcd_panel_init(panel_handle));
    // user can flush pre-defined pattern to the screen before we turn on the screen or backlight
    ESP_ERROR_CHECK(esp_lcd_panel_disp_on_off(panel_handle, true));

    ESP_LOGI(TAG, "Initialize LVGL library");

    // lv_display_add_event_cb(disp, lvgl_port_rounder_callback, LV_EVENT_RENDER_START, NULL);
    lv_color_t* buf_3_1 = (lv_color_t *)heap_caps_malloc(TFT_HOR_RES * TFT_VER_RES * 2, MALLOC_CAP_SPIRAM);
    lv_color_t* buf_3_2 = (lv_color_t *)heap_caps_malloc(TFT_HOR_RES * TFT_VER_RES * 2, MALLOC_CAP_SPIRAM);

    /* If failed */
    if ((buf_3_1 == NULL) || (buf_3_2 == NULL)) {
        ESP_LOGE(TAG, "malloc buffer from PSRAM fialed");
        while (1);
    } else {
        ESP_LOGI(TAG, "malloc buffer from PSRAM successful");

        ESP_LOGI(TAG, "free PSRAM: %d\r\n", heap_caps_get_free_size(MALLOC_CAP_DMA));
    }

    lv_display_set_user_data(disp, panel_handle);
    lv_display_set_buffers(disp, buf_3_1, buf_3_2, TFT_HOR_RES * TFT_VER_RES * 2, LV_DISPLAY_RENDER_MODE_FULL);

    ESP_LOGI(TAG, "Register display driver to LVGL");
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

/*Initialize your display and the required peripherals.*/
static void disp_init(void)
{
    /*You code here*/
    gpio_reset_pin(GPIO_NUM_3);
    gpio_set_direction(GPIO_NUM_3, GPIO_MODE_OUTPUT);
    gpio_set_pull_mode(GPIO_NUM_3, GPIO_PULLUP_PULLDOWN);
    gpio_set_level(GPIO_NUM_3, 1);
    vTaskDelay(pdMS_TO_TICKS(10));
}



#else /*Enable this file at the top*/

/*This dummy typedef exists purely to silence -Wpedantic.*/
typedef int keep_pedantic_happy;
#endif
