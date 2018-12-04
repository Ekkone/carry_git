/*************************************************************************************
*	@file			run_task.h
* @author	 	Ekko
*	@version 	V1.0
*	@date			2018/9/22
* @brief		NONE
*************************************************************************************/
#ifndef __RUNTASK_H
#define __RUNTASK_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "pid.h"
#include "gpio.h"
#include "rbc_lcd.h"
#include "cmsis_os.h"
#include "communication.h"
#include "Pixy_Camera.h"
#include "Motor_USE_TIM.h"
#include "location_task.h"
#include "Omnidirectional_Wheel.h"

/* Private function prototypes -----------------------------------------------*/
typedef struct
{
	float dstVmmps_Y;
	float	dstVmmps_Y_offset;
	float dstVmmps_X;
	float	dstVmmps_X_offset;
	float dstVmmps_W;
	char  flag;
	int16_t motor_count[4];
	int16_t motor_count1[4];
} GM_25_type;




extern GM_25_type GM_25;
extern GM_25_type GM_25_spd_set;
extern int16_t motor_count[4];//电机编码器计数
extern uint8_t  goal_x[7];
extern uint8_t  goal_y[7];      //生成的七个目标点的坐标顺序


void Run_Task(void const * argument);
void Chassis_pid_init(void);
uint8_t Move_to(uint8_t num,uint8_t direction,uint16_t speed);
void ABS_limit(float *a, float ABS_MAX);


#endif
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
