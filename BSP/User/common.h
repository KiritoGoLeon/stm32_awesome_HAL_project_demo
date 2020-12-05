#ifndef __COMMON_H_
#define __COMMON_H_

#include "stdint.h"
#include "stdio.h"
#include <stdarg.h>

struct TimeTypeDef{
	uint16_t year;
	uint8_t month;
	uint8_t day;
	uint8_t weekday;
	uint8_t hours;
	uint8_t minutes;
	uint8_t seconds;
};


#endif
