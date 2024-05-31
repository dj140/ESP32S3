#ifndef __Video_Player_H
#define __Video_Player_H

#include "Video_Player_View.h"
#include "Video_Player_Model.h"
#include "JPEGDEC.h"

namespace Page
{

class Video_Player : public PageBase
{
public:
    typedef struct
    {
        uint16_t time;
        lv_color_t color;
    } Param_t;

public:
    Video_Player();
    virtual ~Video_Player();

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
    Video_Player_View View;
    Video_Player_Model Model;
    lv_timer_t* timer;
};

}

#endif
