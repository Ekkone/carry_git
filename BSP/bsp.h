/*************************************************************************************
*	@file			bsp.h
* @author	 	Ekko
*	@version 	V1.0
*	@date			2018/9/22
* @brief		NONE
*************************************************************************************/
#ifndef __bsp_h
#define __bsp_h

/* Includes ------------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "Motor_USE_TIM.h"
#include "Pixy_Camera.h"
#include "rbc_lcd.h"
#include "AX-12A.h"
#include "usart.h"
#include "gpio.h"
#include "tim.h"
#include "can.h"


/* Private function prototypes ---------------------------------------------------*/
extern UART_HandleTypeDef huart1;
/*�������*/
extern UART_HandleTypeDef huart4;
extern uint8_t Laser_buff;    //����
/*AX-12A����*/
extern UART_HandleTypeDef huart5;
extern uint8_t ch[20];

void BSP_Init(void);





#endif
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

