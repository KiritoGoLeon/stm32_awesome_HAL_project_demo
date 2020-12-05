/*----------------------------------------------------------------------------------------------------------------
 * Copyright(c)
 * ---------------------------------------------------------------------------------------------------------------
 * File Name : board.c
 * Author    : kirito
 * Brief     : 板子管理
 * Date      : 2016.07.02
 * ---------------------------------------------------------------------------------------------------------------
 * Modifier                                    Data                                             Brief
 * -------------------------------------------------------------------------------------------------------------*/

#include "board.h"
#include "common.h"

/**
* @ Function Name : driver_manager_init
* @ Author        : kirito
* @ Brief         : driver管理初始化
* @ Date          : 2020.11.06
* @ Modify        : ...
**/
void board_init(void)
{
    
}

void delay_ms(int val)
{
	HAL_Delay(val);
}

void delay_us(int val)
{
	
}

void usleep(long value)
{
	delay_us(value);
}
void sleep(float value)
{
	delay_ms(value*1000);
}

// gpio
void gpio_write(GPIO_TypeDef *GPIOx, uint32_t PinMask,uint8_t state)
{
	#ifdef GPIO_USE_LL
	if(state){
		LL_GPIO_SetOutputPin(GPIOx,PinMask);
	}else{
		LL_GPIO_ResetOutputPin(GPIOx,PinMask);
	}
	#else
	HAL_GPIO_WritePin(GPIOx,PinMask,state);
	#endif
}


