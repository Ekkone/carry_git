/*************************************************************************************
*	@file			planning.c
* @author	 	
*	@version 	V1.0
*	@date			
* @brief		
*************************************************************************************/
/* Includes ------------------------------------------------------------------------*/
#include "QR_Code.h"

/* External variables --------------------------------------------------------*/
extern volatile uint8_t  way_color[4];
/* Internal variables --------------------------------------------------------*/
uint8_t QR_num[10] = {0};

/* Private function prototypes --------------- --------------------------------*/

void Open_QRcode(void)
{
  static uint8_t message[2] = {0x1b,0x31};//触发指令
  HAL_UART_Receive_DMA(&huart5,QR_num,10);
  HAL_UART_Transmit(&huart5,message,2,10);
}

void Close_QRcode(void)
{
  static uint8_t message[2] = {0x1b,0x30};//触发指令
  HAL_UART_Transmit(&huart5,message,2,10);
}
void QRcode_plan(void)
{
  for(uint8_t i = 0;i < 10;i++)
  {
    if(QR_Buff[i] == 0x41 && QR_Buff[i+4] == 0x0D)
    {
      way_color[0] = QR_Buff[i+1] - 0x30;
      way_color[1] = QR_Buff[i + 2] - 0x30;
      way_color[2] = QR_Buff[i + 3] - 0x30;
//			way_color[3] = QR_Buff[i + 3];
    }
  }
  
  Close_QRcode();
//  HAL_UART_DMAStop(&huart5);
}