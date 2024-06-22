#include "Test_Page_Model.h"

using namespace Page;

uint32_t Test_Page_Model::GetData()
{
    return lv_tick_get();
}
