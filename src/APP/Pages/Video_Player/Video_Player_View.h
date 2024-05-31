#ifndef __Video_Player_VIEW_H
#define __Video_Player_VIEW_H

#include "../Page.h"

namespace Page
{

class Video_Player_View
{
public:
    void Create(lv_obj_t* root);
    uint32_t Storage_GetDirectoryBitmapFiles (const char* DirName, char* Files[]);

public:
    struct
    {
        lv_obj_t* labelTitle;
        lv_obj_t* Spinner;
        lv_obj_t* cont;
        lv_obj_t* canvas;

    } ui;

private:

};

}

#endif // !__VIEW_H
