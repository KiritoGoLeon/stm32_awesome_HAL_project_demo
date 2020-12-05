/*----------------------------------------------------------------------------------------------------------------
 * Copyright(c)
 * ---------------------------------------------------------------------------------------------------------------
 * File Name : kprotocol.c
 * Author    : kirito
 * Brief     : 
 * Date      :  2020.11.06
 * ---------------------------------------------------------------------------------------------------------------
 * Modifier                                    Data                                             Brief
 * -------------------------------------------------------------------------------------------------------------*/

#include "driver_rtc.h"
#include "rtc.h"

static struct TimeTypeDef g_time;
static RTC_TimeTypeDef g_timestructure;
static RTC_DateTypeDef g_datestructure;

static void driver_rtc_update_time(void);

/**
* @ Function Name : kprotocol_init
* @ Author        : kirito
* @ Brief         : service
* @ Date          : 2020.11.06
* @ Modify        : ...
**/
void driver_rtc_init(void)
{
  MX_RTC_Init();
}

/**
* @ Function Name : kprotocol_handle
* @ Author        : kirito
* @ Brief         : service
* @ Date          : 2020.11.06
* @ Modify        : ...
**/
void driver_rtc_handle(void)
{
	driver_rtc_update_time();
}


/**
* @ Function Name : kprotocol_exit
* @ Author        : kirito
* @ Brief         : service
* @ Date          : 2020.11.06
* @ Modify        : ...
**/
void driver_rtc_exit(void)
{
	
}

// 设置时间
void driver_rtc_set_time(uint16_t year,uint8_t month,uint8_t day,uint8_t weekday,uint8_t hours,uint8_t minutes,uint8_t seconds)
{

	RTC_TimeTypeDef RTC_Time = {0};
  RTC_DateTypeDef RTC_Date = {0};
	
	RTC_Time.Hours = hours;
	RTC_Time.Minutes = minutes;
	RTC_Time.Seconds = seconds;
	RTC_Time.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
	RTC_Time.StoreOperation = RTC_STOREOPERATION_RESET;
	HAL_RTC_SetTime(&hrtc, &RTC_Time, RTC_FORMAT_BIN);
			
	RTC_Date.WeekDay = weekday;
	RTC_Date.Month = month;
	RTC_Date.Date = day;
	RTC_Date.Year =year-TIME_BASE;	
	HAL_RTC_SetDate(&hrtc, &RTC_Date, RTC_FORMAT_BIN);
	
}

// 获得时间
void driver_rtc_get_time(struct TimeTypeDef *time)
{
	*time = g_time;
}

// 更新时间
void driver_rtc_update_time(void)
{
		/* Get the RTC current Time ,must get time first*/
	HAL_RTC_GetTime(&hrtc, &g_timestructure, RTC_FORMAT_BIN);
	/* Get the RTC current Date */
	HAL_RTC_GetDate(&hrtc, &g_datestructure, RTC_FORMAT_BIN);

	g_time.year = g_datestructure.Year;
	g_time.month = g_datestructure.Month;
	g_time.day = g_datestructure.Date;
	g_time.weekday = g_datestructure.WeekDay;
	
	g_time.hours = g_timestructure.Hours;
	g_time.minutes = g_timestructure.Minutes;
	g_time.seconds = g_timestructure.Seconds;
	
	g_time.year = g_time.year + TIME_BASE;
}

// 设置普通闹钟
void driver_rtc_set_alarm(uint8_t alarm,uint8_t hours,uint8_t minutes, uint8_t seconds,void (*arg_alarm_a_callback)(void))
{
	MX_RTC_set_alarm(alarm,hours,minutes, seconds,arg_alarm_a_callback);
}


// 设置计时器闹钟
void driver_rtc_set_calalarm(uint8_t alarm,uint8_t hours,uint8_t minutes, uint8_t seconds,void (*arg_alarm_a_callback)(void))
{
	MX_RTC_set_calalarm(alarm,hours,minutes, seconds,arg_alarm_a_callback);
}

// 设置定时唤醒
void driver_rtc_set_wakeup_time(uint16_t time,void (*arg_alarm_a_callback)(void))
{
	MX_RTC_set_wakeup_time(time,arg_alarm_a_callback);
}

