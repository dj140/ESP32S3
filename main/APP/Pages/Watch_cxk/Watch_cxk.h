#ifndef __Watch_cxk_H
#define __Watch_cxk_H

#include "Watch_cxk_View.h"
#include "Watch_cxk_Model.h"

namespace Page
{

class Watch_cxk : public PageBase
{
public:
    typedef struct
    {
        uint16_t time;
        lv_color_t color;
    } Param_t;

public:
    Watch_cxk();
    virtual ~Watch_cxk();

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
    Watch_cxk_View View;
    Watch_cxk_Model Model;
    lv_timer_t* timer;
};

}

#endif
