#ifndef __LightBand_H_
#define	__LightBand_H_

#include "stm32f4xx.h"
#include "can.h"
#include "usart.h"

#define sizeofLB 26


typedef struct	
{
	uint8_t		site;
	float 		offset;
	uint16_t 	senor0;
	uint16_t  senor1;
	uint16_t	senor2;
  uint16_t  senor3;
	uint32_t 	num;
	uint8_t   flag;
	
}lightband;



extern lightband LB_1;
extern lightband LB_2;



extern CAN_TX LightBand_Tx;
extern CAN_RX LightBand_Rx;

int LightBand_IRHandler(uint8_t *buff,UART_HandleTypeDef *huart);
HAL_StatusTypeDef Send_LightBand(uint8_t id);

#endif



