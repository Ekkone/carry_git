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
	/*引脚*/
	MX_GPIO_Init();
	/*外部中断*/
//	EXIT_Iint();
	/*定时器*/
	MX_TIM1_Init();
	MX_TIM8_Init();
	/*编码器*/
	MX_TIM2_Init();
	MX_TIM3_Init();
	MX_TIM4_Init();
	MX_TIM5_Init();
	MX_TIM9_Init(); //用于清空编码器
	/*CAN灯板数据接收*/
//	MX_CAN1_Init();
	/*串口*/
	MX_DMA_Init();
  MX_USART1_UART_Init();  //舵机发送和陀螺仪接收
  MX_UART2_Init();        //灯板1和陀螺仪发送
  MX_UART3_Init();        //灯板2
  MX_UART4_Init();        //激光
  MX_UART5_Init();        //二维码
  MX_USART6_Init();       //颜色传感器

	/*开启中断*/ 
	HAL_UART_Receive_DMA(&huart1,USART1_RX_DATA,SizeofJY61);	//陀螺仪接收
  HAL_UART_Receive_DMA(&huart2,LightBand1,sizeofLB);			//灯板1数据
  HAL_UART_Receive_DMA(&huart3,LightBand2,sizeofLB); 	  	//灯板2数据
  HAL_UART_Receive_DMA(&huart4,buff,20); 				 	  //打开激光数据接受中断
	HAL_UART_Receive_DMA(&huart5,QR_Buff,11);
//  HAL_UART_Receive_DMA(&huart6,color_buff,54);      //打开颜色传感器接受中断
	/*关闭半传输完成中断*/
	__HAL_DMA_DISABLE_IT(&hdma_usart1_rx,DMA_IT_HT);	//关闭串口1半传输完成中断
	__HAL_DMA_DISABLE_IT(&hdma_usart2_rx,DMA_IT_HT);	//关闭串口2半传输完成中断
	__HAL_DMA_DISABLE_IT(&hdma_usart3_rx,DMA_IT_HT);	//关闭串口3半传输完成中断
	__HAL_DMA_DISABLE_IT(&hdma_usart4_rx,DMA_IT_HT);	//关闭串口4半传输完成中断
	__HAL_DMA_DISABLE_IT(&hdma_usart5_rx,DMA_IT_HT);//关闭串口5半传输完成中断
//	__HAL_DMA_DISABLE_IT(&hdma_usart6_rx,DMA_IT_HT);	//关闭串口6半传输完成中断

//	CAN_START_IT();																	//打开灯板数据中断1M波特率
  /*编码器初始化*/
	HAL_TIM_Encoder_Start(&htim2,TIM_CHANNEL_ALL);
	HAL_TIM_Encoder_Start(&htim4,TIM_CHANNEL_ALL);
	HAL_TIM_Encoder_Start(&htim3,TIM_CHANNEL_ALL);
	HAL_TIM_Encoder_Start(&htim5,TIM_CHANNEL_ALL);
	/*led和lcd*/
  LED_Init();
  ROC_LCD_Init();
	KEY_Init();
	/*舵机初始化*/
	AX_Init();
	/*底盘电机初始化*/
	GUN_Init();
	
}








/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

