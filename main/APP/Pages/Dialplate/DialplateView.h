#ifndef __DIALPLATE_VIEW_H
#define __DIALPLATE_VIEW_H

#include "../Page.h"

namespace Page
{

class DialplateView
{


public:
    struct
    {
        struct
        {
            lv_obj_t* cont;
            lv_obj_t* bg;
            lv_obj_t* labelClock;
            lv_obj_t* labelClockmin;
            lv_obj_t* labelClockhour;
        } dialplate;

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
