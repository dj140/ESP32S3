#ifndef __WatchFace_Select__VIEW_H
#define __WatchFace_Select__VIEW_H

#include "../Page.h"

namespace Page
{



class WatchFace_Select_View
{

public:
    typedef struct
    {
        lv_obj_t* cont;
        lv_obj_t* lableValue;
        lv_obj_t* lableUnit;
    } SubInfo_t;

public:
    int numFaces = 0;
    typedef struct WatchFace
    {
        const char* name;
        const void* preview;
        lv_obj_t* watchface;
    } Face;

    Face faces[15];


    lv_obj_t* ui_faceSelect;
    lv_obj_t* ui_home;


    struct
    {
        lv_obj_t* faceSelect;

        struct
        {
            lv_obj_t* cont;
            lv_obj_t* labelSpeed;
            lv_obj_t* labelUint;
        } topInfo;

        struct
        {
            lv_obj_t* cont;
            lv_obj_t* bg;
            lv_obj_t* labelClock;
            lv_obj_t* labelClockmin;
            lv_obj_t* labelClockhour;
            lv_obj_t* labelweek;
            lv_obj_t* labelday;

            SubInfo_t labelInfoGrp[4];
        } bottomInfo;

        struct
        {
            lv_obj_t* style1;
            lv_obj_t* style2;
            lv_obj_t* style3;
            lv_obj_t* style4;
        } watchface;

        lv_anim_timeline_t* anim_timeline;
    } ui;

    void Create(lv_obj_t* root);
    void Delete();
    void AppearAnimStart(bool reverse = false);
    void addWatchface(const char* name, const void* src, int index);
    void registerWatchface_cb(const char* name, const void* value, lv_obj_t* par);

private:
    void init_face_select(lv_obj_t* par);
    void ui_watchfaces_init(void);
    void TopInfo_Create(lv_obj_t* par);
    void BottomInfo_Create(lv_obj_t* par);
    void SubInfoGrp_Create(lv_obj_t* par, SubInfo_t* info, const char* unitText);
    void BtnCont_Create(lv_obj_t* par);
    lv_obj_t* Btn_Create(lv_obj_t* par, const void* img_src, lv_coord_t x_ofs);
};

}

#endif // !__VIEW_H
