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
#include "LightBand.h"
#include "rbc_lcd.h"
#include "AX-12A.h"
#include "usart.h"
#include "gpio.h"
#include "tim.h"
#include "can.h"
#include "dma.h"

/* Private function prototypes ---------------------------------------------------*/
/*�������*/
extern uint8_t buff[20];    //����
/*��ά�����*/
extern uint8_t QR_Buff[11];
/*�ư����*/
extern uint8_t LightBand1[sizeofLB];
extern uint8_t LightBand2[sizeofLB];
/*��ɫ����������*/
extern uint8_t color_buff[54];

void BSP_Init(void);





#endif
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

