/*----------------------------------------------------------------------------------------------------------------
 * Copyright(c)
 * ---------------------------------------------------------------------------------------------------------------
 * File Name : kprotocol.c
 * Author    : kirito
 * Brief     :
 * Date      :  2020.11.06
 * ---------------------------------------------------------------------------------------------------------------
 * Modifier                                    Data                                             Brief
 * -------------------------------------------------------------------------------------------------------------*/

#include "module_iwdg.h"
#include "iwdg.h"

/**
* @ Function Name : kprotocol_init
* @ Author        : kirito
* @ Brief         : service
* @ Date          : 2020.11.06
* @ Modify        : ...
**/
void module_iwdg_init(void)
{
    MX_IWDG_Init();
}

/**
* @ Function Name : kprotocol_handle
* @ Author        : kirito
* @ Brief         : service
* @ Date          : 2020.11.06
* @ Modify        : ...
**/
void module_iwdg_handle(void)
{
    MX_IWDG_Refresh();
}


/**
* @ Function Name : kprotocol_exit
* @ Author        : kirito
* @ Brief         : service
* @ Date          : 2020.11.06
* @ Modify        : ...
**/
void module_iwdg_exit(void)
{

}


/**
* @ Function Name : kprotocol_exit
* @ Author        : kirito
* @ Brief         : service
* @ Date          : 2020.11.06
* @ Modify        : ...
**/
void module_iwdg_refresh(void)
{
    MX_IWDG_Refresh();
}
