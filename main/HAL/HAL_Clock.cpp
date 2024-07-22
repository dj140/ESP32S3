#include "HAL.h"
//#include "rtc.h"
#include "esp_sntp.h"
#include "esp_log.h"
#include "time.h"

static const char *TAG = "RTC";

time_t now;
char strftime_buf[64];
struct tm timeinfo;
struct timeval tv_now;

/**
  * @brief  Configure the current time and date.
  * @param  None
  * @retval None
  */
static void RTC_CalendarConfig(void)
{

}
/*!
    @brief  get the internal RTC time as a tm struct
*/
tm getTimeStruct(){
  struct tm timeinfo;
  time_t now;
  time(&now);
  localtime_r(&now, &timeinfo);
  time_t tt = mktime (&timeinfo);  
  struct tm * tn = localtime(&tt);
  return *tn;
}

void HAL::Clock_Init()
{
  time(&now);
  // Set timezone to China Standard Time
  setenv("TZ", "CST-8", 1);
  tzset();
    // 设置当前时间
  timeinfo.tm_year = 2024 - 1900;  // 设置年份
  timeinfo.tm_mon = 5 - 1;  // 设置月份
  timeinfo.tm_mday = 2;  // 设置日期
  timeinfo.tm_hour = 13;  // 设置小时
  timeinfo.tm_min = 45;  // 设置分钟
  timeinfo.tm_sec = 30;  // 设置秒
  const time_t now = mktime(&timeinfo);  // 将tm结构体转换为time_t格式
  struct timeval tv = { .tv_sec = now };  // 定义一个timeval结构体变量tv，并设置其秒数
  settimeofday(&tv, NULL);  // 设置系统时间
}

void HAL::Clock_GetInfo(Clock_Info_t* info)
{
  timeinfo = getTimeStruct();
  strftime(strftime_buf, sizeof(strftime_buf), "%c", &timeinfo);
  
  gettimeofday(&tv_now, NULL);
  int64_t time_us = (int64_t)tv_now.tv_sec * 1000000L + (int64_t)tv_now.tv_usec;

  info->year = timeinfo.tm_year;
  info->month = timeinfo.tm_mon;
  info->day = timeinfo.tm_mday;
  info->week = timeinfo.tm_wday;
  info->hour = timeinfo.tm_hour;
  info->minute = timeinfo.tm_min;
  info->second = timeinfo.tm_sec;
  info->millisecond = time_us;

  ESP_LOGI(TAG, "The current date/time in Shanghai is: %s", strftime_buf);
}

void HAL::Clock_SetInfo(const Clock_Info_t* info)
{
  timeinfo.tm_year = info->year - 1900;  // 设置年份
  timeinfo.tm_mon = info->month - 1;  // 设置月份
  timeinfo.tm_mday = info->day;  // 设置日期
  timeinfo.tm_hour = info->hour;  // 设置小时
  timeinfo.tm_min = info->minute;  // 设置分钟
  timeinfo.tm_sec = info->second;  // 设置秒
  setenv("TZ", "CST-8", 1);  // 设置时区为中国标准时间
  tzset();  // 使时区设置生效
  const time_t now = mktime(&timeinfo);  // 将tm结构体转换为time_t格式
  struct timeval tv = { .tv_sec = now };  // 定义一个timeval结构体变量tv，并设置其秒数
  settimeofday(&tv, NULL);  // 设置系统时间
}

const char* HAL::Clock_GetWeekString(uint8_t week)
{
    const char* week_str[] = {"SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT"};
    return week < 7 ? week_str[week] : "";
}
