/*************************************************************************************
*	@file			bsp.c
* @author	 	Ekko
*	@version 	V1.0
*	@date			2018/9/22
* @brief		NONE
*************************************************************************************/
/* Includes ------------------------------------------------------------------------*/
#include "bsp.h"


extern DMA_HandleTypeDef  hdma_usart1_rx;
extern DMA_HandleTypeDef  hdma_usart3_rx;
extern DMA_HandleTypeDef  hdma_usart2_rx;
extern DMA_HandleTypeDef  hdma_usart4_rx;
extern DMA_HandleTypeDef  hdma_usart5_rx;
extern DMA_HandleTypeDef  hdma_usart6_rx;
/* Private function prototypes -----------------------------------------------*/


void BSP_Init(void)
{
	/*����*/
	MX_GPIO_Init();
	/*�ⲿ�ж�*/
//	EXIT_Iint();
	/*��ʱ��*/
	MX_TIM1_Init();
	MX_TIM8_Init();
	/*������*/
	MX_TIM2_Init();
	MX_TIM3_Init();
	MX_TIM4_Init();
	MX_TIM5_Init();
	MX_TIM9_Init(); //������ձ�����
	/*CAN�ư����ݽ���*/
//	MX_CAN1_Init();
	/*����*/
	MX_DMA_Init();
  MX_USART1_UART_Init();  //������ͺ������ǽ���
  MX_UART2_Init();        //�ư�1�������Ƿ���
  MX_UART3_Init();        //�ư�2
  MX_UART4_Init();        //����
  MX_UART5_Init();        //��ά��
  MX_USART6_Init();       //��ɫ������

	/*�����ж�*/ 
	HAL_UART_Receive_DMA(&huart1,USART1_RX_DATA,SizeofJY61);	//�����ǽ���
  HAL_UART_Receive_DMA(&huart2,LightBand1,sizeofLB);			//�ư�1����
  HAL_UART_Receive_DMA(&huart3,LightBand2,sizeofLB); 	  	//�ư�2����
  HAL_UART_Receive_DMA(&huart4,buff,20); 				 	  //�򿪼������ݽ����ж�
	HAL_UART_Receive_DMA(&huart5,QR_Buff,11);
//  HAL_UART_Receive_DMA(&huart6,color_buff,54);      //����ɫ�����������ж�
	/*�رհ봫������ж�*/
	__HAL_DMA_DISABLE_IT(&hdma_usart1_rx,DMA_IT_HT);	//�رմ���1�봫������ж�
	__HAL_DMA_DISABLE_IT(&hdma_usart2_rx,DMA_IT_HT);	//�رմ���2�봫������ж�
	__HAL_DMA_DISABLE_IT(&hdma_usart3_rx,DMA_IT_HT);	//�رմ���3�봫������ж�
	__HAL_DMA_DISABLE_IT(&hdma_usart4_rx,DMA_IT_HT);	//�رմ���4�봫������ж�
	__HAL_DMA_DISABLE_IT(&hdma_usart5_rx,DMA_IT_HT);//�رմ���5�봫������ж�
//	__HAL_DMA_DISABLE_IT(&hdma_usart6_rx,DMA_IT_HT);	//�رմ���6�봫������ж�

//	CAN_START_IT();																	//�򿪵ư������ж�1M������
  /*��������ʼ��*/
	HAL_TIM_Encoder_Start(&htim2,TIM_CHANNEL_ALL);
	HAL_TIM_Encoder_Start(&htim4,TIM_CHANNEL_ALL);
	HAL_TIM_Encoder_Start(&htim3,TIM_CHANNEL_ALL);
	HAL_TIM_Encoder_Start(&htim5,TIM_CHANNEL_ALL);
	/*led��lcd*/
  LED_Init();
  ROC_LCD_Init();
	KEY_Init();
	/*�����ʼ��*/
	AX_Init();
	/*���̵����ʼ��*/
	GUN_Init();
	
}








/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

