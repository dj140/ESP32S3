#ifndef __WatchFace_Select__PRESENTER_H
#define __WatchFace_Select__PRESENTER_H

#include "WatchFace_Select_View.h"
#include "WatchFace_Select_Model.h"

namespace Page
{

class WatchFace_Select : public PageBase
{
public:
    WatchFace_Select();
    virtual ~WatchFace_Select();

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


private:
    void Update();
    void AttachEvent(lv_obj_t* obj);
    static void onTimerUpdate(lv_timer_t* timer);
    static void onEvent(lv_event_t* event);


private:
    WatchFace_Select_View View;
    WatchFace_Select_Model Model;
    lv_timer_t* timer;
    lv_obj_t* lastFocus;
};

}

#endif
