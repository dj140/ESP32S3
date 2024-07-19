#include "ResourcePool.h"
#include "APP/Utils/ResourceManager/ResourceManager.h"

static ResourceManager Font_;
static ResourceManager Image_;

extern "C" {
#define IMPORT_FONT(name) \
do{\
    LV_FONT_DECLARE(font_##name)\
    Font_.AddResource(#name, (void*)&font_##name);\
}while(0)

#define IMPORT_IMG(name) \
do{\
    LV_IMG_DECLARE(img_src_##name)\
    Image_.AddResource(#name, (void*)&img_src_##name);\
}while (0)

    static void Resource_Init()
    {
        /* Import Fonts */
//        IMPORT_FONT(bahnschrift_13);
        IMPORT_FONT(bahnschrift_17);
//        IMPORT_FONT(bahnschrift_32);
//        IMPORT_FONT(bahnschrift_65);
//        IMPORT_FONT(agencyb_36);
//        IMPORT_FONT(Number_extra);
        IMPORT_FONT(montserratMedium_110);

        /* Import Images */
//        IMPORT_IMG(alarm);
//        IMPORT_IMG(battery);
//        IMPORT_IMG(battery_info);
//        IMPORT_IMG(bicycle);
//        IMPORT_IMG(compass);
//        IMPORT_IMG(gps_arrow_default);
//        IMPORT_IMG(gps_arrow_dark);
//        IMPORT_IMG(gps_arrow_light);
//        IMPORT_IMG(gyroscope);
//        IMPORT_IMG(locate);
//        IMPORT_IMG(map_location);
//        IMPORT_IMG(menu);
//        IMPORT_IMG(origin_point);
//        IMPORT_IMG(pause);
//        IMPORT_IMG(satellite);
//        IMPORT_IMG(sd_card);
//        IMPORT_IMG(start);
//        IMPORT_IMG(stop);
//        IMPORT_IMG(storage);
//        IMPORT_IMG(system_info);
//        IMPORT_IMG(time_info);
//        IMPORT_IMG(trip);
//        IMPORT_IMG(bg1_png);
//        IMPORT_IMG(bg2_png);
//        IMPORT_IMG(bg3_png);
        IMPORT_IMG(clockwise_hour);
        IMPORT_IMG(clockwise_min);
        IMPORT_IMG(clockwise_sec);
        IMPORT_IMG(sec_dot_png);
//        IMPORT_IMG(app_icon_hdpi_boxing_png);
//        IMPORT_IMG(app_icon_hdpi_pingpong_png);
//        IMPORT_IMG(app_icon_hdpi_settings_png);
        IMPORT_IMG(wave1_png);
        IMPORT_IMG(wave2_png);
        // IMPORT_IMG(bg_digital_392x392);
        // IMPORT_IMG(dot_alpha_8x8);
        // IMPORT_IMG(icn_flash_blue_alpha_17x21);
        // IMPORT_IMG(icn_message_alpha_25x25);
        // IMPORT_IMG(icn_sport_alpha_12x24);
        // IMPORT_IMG(icn_step_red_alpha_17x21);
        // IMPORT_IMG(icn_weather_1_alpha_41x33);
        // IMPORT_IMG(menu_alpha_11x117);
        // IMPORT_IMG(text_message_alpha_70x70);
        // IMPORT_IMG(text_sport_alpha_50x50);
        IMPORT_IMG(app_icon_Instagram);
        IMPORT_IMG(app_icon_LinkedIn);
        IMPORT_IMG(app_icon_Meta);
        IMPORT_IMG(app_icon_WeChat);
        IMPORT_IMG(app_icon_Vimeo);
        IMPORT_IMG(app_icon_Twitter);
//        IMPORT_IMG(app_icon_Spotify);
        IMPORT_IMG(app_icon_Reddit);
        IMPORT_IMG(apple_watch);
        IMPORT_IMG(cxk_hour);
        IMPORT_IMG(cxk_min);
        IMPORT_IMG(cxk_sec);
        IMPORT_IMG(setting_menu);
        IMPORT_IMG(watch_face2);
        IMPORT_IMG(SHM_Logo);
        IMPORT_IMG(bg_day);
        IMPORT_IMG(image1);
        IMPORT_IMG(image2);
        IMPORT_IMG(image3);
        IMPORT_IMG(stopwatch);
        IMPORT_IMG(stopwatch_add);
        IMPORT_IMG(stopwatch_pause);
        IMPORT_IMG(stopwatch_start);
        IMPORT_IMG(stopwatch_reset);
        IMPORT_IMG(wifi_icon);
        IMPORT_IMG(Ping_icon);

    }

} /* extern "C" */

void ResourcePool::Init()
{
    Resource_Init();
    Font_.SetDefault((void*)LV_FONT_DEFAULT);
}

lv_font_t* ResourcePool::GetFont(const char* name)
{
    return (lv_font_t*)Font_.GetResource(name);
}
const void* ResourcePool::GetImage(const char* name)
{
    return Image_.GetResource(name);
}
