#ifndef __DIALPLATE_VIEW_H
#define __DIALPLATE_VIEW_H

#include "../Page.h"

namespace Page
{

class DialplateView
{

public:
    uint8_t* dog_lottile_buf;
    uint8_t* sun_lottile_buf;
    struct
    {
        struct
        {
            lv_obj_t* cont;
            lv_obj_t* bg;
            lv_obj_t* labelClock;
            lv_obj_t* labelClockmin;
            lv_obj_t* labelClockhour;
            lv_obj_t* Power;
        } dialplate;
        
        struct
        {
            lv_obj_t* img;
            lv_obj_t* objUsage;
            lv_obj_t* label;
        } battery;

        lv_anim_timeline_t* anim_timeline;
    } ui;

    void Create(lv_obj_t* root);
    void Delete();
    void AppearAnimStart(bool reverse = false);

private:
    void Dialplate_Create(lv_obj_t* par);

};

}

#endif // !__VIEW_H
