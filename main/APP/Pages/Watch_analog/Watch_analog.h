#ifndef __WATCH_ANALOG_H
#define __WATCH_ANALOG_H

#include "Watch_analog_View.h"
#include "Watch_analog_Model.h"

namespace Page
{

class Watch_analog : public PageBase
{
public:
    typedef struct
    {
        uint16_t time;
        lv_color_t color;
    } Param_t;

public:
    Watch_analog();
    virtual ~Watch_analog();

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
    Watch_analog_View View;
    Watch_analog_Model Model;
    lv_timer_t* timer;
};

}

#endif
