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
	//引脚
	MX_GPIO_Init();
	//外部中断
	EXIT_Iint();
	//定时器
	MX_TIM1_Init();
	MX_TIM2_Init();
	MX_TIM3_Init();
	MX_TIM4_Init();
	MX_TIM8_Init();
	MX_TIM9_Init();
	MX_TIM5_Init(); //用于清空编码器
	//CAN灯板数据接收
	MX_CAN1_Init();
	//串口
  MX_USART1_UART_Init();
  MX_UART5_Init();
  MX_UART4_Init();
	//开启中断
  HAL_UART_Receive_IT(&huart5,QR_Buff,11);        //打开二维码接受中断
  HAL_UART_Receive_IT(&huart1,Pixy_Temp,1);  		  //打开PIXY数据接受中断
//  HAL_UART_Receive_IT(&huart4,&Laser_buff,1); 	  //打开激光测距数据接受中断
	CAN_START_IT();																	//打开灯板数据中断1M波特率
	//led和lcd
  LED_Init();
  ROC_LCD_Init();
	//舵机初始化
	AX_Init();
	//底盘电机初始化
	GUN_Init();
	
}








/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

