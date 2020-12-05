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

#include "driver_spi_flash.h"
#include "common.h"
#include "gpio.h"
#include "spi.h"


static __IO uint32_t  SPITimeout = SPIT_LONG_TIMEOUT;
static uint16_t SPI_TIMEOUT_UserCallback(uint8_t errorCode);


// cs -low
static void SPI_FLASH_CS_LOW() {
    LL_GPIO_ResetOutputPin(SPI1_CS_GPIO_Port,SPI1_CS_Pin);
}

// cs- high
static void  SPI_FLASH_CS_HIGH() {
    LL_GPIO_SetOutputPin(SPI1_CS_GPIO_Port,SPI1_CS_Pin);
}


#define  FLASH_WriteAddress     0x00000
#define  FLASH_ReadAddress      FLASH_WriteAddress
#define  FLASH_SectorToErase    FLASH_WriteAddress


#define BufferSize 4096

uint8_t Tx_Buffer[] = "hell world";
uint8_t Rx_Buffer[BufferSize];


/**
* @ Function Name : kprotocol_init
* @ Author        : kirito
* @ Brief         : service
* @ Date          : 2020.11.06
* @ Modify        : ...
**/
void driver_spi_flash_init(void)
{

    // cs -high
    SPI_FLASH_CS_HIGH();
    // enable spi1
    __HAL_SPI_ENABLE(&hspi1);

    SPI_Flash_WAKEUP();

    // read flash_id
    uint32_t id = SPI_FLASH_ReadID();
    // read device_id
    uint32_t did = SPI_FLASH_ReadDeviceID();
    if(id == sFLASH_ID) {
        printf("spi flash init ok!!!");


//		SPI_FLASH_SectorErase(FLASH_SectorToErase);
//
//		SPI_FLASH_BufferWrite(Tx_Buffer, FLASH_WriteAddress, BufferSize);
//		printf("\r\n123\r\n%s", Tx_Buffer);

        //SPI_FLASH_BufferRead(Rx_Buffer, 1000, 1000);
        printf("\r\n123\r\n%s", Rx_Buffer);

    }

}


/**
  * @brief
  * @param
  * @retval
  */
void SPI_FLASH_SectorErase(uint32_t SectorAddr)
{

    SPI_FLASH_WriteEnable();
    SPI_FLASH_WaitForWriteEnd();

    SPI_FLASH_CS_LOW();

    SPI_FLASH_SendByte(W25X_SectorErase);

    SPI_FLASH_SendByte((SectorAddr & 0xFF0000) >> 16);

    SPI_FLASH_SendByte((SectorAddr & 0xFF00) >> 8);

    SPI_FLASH_SendByte(SectorAddr & 0xFF);

    SPI_FLASH_CS_HIGH();

    SPI_FLASH_WaitForWriteEnd();
}


/**
 * @brief
 * @param
 * @retval
 */
void SPI_FLASH_BulkErase(void)
{

    SPI_FLASH_WriteEnable();


    SPI_FLASH_CS_LOW();

    SPI_FLASH_SendByte(W25X_ChipErase);

    SPI_FLASH_CS_HIGH();

    SPI_FLASH_WaitForWriteEnd();
}

/**
 * @brief
 * @param
 * @param
 * @param
 * @retval
 */
void SPI_FLASH_PageWrite(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite)
{

    SPI_FLASH_WriteEnable();


    SPI_FLASH_CS_LOW();

    SPI_FLASH_SendByte(W25X_PageProgram);

    SPI_FLASH_SendByte((WriteAddr & 0xFF0000) >> 16);

    SPI_FLASH_SendByte((WriteAddr & 0xFF00) >> 8);

    SPI_FLASH_SendByte(WriteAddr & 0xFF);

    if(NumByteToWrite > SPI_FLASH_PerWritePageSize)
    {
        NumByteToWrite = SPI_FLASH_PerWritePageSize;
        FLASH_ERROR("SPI_FLASH_PageWrite too large!");
    }


    while (NumByteToWrite--)
    {

        SPI_FLASH_SendByte(*pBuffer);

        pBuffer++;
    }


    SPI_FLASH_CS_HIGH();


    SPI_FLASH_WaitForWriteEnd();
}


/**
 * @brief
 * @param
 * @param
 * @param
 * @retval
 */
