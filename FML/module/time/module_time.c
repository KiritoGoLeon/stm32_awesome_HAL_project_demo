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

#include "module_time.h"
#include "driver_rtc.h"


/**
* @ Function Name : kprotocol_init
* @ Author        : kirito
* @ Brief         : service
* @ Date          : 2020.11.06
* @ Modify        : ...
**/
void module_time_init(void)
{
	driver_rtc_init();
	driver_rtc_set_time(2020,11,13,5,16,16,30);
	driver_rtc_handle();
}


/**
* @ Function Name : kprotocol_handle
* @ Author        : kirito
* @ Brief         : service
* @ Date          : 2020.11.06
* @ Modify        : ...
**/
void module_time_handle(void)
{
	 driver_rtc_handle();
	
	// struct TimeTypeDef time;
	// driver_rtc_get_time(&time);
	// printf("time:%d-%d-%d %d:%d:%d\r\n",time.year,time.month,time.day,time.hours,time.minutes,time.seconds);
}


/**
* @ Function Name : kprotocol_exit
* @ Author        : kirito
* @ Brief         : service
* @ Date          : 2020.11.06
* @ Modify        : ...
**/
void module_time_exit(void)
{

}

// 设置时间
void module_time_set_time(uint16_t year,uint8_t month,uint8_t day,uint8_t weekday,uint8_t hours,uint8_t minutes,uint8_t seconds)
{
	driver_rtc_set_time(year,month, day,weekday,hours,minutes,seconds);
}

// 获得时间
void module_time_get_time(struct TimeTypeDef *time)
{
	driver_rtc_get_time(time);
}

// 设置计时器闹钟
void module_time_set_alarm(uint8_t alarm,uint8_t hours,uint8_t minutes, uint8_t seconds,void (*arg_alarm_a_callback)(void))
{
	driver_rtc_set_alarm(alarm,hours, minutes, seconds,arg_alarm_a_callback);
}

// 设置闹钟
void module_time_set_calalarm(uint8_t alarm,uint8_t hours,uint8_t minutes, uint8_t seconds,void (*arg_alarm_a_callback)(void))
{
	driver_rtc_set_calalarm(alarm,hours, minutes, seconds,arg_alarm_a_callback);
}
// 设置定时唤醒
void module_time_set_wakeup_time(uint16_t time,void (*arg_alarm_a_callback)(void))
{
	driver_rtc_set_wakeup_time(time,arg_alarm_a_callback);
}

