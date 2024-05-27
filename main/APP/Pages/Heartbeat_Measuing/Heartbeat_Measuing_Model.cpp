#include "Heartbeat_Measuing_Model.h"

using namespace Page;

uint32_t Heartbeat_Measuing_Model::GetData()
{
    return lv_tick_get();
}
