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
#include "string.h"
#include "bsp.h"
#include "math.h"
#include "LightBand.h"
/* Private function prototypes -----------------------------------------------*/

//选择传感器组合
enum SELECT_SENOR{
	
	UP = 1,
	DOWN

};
//车子运动方向
enum car_state
{
	x_pos = 1,
	
	x_nag,
	
	y_pos,
	
	y_nag,
	
	stop
		
};
enum Local_State
{
	blank = 1,
	single_line,
	double_line
	
};

typedef struct{
	
	uint16_t senor1;
	uint16_t senor2;
	uint16_t senor3;
	uint16_t senor4;
	uint16_t total;
	uint16_t total_last;	
	
}LOCAL;

extern LOCAL local_up;
extern LOCAL local_down;
extern enum Local_State local_state;
extern enum Local_State local_state_last;
extern float x_now;
extern float y_now;

//供外部调用函数
void select_senor(enum SELECT_SENOR senor);


//所有函数不供外调用

void Location_Task(void const * argument);





#endif
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
