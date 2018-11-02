/*************************************************************************************
*	@file			correct_task.c
* @author	 	Ekko
*	@version 	V1.0
*	@date			2018/9/22
* @brief		NONE
*************************************************************************************/
/* Includes ------------------------------------------------------------------------*/
#include "test_task.h"

/* External variables --------------------------------------------------------*/

/* Internal variables --------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

void Test_Task(void const * argument)
{


  for(;;)
  {
		static uint8_t LED1_NUM = 0;
		
		if(LED1_NUM > 30)
		{
			HAL_GPIO_TogglePin(LED1_GPIO_Port,LED1_Pin);
			LED1_NUM = 0;
		}
		
		LED1_NUM++;

    osDelay(10);
  }
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
