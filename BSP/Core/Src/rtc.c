/**
  ******************************************************************************
  * File Name          : RTC.c
  * Description        : This file provides code for the configuration
  *                      of the RTC instances.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "rtc.h"

/* USER CODE BEGIN 0 */

	
/* USER CODE END 0 */

RTC_HandleTypeDef hrtc;

/* RTC init function */
void MX_RTC_Init(void)
{
  RTC_TimeTypeDef sTime = {0};
  RTC_DateTypeDef sDate = {0};
  RTC_AlarmTypeDef sAlarm = {0};

  /** Initialize RTC Only
  */
  hrtc.Instance = RTC;
  hrtc.Init.HourFormat = RTC_HOURFORMAT_24;
  hrtc.Init.AsynchPrediv = 127;
  hrtc.Init.SynchPrediv = 255;
  hrtc.Init.OutPut = RTC_OUTPUT_DISABLE;
  hrtc.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
  hrtc.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN;
  if (HAL_RTC_Init(&hrtc) != HAL_OK)
  {
    Error_Handler();
  }

  /* USER CODE BEGIN Check_RTC_BKUP */

  /* USER CODE END Check_RTC_BKUP */

  /** Initialize RTC and set the Time and Date
  */
  sTime.Hours = 12;
  sTime.Minutes = 55;
  sTime.Seconds = 0;
  sTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
  sTime.StoreOperation = RTC_STOREOPERATION_RESET;
  if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN) != HAL_OK)
  {
    Error_Handler();
  }
  sDate.WeekDay = RTC_WEEKDAY_MONDAY;
  sDate.Month = RTC_MONTH_NOVEMBER;
  sDate.Date = 19;
  sDate.Year = 20;

  if (HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BIN) != HAL_OK)
  {
    Error_Handler();
  }
  /** Enable the Alarm A
  */
  sAlarm.AlarmTime.Hours = 0;
  sAlarm.AlarmTime.Minutes = 0;
  sAlarm.AlarmTime.Seconds = 0;
  sAlarm.AlarmTime.SubSeconds = 0;
  sAlarm.AlarmTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
  sAlarm.AlarmTime.StoreOperation = RTC_STOREOPERATION_RESET;
  sAlarm.AlarmMask = RTC_ALARMMASK_DATEWEEKDAY;
  sAlarm.AlarmSubSecondMask = RTC_ALARMSUBSECONDMASK_ALL;
  sAlarm.AlarmDateWeekDaySel = RTC_ALARMDATEWEEKDAYSEL_DATE;
  sAlarm.AlarmDateWeekDay = 1;
  sAlarm.Alarm = RTC_ALARM_A;
  if (HAL_RTC_SetAlarm_IT(&hrtc, &sAlarm, RTC_FORMAT_BIN) != HAL_OK)
  {
    Error_Handler();
  }
  /** Enable the Alarm B
  */
  sAlarm.AlarmMask = RTC_ALARMMASK_NONE;
  sAlarm.AlarmDateWeekDay = 1;
  sAlarm.Alarm = RTC_ALARM_B;
  if (HAL_RTC_SetAlarm_IT(&hrtc, &sAlarm, RTC_FORMAT_BIN) != HAL_OK)
  {
    Error_Handler();
  }
  /** Enable the WakeUp
  */
  if (HAL_RTCEx_SetWakeUpTimer_IT(&hrtc, 5, RTC_WAKEUPCLOCK_CK_SPRE_16BITS) != HAL_OK)
  {
    Error_Handler();
  }

}

