/*************************************************************************************
*	@file			display_task.c
* @author	 	Ekko
*	@version 	V1.0
*	@date			2018/9/22
* @brief		NONE
*************************************************************************************/
/* Includes ------------------------------------------------------------------------*/
#include "display_task.h"

/* External variables --------------------------------------------------------*/

extern CAN_RX LightBand_Rx;
/* Internal variables --------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

void Display_Task(void const * argument)
{
		
	//单位：角度：限制角度0~300
	//      RPM：最大转速114RPM
	float servo[7][6] = {
					{180,290,230,100,100,50},//稳定姿态
					{100,100,100,100,100,50},//抓取物块
					{100,100,100,100,100,50},//放下物块
					{100,100,100,100,100,50},//中间姿态
					{100,100,100,100,100,50},//放开爪子
					{100,100,100,100,100,50},//抓紧爪子
					{180,290,230,100,100,50},//预留姿态(伸展姿态)
					};
	servo_set(servo);
					
  for(;;)
  {
		static uint8_t LED3_NUM = 0;
		
		if(LED3_NUM > 30)
		{
			HAL_GPIO_TogglePin(LED3_GPIO_Port,LED3_Pin);
			LED3_NUM = 0;
		}
		
		LED3_NUM++;
		
    LCD_Display_float(LB_1.id,1,1);
		LCD_Display_float(LB_1.direction,1,2);
		LCD_Display_float(LB_1.distance,1,3);
		LCD_Display_float(LB_1.site,1,4);

    //LCD_Display_int(angle * 0.293,1,1);
		


		StretchPose();	//0

     osDelay(5);
  }
  
}




/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

