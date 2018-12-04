#ifndef _COMMUNICATION_H
#define _COMMUNICATION_H

/* ����ͷ�ļ� ----------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "usart.h"
#include "string.h"


#define SizeofJY61	 33  


#define abs(a) (a>0)?(a):(-a)
extern uint8_t USART1_RX_DATA[(SizeofJY61)];//���������
extern uint16_t USART1_RX_NUM;

/* ��ģ�����ⲿ�ṩ���������Ͷ��� --------------------------------------------*/
///////////���������////////////////
struct STime
{
	unsigned char ucYear;
	unsigned char ucMonth;
	unsigned char ucDay;
	unsigned char ucHour;
	unsigned char ucMinute;
	unsigned char ucSecond;
	unsigned short usMiliSecond;
};
struct SAcc
{
	short a[3];
	short T;
};
struct SGyro
{
	short w[3];
	int8_t  zl;
	int8_t  zh;
	short T;
};
struct SAngle
{
	short Angle[3];
	short T;
};
struct SMag
{
	short h[3];
	short T;
};

struct SDStatus
{
	short sDStatus[4];
};

struct SPress
{
	long lPressure;
	long lAltitude;
};

struct SLonLat
{
	long lLon;
	long lLat;
};

struct SGPSV
{
	short sGPSHeight;
	short sGPSYaw;
	long lGPSVelocity;
};
struct SQ
{ short q[4];
};

typedef struct    //���������    ���Ըĳ����õ�������Ľṹ��moto_measure_t  _����
{
	float err;
	float JY_angle;
	float JY_angle_last;
	float first_angle;
	float angle_round;
  float final_angle;
  float last_final_angle;
	float vx;
	float vy;	
	float vz;
	float vx_last;
	float vy_last;
	float vz_last;
	int8_t frame;
	uint8_t times;
}JY_t;




/* ��ģ�����ⲿ�ṩ�ĺ궨�� --------------------------------------------------*/

/* ��ģ�����ⲿ�ṩ�Ľӿڳ������� --------------------------------------------*/
/**************���������*******************/
extern JY_t  	jy61_yaw;//�������������

/* ��ģ�����ⲿ�ṩ�Ľӿں���ԭ������ ----------------------------------------*/
//���������
void JY61_Frame(void);
void JY61_Data_Pro(void);
uint8_t JY_Select(void);
float Limit_filter(float oldData,float newData,float val);



#endif
