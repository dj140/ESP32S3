#ifndef __WATCH_ANALOG_MODEL_H
#define __WATCH_ANALOG_MODEL_H

#include "lvgl.h"
#include "APP/Common/DataProc/DataProc.h"

namespace Page
{

class Watch_analog_Model
{
public:
    HAL::Clock_Info_t clock;

public:
    uint32_t TickSave;
    uint32_t GetData();
    void GetClockinfo(HAL::Clock_Info_t* info);


    void Init();
    void Deinit();

private:
    Account* account;

private:
    static int onEvent(Account* account, Account::EventParam_t* param);

};

}

#endif
