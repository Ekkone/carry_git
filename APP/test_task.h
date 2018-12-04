/*************************************************************************************
*	@file			run_task.h
* @author	 	Ekko
*	@version 	V1.0
*	@date			2018/9/22
* @brief		NONE
*************************************************************************************/
#ifndef __TESTTASK_H
#define __TESTTASK_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "cmsis_os.h"
#include "AX-12A.h"
#include "gpio.h"
#include "bsp.h"
#include "color.h"
#include "QR_Code.h"
#include "rbc_lcd.h"
#include "LightBand.h"
#include "communication.h"
/* Private function prototypes -----------------------------------------------*/

void Test_Task(void const * argument);





#endif
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
