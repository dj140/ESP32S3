#include "DataProc.h"
#include "../HAL/HAL.h"

static int onEvent(Account* account, Account::EventParam_t* param)
{
    if (param->event == Account::EVENT_PUB_PUBLISH)
    {
        
        return Account::RES_OK;
    }

    if (param->event != Account::EVENT_SUB_PULL)
    {
        return Account::RES_UNSUPPORTED_REQUEST;
    }

    if (param->size != sizeof(HAL::Button_Info_t))
    {
        return Account::RES_SIZE_MISMATCH;
    }

    HAL::Button_Info_t* info = (HAL::Button_Info_t*)param->data_p;
    HAL::Button_GetInfo(info);

    return Account::RES_OK;
}


DATA_PROC_INIT_DEF(Button)
{
    // HAL::Button_SetCommitCallback([](void* info, void* userData){
    //     Account* account = (Account*)userData;
    //     return account->Commit(info, sizeof(HAL::Button_Info_t));
    // }, account);
    account->SetEventCallback(onEvent);
}
