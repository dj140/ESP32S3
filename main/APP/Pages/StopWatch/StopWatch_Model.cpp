#include "StopWatch_Model.h"

using namespace Page;

uint32_t StopWatch_Model::GetData()
{
    return lv_tick_get();
}
