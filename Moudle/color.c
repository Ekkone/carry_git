/*************************************************************************************
*	@file			color.c
* @author	 	
*	@version 	V1.0
*	@date			
* @brief		NONE
*************************************************************************************//* Includes ------------------------------------------------------------------------*/
#include "color.h"
/* External variables --------------------------------------------------------------*/
extern UART_HandleTypeDef huart6;
/* Internal variables --------------------------------------------------------------*/

TCS3200 tcs3200; //ÑÕÉ«´«¸ÐÆ÷

/* Private function prototypes ---------------------------------------------------*/



void Color_RGB(void)
{
	if(tcs3200.get_flag == 1)
	{
		if(tcs3200.updata_flag == 1)
		{
			
			tcs3200.updata_flag = 0;			
			CO_GetRGB();
			
		}
	}
}


void CO_GetRGB(void)
{
  static uint8_t message[] = "AT+COLOR\r\n";
  HAL_UART_Transmit(&huart6,message,sizeof(message),5);
//  if (HAL_UART_Transmit_DMA(&huart6,message,sizeof(message)) != HAL_OK)
//  {
//    _Error_Handler(__FILE__, __LINE__);
//  }
}
void CO_WhiteBalance(void)
{
  static uint8_t message[] = "AT+ADJ\r\n";
  HAL_UART_Transmit(&huart6,message,sizeof(message),5);
//  if (HAL_UART_Transmit_DMA(&huart6,message,sizeof(message)) != HAL_OK)
//  {
//    _Error_Handler(__FILE__, __LINE__);
//  }

}
void CO_Reset(void)
{
  static uint8_t message[] = "AT+RESET\r\n";
  if (HAL_UART_Transmit_DMA(&huart6,message,sizeof(message))  != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }
}
void CO_LED(uint8_t status)
{
  static uint8_t message1[] = "AT+LIGHT+OFF\r\n";
  static uint8_t message2[] = "AT+LIGHT+ON\r\n";
  switch(status)
  {
    case 0:
      if (HAL_UART_Transmit_DMA(&huart6,message1,sizeof(message1))  != HAL_OK)
      {
        _Error_Handler(__FILE__, __LINE__);
      }
    case 1:
      if (HAL_UART_Transmit_DMA(&huart6,message2,sizeof(message2))  != HAL_OK)
      {
        _Error_Handler(__FILE__, __LINE__);
      }
  }
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
