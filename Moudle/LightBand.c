#include "LightBand.h"
#include "string.h"

CAN_TX LightBand_Tx;
CAN_RX LightBand_Rx;

lightband LB_1;
lightband LB_2;


lightband *LB;


/**
	**************************************************************
	** Descriptions:
	** Input: 	
  **						
	**					
	**					
	** Output: NULL
	**************************************************************
**/

int LightBand_IRHandler(uint8_t *buff,UART_HandleTypeDef *huart)
{
		
	 static uint8_t sum = 0;
	
	if(huart->Instance == USART2)
	{
		LB = &LB_1;
	}
	else 
	{
		LB = &LB_2;
	}
		
	for(uint8_t i = 0;i < sizeofLB; i++)
	{	
		if(buff[i] == 0xff)
		{
	
			//校验
			sum = (uint8_t)(0xff + buff[i + 1] + buff[i + 2] + buff[i + 3] + buff[i + 4] + buff[i + 5] + buff[i + 6] + buff[i + 7] + buff[i + 8] + buff[i + 9]) + buff[i + 10] + buff[i + 11];
			//数据更新标志位
			if(sum == buff[i + 12])
			{
				
				LB->site = buff[i + 1];
				LB->offset = (buff[i + 2] << 8| buff[i + 3]) - 1000;
				LB->senor0 = buff[i + 4] << 8 | buff[i + 5];
				LB->senor1 = buff[i + 6] << 8	|	buff[i +7];
				LB->senor2 = buff[i + 8] << 8 |	buff[i + 9];
				LB->senor3 = buff[i + 10] << 8 | buff[i + 11];

				LB->flag = 1;
				//数据接收成功

				return 3;
			}
			else
			{
				LB->flag = 0;

				//数据校验不对
				return 2;
			}

		}
	
	}

	/******************/
		return 1;
}






HAL_StatusTypeDef Send_LightBand(uint8_t id)
{
  static uint8_t data[3] = {0xff,0,0};
  data[1] = id;
  data[2] = 0xff + id;
  return HAL_UART_Transmit(&huart2,data,3,5);
}