void HAL_RTC_MspInit(RTC_HandleTypeDef* rtcHandle)
{

  if(rtcHandle->Instance==RTC)
  {
  /* USER CODE BEGIN RTC_MspInit 0 */

  /* USER CODE END RTC_MspInit 0 */
    /* RTC clock enable */
    __HAL_RCC_RTC_ENABLE();

    /* RTC interrupt Init */
    HAL_NVIC_SetPriority(RTC_WKUP_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(RTC_WKUP_IRQn);
    HAL_NVIC_SetPriority(RTC_Alarm_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(RTC_Alarm_IRQn);
  /* USER CODE BEGIN RTC_MspInit 1 */

  /* USER CODE END RTC_MspInit 1 */
  }
}

void HAL_RTC_MspDeInit(RTC_HandleTypeDef* rtcHandle)
{

  if(rtcHandle->Instance==RTC)
  {
  /* USER CODE BEGIN RTC_MspDeInit 0 */

  /* USER CODE END RTC_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_RTC_DISABLE();

    /* RTC interrupt Deinit */
    HAL_NVIC_DisableIRQ(RTC_WKUP_IRQn);
    HAL_NVIC_DisableIRQ(RTC_Alarm_IRQn);
  /* USER CODE BEGIN RTC_MspDeInit 1 */

  /* USER CODE END RTC_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */

#include "stdio.h"

void (*g_alarm_a_callback)(void);
void (*g_alarm_b_callback)(void);
void (*g_alarm_wakeup_callback)(void);

void MX_RTC_set_alarm(uint8_t alarm,uint8_t hours,uint8_t minutes, uint8_t seconds,void (*arg_alarm_a_callback)(void))
{
	RTC_AlarmTypeDef  RTC_AlarmStructure;



	if(alarm ==0 ){
		RTC_AlarmStructure.Alarm = RTC_ALARM_A;
		g_alarm_a_callback = arg_alarm_a_callback;
	}else{
		RTC_AlarmStructure.Alarm = RTC_ALARM_B;
		g_alarm_b_callback = arg_alarm_a_callback;
	}
	
	RTC_AlarmStructure.AlarmTime.TimeFormat = RTC_HOURFORMAT12_AM;
	RTC_AlarmStructure.AlarmTime.Hours   = hours;
	RTC_AlarmStructure.AlarmTime.Minutes =minutes;
	RTC_AlarmStructure.AlarmTime.Seconds =seconds;
	RTC_AlarmStructure.AlarmMask = RTC_ALARMMASK_DATEWEEKDAY;
	RTC_AlarmStructure.AlarmDateWeekDaySel = RTC_ALARMDATEWEEKDAYSEL_DATE;
	RTC_AlarmStructure.AlarmDateWeekDay = 2;  


	HAL_RTC_SetAlarm_IT(&hrtc,&RTC_AlarmStructure,RTC_FORMAT_BIN); 
}

// 设置计时闹钟
void MX_RTC_set_calalarm(uint8_t alarm,uint8_t hours,uint8_t minutes, uint8_t seconds,void (*arg_alarm_a_callback)(void))
{
	RTC_AlarmTypeDef  RTC_AlarmStructure;

	RTC_TimeTypeDef stime;
	
	if(alarm ==0 ){
		RTC_AlarmStructure.Alarm = RTC_ALARM_A;
		g_alarm_a_callback = arg_alarm_a_callback;
	}else{
		RTC_AlarmStructure.Alarm = RTC_ALARM_B;
		g_alarm_b_callback = arg_alarm_a_callback;
	}
	
	HAL_RTC_GetTime(&hrtc, &stime, RTC_FORMAT_BIN);   //获取设置中断时的时间
	

	RTC_AlarmStructure.AlarmTime.Hours   = hours + stime.Hours;
	RTC_AlarmStructure.AlarmTime.Minutes =minutes  + stime.Minutes;
	RTC_AlarmStructure.AlarmTime.Seconds =seconds + stime.Seconds;
	RTC_AlarmStructure.AlarmMask = RTC_ALARMMASK_DATEWEEKDAY;
	RTC_AlarmStructure.AlarmDateWeekDaySel = RTC_ALARMDATEWEEKDAYSEL_DATE;
	RTC_AlarmStructure.AlarmDateWeekDay = 2; 
	
	if (RTC_AlarmStructure.AlarmTime.Seconds > 59)
	{
	  RTC_AlarmStructure.AlarmTime.Seconds -= 60;
	  RTC_AlarmStructure.AlarmTime.Minutes += 1;
	}

	if ( RTC_AlarmStructure.AlarmTime.Minutes >59)
	{
	   RTC_AlarmStructure.AlarmTime.Minutes -= 60;
	   RTC_AlarmStructure.AlarmTime.Hours += 1;
	}
	if (RTC_AlarmStructure.AlarmTime.Hours > 23)
	{
	   RTC_AlarmStructure.AlarmTime.Hours -= 24;
	}
    
	HAL_RTC_SetAlarm_IT(&hrtc,&RTC_AlarmStructure,RTC_FORMAT_BIN); 
}

//唤醒时间
void MX_RTC_set_wakeup_time(uint16_t time,void (*arg_alarm_a_callback)(void))
{
	  /** Enable the WakeUp
  */
  if (HAL_RTCEx_SetWakeUpTimer_IT(&hrtc, time, RTC_WAKEUPCLOCK_CK_SPRE_16BITS) != HAL_OK)
  {
    Error_Handler();
  }
	g_alarm_wakeup_callback = arg_alarm_a_callback;
}




void HAL_RTC_AlarmAEventCallback(RTC_HandleTypeDef *hrtc)
{
	g_alarm_a_callback();
}

void HAL_RTCEx_AlarmBEventCallback(RTC_HandleTypeDef *hrtc)
{
	g_alarm_b_callback();
}

void HAL_RTCEx_WakeUpTimerEventCallback(RTC_HandleTypeDef *hrtc)
{
	if(g_alarm_wakeup_callback){
		g_alarm_wakeup_callback();
	}
	
}


/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
