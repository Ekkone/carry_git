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
//  AX_Init();
//	
//	
//	//��λ���Ƕȣ����ƽǶ�0~300
//	//      RPM�����ת��114RPM
//	float servo[7][6] = {
//					{100,100,100,100,100,50},//�ȶ���̬
//					{100,100,100,100,100,50},//ץȡ���
//					{100,100,100,100,100,50},//�������
//					{100,100,100,100,100,50},//�м���̬
//					{100,100,100,100,100,50},//�ſ�צ��
//					{100,100,100,100,100,50},//ץ��צ��
//					{100,100,100,100,100,50},//Ԥ����̬
//					};
//	servo_set(servo);
					
  for(;;)
  {
		
    LCD_Display_float(LB_1.id,1,1);
		LCD_Display_float(LB_1.direction,1,2);
		LCD_Display_float(LB_1.distance,1,3);
		LCD_Display_float(LB_1.site,1,4);

    //LCD_Display_int(angle * 0.293,1,1);
		


		//StablePose();	//0

     osDelay(5);
  }
  
}




/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

