/**
  ******************************************************************************
  * @file    stm32f4xx_it.c
  * @brief   Interrupt Service Routines.
  ******************************************************************************
  *
  * COPYRIGHT(c) 2018 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "stm32f4xx_it.h"
#include "stm32f4xx.h"
#include "cmsis_os.h"

/* USER CODE BEGIN 0 */
#include "Motor_USE_TIM.h"
#include "Pixy_Camera.h"
#include "LightBand.h"
#include "AX-12A.h"
#include "QR_Code.h"
/*Pixy变量*/
uint8_t Re_Counter = 0;
uint8_t ReSign_OK = 0;
static uint8_t USART1_FLAG = 0;	//通信标志

/*激光测距变量*/
float Distance = 0;				 //距离
uint8_t Laser_buff = 0;    //缓存

/*二维码变量*/
uint8_t QR_Buff[11] = {0};

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern UART_HandleTypeDef huart4;
extern UART_HandleTypeDef huart5;
extern UART_HandleTypeDef huart1;

//编码器
extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;
extern TIM_HandleTypeDef htim8;
extern TIM_HandleTypeDef htim9;

//灯带
extern CAN_HandleTypeDef hcan1;

//二维码
extern uint8_t way_color[3];
/******************************************************************************/
/*            Cortex-M4 Processor Interruption and Exception Handlers         */ 
/******************************************************************************/

/**
* @brief This function handles Non maskable interrupt.
*/
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */

  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
* @brief This function handles Hard fault interrupt.
*/
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */

  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_HardFault_IRQn 0 */
    /* USER CODE END W1_HardFault_IRQn 0 */
  }
  /* USER CODE BEGIN HardFault_IRQn 1 */

  /* USER CODE END HardFault_IRQn 1 */
}

/**
* @brief This function handles Memory management fault.
*/
void MemManage_Handler(void)
{
  /* USER CODE BEGIN MemoryManagement_IRQn 0 */

  /* USER CODE END MemoryManagement_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_MemoryManagement_IRQn 0 */
    /* USER CODE END W1_MemoryManagement_IRQn 0 */
  }
  /* USER CODE BEGIN MemoryManagement_IRQn 1 */

  /* USER CODE END MemoryManagement_IRQn 1 */
}

/**
* @brief This function handles Pre-fetch fault, memory access fault.
*/
void BusFault_Handler(void)
{
  /* USER CODE BEGIN BusFault_IRQn 0 */

  /* USER CODE END BusFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_BusFault_IRQn 0 */
    /* USER CODE END W1_BusFault_IRQn 0 */
  }
  /* USER CODE BEGIN BusFault_IRQn 1 */

  /* USER CODE END BusFault_IRQn 1 */
}

/**
* @brief This function handles Undefined instruction or illegal state.
*/
void UsageFault_Handler(void)
{
  /* USER CODE BEGIN UsageFault_IRQn 0 */

  /* USER CODE END UsageFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_UsageFault_IRQn 0 */
    /* USER CODE END W1_UsageFault_IRQn 0 */
  }
  /* USER CODE BEGIN UsageFault_IRQn 1 */

  /* USER CODE END UsageFault_IRQn 1 */
}

/**
* @brief This function handles Debug monitor.
*/
void DebugMon_Handler(void)
{
  /* USER CODE BEGIN DebugMonitor_IRQn 0 */

  /* USER CODE END DebugMonitor_IRQn 0 */
  /* USER CODE BEGIN DebugMonitor_IRQn 1 */

  /* USER CODE END DebugMonitor_IRQn 1 */
}

/**
* @brief This function handles System tick timer.
*/
void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_IRQn 0 */
  HAL_IncTick();
  /* USER CODE END SysTick_IRQn 0 */
  osSystickHandler();
  /* USER CODE BEGIN SysTick_IRQn 1 */

  /* USER CODE END SysTick_IRQn 1 */
}

/******************************************************************************/
/* STM32F4xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f4xx.s).                    */
/******************************************************************************/

/**
* @brief This function handles TIM1 update interrupt and TIM10 global interrupt.
*/
void TIM1_IRQHandler(void)
{
  /* USER CODE BEGIN TIM1_UP_TIM10_IRQn 0 */

  /* USER CODE END TIM1_UP_TIM10_IRQn 0 */
  HAL_TIM_IRQHandler(&htim1);
  /* USER CODE BEGIN TIM1_UP_TIM10_IRQn 1 */

  /* USER CODE END TIM1_UP_TIM10_IRQn 1 */
}


