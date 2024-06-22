#ifndef __Test_Page_H
#define __Test_Page_H

#include "Test_Page_View.h"
#include "Test_Page_Model.h"

namespace Page
{

class Test_Page : public PageBase
{
public:
    typedef struct
    {
        uint16_t time;
        lv_color_t color;
    } Param_t;

public:
    Test_Page();
    virtual ~Test_Page();

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
    void AttachEvent(lv_obj_t* obj, lv_event_cb_t event_cb, lv_event_code_t filter);
    static void onTimerUpdate(lv_timer_t* timer);
    static void onEvent(lv_event_t* event);
    static void switch_handler(lv_event_t* event);
    static void brightness_handler(lv_event_t* event);
    
private:
    Test_Page_View View;
    Test_Page_Model Model;
    lv_timer_t* timer;
};

}

#endif
