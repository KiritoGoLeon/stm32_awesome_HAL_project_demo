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


#include "service_monitor.h"
#include "module_iwdg.h"
#include "module_itemp.h"
#include "module_time.h"
#include "module_pwr.h"

#include "gpio.h"
#include "board.h"
#include "module_log.h"
#include "module_filesystem.h"



static void mtimer_callback(void)
{
	printf("\r\n---- reboot --\r\n");
}

volatile char g_satate = 0;
static void mcaltimer_callback(void)
{
	module_pwr_stop_mode_wake();
	g_satate = 1;
}

static void time_wakeup_callback(void)
{
	
	printf("\r\n---- wake up --\r\n");
}




/**
* @ Function Name : service_com_init
* @ Author        : kirito
* @ Brief         : service?????
* @ Date          : 2020.11.06
* @ Modify        : ...
**/
void service_monitor_init(void)
{
		  /* Check and handle if the system was resumed from Standby mode 确认系统是否从待机模式恢复*/ 
  if (__HAL_PWR_GET_FLAG(PWR_FLAG_SB) != RESET)
  {
    /* Clear Standby flag 如果恢复则清楚待机标志位*/
    __HAL_PWR_CLEAR_FLAG(PWR_FLAG_SB);
		printf("\r\n my standby rest\r\n");
  }
	
	module_iwdg_init();
	module_itemp_init();
	module_time_init();
	module_pwr_init();
	module_log_init();
	module_filesystem_init();
	
	//module_time_set_alarm(0,16,16,40,mtimer_callback);
	//module_time_set_calalarm(1,0,0,5,mcaltimer_callback);
	//module_time_set_wakeup_time(5,time_wakeup_callback);
	//module_pwr_enter_stop_mode();
	//module_pwr_enter_standby_mode();
}


/**
* @ Function Name : service_com_handle
* @ Author        : kirito
* @ Brief         : service????
* @ Date          : 2020.11.06
* @ Modify        : ...
**/
void service_monitor_handle(void)
{
	
	module_itemp_handle();
	module_time_handle();
	module_pwr_handle();
	module_iwdg_handle();
	module_log_handle();
	module_filesystem_handle();

//	gpio_write(LED1_GPIO_Port,LED1_Pin,1);
//	delay_ms(200);
//	gpio_write(LED1_GPIO_Port,LED1_Pin,0);
//	delay_ms(200);
//	
	//Logv("init","init ok");
}


/**
* @ Function Name : service_com_exit
* @ Author        : kirito
* @ Brief         : service????
* @ Date          : 2020.11.06
* @ Modify        : ...
**/
void service_monitor_exit(void)
{
	module_iwdg_exit();
}
