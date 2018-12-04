/*******************************************************************************
                      版权所有 (C), 2017-, Mushiny
 *******************************************************************************
  文 件 名   : communication.c
  版 本 号   : 初稿
  作    者   : liyifeng
  生成日期   : 2018年7月
  最近修改   :
  功能描述   : 串口通信库
  函数列表   :
*******************************************************************************/
/* 包含头文件 ----------------------------------------------------------------*/
#include "communication.h "

/* 内部自定义数据类型 --------------------------------------------------------*/
uint8_t USART1_RX_DATA[(SizeofJY61)];//外接陀螺仪
uint16_t USART1_RX_NUM;
struct STime			stcTime;
struct SAcc 			stcAcc;
struct SGyro 		stcGyro;
struct SAngle 		stcAngle;
struct SMag 			stcMag;
struct SDStatus  stcDStatus;
struct SPress 		stcPress;
struct SLonLat 	stcLonLat;
struct SGPSV 		stcGPSV;
struct SQ        stcQ;


extern DMA_HandleTypeDef  hdma_usart1_rx;

/* 内部宏定义 ----------------------------------------------------------------*/

/* 任务相关信息定义-----------------------------------------------------------*/

/* 内部常量定义---------------------------------------------------------------*/

/* 外部变量声明 --------------------------------------------------------------*/

/* 外部函数原型声明 ----------------------------------------------------------*/

/* 内部变量 ------------------------------------------------------------------*/
//外接陀螺仪
JY_t   jy61_yaw =  {0};


/* 内部函数原型声明 ----------------------------------------------------------*/

/* 任务主体部分 --------------------------------------------------------------*/




/**
	**************************************************************
	** Descriptions:	JY61休眠/解休眠
	** Input:	huart  发送指令的串口，波特率要求为115200
  **						
	**					
	**					
	** Output: NULL
	**************************************************************
**/
void JY61_SLEEPorUNSLEEP(UART_HandleTypeDef *huart)
{
	uint8_t buff[3] = {0xff,0xaa,0x60};
	//休眠,解休眠
	HAL_UART_Transmit(huart,buff,3,5);
}

/**
	**************************************************************
	** Descriptions: JY61设置初始化
	** Input: huart  发送指令的串口，波特率要求为115200
  **						
	**					
	**					
	** Output: NULL
	**************************************************************
**/

void jy61_init(void)
{
	uint8_t buff[3] = {0xFF,0xAA,0x67};
	//校准加速度
	HAL_UART_Transmit(&huart5,buff,3,100);
	//角度归零
	buff[2] = 0x52;
	HAL_UART_Transmit(&huart5,buff,3,100);
	//水平安装
	buff[2] = 0x65;
	HAL_UART_Transmit(&huart5,buff,3,100);
}

/**
	**************************************************************
	** Descriptions: JY61帧对齐函数
	** Input: 	
  **						
	**					
	**					
	** Output: NULL
	**************************************************************
**/
void JY61_Frame(void)
{
	static uint8_t JY61_Frame_flag = 0;
	static	uint8_t JY61_Frame_Num = 0;
//	USART1_RX_DATA;
	
	
	if(USART1_RX_DATA[0] != 0x55 && JY61_Frame_flag == 0)
	{
		
		JY61_SLEEPorUNSLEEP(&huart2);
		
		JY61_Frame_flag = 1;
		

		return;	
	}
	if(JY61_Frame_flag == 1)//休眠一次，必须解休眠
	{
		JY61_Frame_Num++;
		
		if(JY61_Frame_Num > 50)
		{
			
			JY61_SLEEPorUNSLEEP(&huart2);
			JY61_Frame_flag = 0;
			JY61_Frame_Num = 0;
			
			HAL_UART_Receive_DMA(&huart1,USART1_RX_DATA,SizeofJY61);	//陀螺仪接收

			__HAL_DMA_DISABLE_IT(&hdma_usart1_rx,DMA_IT_HT);	//关闭串口1半传输完成中断
		}
		
		return;	
		
	}

	
}

void copy_select(uint8_t *buff,uint8_t dex)
{
	
	switch(buff[dex + 1])//判断数据是哪种数据，然后将其拷贝到对应的结构体中，有些数据包需要通过上位机打开对应的输出后，才能接收到这个数据包的数据
	{

		case 0x52:	memcpy(&stcGyro,&USART1_RX_DATA[dex + 2],8);		  break;
		case 0x53:	memcpy(&stcAngle,&USART1_RX_DATA[dex + 2],8);		  break;

	}
	
}



/***************************************************************************************
**
	*	@brief	
	*	@param
	*	@supplement	
	*	@retval	
****************************************************************************************/
/**
	**************************************************************
	** Descriptions:JY901_Data_Pro()
	**  Input: 	
  **						
	**   								
	**	
	** Output: NULL
	** NOTE: 在中断中被调用，用于串口接收陀螺仪的数据，并对数据进行处理	
	**************************************************************
**/

