/*************************************************************************************
*	@file			correct_task.c
* @author	 	Ekko
*	@version 	V1.0
*	@date			2018/9/22
* @brief		NONE
*************************************************************************************/
/* Includes ------------------------------------------------------------------------*/
#include "location_task.h"

/* External variables --------------------------------------------------------*/

/*
                                           
	  `''```''```''```''```''```''```''`````  
		`                           :``:.    '
		`                         ''    .'.  '
		`                         `.QTI1 ''  '
		`     '`'':               '`     ''  '³µÍ·
		`   `'     ''              `!;:!;.   '
		`   ``QTI2 ``                        '
		`   `'     ''                        '
		`     '!||:                          '
		``''```''```''```''```''```''```''```` 
*/

/* Internal variables --------------------------------------------------------*/
enum car_state Car_State; 
float x_now = 0;
float y_now = 0;
float Qti1_flag = Wihte;
float Qti2_flag = Wihte;
/* Private function prototypes -----------------------------------------------*/

void Location_Task(void const * argument)
{
  for(;;)
  {
		Car_State = x_pos;
		switch(Car_State)
		{
			case x_pos:
								{
									if(Black == QTI1)
									{
										x_now += 0.5;
									}
								}
			break;
			case x_nag:
								{
								
								
								}
			break;
			case y_pos:
								{
								
								}
			break;
			case y_nag:
								{
								
								}
			break;
			default: ;
		}

		
    osDelay(5);
  }
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
