#include "LightBand.h"


CAN_TX LightBand_Tx;
CAN_RX LightBand_Rx;

struct lightband LB_1;
struct lightband LB_2;
struct lightband LB_3;
struct lightband LB_4;




void LightBand_TRHandler(CAN_RX LightBand_Rx)
{
	
	switch(LightBand_Rx.can_rx.StdId)
	{
		case 1: //id:1
					{
						LB_1.id = 1;
						LB_1.distance = LightBand_Rx.data[0];
						LB_1.direction =  LightBand_Rx.data[1];
						LB_1.site = LightBand_Rx.data[3] << 8 | LightBand_Rx.data[2];
					}
		break;
		case 2: //id:2
					{
			  		LB_2.id = 2;
						LB_2.distance = LightBand_Rx.data[0];
						LB_2.direction =  LightBand_Rx.data[1];
						LB_2.site = LightBand_Rx.data[3] << 8 | LightBand_Rx.data[2];	
					}
		break;

		case 3:	//id:3
					{
						LB_3.id = 3;
						LB_3.distance = LightBand_Rx.data[0];
						LB_3.direction =  LightBand_Rx.data[1];
						LB_3.site = LightBand_Rx.data[3] << 8 | LightBand_Rx.data[2];						
					}
		break;

		case 4:	//id:4
					{
						LB_4.id = 4;
						LB_4.distance = LightBand_Rx.data[0];
						LB_4.direction =  LightBand_Rx.data[1];
						LB_4.site = LightBand_Rx.data[3] << 8 | LightBand_Rx.data[2];									
					}
		break;
		default: ;
		
	}
		

}
