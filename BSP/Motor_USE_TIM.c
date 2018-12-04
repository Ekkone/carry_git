/*******************************************************************************
*                     版权所有 (C), 2017-,NCUROBOT
************************************************************************************************************************************************************
* 文 件 名   : Motor_USE_TIM.c
* 版 本 号   : 初稿
* 作    者   : NCURM
* 生成日期   : 2018年7月
* 最近修改   :
* 功能描述   : 电机库模块中使用TIM进行控制的电机
* 函数列表   :
*
*							Friction_Wheel_Motor(uint32_t wheelone,uint32_t wheeltwo)
*							Friction_Wheel_Motor_Stop(void)
*					
	******************************************************************************
*/
#include "Motor_USE_TIM.h"

/**
	**************************************************************
	** Descriptions: 电机驱动函数
	** Input:  NULL	
	** Output: NULL
	**************************************************************
**/
void Motor1(uint32_t speed1,uint32_t speed2)
{
	TIM1->CCR1 = speed1;
	TIM1->CCR2 = speed2;
}

void Motor2(uint32_t speed1,uint32_t speed2)
{
	TIM1->CCR3 = speed1;
	TIM1->CCR4 = speed2;
}

void Motor3(uint32_t speed1,uint32_t speed2)
{
	TIM8->CCR1 = speed1;
	TIM8->CCR2 = speed2;
}

void Motor4(uint32_t speed1,uint32_t speed2)
{
	TIM8->CCR3 = speed1;
	TIM8->CCR4 = speed2;
}

/**
	**************************************************************
	** Descriptions: 电机初始化函数
	** Input:  NULL	
	** Output: NULL
	**************************************************************
**/
void GUN_Init(void)
{
		__HAL_TIM_ENABLE(&htim1);
	  __HAL_TIM_ENABLE(&htim8);
		HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_1);
		HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_2);
		HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_3);	
		HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_4);
		HAL_TIM_PWM_Start(&htim8,TIM_CHANNEL_1);
		HAL_TIM_PWM_Start(&htim8,TIM_CHANNEL_2);
		HAL_TIM_PWM_Start(&htim8,TIM_CHANNEL_3);
		HAL_TIM_PWM_Start(&htim8,TIM_CHANNEL_4);
		HAL_Delay(1000);

}


void Friction_Wheel_Motor_Stop(void)
{
	
	htim3.Instance->CR1 &= ~(0x01);  //关闭定时器
		
}


/**
	**************************************************************
	** Descriptions: 编码器计数
	** Input:  NULL	
	** Output: NULL
	**************************************************************
**/
void Motor_Count(void)
{
	static int8_t i;
	static int16_t count1[4]={0,0,0,0};

	
	GM_25.motor_count1[0]=(int16_t)(__HAL_TIM_GET_COUNTER(&htim2));
	GM_25.motor_count1[1]=(int16_t)(__HAL_TIM_GET_COUNTER(&htim3));
	GM_25.motor_count1[2]=(int16_t)(__HAL_TIM_GET_COUNTER(&htim4));
	GM_25.motor_count1[3]=(int16_t)(__HAL_TIM_GET_COUNTER(&htim5));
	
				if(GM_25.motor_count1[0]>5000)
		{
			GM_25.motor_count1[0]=10000-GM_25.motor_count1[0];
		}
		
			if(GM_25.motor_count1[1]>5000)
		{
			GM_25.motor_count1[1]=10000-GM_25.motor_count1[1];
		}
		
			if(GM_25.motor_count1[2]>5000)
		{
			GM_25.motor_count1[2]=10000-GM_25.motor_count1[2];
		}
		
			if(GM_25.motor_count1[3]>5000)
		{
			GM_25.motor_count1[3]=10000-GM_25.motor_count1[3];
		}

		count1[0]+=(GM_25.motor_count1[0]);
	  count1[1]+=(GM_25.motor_count1[1]);
	  count1[2]+=(GM_25.motor_count1[2]);
	  count1[3]+=(GM_25.motor_count1[3]);
		
			if(i==5){
		
		GM_25.motor_count[0]=count1[0]/5;
		GM_25.motor_count[1]=count1[1]/5;
		GM_25.motor_count[2]=count1[2]/5;
		GM_25.motor_count[3]=count1[3]/5;

		
		i=0;
		count1[0]=0;
		count1[1]=0;
		count1[2]=0;
		count1[3]=0;
	}
		
	i++;
		
}