void SPI_FLASH_BufferWrite(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite)
{
    uint8_t NumOfPage = 0, NumOfSingle = 0, Addr = 0, count = 0, temp = 0;

    // page size == 256字节, 如果地址小于256, 就写第0个页
    Addr = WriteAddr % SPI_FLASH_PageSize;

    // 差几个可以对齐一页
    count = SPI_FLASH_PageSize - Addr;

    // 会写几页
    NumOfPage =  NumByteToWrite / SPI_FLASH_PageSize;
    // 求余 ,计算不满一页的直接数
    NumOfSingle = NumByteToWrite % SPI_FLASH_PageSize;

    // 如果是第0地址
    if (Addr == 0)
    {
        /* 小于一页 */
        if (NumOfPage == 0)
        {
            SPI_FLASH_PageWrite(pBuffer, WriteAddr, NumByteToWrite);
        }
        // 写剩余字节到flash
        else /* NumByteToWrite > SPI_FLASH_PageSize */
        {

            // 写整页
            while (NumOfPage--)
            {
                SPI_FLASH_PageWrite(pBuffer, WriteAddr, SPI_FLASH_PageSize);
                WriteAddr +=  SPI_FLASH_PageSize;
                pBuffer += SPI_FLASH_PageSize;
            }
            // 写不满一页的数据
            SPI_FLASH_PageWrite(pBuffer, WriteAddr, NumOfSingle);
        }
    }
    else
    {
        // 如果数据小于一页
        if (NumOfPage == 0)
        {
            // 当前页剩余的个数位置比剩余的数据小, 一次写不完
            if (NumOfSingle > count)
            {
                temp = NumOfSingle - count;
                // 先写满当前页
                SPI_FLASH_PageWrite(pBuffer, WriteAddr, count);
                WriteAddr +=  count;
                pBuffer += count;
                // 再写剩余的数据
                SPI_FLASH_PageWrite(pBuffer, WriteAddr, temp);
            }
            else
            {
// 当前页剩余的页面能写完剩余的数据
                SPI_FLASH_PageWrite(pBuffer, WriteAddr, NumByteToWrite);
            }
        }
				// 如果是很多页
        else /* NumByteToWrite > SPI_FLASH_PageSize */
        {
						
            NumByteToWrite -= count;
            NumOfPage =  NumByteToWrite / SPI_FLASH_PageSize;
            NumOfSingle = NumByteToWrite % SPI_FLASH_PageSize;
					
					// 先把不对齐的数据写了
            SPI_FLASH_PageWrite(pBuffer, WriteAddr, count);
            WriteAddr +=  count;
            pBuffer += count;
	
							// 先写整数页
            while (NumOfPage--)
            {
                SPI_FLASH_PageWrite(pBuffer, WriteAddr, SPI_FLASH_PageSize);
                WriteAddr +=  SPI_FLASH_PageSize;
                pBuffer += SPI_FLASH_PageSize;
            }
						// 再写单页
            if (NumOfSingle != 0)
            {
                SPI_FLASH_PageWrite(pBuffer, WriteAddr, NumOfSingle);
            }
        }
    }
}

/**
 * @brief
 * @param
 * @param
 * @param
 * @retval
 */
void SPI_FLASH_BufferRead(uint8_t* pBuffer, uint32_t ReadAddr, uint16_t NumByteToRead)
{

    SPI_FLASH_CS_LOW();


    SPI_FLASH_SendByte(W25X_ReadData);


    SPI_FLASH_SendByte((ReadAddr & 0xFF0000) >> 16);

    SPI_FLASH_SendByte((ReadAddr& 0xFF00) >> 8);

    SPI_FLASH_SendByte(ReadAddr & 0xFF);


    while (NumByteToRead--)
    {

        *pBuffer = SPI_FLASH_SendByte(Dummy_Byte);

        pBuffer++;
    }

    SPI_FLASH_CS_HIGH();
}


/**
 * @brief
 * @param
 * @retval FLASH ID
 */
uint32_t SPI_FLASH_ReadID(void)
{
    uint32_t Temp = 0, Temp0 = 0, Temp1 = 0, Temp2 = 0;


    SPI_FLASH_CS_LOW();


    SPI_FLASH_SendByte(W25X_JedecDeviceID);


    Temp0 = SPI_FLASH_SendByte(Dummy_Byte);


    Temp1 = SPI_FLASH_SendByte(Dummy_Byte);


    Temp2 = SPI_FLASH_SendByte(Dummy_Byte);


    SPI_FLASH_CS_HIGH();


    Temp = (Temp0 << 16) | (Temp1 << 8) | Temp2;

    return Temp;
}

/**
 * @brief
 * @param
 * @retval FLASH Device ID
 */
uint32_t SPI_FLASH_ReadDeviceID(void)
{
    uint32_t Temp = 0;

    /* Select the FLASH: Chip Select low */
    SPI_FLASH_CS_LOW();

    /* Send "RDID " instruction */
    SPI_FLASH_SendByte(W25X_DeviceID);
    SPI_FLASH_SendByte(Dummy_Byte);
    SPI_FLASH_SendByte(Dummy_Byte);
    SPI_FLASH_SendByte(Dummy_Byte);

    /* Read a byte from the FLASH */
    Temp = SPI_FLASH_SendByte(Dummy_Byte);

    /* Deselect the FLASH: Chip Select high */
    SPI_FLASH_CS_HIGH();

    return Temp;
}
/*******************************************************************************
* Function Name  : SPI_FLASH_StartReadSequence
* Description    : Initiates a read data byte (READ) sequence from the Flash.
*                  This is done by driving the /CS line low to select the device,
*                  then the READ instruction is transmitted followed by 3 bytes
*                  address. This function exit and keep the /CS line low, so the
*                  Flash still being selected. With this technique the whole
*                  content of the Flash is read with a single READ instruction.
* Input          : - ReadAddr : FLASH's internal address to read from.
* Output         : None
* Return         : None
*******************************************************************************/
void SPI_FLASH_StartReadSequence(uint32_t ReadAddr)
{
    /* Select the FLASH: Chip Select low */
    SPI_FLASH_CS_LOW();

    /* Send "Read from Memory " instruction */
    SPI_FLASH_SendByte(W25X_ReadData);

    /* Send the 24-bit address of the address to read from -----------------------*/
    /* Send ReadAddr high nibble address byte */
    SPI_FLASH_SendByte((ReadAddr & 0xFF0000) >> 16);
    /* Send ReadAddr medium nibble address byte */
    SPI_FLASH_SendByte((ReadAddr& 0xFF00) >> 8);
    /* Send ReadAddr low nibble address byte */
    SPI_FLASH_SendByte(ReadAddr & 0xFF);
}


