#ifndef __Video_Player_MODEL_H
#define __Video_Player_MODEL_H

#include "lvgl.h"
#include "APP/Common/DataProc/DataProc.h"

namespace Page
{

class Video_Player_Model
{
public:
    void Init();
    void Deinit();
    void GetButtonInfo(bool* status);

private:
    Account* account;

};

}

#endif
