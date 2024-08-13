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
       IMPORT_IMG(battery);
//        IMPORT_IMG(battery_info);
        IMPORT_IMG(clockwise_hour);
        IMPORT_IMG(clockwise_min);
        IMPORT_IMG(clockwise_sec);
        IMPORT_IMG(sec_dot_png);
        IMPORT_IMG(wave1_png);
        IMPORT_IMG(wave2_png);
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
