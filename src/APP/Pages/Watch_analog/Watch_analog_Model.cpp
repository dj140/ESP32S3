#include "Watch_analog_Model.h"
#include "cstring"

using namespace Page;

void Watch_analog_Model::Init()
{
    account = new Account("Watch_analog_Model", DataProc::Center(), 0, this);
    account->Subscribe("Clock");

    account->SetEventCallback(onEvent);
}
void Watch_analog_Model::Deinit()
{
    if (account)
    {
        delete account;
        account = nullptr;
    }
}
uint32_t Watch_analog_Model::GetData()
{
    return lv_tick_get();
}

void Watch_analog_Model::GetClockinfo(HAL::Clock_Info_t* info)
{
    memset(info, 0, sizeof(HAL::Clock_Info_t));
    if (account->Pull("Clock", info, sizeof(HAL::Clock_Info_t)) != Account::RES_OK)
    {
        return;
    }
}

int Watch_analog_Model::onEvent(Account* account, Account::EventParam_t* param)
{
    if (param->event != Account::EVENT_PUB_PUBLISH)
    {
        return Account::RES_UNSUPPORTED_REQUEST;
    }

    //if (strcmp(param->tran->ID, "SportStatus") != 0
    //    || param->size != sizeof(HAL::SportStatus_Info_t))
    //{
    //    return Account::RES_PARAM_ERROR;
    //}

    //DialplateModel* instance = (DialplateModel*)account->UserData;
    //memcpy(&(instance->sportStatusInfo), param->data_p, param->size);

    return Account::RES_OK;
}

