/*******************************************************************************
*                     ��Ȩ���� (C), 2018-,NCUROBOT
************************************************************************************************************************************************************
* �� �� ��   : Omnidirectional_Wheel.c
* �� �� ��   : ����
* ��    ��   : NCURM
* ��������   : 2018��10��
* ����޸�   :
* ��������   : ����ȫ���ֽ��㺯��
* �����б�   :
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
	  
	  V_VALUE=sqrt(2)/2;
	  L_omni=0.5*sqrt(2);//(a+b)/2
	
		wheel[0] = (-dstVmmps_X*V_VALUE + dstVmmps_Y*V_VALUE + dstVmmps_W*L_omni);
		wheel[1] = (-(dstVmmps_X*V_VALUE + dstVmmps_Y*V_VALUE - dstVmmps_W*L_omni));
		wheel[2] = (-(-dstVmmps_X*V_VALUE + dstVmmps_Y*V_VALUE - dstVmmps_W*L_omni));
		wheel[3] = (dstVmmps_X*V_VALUE + dstVmmps_Y*V_VALUE + dstVmmps_W*L_omni);	
}
	
	
	