/**
 * @brief
 * @param
 * @retval
 */
uint8_t SPI_FLASH_ReadByte(void)
{
    return (SPI_FLASH_SendByte(Dummy_Byte));
}


/**
 * @brief
 * @param
 * @retval
 */
uint8_t SPI_FLASH_SendByte(uint8_t byte)
{
    SPITimeout = SPIT_FLAG_TIMEOUT;


    while (__HAL_SPI_GET_FLAG( &hspi1, SPI_FLAG_TXE ) == RESET)
    {
        if((SPITimeout--) == 0) return SPI_TIMEOUT_UserCallback(0);
    }


    WRITE_REG(hspi1.Instance->DR, byte);

    SPITimeout = SPIT_FLAG_TIMEOUT;


    while (__HAL_SPI_GET_FLAG( &hspi1, SPI_FLAG_RXNE ) == RESET)
    {
        if((SPITimeout--) == 0) return SPI_TIMEOUT_UserCallback(1);
    }

    return READ_REG(hspi1.Instance->DR);
}

/*******************************************************************************
* Function Name  : SPI_FLASH_SendHalfWord
* Description    : Sends a Half Word through the SPI interface and return the
*                  Half Word received from the SPI bus.
* Input          : Half Word : Half Word to send.
* Output         : None
* Return         : The value of the received Half Word.
*******************************************************************************/
uint16_t SPI_FLASH_SendHalfWord(uint16_t HalfWord)
{

    SPITimeout = SPIT_FLAG_TIMEOUT;

    /* Loop while DR register in not emplty */
    while (__HAL_SPI_GET_FLAG( &hspi1,  SPI_FLAG_TXE ) == RESET)
    {
        if((SPITimeout--) == 0) return SPI_TIMEOUT_UserCallback(2);
    }

    /* Send Half Word through the SPIx peripheral */
    WRITE_REG(hspi1.Instance->DR, HalfWord);

    SPITimeout = SPIT_FLAG_TIMEOUT;

    /* Wait to receive a Half Word */
    while (__HAL_SPI_GET_FLAG( &hspi1, SPI_FLAG_RXNE ) == RESET)
    {
        if((SPITimeout--) == 0) return SPI_TIMEOUT_UserCallback(3);
    }
    /* Return the Half Word read from the SPI bus */
    return READ_REG(hspi1.Instance->DR);
}


/**
 * @brief
 * @param  none
 * @retval none
 */
void SPI_FLASH_WriteEnable(void)
{

    SPI_FLASH_CS_LOW();


    SPI_FLASH_SendByte(W25X_WriteEnable);


    SPI_FLASH_CS_HIGH();
}

/**
 * @brief
 * @param  none
 * @retval none
 */
void SPI_FLASH_WaitForWriteEnd(void)
{
    uint8_t FLASH_Status = 0;


    SPI_FLASH_CS_LOW();


    SPI_FLASH_SendByte(W25X_ReadStatusReg);

    SPITimeout = SPIT_FLAG_TIMEOUT;

    do
    {

        FLASH_Status = SPI_FLASH_SendByte(Dummy_Byte);

        {
            if((SPITimeout--) == 0)
            {
                SPI_TIMEOUT_UserCallback(4);
                return;
            }
        }
    }
    while ((FLASH_Status & WIP_Flag) == SET);


    SPI_FLASH_CS_HIGH();
}


void SPI_Flash_PowerDown(void)
{

    SPI_FLASH_CS_LOW();


    SPI_FLASH_SendByte(W25X_PowerDown);


    SPI_FLASH_CS_HIGH();
}


void SPI_Flash_WAKEUP(void)
{

    SPI_FLASH_CS_LOW();

    SPI_FLASH_SendByte(W25X_ReleasePowerDown);

    SPI_FLASH_CS_HIGH();
}


/**
  * @brief  �ȴ���ʱ�ص�����
  * @param  None.
  * @retval None.
  */
static  uint16_t SPI_TIMEOUT_UserCallback(uint8_t errorCode)
{

    FLASH_ERROR("SPI !errorCode = %d",errorCode);
    return 0;
}


