/*************************************************************************************
*	@file			display_task.h
* @author	 	Ekko
*	@version 	V1.0
*	@date			2018/9/22
* @brief		NONE
*************************************************************************************/
#ifndef __DISPLAYTASK_H
#define __DISPLAYTASK_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "cmsis_os.h"
#include "rbc_lcd.h"
#include "gpio.h"
#include "Mechanical_arm.h"
#include "decision_task.h"



#include "LightBand.h"

extern UART_HandleTypeDef huart4;
extern UART_HandleTypeDef huart5;
extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef huart3;
extern uint8_t call_message[4];
extern uint32_t call_status;
/* Private function prototypes -----------------------------------------------*/

void Display_Task(void const * argument);





#endif
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
