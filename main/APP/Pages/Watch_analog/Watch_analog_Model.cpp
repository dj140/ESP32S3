#include "Watch_analog_Model.h"

using namespace Page;

uint32_t Watch_analog_Model::GetData()
{
    return lv_tick_get();
}
