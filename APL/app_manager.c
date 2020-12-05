/*----------------------------------------------------------------------------------------------------------------
 * Copyright(c)
 * ---------------------------------------------------------------------------------------------------------------
 * File Name : app_manager.c
 * Author    : kirito
 * Brief     : APP管理
 * Date      : 2020.11.06
 * ---------------------------------------------------------------------------------------------------------------
 * Modifier                                    Data                                             Brief
 * -------------------------------------------------------------------------------------------------------------*/

#include "app_manager.h"
#include "service_manager.h"


/**
* @ Function Name : app_manager_init
* @ Author        : kirito
* @ Brief         : app管理初始化
* @ Date          : 2020.11.06
* @ Modify        : ...
**/
void app_manager_init(void)
{
	service_manager_init();
}

/**
* @ Function Name : app_manager_handle
* @ Author        : kirito
* @ Brief         : app管理处理
* @ Date          : 2020.11.06
* @ Modify        : ...
**/
void app_manager_handle(void)
{
	service_manager_handle();
}


/**
* @ Function Name : app_manager_exit
* @ Author        : kirito
* @ Brief         : app管理退出
* @ Date          : 2020.11.06
* @ Modify        : ...
**/
void app_manager_exit(void)
{
	service_manager_exit();
}

