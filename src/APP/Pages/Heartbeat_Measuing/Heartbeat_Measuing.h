#ifndef __Heartbeat_Measuing_H
#define __Heartbeat_Measuing_H

#include "Heartbeat_Measuing_View.h"
#include "Heartbeat_Measuing_Model.h"

namespace Page
{

class Heartbeat_Measuing : public PageBase
{
public:
    typedef struct
    {
        uint16_t time;
        lv_color_t color;
    } Param_t;

public:
    Heartbeat_Measuing();
    virtual ~Heartbeat_Measuing();

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
    Heartbeat_Measuing_View View;
    Heartbeat_Measuing_Model Model;
    lv_timer_t* timer;
};

}

#endif
