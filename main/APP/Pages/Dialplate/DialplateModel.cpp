#include "DialplateModel.h"
#include "cstring"

using namespace Page;

void DialplateModel::Init()
{
    account = new Account("DialplateModel", DataProc::Center(), 0, this);
    account->Subscribe("Clock");
    account->Subscribe("Power");
//    account->Subscribe("StatusBar");
//    account->Subscribe("GPS");
//    account->Subscribe("MusicPlayer");
    account->SetEventCallback(onEvent);
}

void DialplateModel::Deinit()
{
    if (account)
    {
        delete account;
        account = nullptr;
    }
}

void DialplateModel::GetClockinfo(HAL::Clock_Info_t* info)
{
    memset(info, 0, sizeof(HAL::Clock_Info_t));
    if (account->Pull("Clock", info, sizeof(HAL::Clock_Info_t)) != Account::RES_OK)
    {
        return;
    }
}

void DialplateModel::GetPowerInfo(HAL::Power_Info_t* info)
{
    memset(info, 0, sizeof(HAL::Power_Info_t));
    if (account->Pull("Clock", info, sizeof(HAL::Power_Info_t)) != Account::RES_OK)
    {
        return;
    }
}

int DialplateModel::onEvent(Account* account, Account::EventParam_t* param)
{
    if (param->event != Account::EVENT_PUB_PUBLISH)
    {
        return Account::RES_UNSUPPORTED_REQUEST;
    }

    return Account::RES_OK;
}
