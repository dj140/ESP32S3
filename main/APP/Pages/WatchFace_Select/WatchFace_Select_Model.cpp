#include "WatchFace_Select_Model.h"

using namespace Page;

void WatchFace_Select_Model::Init()
{
    account = new Account("WatchFace_Select_Model", DataProc::Center(), 0, this);

    account->SetEventCallback(onEvent);
}

void WatchFace_Select_Model::Deinit()
{
    if (account)
    {
        delete account;
        account = nullptr;
    }
}


int WatchFace_Select_Model::onEvent(Account* account, Account::EventParam_t* param)
{
    if (param->event != Account::EVENT_PUB_PUBLISH)
    {
        return Account::RES_UNSUPPORTED_REQUEST;
    }
    WatchFace_Select_Model* instance = (WatchFace_Select_Model*)account->UserData;

    return Account::RES_OK;
}

