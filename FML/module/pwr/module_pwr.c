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

#include "module_pwr.h"
#include "board.h"
#include "gpio.h"
#include "usart.h"


static void key2_callback(uint16_t GPIO_Pin)
{
	if(GPIO_Pin== KEY2_Pin){
		printf("key2\r\n");
		module_pwr_enter_standby_mode();
	}
}

/**
* @ Function Name : kprotocol_init
* @ Author        : kirito
* @ Brief         : service
* @ Date          : 2020.11.06
* @ Modify        : ...
**/
void module_pwr_init(void)
{
	HAL_GPIO_set_keycallback(key2_callback);

}

/**
* @ Function Name : kprotocol_handle
* @ Author        : kirito
* @ Brief         : service
* @ Date          : 2020.11.06
* @ Modify        : ...
**/
void module_pwr_handle(void)
{
//	sleep(1);
//	printf("begin sleep\r\n");
//	module_pwr_enter_stop_mode();
	
//	module_pwr_enter_sleep_mode();
//	printf("sleep end\r\n");
}


/**
* @ Function Name : kprotocol_exit
* @ Author        : kirito
* @ Brief         : service
* @ Date          : 2020.11.06
* @ Modify        : ...
**/
void module_pwr_exit(void)
{

}

// 进入低功耗模式  -如果是中断就先执行中断的程序,然后执行上次停下的代码
void module_pwr_enter_sleep_mode(void)
{
	printf("begin sleep mode\r\n");
	HAL_SuspendTick();
	HAL_PWR_EnterSLEEPMode(PWR_MAINREGULATOR_ON,PWR_SLEEPENTRY_WFI);
	HAL_ResumeTick();
}


// 进入STOP模式,靠外部中断唤醒
void module_pwr_enter_stop_mode(void)
{
	 printf("begin stop mode\r\n");
	 HAL_SuspendTick();
	 HAL_PWR_EnterSTOPMode(PWR_LOWPOWERREGULATOR_ON,PWR_STOPENTRY_WFI);   
}

// 进入待机模式
void module_pwr_enter_standby_mode(void)
{
	 printf("begin standby mode\r\n");
   

	HAL_PWR_DisableWakeUpPin(PWR_WAKEUP_PIN1);

  /* Clear all related wakeup flags*/
  __HAL_PWR_CLEAR_FLAG(PWR_FLAG_WU);
  
  /* Enable WakeUp Pin PWR_WAKEUP_PIN1 connected to PA.00 使能PA00的唤醒功能*/
  HAL_PWR_EnableWakeUpPin(PWR_WAKEUP_PIN1);

  /* Enter the Standby mode进入待机模式 */
  HAL_PWR_EnterSTANDBYMode();
	
	
}


// STOP模式唤醒, 配置时钟
 void module_pwr_stop_mode_wake(void)
{
	// 配置系统时钟
	RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSI|RCC_OSCILLATORTYPE_HSE
                              |RCC_OSCILLATORTYPE_LSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 25;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_RTC;
  PeriphClkInitStruct.RTCClockSelection = RCC_RTCCLKSOURCE_LSE;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
	
	// 恢复系统时钟
	HAL_ResumeTick();

	
}

