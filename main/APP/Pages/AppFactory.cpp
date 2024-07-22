  /*
 * MIT License
 * Copyright (c) 2021 _VIFEXTech
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#include "AppFactory.h"
#include "Video_Player/Video_Player.h"
//#include "LiveMap/LiveMap.h"
#include "Dialplate/Dialplate.h"
#include "SystemInfos/SystemInfos.h"
#include "StartUp/StartUp.h"
#include "Blood_oxy/Blood_oxy.h"
#include "Heartbeat_Measuing/Heartbeat_Measuing.h"
#include "Setting/Setting.h"
#include "Watch_analog/Watch_analog.h"
#include "Watch_cxk/Watch_cxk.h"
#include "Image_Player/Image_Player.h"
// #include "Menu/Menu.h"
#include "Test_Page/Test_Page.h"
#include "StopWatch/StopWatch.h"
#include "WatchFace_Select/WatchFace_Select.h"

#define APP_CLASS_MATCH(className)\
do{\
    if (strcmp(name, #className) == 0)\
    {\
        return new Page::className;\
    }\
}while(0)

PageBase* AppFactory::CreatePage(const char* name)
{
    APP_CLASS_MATCH(Video_Player);
    APP_CLASS_MATCH(Dialplate);
    APP_CLASS_MATCH(SystemInfos);
    APP_CLASS_MATCH(Startup);
    APP_CLASS_MATCH(Watch_analog);
    APP_CLASS_MATCH(Blood_oxy);
    APP_CLASS_MATCH(Heartbeat_Measuing);
    APP_CLASS_MATCH(Setting);
    APP_CLASS_MATCH(Watch_cxk);
    APP_CLASS_MATCH(Image_Player);
    APP_CLASS_MATCH(Test_Page);
    APP_CLASS_MATCH(StopWatch);
    APP_CLASS_MATCH(WatchFace_Select);

    return nullptr;
}