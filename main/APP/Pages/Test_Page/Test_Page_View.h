#ifndef __Test_Page_VIEW_H
#define __Test_Page_VIEW_H

#include "../Page.h"

namespace Page
{

class Test_Page_View
{
public:
    void Create(lv_obj_t* root);

public:
    struct
    {
        lv_obj_t* cont;
        lv_obj_t* menu;
        lv_obj_t* rootPage;
        lv_obj_t* sidebar;
        lv_obj_t* button;
        lv_obj_t* Brightness;
    } ui;

private:

};

}

#endif // !__VIEW_H
