#ifndef __StopWatch_VIEW_H
#define __StopWatch_VIEW_H

#include "../Page.h"

namespace Page
{
    // static lv_obj_t* labelTime;
    // static lv_obj_t* listHistory;

    typedef struct
    {
        lv_obj_t* list_btn;
        const char* text;
        const uint16_t btnVal;
    } ListBtn_Typedef;

    enum BtnGrpEnum
    {
        BtnReset,
        BtnStart,
        BtnAdd
    };
    static bool SW_IsPause = true;

    static uint32_t SW_CurrentTime = 0;
    static uint32_t SW_IntervalTime = 0;
    static uint32_t SW_LastTime = 0;
    static uint8_t  HistoryRecCnt = 0;

class StopWatch_View
{
public:
    void Create(lv_obj_t* root);
    void CreateAnim();
    void AppearAnimStart(bool reverse = false);
    void LabelTime_Create(lv_obj_t* par);
    void BtnGrp_Create(lv_obj_t* par);
    void listHistory_Create(lv_obj_t* par);

public:

    struct
    {
        lv_obj_t* cont;
        lv_obj_t* button_reset;
        lv_obj_t* button_pause;
        lv_obj_t* button_add;
        lv_obj_t* time;
        lv_obj_t* listHistory;
        lv_obj_t* button_img;

        lv_anim_timeline_t* anim_timeline;
    } ui;

private:

};

}

#endif // !__VIEW_H
