#include "HAL.h"
//#include "rtc.h"




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


  /*##-2- Check if Data stored in BackUp register1: No Need to reconfigure RTC#*/
  /* Read the Back Up Register 1 Data */
//  if (HAL_RTCEx_BKUPRead(&RtcHandle, RTC_BKP_DR1) != 0x32F2)
//  {
//    /* Configure RTC Calendar */
//    RTC_CalendarConfig();
//  }
//  else
//  {
//    /* Check if the Power On Reset flag is set */
//    if (__HAL_RCC_GET_FLAG(RCC_FLAG_PORRST) != RESET)
//    {
//      /* Turn on LED2: Power on reset occurred */
////      BSP_LED_On(LED2);
//    }
//    /* Check if Pin Reset flag is set */
//    if (__HAL_RCC_GET_FLAG(RCC_FLAG_PINRST) != RESET)
//    {
//      /* Turn on LED1: External reset occurred */
////      BSP_LED_On(LED1);
//    }
//    /* Clear source Reset Flag */
//    __HAL_RCC_CLEAR_RESET_FLAGS();
//  }

}

void HAL::Clock_GetInfo(Clock_Info_t* info)
{

}

void HAL::Clock_SetInfo(const Clock_Info_t* info)
{
//  RTC_DateTypeDef sdatestructure;
//  RTC_TimeTypeDef stimestructure;

//  /*##-1- Configure the Date #################################################*/
//  /* Set Date: Tuesday February 18th 2014 */
//  sdatestructure.Year = info->year;
//  sdatestructure.Month = info->month;
//  sdatestructure.Date = info->day;
//  sdatestructure.WeekDay = info->week;
//  
//  if(HAL_RTC_SetDate(&RtcHandle,&sdatestructure,RTC_FORMAT_BCD) != HAL_OK)
//  {
//    /* Initialization Error */
////    Error_Handler();
//  }

//  /*##-2- Configure the Time #################################################*/
//  /* Set Time: 02:00:00 */
//  stimestructure.Hours = info->hour;
//  stimestructure.Minutes = info->minute;
//  stimestructure.Seconds = info->second;
//  stimestructure.TimeFormat = RTC_HOURFORMAT_24;
//  stimestructure.DayLightSaving = RTC_DAYLIGHTSAVING_NONE ;
//  stimestructure.StoreOperation = RTC_STOREOPERATION_RESET;

//  if (HAL_RTC_SetTime(&RtcHandle, &stimestructure, RTC_FORMAT_BCD) != HAL_OK)
//  {
//    /* Initialization Error */
////    Error_Handler();
//  }

//  /*##-3- Writes a data in a RTC Backup data Register1 #######################*/
//  HAL_RTCEx_BKUPWrite(&RtcHandle, RTC_BKP_DR1, 0x32F2);
//    RTC_SetTime(
//        info->year,
//        info->month,
//        info->day,
//        info->hour,
//        info->minute,
//        info->second
//    );
}

const char* HAL::Clock_GetWeekString(uint8_t week)
{
    const char* week_str[] = {"SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT"};
    return week < 7 ? week_str[week] : "";
}
