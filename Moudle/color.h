/*************************************************************************************
*	@file			color.h
* @author	 	
*	@version 	V1.0
*	@date			
* @brief		NONE
*************************************************************************************/
#ifndef color_h
#define color_h
/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

#define Start_Get_RGB()   (tcs3200.get_flag = 1;tcs3200.updata_flag = 1;)
#define Stop_Get_RGB()		(tcs3200.get_flag = 0;tcs3200.updata_flag = 0;)

typedef struct 
{
	uint8_t R_value;
	uint8_t G_value;		
	uint8_t B_value;
	uint8_t	updata_flag;  //数据更新完成标志
	uint8_t get_flag;			//数据更新请求标志
	
}TCS3200;

extern TCS3200 tcs3200;

void Color_RGB(void);
void CO_GetRGB(void);
void CO_WhiteBalance(void);
void CO_Reset(void);
void CO_LED(uint8_t status);
#endif
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
