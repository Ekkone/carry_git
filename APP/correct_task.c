/*************************************************************************************
*	@file			correct_task.c
* @author	 	Ekko
*	@version 	V1.0
*	@date			2018/9/22
* @brief		NONE
*************************************************************************************/
/* Includes ------------------------------------------------------------------------*/
#include "correct_task.h"

/* External variables --------------------------------------------------------*/
extern CAN_RX LightBand_Rx;
/* Internal variables --------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

void Correct_Task(void const * argument)
{
  for(;;)
  {
<<<<<<< HEAD
    
=======
		static uint8_t LED4_NUM = 0;
		
		if(LED4_NUM > 30)
		{
			HAL_GPIO_TogglePin(LED4_GPIO_Port,LED4_Pin);
			LED4_NUM = 0;
		}
		
		LED4_NUM++;
>>>>>>> upstream/location&run
    
    osDelay(10);
  }
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
