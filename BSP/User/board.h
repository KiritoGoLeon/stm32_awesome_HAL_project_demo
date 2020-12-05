#ifndef __BSP_BOARD_MANAGER_H_
#define __BSP_BOARD_MANAGER_H_

#define GPIO_USE_LL

#include "main.h"
#include "common.h"

void board_init(void);
void delay_ms(int val);
void delay_us(int val);
void usleep(long value);
void sleep(float value);

void gpio_write(GPIO_TypeDef *GPIOx, uint32_t PinMask,uint8_t state);

#endif
