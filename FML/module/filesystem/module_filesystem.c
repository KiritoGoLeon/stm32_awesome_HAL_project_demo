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

#include "module_filesystem.h"
#include "board.h"
#include "fatfs.h"
#include "driver_spi_flash.h"


// 工具做
#define WORK_BUFFER_SIZE  4096
static char work_buffer[WORK_BUFFER_SIZE];

// 初始化
static void init_spiflash_fatfs(void);
static void init_sdcard_fatfs(void);

// 测试
static void spi_flash_fatfs_test(void);
static void sdcard_fatfs_test(void);
static void spiflash_mkfs(void);

uint8_t exf_getfree(uint8_t *drv,uint32_t *total,uint32_t *free)
{
    FATFS *fs1;
    uint8_t res;
    uint32_t fre_clust=0, fre_sect=0, tot_sect=0;
    res =(uint32_t)f_getfree((const TCHAR*)drv, (DWORD*)&fre_clust, &fs1);
    if(res==0)
    {
        tot_sect=(fs1->n_fatent-2)*fs1->csize;
        fre_sect=fre_clust*fs1->csize;
#if _MAX_SS!=512
        tot_sect*=fs1->ssize/512;
        fre_sect*=fs1->ssize/512;
#endif
        *total=tot_sect>>1;	//եλΪKB
        *free=fre_sect>>1;	//եλΪKB
    }
    return 0;
}

/**
* @ Function Name : kprotocol_init
* @ Author        : kirito
* @ Brief         : service
* @ Date          : 2020.11.06
* @ Modify        : ...
**/
void module_filesystem_init(void)
{
    driver_spi_flash_init();
    printf("sd path:%s  flash path:%s\r\n",SDPath,USERPath);


    //init_spiflash_fatfs();
    MX_FATFS_USER_Init();
    MX_FATFS_SDcard_Init();
    //init_sdcard_fatfs();

    uint32_t total,free;

    while(exf_getfree("1:",&total,&free))
    {
        delay_ms(200);
        printf("wait find sd size\r\n");
    }
    printf("spi flash total size:%d KB  %dMB, free size:%d KB   %dMB\r\n",total,total/1024,free,free/1024);
		delay_ms(2000);
		//driver_spi_flash_init();
		MX_FATFS_USER_Init();
   

		while(exf_getfree("0:",&total,&free))
	{
		delay_ms(200);
		printf("wait find sd size\r\n");
	}
	printf("sd flash total size:%d KB  %dMB, free size:%dKB  %dMB\r\n",total,total/1024,free,free/1024);

		//spiflash_mkfs();
    //spi_flash_fatfs_test();
    //sdcard_fatfs_test();
}

/**
* @ Function Name : kprotocol_handle
* @ Author        : kirito
* @ Brief         : service
* @ Date          : 2020.11.06
* @ Modify        : ...
**/
void module_filesystem_handle(void)
{

}


/**
* @ Function Name : kprotocol_exit
* @ Author        : kirito
* @ Brief         : service
* @ Date          : 2020.11.06
* @ Modify        : ...
**/
void module_filesystem_exit(void)
{

}


FATFS spi_flash;

static void spiflash_mkfs(void)
{
	FRESULT retSD;
	retSD = f_mkfs(USERPath,FM_FAT,0,work_buffer,WORK_BUFFER_SIZE);
	if(retSD != FR_OK)
	{
			printf("f_mkfs spi-flash error,err = %d\r\n", retSD);
			while(1);
	}else{
		printf("f_mkfs spi-flash ok\r\n");
	}
}

// spiflash初始化--
static void init_spiflash_fatfs(void)
{
    FRESULT retSD;

    // 挂载spi flash -- 如果userfs不能用, 就用自己定义的fatfs
    retSD = f_mount(&spi_flash, "1:", 0);
    // 如果挂载不成功
    if(retSD)
    {
        // 如果没文件系统
        if(retSD == FR_NO_FILESYSTEM)
        {
            printf("spi-flash f_mount no file system  begin mkfs spi-flash\r\n");
            retSD = f_mkfs(USERPath,FM_FAT,0,work_buffer,WORK_BUFFER_SIZE);
            if(retSD != FR_OK)
            {
                printf("f_mkfs spi-flash error,err = %d\r\n", retSD);
                while(1);
            }
            else
            {
                printf("f_mount spi-flash ok \r\n");
                retSD = f_mount(&USERFatFS, USERPath, 0);
                if(retSD != FR_OK)
                {
                    printf("f_mount spi-flash error,err = %d\r\n", retSD);
                }
                else {
                    printf("f_mount spi-flash ok\r\n");
                }
            }
        }
        else
        {
            printf("f_mount spi-flash,err = %d\r\n", retSD);
            while(1);
        }
    }
    else {
        printf("spi-flash init fs ok!\r\n");
    }




}

