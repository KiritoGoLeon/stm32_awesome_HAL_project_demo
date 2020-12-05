/*----------------------------------------------------------------------------------------------------------------
 * Copyright(c)
 * ---------------------------------------------------------------------------------------------------------------
 * File Name : kprotocol.c
 * Author    : kirito
 * Brief     : ????
 * Date      :  2020.11.06
 * ---------------------------------------------------------------------------------------------------------------
 * Modifier                                    Data                                             Brief
 * -------------------------------------------------------------------------------------------------------------*/

#include "module_itemp.h"
#include "board.h"
#include "adc.h"



static uint32_t temp_adc_value;
static float temp_value;
/**
* @ Function Name : kprotocol_init
* @ Author        : kirito
* @ Brief         : service
* @ Date          : 2020.11.06
* @ Modify        : ...
**/
void module_itemp_init(void)
{
	 MX_ADC1_set_mem_addr(&temp_adc_value);
}

/**
* @ Function Name : kprotocol_handle
* @ Author        : kirito
* @ Brief         : service
* @ Date          : 2020.11.06
* @ Modify        : ...
**/
void module_itemp_handle(void)
{
	temp_value = ((temp_adc_value*3300/4096-760)/2.5+25);
}


/**
* @ Function Name : kprotocol_exit
* @ Author        : kirito
* @ Brief         : service
* @ Date          : 2020.11.06
* @ Modify        : ...
**/
void module_itemp_exit(void)
{

}

float module_itemp_get_temp(void)
{
		return temp_value;
}
