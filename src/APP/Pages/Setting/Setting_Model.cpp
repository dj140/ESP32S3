#include "Setting_Model.h"

using namespace Page;

uint32_t Setting_Model::GetData()
{
    return lv_tick_get();
}
