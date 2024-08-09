#include "Video_Player_Model.h"

using namespace Page;

void Video_Player_Model::Init()
{
    account = new Account("Video_Player_Model", DataProc::Center(), 0, this);

    account->Subscribe("Button");

}

void Video_Player_Model::Deinit()
{
    if (account)
    {
        delete account;
        account = nullptr;
    }
}

void Video_Player_Model::GetButtonInfo(bool* status)
{

    HAL::Button_Info_t Button = { 0 };
    account->Pull("Button", &Button, sizeof(Button));
    *status = Button.PRESS;

}
