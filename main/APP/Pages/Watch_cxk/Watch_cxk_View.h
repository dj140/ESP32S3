#ifndef __Watch_cxk_VIEW_H
#define __Watch_cxk_VIEW_H

#include "../Page.h"

namespace Page
{

class Watch_cxk_View
{
public:
    void Create(lv_obj_t* root);
    void Delete();
    void AppearAnimStart(bool reverse = false);

public:
    struct
    {
        lv_obj_t* cont;
        lv_obj_t* image;
        lv_obj_t* ui_bg;
        lv_obj_t* ui_clock;
        lv_obj_t* ui_dots;
        lv_obj_t* ui_sec;
        lv_obj_t* ui_min;
        lv_obj_t* ui_hour;
        lv_anim_timeline_t* anim_timeline;

    } ui;

private:
    void Watch_Create(lv_obj_t* par);

};

}

#endif // !__VIEW_H