void TIM2_IRQHandler(void)
{
  /* USER CODE BEGIN TIM2_IRQn 0 */

  /* USER CODE END TIM2_IRQn 0 */
  HAL_TIM_IRQHandler(&htim2);
  /* USER CODE BEGIN TIM2_IRQn 1 */

  /* USER CODE END TIM2_IRQn 1 */
}

void TIM3_IRQHandler(void)
{
  /* USER CODE BEGIN TIM3_IRQn 0 */

  /* USER CODE END TIM3_IRQn 0 */
  HAL_TIM_IRQHandler(&htim3);
  /* USER CODE BEGIN TIM3_IRQn 1 */

  /* USER CODE END TIM3_IRQn 1 */
}


void TIM4_IRQHandler(void)
{
  /* USER CODE BEGIN TIM4_IRQn 0 */

  /* USER CODE END TIM4_IRQn 0 */
  HAL_TIM_IRQHandler(&htim4);
  /* USER CODE BEGIN TIM4_IRQn 1 */

  /* USER CODE END TIM4_IRQn 1 */
}

void TIM9_IRQHandler(void)
{
  /* USER CODE BEGIN TIM9_IRQn 0 */

  /* USER CODE END TIM9_IRQn 0 */
  HAL_TIM_IRQHandler(&htim9);
  /* USER CODE BEGIN TIM9_IRQn 1 */

  /* USER CODE END TIM9_IRQn 1 */
}

/**
* @brief This function handles USART1 global interrupt.
*/
void USART1_IRQHandler(void)
{
  /* USER CODE BEGIN USART1_IRQn 0 */
  
  /* USER CODE END USART1_IRQn 0 */
  HAL_UART_IRQHandler(&huart1);
  /* USER CODE BEGIN USART1_IRQn 1 */

  /* USER CODE END USART1_IRQn 1 */
}

/**
* @brief This function handles UART4 global interrupt.
*/
void UART4_IRQHandler(void)
{
  /* USER CODE BEGIN UART4_IRQn 0 */

  /* USER CODE END UART4_IRQn 0 */
  HAL_UART_IRQHandler(&huart4);
  /* USER CODE BEGIN UART4_IRQn 1 */

  /* USER CODE END UART4_IRQn 1 */
}

/**
* @brief This function handles UART5 global interrupt.
*/
void UART5_IRQHandler(void)
{
  /* USER CODE BEGIN UART5_IRQn 0 */

  /* USER CODE END UART5_IRQn 0 */
  HAL_UART_IRQHandler(&huart5);
  /* USER CODE BEGIN UART5_IRQn 1 */

  /* USER CODE END UART5_IRQn 1 */
}


/**
* @brief This function handles CAN1 RX0 interrupts.
*/
void CAN1_RX0_IRQHandler(void)
{
  /* USER CODE BEGIN CAN1_RX0_IRQn 0 */

  /* USER CODE END CAN1_RX0_IRQn 0 */
  HAL_CAN_IRQHandler(&hcan1);
  /* USER CODE BEGIN CAN1_RX0_IRQn 1 */

  /* USER CODE END CAN1_RX0_IRQn 1 */
}


