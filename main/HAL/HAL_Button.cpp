#include "HAL/HAL.h"
#include "ButtonEvent.h"

static HAL::CommitFunc_t CommitFunc = nullptr;
static void* UserData = nullptr;

static ButtonEvent EncoderPush(1000);

using namespace HAL;


bool press;

static void Encoder_PushHandler(ButtonEvent* btn, int event)
{

    if(event == ButtonEvent::EVENT_PRESSED)
    {
        press = 1;
        // info->PRESS = ~info->PRESS;
        // printf("EVENT_CLICKED : %d \n", press);

    }
    if(event == ButtonEvent::EVENT_RELEASED)
    {
        press = 0;
        // printf("EVENT_LONG_PRESSED  \n");
    }

}
void HAL::Button_Init()
{
    gpio_reset_pin(GPIO_NUM_39);
    gpio_set_direction(GPIO_NUM_39, GPIO_MODE_INPUT);
    // gpio_set_pull_mode(GPIO_NUM_39, GPIO_PULLUP_PULLDOWN);
    EncoderPush.EventAttach(Encoder_PushHandler);
}

// void HAL::Button_SetCommitCallback(CommitFunc_t func, void* userData)
// {
//     CommitFunc = func;
//     UserData = userData;
// }

void HAL::Button_Update()
{
    
    EncoderPush.EventMonitor(Button_GetIsPush());

    // if(CommitFunc)
    // {
    //     CommitFunc(&info, UserData);
    // }
    // if(PRESS = 1)
    // {
    //     info->PRESS = 1;
    //     printf("EVENT_PRESSED  \n");
    // }
    // else
    // {
    //     info->PRESS = 0;
    //     printf("EVENT_RELESED  \n");
    // }
}
bool HAL::Button_GetIsPush()
{
    return (gpio_get_level(GPIO_NUM_39) == 0);
}
void HAL::Button_GetInfo(Button_Info_t* info)
{
    if(press == 1)
    {
        info->PRESS = 1;
        // printf("EVENT_PRESSED  \n");
    }
    else
    {
        info->PRESS = 0;
    }
}

