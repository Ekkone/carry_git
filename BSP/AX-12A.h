/*************************************************************************************
*	@file			AX12-A.h
* @author	 	
*	@version 	V1.0
*	@date			2018/10/8
* @brief		数字总线舵机驱动程序
*************************************************************************************/
#ifndef __ax12_a_h
#define __ax12_a_h

/* Includes ------------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "main.h"
/* Private function prototypes -----------------------------------------------------*/
#define BEGIN 0XFF

#if car_one

//#define	Set_AX11 ax12a1
//#define Set_AX6  ax12a2
//#define Set_AX8  ax12a3
//#define Set_AX18 ax12a4

#define Set_AX6  ax12a1
#define Set_AX2  ax12a2
#define Set_AX18 ax12a3
#define Set_AX8  ax12a4

#endif

#if car_two
#define	Set_AX14       ax12a1
#define Set_AX11_down  ax12a2
#define Set_AX9        ax12a3
#define Set_AX7        ax12a4
#define Set_AX11_up    ax12a5

#endif

typedef enum
{
  LEFT_ID  = 0x1,
  RIGHT_ID = 0x2,
  HAND_ID  = 0x3
}AX_ID;

typedef struct
{
  uint8_t begin_1;
  uint8_t begin_2;
  uint8_t ID;
  uint8_t LENGTH;
  uint8_t INSTRUCTION;
  uint8_t PARAMETER[3];
  uint8_t CHECK_SUM;
  
}AX_TxMsgTypeDef;

typedef struct
{
  uint8_t begin_1;
  uint8_t begin_2;
  uint8_t ID;
  uint8_t LENGTH;
  uint8_t ERROR;
  uint8_t PARAMETER[10];
  uint8_t CHECK_SUM;
  
}AX_RxMsgTypeDef;

void AX_Init(void);
void uart_t(uint8_t data);
/*CAR1*/
void Set_AX6(uint16_t angle,uint16_t speed);
void Set_AX8(uint16_t angle,uint16_t speed);
void Set_AX18(uint16_t angle,uint16_t speed);
void Set_AX2(uint16_t angle,uint16_t speed);
/*CAR2*/
void Set_AX11_down(uint16_t angle,uint16_t speed);
void Set_AX14(uint16_t angle,uint16_t speed);
void Set_AX7(uint16_t angle,uint16_t speed);
void Set_AX9(uint16_t angle,uint16_t speed);
void Set_AX11_up(uint16_t angle,uint16_t speed);




#endif
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

