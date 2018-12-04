/*******************************************************************************
                      ��Ȩ���� (C), 2017-, Mushiny
 *******************************************************************************
  �� �� ��   : communication.c
  �� �� ��   : ����
  ��    ��   : liyifeng
  ��������   : 2018��7��
  ����޸�   :
  ��������   : ����ͨ�ſ�
  �����б�   :
*******************************************************************************/
/* ����ͷ�ļ� ----------------------------------------------------------------*/
#include "communication.h "

/* �ڲ��Զ����������� --------------------------------------------------------*/
uint8_t USART1_RX_DATA[(SizeofJY61)];//���������
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

/* �ڲ��궨�� ----------------------------------------------------------------*/

/* ���������Ϣ����-----------------------------------------------------------*/

/* �ڲ���������---------------------------------------------------------------*/

/* �ⲿ�������� --------------------------------------------------------------*/

/* �ⲿ����ԭ������ ----------------------------------------------------------*/

/* �ڲ����� ------------------------------------------------------------------*/
//���������
JY_t   jy61_yaw =  {0};


/* �ڲ�����ԭ������ ----------------------------------------------------------*/

/* �������岿�� --------------------------------------------------------------*/




/**
	**************************************************************
	** Descriptions:	JY61����/������
	** Input:	huart  ����ָ��Ĵ��ڣ�������Ҫ��Ϊ115200
  **						
	**					
	**					
	** Output: NULL
	**************************************************************
**/
void JY61_SLEEPorUNSLEEP(UART_HandleTypeDef *huart)
{
	uint8_t buff[3] = {0xff,0xaa,0x60};
	//����,������
	HAL_UART_Transmit(huart,buff,3,5);
}

/**
	**************************************************************
	** Descriptions: JY61���ó�ʼ��
	** Input: huart  ����ָ��Ĵ��ڣ�������Ҫ��Ϊ115200
  **						
	**					
	**					
	** Output: NULL
	**************************************************************
**/

void jy61_init(void)
{
	uint8_t buff[3] = {0xFF,0xAA,0x67};
	//У׼���ٶ�
	HAL_UART_Transmit(&huart5,buff,3,100);
	//�Ƕȹ���
	buff[2] = 0x52;
	HAL_UART_Transmit(&huart5,buff,3,100);
	//ˮƽ��װ
	buff[2] = 0x65;
	HAL_UART_Transmit(&huart5,buff,3,100);
}

/**
	**************************************************************
	** Descriptions: JY61֡���뺯��
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
	if(JY61_Frame_flag == 1)//����һ�Σ����������
	{
		JY61_Frame_Num++;
		
		if(JY61_Frame_Num > 50)
		{
			
			JY61_SLEEPorUNSLEEP(&huart2);
			JY61_Frame_flag = 0;
			JY61_Frame_Num = 0;
			
			HAL_UART_Receive_DMA(&huart1,USART1_RX_DATA,SizeofJY61);	//�����ǽ���

			__HAL_DMA_DISABLE_IT(&hdma_usart1_rx,DMA_IT_HT);	//�رմ���1�봫������ж�
		}
		
		return;	
		
	}

	
}

void copy_select(uint8_t *buff,uint8_t dex)
{
	
	switch(buff[dex + 1])//�ж��������������ݣ�Ȼ���俽������Ӧ�Ľṹ���У���Щ���ݰ���Ҫͨ����λ���򿪶�Ӧ������󣬲��ܽ��յ�������ݰ�������
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
	** NOTE: ���ж��б����ã����ڴ��ڽ��������ǵ����ݣ��������ݽ��д���	
	**************************************************************
**/

