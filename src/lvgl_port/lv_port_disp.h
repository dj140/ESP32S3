/**
 * @file lv_port_disp_templ.h
 *
 */

/*Copy this file as "lv_port_disp.h" and set this value to "1" to enable content*/
#if 1

#ifndef LV_PORT_DISP_H
#define LV_PORT_DISP_H


// #ifdef __cplusplus
// extern "C" {
// #endif
#define LV_LVGL_H_INCLUDE_SIMPLE 1

/*********************
 *      INCLUDES
 *********************/
#if defined(LV_LVGL_H_INCLUDE_SIMPLE)
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif
#include <LovyanGFX.hpp>
#include "HAL/HAL_Config.h"


static const char* TAG = "LVGL";

/// 独自の設定を行うクラスを、LGFX_Deviceから派生して作成します。
class LGFX : public lgfx::LGFX_Device {
    // 接続するパネルの型にあったインスタンスを用意します。
    lgfx::Panel_SH8601Z     _panel_instance;
    // パネルを接続するバスの種類にあったインスタンスを用意します。
    lgfx::Bus_QSPI      _bus_instance;

    public:
        // コンストラクタを作成し、ここで各種設定を行います。
        // クラス名を変更した場合はコンストラクタも同じ名前を指定してください。
        LGFX(void)
        {
            { // バス制御の設定を行います。
                auto cfg = _bus_instance.config();    // バス設定用の構造体を取得します。

                // SPIバスの設定
                cfg.spi_host = SPI3_HOST;     // 使用するSPIを選択  ESP32-S2,C3 : SPI2_HOST or SPI3_HOST / ESP32 : VSPI_HOST or HSPI_HOST
                // ※ ESP-IDFバージョンアップに伴い、VSPI_HOST , HSPI_HOSTの記述は非推奨になるため、エラーが出る場合は代わりにSPI2_HOST , SPI3_HOSTを使用してください。
                cfg.spi_mode = 1;             // SPI通信モードを設定 (0 ~ 3)
                //   cfg.freq_write = 1*1000*1000;    // 送信時のSPIクロック (最大80MHz, 80MHzを整数で割った値に丸められます)
                //   cfg.freq_write = 10*1000*1000;
                cfg.freq_write = 40*1000*1000;
                cfg.freq_read  = 16000000;    // 受信時のSPIクロック
                cfg.spi_3wire  = true;        // 受信をMOSIピンで行う場合はtrueを設定
                cfg.use_lock   = true;        // トランザクションロックを使用する場合はtrueを設定
                cfg.dma_channel = SPI_DMA_CH_AUTO; // 使用するDMAチャンネルを設定 (0=DMA不使用 / 1=1ch / 2=ch / SPI_DMA_CH_AUTO=自動設 定)

                cfg.pin_sclk    = AMOLED_CLK_PIN;
                cfg.pin_io0     = AMOLED_D0_PIN;
                cfg.pin_io1     = AMOLED_D1_PIN;
                cfg.pin_io2     = AMOLED_D2_PIN;
                cfg.pin_io3     = AMOLED_D3_PIN;
                // cfg.pin_dc      = -1;

                _bus_instance.config(cfg);    // 設定値をバスに反映します。
                _panel_instance.setBus(&_bus_instance);      // バスをパネルにセットします。
            }

            { // 表示パネル制御の設定を行います。
                auto cfg = _panel_instance.config();    // 表示パネル設定用の構造体を取得します。

                cfg.pin_cs           =    AMOLED_CS_PIN;  // CSが接続されているピン番号   (-1 = disable)
                cfg.pin_rst          =    AMOLED_RESET_PIN;  // RSTが接続されているピン番号  (-1 = disable)
                cfg.pin_busy         =    -1;  // BUSYが接続されているピン番号 (-1 = disable)

                // ※ 以下の設定値はパネル毎に一般的な初期値が設定されていますので、不明な項目はコメントアウトして試してみてください。

                cfg.panel_width      =   410;  // 実際に表示可能な幅
                cfg.panel_height     =   502;  // 実際に表示可能な高さ

                // cfg.panel_width      =   320;  // 実際に表示可能な幅
                // cfg.panel_height     =   240;  // 実際に表示可能な高さ


                cfg.offset_x         =     0;  // パネルのX方向オフセット量
                cfg.offset_y         =     0;  // パネルのY方向オフセット量
                cfg.offset_rotation  =     0;  // 回転方向の値のオフセット 0~7 (4~7は上下反転)
                cfg.dummy_read_pixel =     8;  // ピクセル読出し前のダミーリードのビット数
                cfg.dummy_read_bits  =     1;  // ピクセル以外のデータ読出し前のダミーリードのビット数
                cfg.readable         =  true;  // データ読出しが可能な場合 trueに設定
                cfg.invert           = true;  // パネルの明暗が反転してしまう場合 trueに設定
                cfg.rgb_order        = true;  // パネルの赤と青が入れ替わってしまう場合 trueに設定
                cfg.dlen_16bit       = false;  // 16bitパラレルやSPIでデータ長を16bit単位で送信するパネルの場合 trueに設定
                cfg.bus_shared       =  true;  // SDカードとバスを共有している場合 trueに設定(drawJpgFile等でバス制御を行います)

                // 以下はST7735やILI9163のようにピクセル数が可変のドライバで表示がずれる場合にのみ設定してください。
                cfg.memory_width     =   480;  // ドライバICがサポートしている最大の幅
                cfg.memory_height    =   480;  // ドライバICがサポートしている最大の高さ

                _panel_instance.config(cfg);
            }
            setPanel(&_panel_instance); // 使用するパネルをセットします。
        }


        inline bool init(void) {
            
            /* PEN pin */
            gpio_reset_pin(AMOLED_VCI_EN_PIN);
            gpio_set_direction(AMOLED_VCI_EN_PIN, GPIO_MODE_OUTPUT);
            gpio_set_pull_mode(AMOLED_VCI_EN_PIN, GPIO_PULLUP_PULLDOWN);
            gpio_set_level(AMOLED_VCI_EN_PIN, 1);
            vTaskDelay(pdMS_TO_TICKS(10));

            /* TE pin */
            gpio_reset_pin(AMOLED_TE_PIN);
            gpio_set_direction(AMOLED_TE_PIN, GPIO_MODE_INPUT);
            // vTaskDelay(pdMS_TO_TICKS(10));

            /* Lgfx */
            return lgfx::LGFX_Device::init();
        }
};


/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/
/* Initialize low level display driver */
void lv_port_disp_init(void);

/* Enable updating the screen (the flushing process) when disp_flush() is called by LVGL
 */
void disp_enable_update(void);

/* Disable updating the screen (the flushing process) when disp_flush() is called by LVGL
 */
void disp_disable_update(void);

/**********************
 *      MACROS
 **********************/

// #ifdef __cplusplus
// } /*extern "C"*/
// #endif

#endif /*LV_PORT_DISP_TEMPL_H*/

#endif /*Disable/Enable content*/
