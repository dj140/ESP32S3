#ifndef __WATCH_ANALOG_VIEW_H
#define __WATCH_ANALOG_VIEW_H

#include "../Page.h"
#include "Watch_analog_Model.h"

namespace Page
{

class Watch_analog_View
{
public:
    void Create(lv_obj_t* root);
    void Delete();
    void AppearAnimStart(bool reverse = false);

public:
    struct
    {
        lv_obj_t* labelTitle;
        lv_obj_t* labelTick;
        lv_obj_t* cont;
        lv_obj_t* image;
        lv_obj_t* ui_bg_2;
        lv_obj_t* ui_clock;
        lv_obj_t* ui_dots;
        lv_obj_t* ui_sec;
        lv_obj_t* ui_min;
        lv_obj_t* ui_hour;
        lv_obj_t* ui_year;
        lv_obj_t* ui_month;
        lv_obj_t* ui_day;
        lv_anim_timeline_t* anim_timeline;

    } ui;

private:
    void Watch_Create(lv_obj_t* par);
    Watch_analog_Model Model;
    Account* myaccount;
};

}

#endif // !__VIEW_H