uint8_t JY_Select(void)
{

//		memcpy(&stcGyro,&USART1_RX_DATA[13],8);	
//		memcpy(&stcAngle,&USART1_RX_DATA[24],8);		
	static uint8_t test = 0;
	static uint8_t Updata_flag = 0;

	/*Ѱ�ҵ�һ��֡ͷλ�ã�copy���֡ͷ֮ǰ�����ݣ�����һ֡֡β���*/

	uint8_t JY_NUM = 0;
	static uint8_t buff_last[11] = {0};  	 //��һ֡�Ĳ�������
	static uint8_t index = 0;						 //
	
	
	//copy��һ֡��������
	switch(buff_last[1])//�ж��������������ݣ�Ȼ���俽������Ӧ�Ľṹ���У���Щ���ݰ���Ҫͨ����λ���򿪶�Ӧ������󣬲��ܽ��յ�������ݰ�������
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
	
	
	//copy��һ��֡ͷ���������
	switch(USART1_RX_DATA[JY_NUM + 1])//�ж��������������ݣ�Ȼ���俽������Ӧ�Ľṹ���У���Щ���ݰ���Ҫͨ����λ���򿪶�Ӧ������󣬲��ܽ��յ�������ݰ�������
	{

		case 0x52:	memcpy(&stcGyro,&USART1_RX_DATA[JY_NUM + 2],8);		  break;
		case 0x53:	memcpy(&stcAngle,&USART1_RX_DATA[JY_NUM + 2],8);		break;

	}
	
//	copy_select(USART1_RX_DATA,JY_NUM);
	
	JY_NUM += 11;
	//copy�ڶ���֡ͷ���������
	switch(USART1_RX_DATA[JY_NUM + 1])//�ж��������������ݣ�Ȼ���俽������Ӧ�Ľṹ���У���Щ���ݰ���Ҫͨ����λ���򿪶�Ӧ������󣬲��ܽ��յ�������ݰ�������
	{

		case 0x52:	memcpy(&stcGyro,&USART1_RX_DATA[JY_NUM + 2],8);		  break;
		case 0x53:	memcpy(&stcAngle,&USART1_RX_DATA[JY_NUM + 2],8);		break;

	}
//	copy_select(USART1_RX_DATA,JY_NUM);
	
	JY_NUM += 11;

	//copy֡β��������
	memcpy(&buff_last[index],&USART1_RX_DATA[JY_NUM],SizeofJY61 - JY_NUM);
	
	JY61_Data_Pro();

	/**************************END*******************************/
/*	
	//֡ͷѰ��
	for( JY_NUM = 0;JY_NUM < SizeofJY61 - 10;JY_NUM++)
	{
		if(USART1_RX_DATA[JY_NUM] == 0x55)
		{
			//�ٶ�
			if(USART1_RX_DATA[JY_NUM + 1] == 0x52)
			{
				//��ֵ�ڴ沢���±�־
				memcpy(&stcGyro,&USART1_RX_DATA[JY_NUM + 2],8);
				Updata_flag = 1;
				
			}
			//�Ƕ�
			else if(USART1_RX_DATA[JY_NUM + 1] == 0x53)
			{
				//��ֵ�ڴ沢���±�־
				memcpy(&stcAngle,&USART1_RX_DATA[JY_NUM + 2],8);
				Updata_flag = 1;
				
			}

			//��һ��֡ͷ
			JY_NUM += 10;
			
		}
		test = JY_NUM;
	}
	//���±�־
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
	** Descriptions: ���������ݽṹ�����
	** Input: NULL	
  **						
	**					
	**					
	** Output: NULL
	**************************************************************
**/

void JY61_Data_Pro(void)
{
		//��ֵ
	jy61_yaw.JY_angle = (float)stcAngle.Angle[2] * 0.005493f;	
 

	if(jy61_yaw.times>3)
	{
//		//�˲�
//		jy61_yaw.JY_angle = Limit_filter(jy61_yaw.JY_angle_last,jy61_yaw.JY_angle,30);
		//�ñ�־λ
		jy61_yaw.times = 4;
		//�������
		jy61_yaw.err = jy61_yaw.JY_angle - jy61_yaw.JY_angle_last;
		//��Ȧ
		if(jy61_yaw.err<-180)  
		{
			jy61_yaw.angle_round++;
		}
		else if(jy61_yaw.err>180) 
		{			
			jy61_yaw.angle_round--;
		}	
		//�������ܽ��
		jy61_yaw.final_angle = (jy61_yaw.angle_round*360 + jy61_yaw.JY_angle - jy61_yaw.first_angle) * 100 ;
		
	}
	else 
	{
		//�ɼ�ƫ����
		jy61_yaw.first_angle = jy61_yaw.JY_angle;
	}
	

	jy61_yaw.JY_angle_last = jy61_yaw.JY_angle;
	jy61_yaw.times++;

	//����yaw���ٶ�
	jy61_yaw.vz = stcGyro.w[2] * 0.06103516f;			
	jy61_yaw.vz_last = jy61_yaw.vz;

}



/*
** Descriptions: �޷��˲�
** Input:   ���ڵ���������
** Output: �˲����
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










