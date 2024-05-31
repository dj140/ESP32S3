#ifndef __IMAGE_PLAYER_VIEW_H
#define __IMAGE_PLAYER_VIEW_H

#include "../Page.h"

namespace Page
{

class Image_Player_View
{
public:
    void Create(lv_obj_t* root);
    uint32_t Storage_GetDirectoryBitmapFiles (const char* DirName, char* Files[]);

public:
    struct
    {
        lv_obj_t* cont;
        lv_obj_t* lottie;
        lv_obj_t* image;

    } ui;

private:

};

}

#endif // !__VIEW_H
