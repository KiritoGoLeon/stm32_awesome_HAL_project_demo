#ifndef __DRIVER_RTC_H_
#define __DRIVER_RTC_H_

#define TIME_BASE ((uint16_t)2000)

#include "common.h"


void driver_rtc_init(void);
void driver_rtc_handle(void);
void driver_rtc_exit(void);

void driver_rtc_set_time(uint16_t year,uint8_t month,uint8_t day,uint8_t weekday,uint8_t hours,uint8_t minutes,uint8_t seconds);
void driver_rtc_get_time(struct TimeTypeDef *time);

void driver_rtc_set_alarm(uint8_t alarm,uint8_t hours,uint8_t minutes, uint8_t seconds,void (*arg_alarm_a_callback)(void));
void driver_rtc_set_calalarm(uint8_t alarm,uint8_t hours,uint8_t minutes, uint8_t seconds,void (*arg_alarm_a_callback)(void));
void driver_rtc_set_wakeup_time(uint16_t time,void (*arg_alarm_a_callback)(void));
#endif

