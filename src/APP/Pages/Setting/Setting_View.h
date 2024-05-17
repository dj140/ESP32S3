#ifndef __Setting_VIEW_H
#define __Setting_VIEW_H

#include "../Page.h"

namespace Page
{

class Setting_View
{
public:
    void Create(lv_obj_t* root);

public:
    struct
    {
        lv_obj_t* cont;
        lv_obj_t* bg_img;
        lv_obj_t* button;
    } ui;

private:

};

}

#endif // !__VIEW_H
