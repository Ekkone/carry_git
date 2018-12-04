/*************************************************************************************
*	@file			test_task.c
* @author	 	Ekko
*	@version 	V1.0
*	@date			2018/9/22
* @brief		NONE
*************************************************************************************/
/* Includes ------------------------------------------------------------------------*/
#include "test_task.h"

/* External variables --------------------------------------------------------*/
volatile	uint8_t	Data_Updata_flag[6] = {0};

/* Internal variables --------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

void Test_Task(void const * argument)
{
  
	uint32_t NotifyValue;
	tcs3200.get_flag = 1;tcs3200.updata_flag = 1;
	for(;;)
  {
		
		NotifyValue = ulTaskNotifyTake(pdTRUE,portMAX_DELAY);
		if(NotifyValue == 1)
		{
			NotifyValue = 0;
			
			if(Data_Updata_flag[0] == 1)
			{
				//陀螺仪处理
				taskENTER_CRITICAL();  //进入临界段

				JY_Select();	
				Data_Updata_flag[0] = 0;
				
				taskEXIT_CRITICAL();  //退出临界段

			}
			//陀螺仪数据监控
			JY61_Frame();

			if(Data_Updata_flag[1] == 1)
			{
				//灯板1没有产生拥挤，不用进入临界段
				LightBand_IRHandler(LightBand1,&huart2);
				Data_Updata_flag[1] = 0;
			}			
			
			if(Data_Updata_flag[2] == 1)
			{
				//灯板2
				LightBand_IRHandler(LightBand2,&huart3);
				Data_Updata_flag[2] = 0;
			}			
			
			if(Data_Updata_flag[3] == 1)
			{
				//激光不用

				//Data_Updata_flag[3] = 0;
			}			
			
			if(Data_Updata_flag[4] == 1)
			{
				//二维码
					
				Data_Updata_flag[4] = 0;
			}			
			
			//颜色传感器请求数据监控
			Color_RGB(Data_Updata_flag[5]);
			
			if(Data_Updata_flag[5] == 1)
			{
				//颜色传感器
				taskENTER_CRITICAL();  //进入临界段

				Color_IRHandler();
				Data_Updata_flag[5] = 0;
				
				taskEXIT_CRITICAL();  //退出临界段

			}

			
//			CO_GetRGB();
		}
    osDelay(5);
  }
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
