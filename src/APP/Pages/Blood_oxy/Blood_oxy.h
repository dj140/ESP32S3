#ifndef __BLOOD_OXY_H
#define __BLOOD_OXY_H

#include "Blood_oxy_View.h"
#include "Blood_oxy_Model.h"

namespace Page
{

class Blood_oxy : public PageBase
{
public:
    typedef struct
    {
        uint16_t time;
        lv_color_t color;
    } Param_t;

public:
    Blood_oxy();
    virtual ~Blood_oxy();

    virtual void onCustomAttrConfig();
    virtual void onViewLoad();
    virtual void onViewDidLoad();
    virtual void onViewWillAppear();
    virtual void onViewDidAppear();
    virtual void onViewWillDisappear();
    virtual void onViewDidDisappear();
    virtual void onViewUnload();
    virtual void onViewDidUnload();

private:
    void Update();
    void AttachEvent(lv_obj_t* obj);
    static void onTimerUpdate(lv_timer_t* timer);
    static void onEvent(lv_event_t* event);

private:
    Blood_oxy_View View;
    Blood_oxy_Model Model;
    lv_timer_t* timer;
};

}

#endif
