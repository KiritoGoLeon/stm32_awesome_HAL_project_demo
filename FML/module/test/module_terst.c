/*----------------------------------------------------------------------------------------------------------------
 * Copyright(c)
 * ---------------------------------------------------------------------------------------------------------------
 * File Name : service_com.c
 * Author    : kirito
 * Brief     : ????
 * Date      :  2020.11.06
 * ---------------------------------------------------------------------------------------------------------------
 * Modifier                                    Data                                             Brief
 * -------------------------------------------------------------------------------------------------------------*/

#include "module_test.h"
#include "gpio.h"
#include "board.h"
#include "driver_com.h"
#include "adc.h"
#include "sdio.h"

#include "fatfs.h"
#include <string.h>





void callback(uint8_t data)
{
    //drv_com1_write(data);
}
/**
* @ Function Name : service_com_init
* @ Author        : kirito
* @ Brief         : service
* @ Date          : 2020.11.06
* @ Modify        : ...
**/
void module_test_init(void)
{
    MX_GPIO_Init();
    driver_com_regist_reccallback((uint32_t)USART1,callback);
    printf("----------- sys reset init ----------");
    //fatfs_test();

}







/**
* @ Function Name : service_com_handle
* @ Author        : kirito
* @ Brief         : service????
* @ Date          : 2020.11.06
* @ Modify        : ...
**/
void module_test_handle(void)
{

    //printf("hello world");
    //char sd = HAL_GPIO_ReadPin(KEY1_GPIO_Port,KEY1_Pin);
    //printf("KEY:%d",sd);


    //printf(" AD1 value = %1.3fV \r\n",ADC_Value1*3.3f/4096);


//	  HAL_ADC_Start(&hadc1);
//	 HAL_ADC_PollForConversion(&hadc1, 50);

//      /* Check if the continous conversion of regular channel is finished */
//      if(HAL_IS_BIT_SET(HAL_ADC_GetState(&hadc1), HAL_ADC_STATE_REG_EOC))
//      {
//          /*##-3- Get the converted value of regular channel  ######################*/
//          AD_Value = HAL_ADC_GetValue(&hadc1);
//          printf("MCU Temperature : %.1f\r\n",((AD_Value*3300/4096-760)/2.5+25));
//      }
}



/**
* @ Function Name : service_com_exit
* @ Author        : kirito
* @ Brief         : service????
* @ Date          : 2020.11.06
* @ Modify        : ...
**/
void module_test_exit(void)
{

}
