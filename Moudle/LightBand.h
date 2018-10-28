#ifndef __LightBand_H_
#define	__LightBand_H_

#include "stm32f4xx.h"
#include "can.h"

struct	lightband
{
	uint8_t   id;
	float 		site;
	uint8_t 	distance;
	uint8_t 	direction;

};

extern struct lightband LB_1;
extern struct lightband LB_2;
extern struct lightband LB_3;
extern struct lightband LB_4;


extern CAN_TX LightBand_Tx;
extern CAN_RX LightBand_Rx;

void LightBand_TRHandler(CAN_RX LightBand_Rx);


#endif



