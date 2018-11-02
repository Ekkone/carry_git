/*************************************************************************************
*	@file			correct_task.c
* @author	 	Ekko
*	@version 	V1.0
*	@date			2018/9/22
* @brief		NONE
*************************************************************************************/
/* Includes ------------------------------------------------------------------------*/
#include "decision_task.h"

/* External variables --------------------------------------------------------*/

/* Internal variables --------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

void Decision_Task(void const * argument)
{
  for(;;)
  {
		static uint8_t LED5_NUM = 0;
		
		if(LED5_NUM > 30)
		{
			HAL_GPIO_TogglePin(LED5_GPIO_Port,LED5_Pin);
			LED5_NUM = 0;
		}
		
		LED5_NUM++;
    
    osDelay(10);
  }
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
