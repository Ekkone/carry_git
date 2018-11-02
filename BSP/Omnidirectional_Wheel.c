/*******************************************************************************
*                     版权所有 (C), 2018-,NCUROBOT
************************************************************************************************************************************************************
* 文 件 名   : Omnidirectional_Wheel.c
* 版 本 号   : 初稿
* 作    者   : NCURM
* 生成日期   : 2018年10月
* 最近修改   :
* 功能描述   : 四轮全向轮解算函数
* 函数列表   :
*
*	
*					
	******************************************************************************
*/


#include "Omnidirectional_Wheel.h"




void motor_move_setvmmps(float  wheel[4],float dstVmmps_X,float dstVmmps_Y,float dstVmmps_W)
{
		float  V_VALUE;
		float  L_omni;
	  
		dstVmmps_X *= 0.866025;
		dstVmmps_Y *= 0.5;
	
	  V_VALUE=sqrt(2)/2;
	  L_omni=0.5*sqrt(2);//(a+b)/2
	
		wheel[0] = (-dstVmmps_X*V_VALUE + dstVmmps_Y*V_VALUE + dstVmmps_W*L_omni);
		wheel[1] = (-(dstVmmps_X*V_VALUE + dstVmmps_Y*V_VALUE - dstVmmps_W*L_omni));
		wheel[2] = (-(-dstVmmps_X*V_VALUE + dstVmmps_Y*V_VALUE - dstVmmps_W*L_omni));
		wheel[3] = (dstVmmps_X*V_VALUE + dstVmmps_Y*V_VALUE + dstVmmps_W*L_omni);	
}
	
	
	





