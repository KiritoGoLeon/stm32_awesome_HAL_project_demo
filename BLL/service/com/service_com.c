/*----------------------------------------------------------------------------------------------------------------
 * Copyright(c)
 * ---------------------------------------------------------------------------------------------------------------
 * File Name : service_com.c
 * Author    : kirito
 * Brief     : 业务管理
 * Date      :  2020.11.06
 * ---------------------------------------------------------------------------------------------------------------
 * Modifier                                    Data                                             Brief
 * -------------------------------------------------------------------------------------------------------------*/

#include "service_com.h"
#include "module_kprotocol.h"

/**
* @ Function Name : service_com_init
* @ Author        : kirito
* @ Brief         : service管理初始化
* @ Date          : 2020.11.06
* @ Modify        : ...
**/
void service_com_init(void)
{
	module_kprotocol_init();
}

/**
* @ Function Name : service_com_handle
* @ Author        : kirito
* @ Brief         : service管理处理
* @ Date          : 2020.11.06
* @ Modify        : ...
**/
void service_com_handle(void)
{
	module_kprotocol_handle();
}


/**
* @ Function Name : service_com_exit
* @ Author        : kirito
* @ Brief         : service管理退出
* @ Date          : 2020.11.06
* @ Modify        : ...
**/
void service_com_exit(void)
{
	module_kprotocol_exit();
}
