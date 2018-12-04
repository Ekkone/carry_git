/*************************************************************************************
*	@file			correct_task.c
* @author	 	Ekko
*	@version 	V1.0
*	@date			2018/9/22
* @brief		NONE
*************************************************************************************/
/* Includes ------------------------------------------------------------------------*/
#include "correct_task.h"
#include "decision_task.h"
#include "run_task.h"

#define ABS(x)		((x>0)? (x): (-x)) 
/* External variables --------------------------------------------------------*/
extern osThreadId correct_taskHandle;
extern GM_25_type GM_25_spd_set;
/* Internal variables --------------------------------------------------------*/
pid_t correct_pid;
int8_t LB_Flag;
int8_t Corrct_Suc_flag = 0;

/* Private function prototypes -----------------------------------------------*/

void Correct_pid_init(void)
{
	PID_struct_init(&correct_pid,POSITION_PID, 1500, 20,
									5.0f,	0.00f,	10.0f ,0.0f ,0.0f	);  //4 motos angular rate closeloop.
	
	correct_pid.deadband = 10;

}
void Correct_Task(void const * argument)
{
	static float Light_band_offset = 0;

Correct_pid_init();
//	LB_Flag=1;
//	Corrrct_Flag=1;
	for(;;)
	{

		//校验数据并更新
		if( LB_Flag == 2)
		{
			Light_band_offset = LB_2.offset;

			//巡线
			pid_calc(&correct_pid,Light_band_offset,0);
		if(Corrrct_Flag == 1)
			GM_25_spd_set.dstVmmps_X_offset = -correct_pid.pos_out;	
		}

		
		if( LB_Flag == 1)
		{
			Light_band_offset = -LB_1.offset;
			
			//巡线
			pid_calc(&correct_pid,Light_band_offset,0);
		if(Corrrct_Flag == 1)
			GM_25_spd_set.dstVmmps_X_offset = -correct_pid.pos_out;
		}
		
		
		if(ABS(Light_band_offset)<10) Corrct_Suc_flag=1;
  
	      osDelay(10);
}
	}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
