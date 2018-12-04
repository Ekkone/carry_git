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
				//�����Ǵ���
				taskENTER_CRITICAL();  //�����ٽ��

				JY_Select();	
				Data_Updata_flag[0] = 0;
				
				taskEXIT_CRITICAL();  //�˳��ٽ��

			}
			//���������ݼ��
			JY61_Frame();

			if(Data_Updata_flag[1] == 1)
			{
				//�ư�1û�в���ӵ�������ý����ٽ��
				LightBand_IRHandler(LightBand1,&huart2);
				Data_Updata_flag[1] = 0;
			}			
			
			if(Data_Updata_flag[2] == 1)
			{
				//�ư�2
				LightBand_IRHandler(LightBand2,&huart3);
				Data_Updata_flag[2] = 0;
			}			
			
			if(Data_Updata_flag[3] == 1)
			{
				//���ⲻ��

				//Data_Updata_flag[3] = 0;
			}			
			
			if(Data_Updata_flag[4] == 1)
			{
				//��ά��
					
				Data_Updata_flag[4] = 0;
			}			
			
			//��ɫ�������������ݼ��
			Color_RGB(Data_Updata_flag[5]);
			
			if(Data_Updata_flag[5] == 1)
			{
				//��ɫ������
				taskENTER_CRITICAL();  //�����ٽ��

				Color_IRHandler();
				Data_Updata_flag[5] = 0;
				
				taskEXIT_CRITICAL();  //�˳��ٽ��

			}

			
//			CO_GetRGB();
		}
    osDelay(5);
  }
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
