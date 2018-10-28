/*************************************************************************************
*	@file			bsp.c
* @author	 	Ekko
*	@version 	V1.0
*	@date			2018/9/22
* @brief		NONE
*************************************************************************************/
/* Includes ------------------------------------------------------------------------*/
#include "bsp.h"

/* Private function prototypes -----------------------------------------------*/

void BSP_Init(void)
{
	//����
	MX_GPIO_Init();
	//�ⲿ�ж�
	 EXIT_Iint();
	//��ʱ��
	MX_TIM1_Init();
	MX_TIM8_Init();
	MX_TIM2_Init();
	MX_TIM3_Init();
	MX_TIM4_Init();
	MX_TIM5_Init();
	MX_TIM9_Init();
	//CAN�ư����ݽ���
	MX_CAN1_Init();
	//����
  MX_USART1_UART_Init();
  MX_UART5_Init();
  MX_UART4_Init();
	//�����ж�
  HAL_UART_Receive_IT(&huart4,QR_Buff,11);        //�򿪶�ά������ж�
  HAL_UART_Receive_IT(&huart1,Pixy_Temp,1);  		  //��PIXY���ݽ����ж�
  HAL_UART_Receive_IT(&huart4,&Laser_buff,1); 	  //�򿪼��������ݽ����ж�
	CAN_START_IT();																	//�򿪵ư������ж�1M������
	//led��lcd
  LED_Init();
  ROC_LCD_Init();
	//�����ʼ��
	AX_Init();
	//���̵����ʼ��
	GUN_Init();
	
}








/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

