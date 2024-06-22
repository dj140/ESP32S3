#ifndef __StopWatch_H
#define __StopWatch_H

#include "StopWatch_View.h"
#include "StopWatch_Model.h"

namespace Page
{

class StopWatch : public PageBase
{
public:
    typedef struct
    {
        uint16_t time;
        lv_color_t color;
    } Param_t;

public:
    StopWatch();
    virtual ~StopWatch();

    virtual void onCustomAttrConfig();
    virtual void onViewLoad();
    virtual void onViewDidLoad();
    virtual void onViewWillAppear();
    virtual void onViewDidAppear();
    virtual void onViewWillDisappear();
    virtual void onViewDidDisappear();
    virtual void onViewUnload();
    virtual void onViewDidUnload();
    static void SW_ShowTime(uint32_t ms);
    static void SW_Reset();

private:
    void Update();
    void AttachEvent(lv_obj_t* obj, lv_event_cb_t event_cb, lv_event_code_t filter);
    static void onTimerUpdate(lv_timer_t* timer);
    static void onEvent(lv_event_t* event);
    static void SW_Pause();

private:
    StopWatch_View View;
    StopWatch_Model Model;
    lv_timer_t* timer;
};

}

#endif
