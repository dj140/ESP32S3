#include "Video_Player_Model.h"

using namespace Page;

uint32_t Video_Player_Model::GetData()
{
    return lv_tick_get();
}
