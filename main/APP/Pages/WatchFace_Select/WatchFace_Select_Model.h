#ifndef __WatchFace_Select_Model_H
#define __WatchFace_Select_Model_H

#include "Common/DataProc/DataProc.h"

namespace Page
{

class WatchFace_Select_Model
{
public:
    void Init();
    void Deinit();

private:
    Account* account;

private:
    static int onEvent(Account* account, Account::EventParam_t* param);
};

}

#endif
