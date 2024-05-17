#ifndef __Heartbeat_Measuing_VIEW_H
#define __Heartbeat_Measuing_VIEW_H

#include "../Page.h"

namespace Page
{

class Heartbeat_Measuing_View
{
public:
    void Create(lv_obj_t* root);
    void Delete();

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

    } ui;

private:

};

}

#endif // !__VIEW_H
