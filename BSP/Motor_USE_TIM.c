/*******************************************************************************
*                     ��Ȩ���� (C), 2017-,NCUROBOT
************************************************************************************************************************************************************
* �� �� ��   : Motor_USE_TIM.c
* �� �� ��   : ����
* ��    ��   : NCURM
* ��������   : 2018��7��
* ����޸�   :
* ��������   : �����ģ����ʹ��TIM���п��Ƶĵ��
* �����б�   :
*
*							Friction_Wheel_Motor(uint32_t wheelone,uint32_t wheeltwo)
*							Friction_Wheel_Motor_Stop(void)
*					
	******************************************************************************
*/
#include "Motor_USE_TIM.h"

/**
	**************************************************************
	** Descriptions: �����������
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
	** Descriptions: �����ʼ������
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
	
	htim3.Instance->CR1 &= ~(0x01);  //�رն�ʱ��
		
}


/**
	**************************************************************
	** Descriptions: ����������
	** Input:  NULL	
	** Output: NULL
	**************************************************************
**/
void Motor_Count(void)
{
	
	GM_25.motor_count[0]=(int16_t)(__HAL_TIM_GET_COUNTER(&htim2));
	GM_25.motor_count[1]=(int16_t)(__HAL_TIM_GET_COUNTER(&htim3));	
	GM_25.motor_count[2]=(int16_t)(__HAL_TIM_GET_COUNTER(&htim4));	
	GM_25.motor_count[3]=(int16_t)(__HAL_TIM_GET_COUNTER(&htim9));
	
	//����ת����
		if(GM_25.motor_count[0]>5000)
		{
			GM_25.motor_count[0]=10000-GM_25.motor_count[0];
		}
		
			if(GM_25.motor_count[1]>5000)
		{
			GM_25.motor_count[1]=10000-GM_25.motor_count[1];
		}
		
			if(GM_25.motor_count[2]>5000)
		{
			GM_25.motor_count[2]=10000-GM_25.motor_count[2];
		}
		
			if(GM_25.motor_count[3]>5000)
		{
			GM_25.motor_count[3]=10000-GM_25.motor_count[3];
		}
		
}
