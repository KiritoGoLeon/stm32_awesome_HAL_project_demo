#ifndef __MODULE_TIME_H_
#define __MODULE_TIME_H_
#include "common.h"

void module_time_init(void);
void module_time_handle(void);
void module_time_exit(void);

void module_time_set_time(uint16_t year,uint8_t month,uint8_t day,uint8_t weekday,uint8_t hours,uint8_t minutes,uint8_t seconds);
void module_time_get_time(struct TimeTypeDef *time);
void module_time_set_alarm(uint8_t alarm,uint8_t hours,uint8_t minutes, uint8_t seconds,void (*arg_alarm_a_callback)(void));
void module_time_set_calalarm(uint8_t alarm,uint8_t hours,uint8_t minutes, uint8_t seconds,void (*arg_alarm_a_callback)(void));
void module_time_set_wakeup_time(uint16_t time,void (*arg_alarm_a_callback)(void));
#endif
