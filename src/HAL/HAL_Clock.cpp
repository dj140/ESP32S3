#include "HAL.h"
//#include "rtc.h"
#include <ESP32Time.h>

//ESP32Time rtc;
ESP32Time rtc(3600);  // offset in seconds GMT+1



/**
  * @brief  Configure the current time and date.
  * @param  None
  * @retval None
  */
static void RTC_CalendarConfig(void)
{

}

void HAL::Clock_Init()
{
  rtc.setTime(30, 24, 15, 5, 6, 2024);  // 17th Jan 2024 15:24:30
}

void HAL::Clock_GetInfo(Clock_Info_t* info)
{

  info->year = rtc.getYear();
  info->month = rtc.getMonth();
  info->day = rtc.getDay();
  info->week = rtc.getDayofWeek();
  info->hour = rtc.getHour(true);
  info->minute = rtc.getMinute();
  info->second = rtc.getSecond();
  info->millisecond = rtc.getMillis();
  // Serial.println(rtc.getTime("%A, %B %d %Y %H:%M:%S"));   // (String) returns time with specified format 
  // struct tm timeinfo = rtc.getTimeStruct();
}

void HAL::Clock_SetInfo(const Clock_Info_t* info)
{
    rtc.setTime(info->second, info->minute, info->hour, info->day, info->month, info->year);  // 17th Jan 2021 15:24:30
}

const char* HAL::Clock_GetWeekString(uint8_t week)
{
    const char* week_str[] = {"SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT"};
    return week < 7 ? week_str[week] : "";
}
