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
#include "HAL_Config.h"

#define LCD_HOST    SPI3_HOST
static const char *TAG = "LVGL";
#define LCD_BIT_PER_PIXEL       (24)

/**********************
 *  STATIC PROTOTYPES
 **********************/
static void disp_init(void);
static void TE_init(void);

static void disp_flush(lv_display_t * disp, const lv_area_t * area, uint8_t * px_map);


/**********************
 *   GLOBAL FUNCTIONS
 **********************/
static bool example_notify_lvgl_flush_ready(esp_lcd_panel_io_handle_t panel_io, esp_lcd_panel_io_event_data_t *edata, void *user_ctx)
{
    lv_display_t *disp_driver = (lv_display_t *)user_ctx;
    // lv_disp_flush_ready(disp_driver);
    return false;
}

static void disp_flush(lv_display_t * disp, const lv_area_t * area, uint8_t * px_map)
{
    esp_lcd_panel_handle_t panel_handle = (esp_lcd_panel_handle_t)lv_display_get_user_data(disp);

    const int offsetx1 = area->x1;
    const int offsetx2 = area->x2;
    const int offsety1 = area->y1;
    const int offsety2 = area->y2;

    // copy a buffer's content to a specific area of the display
    //RRRRR GGG | GGG BBBBB  ---->  GGG BBBBB | RRRRR GGG
    // lv_draw_sw_rgb565_swap(px_map, (offsetx2 - offsetx1 + 1) * (offsety2 - offsety1 + 1));
    esp_lcd_panel_draw_bitmap(panel_handle, offsetx1 , offsety1, offsetx2 + 1, offsety2 + 1, px_map);
    // esp_lcd_panel_draw_bitmap(panel_handle, 0 , 0, 410, 168, &px_map[0]);
    // esp_lcd_panel_draw_bitmap(panel_handle, 0 , 168, 410, 336, &px_map[410 * 168 * 2]);
    // esp_lcd_panel_draw_bitmap(panel_handle, 0 , 336, 410, 502, &px_map[410 * 336 * 2]);
    lv_disp_flush_ready(disp);

}

void lvgl_rounder_cb(lv_event_t *e)
{
    lv_area_t *area = (lv_area_t *)lv_event_get_param(e);

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

    const spi_bus_config_t buscfg = SH8601_PANEL_BUS_QSPI_CONFIG(AMOLED_D0_PIN,
                                                                AMOLED_D1_PIN,
                                                                AMOLED_CLK_PIN,
                                                                AMOLED_D2_PIN,
                                                                AMOLED_D3_PIN,
                                                                TFT_HOR_RES * TFT_VER_RES * LCD_BIT_PER_PIXEL / 8);

     ESP_ERROR_CHECK(spi_bus_initialize(LCD_HOST, &buscfg, SPI_DMA_CH_AUTO));

    ESP_LOGI(TAG, "Install panel IO");
    esp_lcd_panel_io_handle_t io_handle = NULL;

    const esp_lcd_panel_io_spi_config_t io_config = SH8601_PANEL_IO_QSPI_CONFIG(AMOLED_CS_PIN,
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
        .reset_gpio_num = AMOLED_RESET_PIN,
        .rgb_ele_order = LCD_RGB_ELEMENT_ORDER_RGB,
        .bits_per_pixel = LCD_BIT_PER_PIXEL,
        .vendor_config = &vendor_config,
    };

    ESP_LOGI(TAG, "Install SH8601 panel driver");
    ESP_ERROR_CHECK(esp_lcd_new_panel_sh8601(io_handle, &panel_config, &panel_handle));

    // esp_lcd_panel_set_gap(panel_handle, 0x16, 0x00);
    ESP_ERROR_CHECK(esp_lcd_panel_reset(panel_handle));
    ESP_ERROR_CHECK(esp_lcd_panel_init(panel_handle)); 
    // ESP_ERROR_CHECK(esp_lcd_panel_invert_color(panel_handle, true));
    // user can flush pre-defined pattern to the screen before we turn on the screen or backlight
    ESP_ERROR_CHECK(esp_lcd_panel_disp_on_off(panel_handle, true));

    ESP_LOGI(TAG, "Initialize LVGL library");

    // lv_display_add_event_cb(disp, lvgl_port_rounder_callback, LV_EVENT_RENDER_START, NULL);
    lv_color_t* buf_3_1 = (lv_color_t *)heap_caps_malloc(TFT_HOR_RES * TFT_VER_RES * 3, MALLOC_CAP_SPIRAM);
    lv_color_t* buf_3_2 = (lv_color_t *)heap_caps_malloc(TFT_HOR_RES * TFT_VER_RES * 3, MALLOC_CAP_SPIRAM);

    /* If failed */
    if ((buf_3_1 == NULL) || (buf_3_2 == NULL)) {
        ESP_LOGE(TAG, "malloc buffer from PSRAM fialed");
        while (1);
    } else {
        ESP_LOGI(TAG, "malloc buffer from PSRAM successful");
        ESP_LOGI(TAG, "free PSRAM: %d\r\n", heap_caps_get_free_size(MALLOC_CAP_SPIRAM));
    }

    lv_display_set_user_data(disp, panel_handle);
    // lv_display_add_event_cb(disp, lvgl_rounder_cb, LV_EVENT_INVALIDATE_AREA, NULL);
    lv_display_set_buffers(disp, buf_3_1, buf_3_2, TFT_HOR_RES * TFT_VER_RES * 3, LV_DISPLAY_RENDER_MODE_FULL);
    /*Delete the original display refresh timer*/
    // lv_display_delete_refr_timer(disp);

    ESP_LOGI(TAG, "Register display driver to LVGL");
    TE_init();
}

