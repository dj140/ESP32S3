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
#include <LovyanGFX.hpp>

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

                cfg.pin_sclk    = 7;
                cfg.pin_io0     = 9;
                cfg.pin_io1     = 8;
                cfg.pin_io2     = 5;
                cfg.pin_io3     = 6;
                // cfg.pin_dc      = -1;

                _bus_instance.config(cfg);    // 設定値をバスに反映します。
                _panel_instance.setBus(&_bus_instance);      // バスをパネルにセットします。
            }

            { // 表示パネル制御の設定を行います。
                auto cfg = _panel_instance.config();    // 表示パネル設定用の構造体を取得します。

                cfg.pin_cs           =    13;  // CSが接続されているピン番号   (-1 = disable)
                cfg.pin_rst          =    1;  // RSTが接続されているピン番号  (-1 = disable)
                cfg.pin_busy         =    -1;  // BUSYが接続されているピン番号 (-1 = disable)

                // ※ 以下の設定値はパネル毎に一般的な初期値が設定されていますので、不明な項目はコメントアウトして試してみてください。

                cfg.panel_width      =   368;  // 実際に表示可能な幅
                cfg.panel_height     =   448;  // 実際に表示可能な高さ

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
            gpio_reset_pin(GPIO_NUM_4);
            gpio_set_direction(GPIO_NUM_4, GPIO_MODE_OUTPUT);
            gpio_set_pull_mode(GPIO_NUM_4, GPIO_PULLUP_PULLDOWN);
            gpio_set_level(GPIO_NUM_4, 1);
            // vTaskDelay(pdMS_TO_TICKS(10));

            /* TE pin */
            gpio_reset_pin(GPIO_NUM_2);
            gpio_set_direction(GPIO_NUM_2, GPIO_MODE_INPUT);
            // vTaskDelay(pdMS_TO_TICKS(10));

            /* Lgfx */
            return lgfx::LGFX_Device::init();
        }
};

LGFX display;



/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/
static void disp_init(void);

static void disp_flush(lv_display_t * disp, const lv_area_t * area, uint8_t * px_map);

/**********************
 *  STATIC VARIABLES
 **********************/

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

void lv_port_disp_init(void)
{
    /*-------------------------
     * Initialize your display
     * -----------------------*/
    disp_init();

    /*------------------------------------
     * Create a display and set a flush_cb
     * -----------------------------------*/
    lv_display_t * disp = lv_display_create(TFT_HOR_RES, TFT_VER_RES);
    lv_display_set_flush_cb(disp, disp_flush);
    /* Example 2
     * Two buffers for partial rendering
     * In flush_cb DMA or similar hardware should be used to update the display in the background.*/
    static lv_color_t buf_2_1[TFT_HOR_RES * 50];
    static lv_color_t buf_2_2[TFT_HOR_RES * 50];
    lv_display_set_buffers(disp, buf_2_1, buf_2_2, sizeof(buf_2_1), LV_DISPLAY_RENDER_MODE_PARTIAL);
    // /* Example 3
    //  * Two buffers screen sized buffer for double buffering.
    //  * Both LV_DISPLAY_RENDER_MODE_DIRECT and LV_DISPLAY_RENDER_MODE_FULL works, see their comments*/
    // static lv_color_t buf_3_1[MY_DISP_HOR_RES * MY_DISP_VER_RES];
    // static lv_color_t buf_3_2[MY_DISP_HOR_RES * MY_DISP_VER_RES];
    // lv_display_set_buffers(disp, buf_3_1, buf_3_2, sizeof(buf_3_1), LV_DISPLAY_RENDER_MODE_DIRECT);

}

/**********************
 *   STATIC FUNCTIONS
 **********************/

/*Initialize your display and the required peripherals.*/
static void disp_init(void)
{
    /*You code here*/
    // gfx->begin();
    // gfx->fillScreen(BLACK);
    // pinMode(GFX_BL, OUTPUT);
    // digitalWrite(GFX_BL, HIGH);
    display.init();
    display.setColorDepth(16);
}

volatile bool disp_flush_enabled = true;

/* Enable updating the screen (the flushing process) when disp_flush() is called by LVGL
 */
void disp_enable_update(void)
{
    disp_flush_enabled = true;
}

/* Disable updating the screen (the flushing process) when disp_flush() is called by LVGL
 */
void disp_disable_update(void)
{
    disp_flush_enabled = false;
}

/*Flush the content of the internal buffer the specific area on the display.
 *`px_map` contains the rendered image as raw pixel map and it should be copied to `area` on the display.
 *You can use DMA or any hardware acceleration to do this operation in the background but
 *'lv_display_flush_ready()' has to be called when it's finished.*/
static void disp_flush(lv_display_t * disp_drv, const lv_area_t * area, uint8_t * px_map)
{
    if(disp_flush_enabled) {
        /*The most simple case (but also the slowest) to put all pixels to the screen one-by-one*/
        uint32_t w = (area->x2 - area->x1 + 1);
        uint32_t h = (area->y2 - area->y1 + 1);
        display.startWrite();
        display.setWindow(area->x1, area->y1, area->x2, area->y2);
        display.pushPixels((uint16_t *)px_map, w * h, true);
        display.endWrite();
        // gfx->draw16bitBeRGBBitmap(area->x1, area->y1, (uint16_t *)px_map, w, h);

    }

    /*IMPORTANT!!!
     *Inform the graphics library that you are ready with the flushing*/
    lv_display_flush_ready(disp_drv);
}

#else /*Enable this file at the top*/

/*This dummy typedef exists purely to silence -Wpedantic.*/
typedef int keep_pedantic_happy;
#endif

