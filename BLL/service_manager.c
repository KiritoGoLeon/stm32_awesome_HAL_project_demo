/*----------------------------------------------------------------------------------------------------------------
 * Copyright(c)
 * ---------------------------------------------------------------------------------------------------------------
 * File Name : service_manager.c
 * Author    : kirito
 * Brief     : 业务管理
 * Date      :  2020.11.06
 * ---------------------------------------------------------------------------------------------------------------
 * Modifier                                    Data                                             Brief
 * -------------------------------------------------------------------------------------------------------------*/

#include "service_manager.h"
#include "service_com.h"
#include "service_test.h"
#include "service_monitor.h"

/**
* @ Function Name : service_manager_init
* @ Author        : kirito
* @ Brief         : service管理初始化
* @ Date          : 2020.11.06
* @ Modify        : ...
**/
void service_manager_init(void)
{
	service_com_init();
	service_monitor_init();
	
	service_test_init();

}

/**
* @ Function Name : service_manager_handle
* @ Author        : kirito
* @ Brief         : service管理处理
* @ Date          : 2020.11.06
* @ Modify        : ...
**/
void service_manager_handle(void)
{
	service_com_handle();
	service_monitor_handle();
	
	service_test_handle();

}

/**
* @ Function Name : service_manager_exit
* @ Author        : kirito
* @ Brief         : service管理退出
* @ Date          : 2020.11.06
* @ Modify        : ...
**/
void service_manager_exit(void)
{
}
