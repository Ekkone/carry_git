/*************************************************************************************
*	@file			run_task.h
* @author	 	Ekko
*	@version 	V1.0
*	@date			2018/9/22
* @brief		NONE
*************************************************************************************/
#ifndef __LOCATIONTASK_H
#define __LOCATIONTASK_H

/* Includes ------------------------------------------------------------------*/
#include "cmsis_os.h"
#include "bsp.h"
#include "Pixy_Camera.h"
/* Private function prototypes -----------------------------------------------*/
enum car_state
{
	x_pos = 1,
	
	x_nag,
	
	y_pos,
	
	y_nag
		
};

#define QTI1 			HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_1)
#define QTI2 			HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_2) //¡Ÿ ±
#define Black     GPIO_PIN_SET
#define	Wihte			GPIO_PIN_RESET										 //¡Ÿ ±






void Location_Task(void const * argument);





#endif
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
