/*************************************************************************************
*	@file			run_task.c
* @author	 	Ekko
*	@version 	V1.0
*	@date			2018/9/22
* @brief		NONE
*************************************************************************************/
/* Includes ------------------------------------------------------------------------*/
#include "run_task.h"

/* External variables --------------------------------------------------------*/
extern Pixy_Color Pixy;


pid_t pid_GM25_spd[4];
GM_25_type GM_25_spd_set;
GM_25_type GM_25;
/* Internal variables --------------------------------------------------------*/
#define SPEED 100
#define X_DIRECTION 0
#define Y_DIRECTION 1
/* Private function prototypes -----------------------------------------------*/
enum
{
  X_Pos = 1,
  X_Neg = -1,
  Y_Pos = 1,
  Y_Neg = -1
}Direction;


void Chassis_pid_init(void)
{
		for(int i=0; i<4; i++)
		{ 
			PID_struct_init(&pid_GM25_spd[i], POSITION_PID, 5000, 2000,
										1.0f,	0.1f,	5.0f ,0.0f ,0.0f	);  //4 motos angular rate closeloop.
		}
	}
	
	
void Run_Task(void const * argument)
{
	static float wheel[4]={0,0,0,0};
	static int16_t Val[4]={0,0,0,0}; 
	Chassis_pid_init();
	
  for(;;)
  {
		
   motor_move_setvmmps(wheel,GM_25_spd_set.dstVmmps_X,GM_25_spd_set.dstVmmps_Y,GM_25_spd_set.dstVmmps_W);

   for(int i=0;i<4;i++)
		{
		   pid_calc(&pid_GM25_spd[i],GM_25.motor_count[i],wheel[i] );
			 Val[i] += pid_GM25_spd[i].pout;
		}
		
			if(wheel[0]>0)
			{
				 Motor1(Val[0] ,0);
			}else  Motor1(0,Val[0]);
			
			if(wheel[1]>0)
			{
				Motor1(Val[1] ,0);
			}else  Motor1(0,Val[1]);
		
			if(wheel[2]>0)
			{
			  Motor1(Val[2] ,0);
			}else  Motor1(0,Val[2]);
			
			if(wheel[3]>0)
			{
			  Motor1(Val[3] ,0);
			}else  Motor1(0,Val[3]);
		
			
			
    LCD_Display_int(wheel[0],1,1);
    osDelay(5);
  }
}



uint8_t Move_to(uint8_t num,uint8_t direction,uint16_t speed)
{
  uint8_t const first = direction;  //X�����ƶ����ȣ��ɸ�ΪY_DIRECTION
  uint8_t status = first;
  switch(status)
  {
    case X_DIRECTION:
          /*�ж�X����*/
          if(now_x - goal_x[num] > 0)
            Direction = X_Neg;
          else
            Direction = X_Pos;
          /*δ����ָ��X*/
          if(now_x != goal_x[num])
          {
            GM_25_spd_set.dstVmmps_X = Direction * speed;
          }
          /*����ָ��Y*/
          else
          {
            /*ͣ��������һ�׶�*/
            if(status == first)  //��һ��
              status = !status;
            else                 //�ڶ���
              status = 2;
            GM_25_spd_set.dstVmmps_X = 0;
          }
          break;
    case Y_DIRECTION:
          /*�ж�Y����*/
          if(now_y - goal_y[num] > 0)
            Direction = Y_Neg;
          else
            Direction = Y_Pos;
          /*δ����ָ��Y*/
          if(now_y != goal_y[num])
          {
            GM_25_spd_set.dstVmmps_Y = Direction * speed;
          }
          else
          {
            /*ͣ��������һ�׶�*/
            if(status == first)  //��һ��
              status = !status;
            else                 //�ڶ���
              status = 2;
            GM_25_spd_set.dstVmmps_Y = 0;
          }
          break;
  }
  return status; 
}
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
