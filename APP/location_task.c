/*************************************************************************************
*	@file			correct_task.c
* @author	 	NCURM
*	@version 	V1.0
*	@date			2018/9/22
* @brief		

		
		本任务需要的外部信息:	1. 需要来自灯板的数据更新（数据需要转存并校验，因为灯板数据很容易传输出错）
													2. 当前运动方向的正负
													
		本任务对外提供的信息:	1. 当前最新的坐标信息
													2. 定位任务的状态，当这个状态为Location_Busy时禁止转变车身运动方向

*************************************************************************************/
/* Includes ------------------------------------------------------------------------*/
#include "location_task.h"

/* External variables --------------------------------------------------------*/
//传感器选择
enum SELECT_SENOR Select_Senor;
//车身运动方向
enum car_state Car_State = x_pos; 
//位置状态
enum Local_State local_state;
enum Local_State local_state_last;
//位置信息
LOCAL local_up = {0},local_down = {0};
//任务句柄
extern osThreadId location_taskHandle;
//定位任务获得的当前最新的坐标
float x_now = 0; //初始值为0
float y_now = 0;
extern float Distance;				 //距离
#define ABS(x)		((x>0)? (x): (-x))
#define single_max	3700
#define single_min	2700
/* Internal variables --------------------------------------------------------*/


//四颗传感器，车身坐标系中第一象限到第四象限依次为0~3
/*
#define Senor1	LB_1.senor3
#define Senor2	LB_1.senor0
#define Senor3	LB_2.senor0
#define Senor4	LB_2.senor3
*/

/* Private function prototypes -----------------------------------------------*/

/**
	**************************************************************
	** Descriptions:
	** Input: 	
  **						
	**					
	**					
	** Output: NULL
	**************************************************************
**/

void get_local_data(void)
{
	static uint16_t sum,min,max;
	if(LB_1.flag == 1)
	{
		local_up.total_last=local_up.total;
		
		local_up.senor1 = LB_1.senor0;
		local_up.senor2 = LB_1.senor1;
		local_up.senor3 = LB_1.senor2;
		local_up.senor4 = LB_1.senor3;

		sum= local_up.senor1 + local_up.senor2\
									+ local_up.senor3 + local_up.senor4;
		min = sum - single_min;
		max = sum - single_max;
		if(ABS(max)>100 && ABS(min)>100)
		{
			local_up.total = sum;
		}
		else 
		{
			local_up.total=local_up.total_last;
		}
		
		
		
		LB_1.flag = 0;

	}
	if(LB_2.flag == 1)
	{
		local_down.total_last=local_down.total;
		
		local_down.senor1 = LB_2.senor0;
		local_down.senor2 = LB_2.senor1;
		local_down.senor3 = LB_2.senor2;
		local_down.senor4 = LB_2.senor3;

		sum= local_down.senor1 + local_down.senor2\
									+ local_down.senor3 + local_down.senor4;
		min = sum - single_min;
		max = sum - single_max;
		if(ABS(max)>100 && ABS(min)>100)
		{
			local_down.total = sum;
		}
		else 
		{
			local_down.total = local_down.total_last;
		}
		
		
		LB_2.flag = 0;
	}
	
}

/**
	**************************************************************
	** Descriptions: 选择计线传感器，并指定运动方向
	** Input: 	
  **				SELECT_SENOR 要选择的传感器组合：
	**				
	**							
	** Output: NULL
	**************************************************************
**/
void select_senor(enum SELECT_SENOR senor)
{
	
	Select_Senor = senor;
		
}

/**
	**************************************************************
	** Descriptions: 灯板定位任务
	** Input: NULL
	**
	** Output: NULL
	**************************************************************
**/

void Location_Task(void const * argument)
{
  	

	
	static uint8_t y_pos_step = 0;
	static uint8_t y_nag_step = 0;

	LOCAL *local;
	
	//初始化选择1传感器
	select_senor(UP);
	
	//初始化处于空白状态
	local_state = blank;
	local_state_last = blank;

  for(;;)
  {

		/*数据更新*/
		get_local_data();
		
		/*传感器选择*/
		switch(Select_Senor)
		{
			case UP:
			{
				local = &local_up;
			}
			break;
			case DOWN:
			{
				local = &local_down;
			}
			break;
		}
		
		/*监控状态变化*/
		if(local->total >= single_max)//blank
		{
			
			local_state = blank;
			
		}
		else if(local->total <= single_min)//double_line 
		{
			
			local_state = double_line;

		}
		else//single_line
		{
			
			local_state = single_line;
			
		}
		
		/*结合运动方向判断状态变化*/
		
		if(local_state > local_state_last)
		{
			switch(Car_State)
			{
				case x_pos:
				{
					x_now++;
				}
				break;
				case x_nag:
				{
					x_now--;
				}
				break;
				case y_pos:
				{
					if(local_state_last == single_line)
					{
						y_now++;
					}
				}
				break;
				case y_nag:
				{			
					if(local_state_last == single_line)
					{
						y_now--;
					}
				}
				break;
				case stop: break;
				
			}
					
		if(x_now != 4)
		{
		  if(Distance>480) y_now=3;
	  }else
		 {
			 if(Distance>690)  y_now=3;
		  }
		}
		
		
		if(x_now != 4)
		{
			if(Distance<160) y_now=0;
			if(Distance<400 && Distance>160 ) y_now=1;
			else if(Distance>350 &&Distance<570 ) y_now=2;

		}
		else 
		{
			if(Distance<140) y_now=1;
			if(Distance>190 &&Distance<450) y_now=2;

		}
					
		
		//保存上次状态
		local_state_last = local_state;
		osDelay(5);
			
		/*************end***************/
 
	}		
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