/* USER CODE BEGIN 1 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  if(huart->Instance == USART1)  //PIXY接受中断
  {
  	
		switch(USART1_FLAG)
		{
			case 0:
						{
							//第一字节帧头
							if((Pixy_Temp[0] == 0x55 || Pixy_Temp[0] == 0x56))
							{
								USART1_FLAG = 1; 
								Re_Counter++;
							}
							else
							{
								//重新接收
								USART1_FLAG = 0;
								Re_Counter = 0;
							}
							
						}
			break;
			case 1:
						{
							//第二字节帧头
							if( Pixy_Temp[1] == 0xAA)
							{
								USART1_FLAG = 2;
								Re_Counter++;
							}else
							{
								//重新接收
								USART1_FLAG = 0;
								Re_Counter = 0;
							}
						}
			break;
			case 2:
						{
							//正常接收
							Re_Counter++;
							if(Re_Counter >= 14)
							{
									/* 单一色 1个：帧头为55 aa 55 aa
									单一色 2个：面积大的先发，帧头为55 aa 55 aa  ，下一个帧头为55 aa
									CC模式 1个：帧头为55 aa 56 aa
									CC模式+单一模式 各1个：先发单一模式，帧头为55 aa 55 aa，后发CC模式，帧头为56 aa
									CC模式 2个：帧头为55 aa 56 aa (此情况不准，两个标记会产生结合，角度几乎不对)			  
									*/
								
									//单一色1个   15个数据
									if((Pixy_Temp[2] == 0x55) && (Pixy_Temp[3] == 0xAA) && (Re_Counter == 16))
									{
										Re_Counter = 0;  //重新赋值，准备下一帧数据的接收
										ReSign_OK = 0x01;
										USART1_FLAG = 0;
										
									}
									//单一色2个   13个数据
									else if((Pixy_Temp[2] != 0x55) && (Pixy_Temp[2] != 0x56) && (Re_Counter == 14))
									{
										Re_Counter = 0;  //重新赋值，准备下一帧数据的接收
										ReSign_OK = 0x02;
										USART1_FLAG = 0;
									}
									/*处理数据*/
									Pixy_Camera_Data(ReSign_OK);
									//避免无效数据进入，浪费计算时间
									ReSign_OK = 0;
							 }
							if(Re_Counter > 16)
							{
								USART1_FLAG = 0;
								Re_Counter = 0;  //接受失败,重新赋值，准备下一帧数据的接收

							}
							

						}
			break;
			default: ;	
				
		}
			
    HAL_UART_Receive_IT(&huart1,&Pixy_Temp[Re_Counter],1);
  }
  else if(huart->Instance == UART4)  //激光测距接收中断
  {
    static uint8_t step = 0,high = 0,low = 0;
    switch(step)
    {
      case 0:
              if(Laser_buff == 0X5A)
                  {
                    step++;
                    break;
                  }
              else break;
      case 1:
              if(Laser_buff == 0X5A)
                {
                  step++;
                  break;
                }
              else break;
      case 2:
              if(Laser_buff == 0X15)
                {
                  step++;
                  break;
                }
              else break;
      case 3:
              if(Laser_buff == 0X03)
                {
                  step++;
                  break;
                }
              else break;
      case 4:
              high = Laser_buff;
              step++;
              break;
      case 5:
              low = Laser_buff;
              step++;
              break;
      case 6:
              if(Laser_buff == 0x03 || Laser_buff == 0x02 || Laser_buff == 0x01 || Laser_buff == 0x00)
                {
                  step++;
                  break;
                }
              else break;
      case 7:if(Laser_buff == ((0x5a + 0x5a + 0x15 +0x03 + high + low + 0x03) & 0xff))
                {
                  Distance = high << 8 | low;
                  step = 0;
                  break;
                }
              else break;
    }
        
    HAL_UART_Receive_IT(&huart4,&Laser_buff,1);
    
 }
  else if(huart->Instance == UART5)  //二维码
  {
    if(QR_Buff[0] == 0x02 && QR_Buff[1] == 0x00 && QR_Buff[2] == 0x00 && QR_Buff[3] == 0x01 &&\
       QR_Buff[4] == 0x00 && QR_Buff[5] == 0x33 && QR_Buff[6] == 0x31)
    {
      way_color[0] = QR_Buff[7] - 30;
      way_color[1] = QR_Buff[8] - 30;
      way_color[2] = QR_Buff[9] - 30;
    }
    else
    {
      Get_QRcode();
    }
      HAL_UART_Receive_IT(&huart4,QR_Buff,11);      
  }
  
   
  
}


void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart)
{
  if(huart->Instance == UART5)
  {
      /* Enable the UART Error Interrupt: (Frame error, noise error, overrun error) */
    SET_BIT(huart->Instance->CR3, USART_CR3_EIE);

    /* Enable the UART Parity Error and Data Register not empty Interrupts */
    SET_BIT(huart->Instance->CR1, USART_CR1_PEIE | USART_CR1_RXNEIE);
  }
}


void HAL_CAN_RxFifo0FullCallback(CAN_HandleTypeDef *hcan)
{
	if(hcan == &hcan1)
	{
		HAL_CAN_GetRxMessage(&hcan1,CAN_RX_FIFO0,&LightBand_Rx.can_rx,LightBand_Rx.data);
		LightBand_TRHandler(LightBand_Rx);
	}

        
}


/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM1 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */
  int16_t motor_count;
  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM1) {

  }
  /* USER CODE BEGIN Callback 1 */

	

	if(htim->Instance == TIM5)
	{
		
	  Motor_Count();
    
		//计数清零
		__HAL_TIM_SET_COUNTER(&htim2,0);
		__HAL_TIM_SET_COUNTER(&htim3,0);
		__HAL_TIM_SET_COUNTER(&htim4,0);
		__HAL_TIM_SET_COUNTER(&htim9,0);
		
	}
  /* USER CODE END Callback 1 */
}

/* USER CODE END 1 */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

