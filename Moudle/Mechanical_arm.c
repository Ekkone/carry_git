/*******************************************************************************
                      版权所有 (C), 2017-,NCUROBOT
 *******************************************************************************
  文 件 名   : Mechanical_arm.c
  版 本 号   : 初稿
  作    者   : NCUERM
  生成日期   : 2018年7月
  最近修改   :
  功能描述   : 机械臂模块
  函数列表   : 
	
	示例：初始化时，定义一个7，6的矩阵，再调用servo_set函数即可。

	{
		//单位：角度：限制角度0~300
		//      RPM：最大转速114RPM
		float servo[7][6] = {
							{angle,angle,angle,angle,angle,speed},//稳定姿态
							{angle,angle,angle,angle,angle,speed},//抓取物块
							{angle,angle,angle,angle,angle,speed},//放下物块
								{0},//中间姿态
								{0},//放开爪子
								{0},//抓紧爪子
								{0},//预留姿态
							}	
		servo_set(servo);
	}		


	示例：如果在程序运行过程中更改位置的话,使用方法如下:

	{
		设置id为0的动作stablepose，2表示输入两个角度参数，0表示对1号舵机不执行更改，180表示更改2号舵机的角度参数为180
		servo_change_angle(0, 2,0,180);
		
	}

*******************************************************************************/

/* 包含头文件 ----------------------------------------------------------------*/
#include "Mechanical_arm.h"

/* 内部自定义数据类型 --------------------------------------------------------*/

/* 内部宏定义 ----------------------------------------------------------------*/
#define ABS(x)		((x>0)? (x): (-x)) 
//单位换算
#define RPM 8.98
#define ANGLE 2.84

/* 任务相关信息定义-----------------------------------------------------------*/

/* 内部常量定义---------------------------------------------------------------*/

/* 外部变量声明 --------------------------------------------------------------*/

/* 外部函数原型声明 ----------------------------------------------------------*/

/* 内部变量 ------------------------------------------------------------------*/
static int speed[7] = {0};	 //5种动作，每个动作中5个舵机都是一个速度
static int angle[7][5] = {0};//5种动作，5个舵机
/* 函数原型声明 ----------------------------------------------------------*/


/**
	**************************************************************
	** Descriptions: 单位转换函数
	** Input: 	
	**			  buff[7][6]:表示舵机角度的和速度的矩阵
	**				
	** Output: NULL
	**************************************************************
**/
void servo_set(float buff[7][6])
{
	for(uint8_t i = 0;i < 7;i++)
	{
		speed[i] = (int)(buff[i][5] * RPM);
		for(uint8_t j = 0;j < 5;j++)
		{
			angle[i][j] = (int)(buff[i][j] * ANGLE);
		}
	}
	
}


/**
	**************************************************************
	** Descriptions: 位置参数更改函数
	** Input: 	
	**		  	id: 动作对应的ID号
	**		  	num:输入的参数数量
	**			  参数:为0的时候表示不更改
	**				
	** Output: NULL
	**************************************************************
**/
void servo_change_angle(uint8_t id,int num,...)
{
	va_list valist;
	
    /* 为 num 个参数初始化 valist */
	va_start(valist,num);
	
	/* 访问所有赋给 valist 的参数 */
	for(int i = 0;i < num;i++)
	{
		float buff = 0;
		
		buff = (float)(va_arg(valist,double) * ANGLE);
		//等于0就不给对应位置的参数赋值
		if(buff != 0)
		{
			angle[id][i] = buff;
		}
	}
	
	/* 清理为 valist 保留的内存 */
    va_end(valist);
	
}


/**
	**************************************************************
	** Descriptions: 速度参数更改函数
	** Input: 	
	**		  	id: 动作对应的ID号
	**		  	
	**			  buff:表示舵机速度
	**				
	** Output: NULL
	**************************************************************
**/
void servo_change_speed(uint8_t id,float buff )
{
	speed[id] =(int)(buff * RPM);	
}


/**
	**************************************************************
	** Descriptions: 稳定姿态函数
	** Input:  NULL
	**				
	** Output: NULL
	**************************************************************
**/
void StablePose(void)	//0
{
	int *buff1 = angle[0];
	int  buff2 = speed[0];
	
	ax12a1(buff1[0],buff2);
	ax12a2(buff1[1],buff2);
	ax12a3(buff1[2],buff2);
//	ax12a4(buff1[3],buff2);
//	ax12a5(buff1[4],buff2);

}


/**
	**************************************************************
	** Descriptions: 抓取物块函数
	** Input:  NULL
	**				
	** Output: NULL
	**************************************************************
**/
void GetMaterial(void)	//1
{
	int *buff1 = angle[1];
	int  buff2 = speed[1];
	
	ax12a1(buff1[0],buff2);
	ax12a2(buff1[1],buff2);
	ax12a3(buff1[2],buff2);
	ax12a4(buff1[3],buff2);
//	ax12a5(buff1[4],buff2);

}


/**
	**************************************************************
	** Descriptions: 放下物块函数
	** Input:  NULL
	**				
	** Output: NULL
	**************************************************************
**/
void PutMaterial(void)	//2
{
	int *buff1 = angle[2];
	int  buff2 = speed[2];
	
	ax12a1(buff1[0],buff2);
	ax12a2(buff1[1],buff2);
	ax12a3(buff1[2],buff2);
	ax12a4(buff1[3],buff2);
//	ax12a5(buff1[4],buff2);

}


/**
	**************************************************************
	** Descriptions: 中间姿态函数
	** Input:  NULL
	**				
	** Output: NULL
	**************************************************************
**/
void MiddlePose(void)   //3
{
	int *buff1 = angle[3];
	int  buff2 = speed[3];
	
	ax12a1(buff1[0],buff2);
	ax12a2(buff1[1],buff2);
	ax12a3(buff1[2],buff2);
	ax12a4(buff1[3],buff2);
//	ax12a5(buff1[4],buff2);
}


/**
	**************************************************************
	** Descriptions: 放开爪子函数
	** Input:  NULL
	**				
	** Output: NULL
	**************************************************************
**/
void Open(void)   //4
{
	int *buff1 = angle[4];
	int  buff2 = speed[4];
	
	ax12a1(buff1[0],buff2);
	ax12a2(buff1[1],buff2);
	ax12a3(buff1[2],buff2);
	ax12a4(buff1[3],buff2);
//	ax12a5(buff1[4],buff2);
}


/**
	**************************************************************
	** Descriptions: 抓紧爪子函数
	** Input:  NULL
	**				
	** Output: NULL
	**************************************************************
**/
void Get(void)   //5
{
	int *buff1 = angle[5];
	int  buff2 = speed[5];
	
	ax12a1(buff1[0],buff2);
	ax12a2(buff1[1],buff2);
	ax12a3(buff1[2],buff2);
	ax12a4(buff1[3],buff2);
//	ax12a5(buff1[4],buff2);
}

/**
	**************************************************************
	** Descriptions: 机械臂伸展函数
	** Input:  NULL
	**				
	** Output: NULL
	**************************************************************
**/
void StretchPose(void)   //6
{
	int *buff1 = angle[6];
	int  buff2 = speed[6];
	
	ax12a1(buff1[0],buff2);
	ax12a2(buff1[1],buff2);
	ax12a3(buff1[2],buff2);
	ax12a4(buff1[3],buff2);
//	ax12a5(buff1[4],buff2);
}