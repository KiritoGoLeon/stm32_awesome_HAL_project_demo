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

#include "module_log.h"
#include "common.h"
#include "module_time.h"


static char g_time_buffer[20];
/**
* @ Function Name : kprotocol_init
* @ Author        : kirito
* @ Brief         : service
* @ Date          : 2020.11.06
* @ Modify        : ...
**/
void module_log_init(void)
{
    printf("---- init log-- ok111 \r\n");
}

/**
* @ Function Name : kprotocol_handle
* @ Author        : kirito
* @ Brief         : service
* @ Date          : 2020.11.06
* @ Modify        : ...
**/
void module_log_handle(void)
{

}


/**
* @ Function Name : kprotocol_exit
* @ Author        : kirito
* @ Brief         : service
* @ Date          : 2020.11.06
* @ Modify        : ...
**/
void module_log_exit(void)
{

}


void module_log_write_e(char *tag,char *fmt, ...)
{
    char buffer[50];
    char *p = buffer;

    va_list arg_ptr;
    va_start(arg_ptr, fmt);
    vsnprintf(buffer, 50, fmt, arg_ptr);

    // find time
    struct TimeTypeDef time;
    module_time_get_time(&time);
    sprintf(g_time_buffer,"\r\n%d-%d-%d %d:%d:%d e %s ",time.year,time.month,time.day,time.hours,time.minutes,time.seconds,tag);
    printf("%s",g_time_buffer);
#ifdef LOG_FILE

    printf("%s-", __FILE__);
    printf("%d-", __LINE__);
    printf(":%s ", __func__);
#endif

    printf("%s",buffer);
    va_end(arg_ptr);
}

void module_log_write_v(char *tag,char *fmt, ...)
{
    char buffer[50];
    char *p = buffer;

    va_list arg_ptr;
    va_start(arg_ptr, fmt);
    vsnprintf(buffer, 50, fmt, arg_ptr);

    // find time
    struct TimeTypeDef time;
    module_time_get_time(&time);
    sprintf(g_time_buffer,"\r\n%d-%d-%d %d:%d:%d v %s ",time.year,time.month,time.day,time.hours,time.minutes,time.seconds,tag);
    printf("%s",g_time_buffer);
#ifdef LOG_FILE

    printf("%s-", __FILE__);
    printf("%d-", __LINE__);
    printf(":%s ", __func__);
#endif

    printf("%s",buffer);
    va_end(arg_ptr);
}