/**********************
 *   STATIC FUNCTIONS
 **********************/
static QueueHandle_t gpio_evt_queue = NULL;


static void IRAM_ATTR gpio_isr_handler(void* arg)
{
    uint32_t gpio_num = (uint32_t) arg;
    xQueueSendFromISR(gpio_evt_queue, &gpio_num, NULL);
}

static void TE_task(void* arg)
{
    uint32_t io_num;
    ESP_LOGI(TAG, "TE_task");
    for (;;) {
        if (xQueueReceive(gpio_evt_queue, &io_num, portMAX_DELAY)) {
            // printf("GPIO[%"PRIu32"] intr, val: %d\n", io_num, gpio_get_level(io_num));
            /*Call this anywhere you want to refresh the dirty areas*/
            // _lv_display_refr_timer(NULL);
        }
    }
}
/*Initialize your display and the required peripherals.*/
static void disp_init(void)
{
    /*You code here*/
    gpio_reset_pin(AMOLED_VCI_EN_PIN);
    gpio_set_direction(AMOLED_VCI_EN_PIN, GPIO_MODE_OUTPUT);
    gpio_set_pull_mode(AMOLED_VCI_EN_PIN, GPIO_PULLUP_PULLDOWN);
    gpio_set_level(AMOLED_VCI_EN_PIN, 1);
    vTaskDelay(pdMS_TO_TICKS(10));
}

static void TE_init(void)
{
    gpio_config_t io_conf;
    //interrupt of rising edge
    io_conf.intr_type = GPIO_INTR_POSEDGE;
    //bit mask of the pins, use GPIO4/5 here
    io_conf.pin_bit_mask = 1ULL << AMOLED_TE_PIN;
    //set as input mode
    io_conf.mode = GPIO_MODE_INPUT;
    //enable pull-up mode
    io_conf.pull_up_en = 1;
    gpio_config(&io_conf);
    
    gpio_evt_queue = xQueueCreate(10, sizeof(uint32_t));

    xTaskCreatePinnedToCore(TE_task, "TE_task", 2048, NULL, 6, NULL, 1);

    // Install ISR service
    gpio_install_isr_service(0);

    // Add GPIO interrupt handler
    gpio_isr_handler_add(AMOLED_TE_PIN, gpio_isr_handler, (void*)AMOLED_TE_PIN);
}

#else /*Enable this file at the top*/

/*This dummy typedef exists purely to silence -Wpedantic.*/
typedef int keep_pedantic_happy;
#endif