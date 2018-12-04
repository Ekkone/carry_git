/*************************************************************************************
*	@file			run_task.h
* @author	 	Ekko
*	@version 	V1.0
*	@date			2018/9/22
* @brief		NONE
*************************************************************************************/
#ifndef __CORRECT_TASK_H
#define __CORRECT_TASK_H

/* Includes ------------------------------------------------------------------*/
#include "cmsis_os.h"
#include "bsp.h"
#include "pid.h"
#include "Pixy_Camera.h"
#include "LightBand.h"
/* Private function prototypes -----------------------------------------------*/
extern int8_t Corrrct_Flag;
extern int8_t Corrct_Suc_flag;

void Correct_Task(void const * argument);




#endif
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
