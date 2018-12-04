/*************************************************************************************
*	@file			run_task.c
* @author	 	Ekko
*	@version 	V1.0
*	@date			2018/9/22
* @brief		NONE
*************************************************************************************/
/* Includes ------------------------------------------------------------------------*/
#include "run_task.h"
#include "correct_task.h"
/* External variables --------------------------------------------------------*/

extern enum car_state Car_State; 

pid_t pid_GM25_spd[4];

pid_t pid_spin;
pid_t pid_spin_spd;

GM_25_type GM_25_spd_set;
GM_25_type GM_25;
/* Internal variables --------------------------------------------------------*/
#define SPEED 100
#define X_DIRECTION 0
#define Y_DIRECTION 1
#define ABS(x)		((x>0)? (x): (-x)) 
#define Rad	0.017453f

/* Private function prototypes -----------------------------------------------*/
enum
{
  X_Pos = 1,
  X_Neg = -1,
  Y_Pos = 1,
  Y_Neg = -1
}Direction;

void ABS_limit(float *a, float ABS_MAX){
     
	if(*a < -ABS_MAX)
        *a = -ABS_MAX;
	if(*a > ABS_MAX)
        *a = ABS_MAX;

}


void Chassis_pid_init(void)
{
		for(int i=0; i<4; i++)
		{ 
			PID_struct_init(&pid_GM25_spd[i], POSITION_PID, 100, 20,
										0.5f,	0.0f,	1.0f ,0.0f ,0.0f	);  //4 motos angular rate closeloop.
		}
    PID_struct_init(&pid_spin, POSITION_PID, 1500, 1000,
										1.2f,	0.0f,	5.0f ,0.0f ,0.0f	);
//	 PID_struct_init(&pid_spin_spd, POSITION_PID, 20, 1,
//										1.0f,	0.00f,	0.0f ,0.0f ,0.0f	);

//  pid_spin.deadband=0.1;
}
	
	
void Run_Task(void const * argument)
{
	static float wheel[4]={0,0,0,0};
	static float Val[4]={0,0,0,0}; 
	Chassis_pid_init();
  static int16_t start_val;
  for(;;)
  {
		#if 0
		/*获取运动方向*/
		if(ABS(GM_25_spd_set.dstVmmps_X) > ABS(GM_25_spd_set.dstVmmps_Y))
		{
			if(GM_25_spd_set.dstVmmps_X > 0)
			{
				Car_State = x_pos;
			}
			else if(GM_25_spd_set.dstVmmps_X < 0)
			{
				Car_State = x_nag;
			}
			else
			{
				Car_State = stop;
			}
		}
		else if(ABS(GM_25_spd_set.dstVmmps_X) < ABS(GM_25_spd_set.dstVmmps_Y))
		{
			if(GM_25_spd_set.dstVmmps_Y > 0)
			{
				Car_State = y_pos;
			}
			else if(GM_25_spd_set.dstVmmps_Y < 0)
			{
				Car_State = y_nag;
			}
			else
			{
				Car_State = stop;
			}
		}
		#endif
		/*end*/
	

	pid_calc(&pid_spin,jy61_yaw.final_angle,0);
		//2车
	GM_25_spd_set.dstVmmps_W = (pid_spin.pos_out);


//	ABS_limit(&GM_25_spd_set.dstVmmps_W,20);
		if(Corrrct_Flag==1) GM_25_spd_set.dstVmmps_Y=0;
		//2车
	motor_move_setvmmps(wheel,-(GM_25_spd_set.dstVmmps_Y + GM_25_spd_set.dstVmmps_Y_offset),(GM_25_spd_set.dstVmmps_X + GM_25_spd_set.dstVmmps_X_offset),GM_25_spd_set.dstVmmps_W);

 		GM_25_spd_set.dstVmmps_X_offset = 0;
		GM_25_spd_set.dstVmmps_Y_offset = 0;
		
//		for(int i=0;i<3;i++)
//		{
//	    if(wheel[i]<500&&wheel[i]>0)wheel[i]=500;
//      if(wheel[i]>-500&&wheel[i]<0)wheel[i]=-500;			
//			
//		}
//		  pid_calc(&pid_GM25_spd[0],GM_25.motor_count[0],ABS(wheel[0]) );
//			Val[0] += (int16_t)(pid_GM25_spd[0].pos_out);
      ABS_limit(&wheel[0],2500);
//		
//		
//		  pid_calc(&pid_GM25_spd[1],GM_25.motor_count[1],ABS(wheel[1]) );
//			Val[1] += (int16_t)(pid_GM25_spd[1].pos_out);
      ABS_limit(&wheel[1],2500);
//		
//		  pid_calc(&pid_GM25_spd[2],GM_25.motor_count[2],ABS(wheel[2]) );
//			Val[2] += (int16_t)(pid_GM25_spd[2].pos_out);
      ABS_limit(&wheel[2],2500);
//			
//		  pid_calc(&pid_GM25_spd[3],GM_25.motor_count[3],ABS(wheel[3]) );
//			Val[3] += (int16_t)(pid_GM25_spd[3].pos_out);
      ABS_limit(&wheel[3],2500);
		
			if(wheel[0]>0)
			{
				 Motor1((int16_t)ABS(wheel[0]) ,0);
			}else  Motor1(0,(int16_t)ABS(wheel[0]));
			
			if(wheel[1]>0)
			{
				Motor2((int16_t)ABS(wheel[1]) ,0);
			}else  Motor2(0,(int16_t)ABS(wheel[1]));
		
			if(wheel[2]>0)
			{
			  Motor3((int16_t)ABS(wheel[2]) ,0);
			}else  Motor3(0,(int16_t)ABS(wheel[2]));
			
			if(wheel[3]>0)
			{
			  Motor4((int16_t)ABS(wheel[3]) ,0);
			}else  Motor4(0,(int16_t)ABS(wheel[3]));

	
    osDelay(10);
  }
}



//uint8_t Move_to(uint8_t num,uint8_t direction,uint16_t speed)
//{
//  uint8_t const first = direction;  //X方向移动优先，可改为Y_DIRECTION
//  uint8_t status = first;
//  switch(status)
//  {
//    case X_DIRECTION:
//          /*判断X方向*/
//          if(x_now - goal_x[num] > 0)
//            Direction = X_Neg;
//          else
//            Direction = X_Pos;
//          /*未到达指定X*/
//          if(x_now != goal_x[num])
//          {
//            GM_25_spd_set.dstVmmps_X = Direction * speed;
//          }
//          /*到达指定Y*/
//          else
//          {
//            /*停车进入下一阶段*/
//            if(status == first)  //第一步
//              status = !status;
//            else                 //第二步
//              status = 2;
//            GM_25_spd_set.dstVmmps_X = 0;
//          }
//          break;
//    case Y_DIRECTION:
//          /*判断Y方向*/
//          if(y_now - goal_y[num] > 0)
//            Direction = Y_Neg;
//          else
//            Direction = Y_Pos;
//          /*未到达指定Y*/
//          if(y_now != goal_y[num])
//          {
//            GM_25_spd_set.dstVmmps_Y = Direction * speed;
//          }
//          else
//          {
//            /*停车进入下一阶段*/
//            if(status == first)  //第一步
//              status = !status;
//            else                 //第二步
//              status = 2;
//            GM_25_spd_set.dstVmmps_Y = 0;
//          }
//          break;
//  }
//  return status; 
//}
///************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