// sd初始化
static void init_sdcard_fatfs(void)
{
    retSD = f_mount(&SDFatFS,SDPath, 0);
    if(retSD)
    {
        printf(" sdcard mount error : %d \r\n",retSD);
        // 如果没文件系统
        if(retSD == FR_NO_FILESYSTEM)
        {
            printf("f_mount no file system  begin mkfs sdcard\r\n");
            retSD = f_mkfs(SDPath,FM_ANY,0,work_buffer,WORK_BUFFER_SIZE);
            if(retSD != FR_OK)
            {
                printf("f_mkfs sdcard error,err = %d\r\n", retSD);
                while(1);
            }
            else
            {
                printf("f_mount sdcard ok \r\n");
                retSD = f_mount(&SDFatFS, SDPath, 0);
                if(retSD != FR_OK)
                {
                    printf("f_mount sdcard error,err = %d\r\n", retSD);
                }
                else {
                    printf("f_mount sdcard ok \r\n");
                }
            }
        }
        else
        {
            printf("f_mount sdcard ,err = %d\r\n", retSD);
            while(1);
        }
    }
    else {
        printf(" mount sdcard ok! \r\n");
    }
}


FIL fil;
unsigned int count = 0;
unsigned char read_buf[50] = {0};
unsigned char write_buf[50] = "skt t1 faker\r\n";

static void spi_flash_fatfs_test(void)
{
    FRESULT retSD;

    // 挂载spi flash
    retSD = f_open(&USERFile, "1:sudaroot.txt", FA_CREATE_ALWAYS | FA_WRITE);
    if(retSD == FR_OK)
    {
        printf("open ok\r\n");
        retSD = f_write(&USERFile, write_buf, strlen((const char *)write_buf), &count);
        if(retSD != FR_OK)
        {
            printf("f_write ,err = %d\r\n", retSD);
            count = 0;
            f_close(&USERFile);
        }
        else
        {
            printf("write ok:%d\n", count);
            printf("write buf :\r\n%s\r\n", write_buf);
            count = 0;
            f_close(&USERFile);
        }
    }
    else
    {
        printf("open sudaroot.txt,err = %d\r\n", retSD);
    }


    retSD = f_open(&USERFile, "1:sudaroot.txt", FA_OPEN_EXISTING | FA_READ);
    if(retSD == FR_OK)
    {
        printf(" open sudaroot ok\r\n");
        retSD = f_read(&USERFile, read_buf, sizeof(read_buf), &count);
        if(retSD != FR_OK)
        {
            printf("f_read ,err = %d\r\n", retSD);
            f_close(&USERFile);
        }
        else
        {
            printf("open ok:%d\n", count);
            printf("read buf:\r\n%s\r\n", read_buf);
            f_close(&USERFile);
        }
    }
    else
    {
        printf("read sudaroot.txt ,err = %d\r\n", retSD);
    }
}



FRESULT fr;
FIL     fd;

char filename[] = "0:test.txt";
uint8_t write_dat[] = "Hello,FATFS!\n";
uint16_t write_num = 0;
static void sdcard_fatfs_test(void)
{

    fr = f_open(&fd, filename, FA_CREATE_ALWAYS | FA_WRITE);
    if(fr == FR_OK)
    {
        printf("open file \"%s\" ok! \r\n", filename);
    }
    else
    {
        printf("open file \"%s\" error : %d\r\n", filename, fr);
    }


    fr = f_write(&fd, write_dat, sizeof(write_dat), (void *)&write_num);
    if(fr == FR_OK)
    {
        printf("write %d dat to file \"%s\" ok,dat is \"%s\".\r\n", write_num, filename, write_dat);
    }
    else
    {
        printf("write dat to file \"%s\" error,error code is:%d\r\n", filename, fr);
    }


    fr = f_close(&fd);
    if(fr == FR_OK)
    {
        printf("close file \"%s\" ok!\r\n", filename);
    }
    else
    {
        printf("close file \"%s\" error, error code is:%d.\r\n", filename, fr);
    }
}

