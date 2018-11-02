/*************************************************************************************
*	@file			correct_task.c
* @author	 	NCURM
*	@version 	V1.0
*	@date			2018/9/22
* @brief		

	  `''```''```''```''```''```''```''`````  
		`                           :``:.    '
		`                         ''    .'.  '
		`                         `.QTI1 ''  '
		`     '`'':               '`     ''  '车头
		`   `'     ''              `!;:!;.   '
		`   ``QTI2 ``                        '
		`   `'     ''                        '
		`     '!||:                          '
		``''```''```''```''```''```''```''```` 
		
		本任务需要的外部信息:	1. 来自run_task的车身运动状态
													2. 来自中断的qit状态
													
		本任务对外提供的信息:	1. 当前最新的坐标信息
													2. 定位任务的状态，当这个状态为Location_Busy时禁止转变车身运动方向

*************************************************************************************/
/* Includes ------------------------------------------------------------------------*/
#include "location_task.h"

/* External variables --------------------------------------------------------*/
//车身当前的运动状态
extern enum car_state Car_State; 
/* Internal variables --------------------------------------------------------*/
<<<<<<< HEAD
enum car_state Car_State; 
float now_x = 0;
float now_y = 0;
float Qti1_flag = Wihte;
float Qti2_flag = Wihte;
=======

//定位任务获得的当前最新的坐标
float x_now = 0.5; //初始值为0.5
float y_now = 0.5;
//qti状态的变换情况
float Qti1_flag[5] = {0};
float Qti2_flag[5] = {0};
//标准情况下经过黑线的状态变化顺序
float std_x[3] = {White,Black,White};			 				 //横线是单线
float std_y[5] = {White,Black,White,Black,White};	 //纵线是双间隔线
//定位状态
uint8_t location_sate = Location_Ok;
>>>>>>> upstream/location&run
/* Private function prototypes -----------------------------------------------*/

/*
** Descriptions: X方向qit状态匹配函数
** Input: 	
**			 car_state  车身运动状态 
**					
**					
** Output: location_ok    定位完成
**				 location_busy	qti正在过线，禁止打扰
*/
int  X_Match(enum car_state state)
{
	float unit = 0;

	if(state == x_pos)//x正方向
	{
		unit = 0.5;
	}
	else
	{
		unit = -0.5;		
	}
	
	if(x_now - (int)x_now > 0) //表示有小数。用qti1来标示整数点q
	{
		if(CMP_X(Qti1_flag) == 0) //为零表示匹配成功，过线
		{
			x_now += unit;
			return Location_Ok;
		}
		else
		{
			//正在过线禁止打扰
			return Location_Busy;
		}
	}
	else		//qti2来标示小数点
	{
		if(CMP_X(Qti2_flag) == 0)
		{
			x_now += unit;
			return Location_Ok;
		}
		else
		{
			return Location_Busy;
		}
	}
}
/*
** Descriptions: Y方向qit状态匹配函数
** Input: 	
**			 car_state  车身运动状态 
**					
**					
** Output: location_ok    定位完成
**				 location_busy	qti正在过线，禁止打扰
*/
int Y_Match(enum car_state state)
{
	float unit = 0;
	
	if(state == y_pos)//y正方向
	{
		unit = 0.5;
	}
	else
	{
		unit = -0.5;		
	}
	
	if(y_now - (int)y_now > 0) //表示有小数。用qti1来标示整数点q
	{
		if(CMP_Y(Qti1_flag) == 0)
		{
			y_now += unit;
			return Location_Ok;
		}
		else
		{
			//正在过线禁止打扰
			return Location_Busy;
		}
	}
	else		//qti2来标示小数点
	{
		if(CMP_Y(Qti2_flag) == 0)
		{
			y_now += unit;
			return Location_Ok;
		}
		else
		{
			return Location_Busy;
		}
	}

}

void Location_Task(void const * argument)
{
	uint32_t NotifyVaule;
  for(;;)
  {
		NotifyVaule = ulTaskNotifyTake(pdTRUE,portMAX_DELAY);
		if(NotifyVaule == 1)
		{	
			
			
			switch(Car_State)
			{
				case x_pos:
									{
										HAL_GPIO_TogglePin(LED6_GPIO_Port,LED6_Pin);

										/*匹配状态,检查是否过线，并返回定位状态*/
										location_sate = X_Match(x_pos);
									}
				break;
				case x_nag:
									{
										location_sate = X_Match(x_nag);
									}
				break;
				case y_pos:
									{
<<<<<<< HEAD
										now_x += 0.5;
=======
										location_sate = Y_Match(y_pos);
>>>>>>> upstream/location&run
									}
				break;
				case y_nag:
									{
										location_sate = Y_Match(y_nag);
									}
				break;
				default: ;
			}
			 //处理完成一次过线记点
			if(location_sate == Location_Ok)
			{
				//清除内存,避免匹配的时候干扰
				memset(Qti1_flag,0,5);
				memset(Qti2_flag,0,5);
				//重新检查一次当前qit状态
				Qti1_flag[0] = QTI1;
				Qti2_flag[0] = QTI2;
			}
			
		}
		
  }
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