uint8_t JY_Select(void)
{

//		memcpy(&stcGyro,&USART1_RX_DATA[13],8);	
//		memcpy(&stcAngle,&USART1_RX_DATA[24],8);		
	static uint8_t test = 0;
	static uint8_t Updata_flag = 0;

	/*寻找第一个帧头位置，copy这个帧头之前的数据，和上一帧帧尾结合*/

	uint8_t JY_NUM = 0;
	static uint8_t buff_last[11] = {0};  	 //上一帧的残余数据
	static uint8_t index = 0;						 //
	
	
	//copy上一帧残留数据
	switch(buff_last[1])//判断数据是哪种数据，然后将其拷贝到对应的结构体中，有些数据包需要通过上位机打开对应的输出后，才能接收到这个数据包的数据
	{

		case 0x52:	memcpy(&stcGyro,&buff_last[2],8);		  break;
		case 0x53:	memcpy(&stcAngle,&buff_last[2],8);		  break;

	}
//	copy_select(buff_last,0);
	
	
	for(uint8_t i = 0;i < 12;i++)
	{
		if(USART1_RX_DATA[i] == 0x55)
		{
			memcpy(buff_last,USART1_RX_DATA,i);
			JY_NUM = i;
			index = i;
			break;
		}
	}
	
	
	//copy第一个帧头代表的数据
	switch(USART1_RX_DATA[JY_NUM + 1])//判断数据是哪种数据，然后将其拷贝到对应的结构体中，有些数据包需要通过上位机打开对应的输出后，才能接收到这个数据包的数据
	{

		case 0x52:	memcpy(&stcGyro,&USART1_RX_DATA[JY_NUM + 2],8);		  break;
		case 0x53:	memcpy(&stcAngle,&USART1_RX_DATA[JY_NUM + 2],8);		break;

	}
	
//	copy_select(USART1_RX_DATA,JY_NUM);
	
	JY_NUM += 11;
	//copy第二个帧头代表的数据
	switch(USART1_RX_DATA[JY_NUM + 1])//判断数据是哪种数据，然后将其拷贝到对应的结构体中，有些数据包需要通过上位机打开对应的输出后，才能接收到这个数据包的数据
	{

		case 0x52:	memcpy(&stcGyro,&USART1_RX_DATA[JY_NUM + 2],8);		  break;
		case 0x53:	memcpy(&stcAngle,&USART1_RX_DATA[JY_NUM + 2],8);		break;

	}
//	copy_select(USART1_RX_DATA,JY_NUM);
	
	JY_NUM += 11;

	//copy帧尾残余数据
	memcpy(&buff_last[index],&USART1_RX_DATA[JY_NUM],SizeofJY61 - JY_NUM);
	
	JY61_Data_Pro();

	/**************************END*******************************/
/*	
	//帧头寻找
	for( JY_NUM = 0;JY_NUM < SizeofJY61 - 10;JY_NUM++)
	{
		if(USART1_RX_DATA[JY_NUM] == 0x55)
		{
			//速度
			if(USART1_RX_DATA[JY_NUM + 1] == 0x52)
			{
				//赋值内存并更新标志
				memcpy(&stcGyro,&USART1_RX_DATA[JY_NUM + 2],8);
				Updata_flag = 1;
				
			}
			//角度
			else if(USART1_RX_DATA[JY_NUM + 1] == 0x53)
			{
				//赋值内存并更新标志
				memcpy(&stcAngle,&USART1_RX_DATA[JY_NUM + 2],8);
				Updata_flag = 1;
				
			}

			//下一个帧头
			JY_NUM += 10;
			
		}
		test = JY_NUM;
	}
	//更新标志
	if(Updata_flag == 1)
	{
		
		JY61_Data_Pro();
		Updata_flag = 0;
		
	}
*/
		
	return 1;
}
/**
	**************************************************************
	** Descriptions: 陀螺仪数据结构体更新
	** Input: NULL	
  **						
	**					
	**					
	** Output: NULL
	**************************************************************
**/

void JY61_Data_Pro(void)
{
		//赋值
	jy61_yaw.JY_angle = (float)stcAngle.Angle[2] * 0.005493f;	
 

	if(jy61_yaw.times>3)
	{
//		//滤波
//		jy61_yaw.JY_angle = Limit_filter(jy61_yaw.JY_angle_last,jy61_yaw.JY_angle,30);
		//置标志位
		jy61_yaw.times = 4;
		//计算误差
		jy61_yaw.err = jy61_yaw.JY_angle - jy61_yaw.JY_angle_last;
		//数圈
		if(jy61_yaw.err<-180)  
		{
			jy61_yaw.angle_round++;
		}
		else if(jy61_yaw.err>180) 
		{			
			jy61_yaw.angle_round--;
		}	
		//计算最总结果
		jy61_yaw.final_angle = (jy61_yaw.angle_round*360 + jy61_yaw.JY_angle - jy61_yaw.first_angle) * 100 ;
		
	}
	else 
	{
		//采集偏置量
		jy61_yaw.first_angle = jy61_yaw.JY_angle;
	}
	

	jy61_yaw.JY_angle_last = jy61_yaw.JY_angle;
	jy61_yaw.times++;

	//处理yaw角速度
	jy61_yaw.vz = stcGyro.w[2] * 0.06103516f;			
	jy61_yaw.vz_last = jy61_yaw.vz;

}



/*
** Descriptions: 限幅滤波
** Input:   相邻的两次数据
** Output: 滤波结果
*/
float Limit_filter(float oldData,float newData,float val)
{
	if(abs(newData-oldData)>val)
		{
			return oldData;
		}
	else
		{
			return newData;
		}
}










