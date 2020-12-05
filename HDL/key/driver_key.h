#ifndef __DRIVER_KEY_H_
#define __DRIVER_KEY_H_

#include "common.h"

#define KEY_SIZE 10
typedef struct KeyFifoTypedef_TAG
{
	uint8_t buff[KEY_SIZE];
	uint8_t read_p;
	uint8_t write_p;
}KeyFifoTypedef;


void driver_key_init(void);
void driver_key_handle(void);
void driver_key_exit(void);

#endif

