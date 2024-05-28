#ifndef __IMAGE_PLAYER_PRESENTER_H
#define __IMAGE_PLAYER_PRESENTER_H

#include "Image_Player_View.h"
#include "Image_Player_Model.h"

namespace Page
{

class Image_Player : public PageBase
{
public:
    typedef struct
    {
        uint16_t time;
        lv_color_t color;
    } Param_t;

public:
    Image_Player();
    virtual ~Image_Player();

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
    Image_Player_View View;
    Image_Player_Model Model;
    lv_timer_t* timer;
};

}

#endif
