/*************************************************************************************
*	@file			correct_task.c
* @author	 	Ekko
*	@version 	V1.0
*	@date			2018/9/22
* @brief		NONE
*************************************************************************************/
/* Includes ------------------------------------------------------------------------*/
#include "decision_task.h"
#include "correct_task.h"
#include "run_task.h"
#include "location_task.h"
#include "planning.h"
/* External variables --------------------------------------------------------*/
//������������������Ȩ�޶�����������п���
extern osThreadId correct_taskHandle;
extern osThreadId decision_taskHandle;
extern osThreadId location_taskHandle;
extern osThreadId test_taskHandle;
extern osThreadId display_taskHandle;
extern osThreadId run_taskHandle;
extern osThreadId start_taskHandle;

////����λ��״̬ 
//enum Local_State local_state;
//enum Local_State local_state_last;
extern enum car_state Car_State; 

extern int8_t LB_Flag;
#define ABS(x)		((x>0)? (x): (-x)) 
#define PON(a,b)   ((a-b) > 0)?1:-1
extern GM_25_type GM_25_spd_set;
extern float Distance;				 //����
extern uint8_t  goal_x[7];
extern uint8_t  goal_y[7];      //���ɵ��߸�Ŀ��������˳��
uint8_t  way_color[4] = {0};   //��ά��ɨ�������ɫ˳��
/* Internal variables --------------------------------------------------------*/
uint8_t carry_num = 0;         //0~2��ʾ3�ΰ������� 
pid_t pid_distance;
pid_t pid_distance_catuch;
int8_t Corrrct_Flag;
 status STATUS;
//static uint8_t break_flag = 0;
//static uint16_t get_flag = 0;
//static uint16_t put_flag = 0;

	static float servo[12][6] = {
					{ 110,   210,      55,    180 ,   155, 40},//׼����ȡ0
					{ 0,   119,      111,   119,   0, 40},//ץȡ���1
					{0,    81,      132,   113,   0, 40},//�������2
					{334,   0,      0,   0  , 0, 40},//׼������3
					{  0 ,     0,       0,    0  ,   163, 40},//�ſ�צ��4
					{  0,     0,       0,     0 ,   198, 40},//ץ��צ��5
					{225,    119,      111,   119,   163, 40},//��ά��6
					{0  ,    243,      21,    203,  0 ,  40},  //̧��צ��7
					{ 110,    164,      129,    112,  86 ,  40},  //ʶ������8
					{ 157,   242,      55,    180 ,   155, 40},//׼����ȡ��9
					{ 81,   242,      55,    180 ,   155, 40},//׼����ȡ��10
					{ 0,   110,      89,   142,   0, 40},//ץȡ���zuo/you11
				};
/* Private function prototypes -----------------------------------------------*/

#if _new
void set_speed(float vx,float vy,enum car_state state)
{
	GM_25_spd_set.dstVmmps_X = vx;
  GM_25_spd_set.dstVmmps_Y = vy;
	Car_State = state;
}
/*�����Σ�����ʼλ���˶�����ά�����򣬲�����*/
void Start_(void)
{
	static uint8_t step = 0;
	//��0��:��y�����˶�һ����
	if(step == 0)
	{
		if(Distance < 220)
		{
			set_speed(0,1500,y_pos);
			Ready_Get();//��е��׼����ȡ_
			step++;
		}
	}	
	//��1��:��x�����˶������Ҹ��ݼ��Ᵽ�ֳ���y������320~280
	else if(step == 1)
	{
		Hands_Up();//������צ_
    set_speed(0,0,y_pos);
		if( x_now < 3 && Distance < 260)  
		{
			set_speed(2000,pid_calc(&pid_distance_catuch,Distance,300),x_pos);
		}	
		else 
		{
			set_speed(1800,0,x_pos);
		}
		if(x_now > 3) 
		{
			set_speed(1500,0,x_pos);	
			step++;
		}
	}
	//��2��:��x�����˶�ֱ����5����
	else if(step == 2 && x_now >= 6)
	{
		
		set_speed(0,0,stop);//ֹͣ����ʱ�ȴ���ά��
		osDelay(200);
		GetQRcode();//�˶���ɨ���ά����̬_
		Open_QRcode();//������ά��
		osDelay(1000); 
		step++;

	}
	//��3��:�ж��Ƿ���Ҫ�ƶ�������һ����Χ��
	else if(step == 3)
	{
		if(Distance > 400 && Distance < 200)
		{
			set_speed(0,pid_calc(&pid_distance_catuch,Distance,320),stop);
			osDelay(100); 
		}
		else
		{
			step++;
		}
	}
	//��4��:�࿪һ�ζ�ά�������������˶�
	else if(step == 4)
	{
		if(x_now == 4)
		{
			step = 0;
			set_speed(0,0,stop);
			Hands_Up();
      way_planning();
			STATUS = Get__;
		}
    else
    {
      set_speed(0,0,stop);
      Open_QRcode();
      osDelay(200);
      set_speed(-1500,-200,x_nag);
    }
	}
	
}

/*��ȡ���ϣ�վ�������ϼ�ȡ��ͬλ�õ�����*/
void Get_(uint8_t goal)
{
	static uint8_t step_get = 0;
	
	
	//��0��:���ߣ�������е��׼������
	if(step_get == 0)
	{

		LB_Flag = 1;			//ѡ�ư�1
		Corrrct_Flag = 1; //��ʼ����				
		osDelay(500);
		Corrrct_Flag = 0; //���߽���

		set_speed(0,0,stop);
		
		//ִ�л�е�۶���
		switch(goal_x[goal])
		{
			case 1://left
			{
				Ready_Get_left();
			}
			break;
			case 2: //medium
			{
				Ready_Get();
			}
			break;
			case 3://right
			{
				Ready_Get_right();
			}
			break;
		}
		
		step_get++;
		
	}
	//��1��:��ಢ����
	else if(step_get == 1)
	{
		if(Distance > 100)
		{
			set_speed(0,pid_calc(&pid_distance_catuch,Distance,80),stop);
		}
		else
		{
			set_speed(0,0,stop);
			step_get++;
		}
	}
	//��2��:����е��ʣ�ද��
	else if(step_get == 2)
	{
		if(goal_x[goal] != 2)
		{
			Get_Material_another();
		}
		else
		{
			Get_Material();
		}
		
		osDelay(500);
		Get();
		osDelay(300);
		Hands_Up();
		osDelay(500);
		Ready_Put();
		step_get = 0;
		STATUS = MoveUp;
	}
}

/*������������ȡ���˶������Ϸ�����*/
void Move_Up(void)
{
	
	LB_Flag = 2;  		//ѡ�ư�2
	Corrrct_Flag = 1;	//����
	//Ѳ����
	if(y_now == 1)
	{
		set_speed(0,1500,y_pos);
	}
	else if(y_now == 2)
	{
		set_speed(0,1300,y_pos);
	}
	else if(y_now == 3)
	{
		Corrrct_Flag = 0;  //�����ֹͣѲ��
		set_speed(0,0,stop);
		osDelay(100);
		STATUS = Put;
	}
	
}

/*���������ɷ������˶�����ȡ������������л�������*/
void Move_Down(void)
{
	static uint8_t step_down = 0;
	//��0��:Ѳ���ߵ���ȡ��
	if(step_down == 0)
	{
		LB_Flag = 2;			//ѡ��ư�2
		Corrrct_Flag = 1;	
		if(y_now == 3)
		{
			set_speed(0,-1500,y_nag);
		}
		else if(y_now == 2)
		{
			set_speed(0,-1300,y_nag);
		}
		if(y_now == 1)
		{
			
			Corrrct_Flag = 0; //�رն���
			set_speed(0,0,stop);
			select_senor(UP);	//ֻ�������л�up������
			osDelay(100);
		}
	}
	//��1��:
	else if(step_down == 1)
	{
		if(Distance > 100)
		{
			set_speed(0,pid_calc(&pid_distance_catuch,Distance,80),stop);
		}
		else
		{
			set_speed(0,0,stop);
			step_down = 0;
			STATUS = Get__;
		}
	}
}

/*���������������˶�����Ӧλ�ã��������ϲ���������*/
void Put_(uint8_t goal)
{
	static uint8_t step_put = 0;
	
	select_senor(DOWN); //��put������ȫ�̶���Ҫʹ��DOWN�ư�
	
	//��0��:ͨ���β�ѡ���˶�����
	if(step_put == 0)
	{
		switch(goal_x[goal])
		{
			case 1://left
			{
				set_speed(-1300,0,x_nag);
				if(x_now == 3)
				{
					set_speed(0,0,stop);
					
					LB_Flag=2;
					Corrrct_Flag = 1;
					osDelay(500);
					set_speed(0,0,stop);
					Corrrct_Flag = 0;
					step_put++;
				}
				
			}
			break;
			case 2:
			{
				LB_Flag=2;
				Corrrct_Flag = 1;
				osDelay(500);
				set_speed(0,0,stop);
				Corrrct_Flag = 0;
				step_put++;
			}
			break;
			case 3:
			{
				set_speed(1300,0,x_pos);
				if(x_now == 5)
				{
					set_speed(0,0,stop);
					LB_Flag=2;
					Corrrct_Flag = 1;
					osDelay(500);
					set_speed(0,0,stop);
					Corrrct_Flag = 0;
					step_put++;
				}
			}
			break;
		}
	}
	//��1��:������
	else if(step_put == 1)
	{
		set_speed(0,-1000,stop);
		osDelay(400);  													//������	_
		set_speed(0,0,stop);
		Put_Material();
		osDelay(800);
		Open();
		osDelay(500);
		step_put++;
	}
	//��2��:������
	if(step_put == 2)
	{
		switch(goal_x[goal])
		{
			case 1://left
			{
				set_speed(1300,0,x_pos);
				if(x_now == 4)
				{
					set_speed(0,0,stop);
					LB_Flag=2;
					Corrrct_Flag = 1;
					osDelay(500);
					set_speed(0,0,stop);
					Corrrct_Flag = 0;
					step_put++;
				}
				
			}
			break;
			case 2:
			{
				step_put++;
			}
			break;
			case 3:
			{
				set_speed(-1300,0,x_nag);
				if(x_now == 4)
				{
					set_speed(0,0,stop);
					LB_Flag=2;
					Corrrct_Flag = 1;
					osDelay(500);
					set_speed(0,0,stop);
					Corrrct_Flag = 0;
					step_put++;
				}
			}
			break;
		}		
	}
	//��3��
	else if(step_put == 3)
	{
		STATUS = MoveDown;
		step_put = 0;
	}
	
}

void Back_home(void)
{
	static uint8_t back_step = 0;
	Hands_Up();
	if(back_step == 0)
	{	
		select_senor(DOWN);
		if(x_now >1)
		{
			GM_25_spd_set.dstVmmps_X=-2000;
				
		}
		else
		{
			GM_25_spd_set.dstVmmps_X = -100;
			back_step++;
		}
	}
	else if(back_step == 1 )
	{
			select_senor(UP);
		if(y_now>0) 
		{
			GM_25_spd_set.dstVmmps_Y =-1500;
		}
		else 
		{
			GM_25_spd_set.dstVmmps_Y=0;
			GM_25_spd_set.dstVmmps_X=0;
		}
	}
}
void Decision_Task(void const * argument)
{

	PID_struct_init(&pid_distance, POSITION_PID, 1500, 1,
										1.0f,	0.00f,	0.0f ,0.0f ,0.0f	);
	pid_distance.deadband=20;
	PID_struct_init(&pid_distance_catuch, POSITION_PID, 1500, 1,
										25.0f,	0.00f,	300.0f ,0.0f ,0.0f	);
	extern float x_now;
	extern float y_now;
	extern uint8_t  color[3];

	STATUS=Start;
	servo_set(servo);
  Hands_Up();
	
	servo_set(servo);
	static uint8_t way_num = 0;
  for(;;)
  {
		switch(STATUS)
		{
			case Start:
			{
				Start_();
			}
			break;
			case Get__:
			{
				Get_(goal_x[way_num]);
			}
			break;
			case MoveUp:
			{
				Move_Up();
			}break;
			case Put:
			{
				Put_(goal_x[way_num + 1]);
			}
			break;
			case MoveDown:
			{
				Move_Down();
				if(STATUS == Get__)
				{
					way_num +=2;
					if(way_num == 4)
					{
						STATUS = Back;
					}
				}
			}
			break;
			case Back:
			{
				Back_home();
			}
			break;
		}
    osDelay(10);
  }

  LCD_Display_int(goal_x[0],1,2); 			LCD_Display_int(goal_x[1],1,3);  			LCD_Display_int(goal_x[2],1,4); 		//ɫ��˳��
	LCD_Display_int(goal_x[3],1,5); 	LCD_Display_int(goal_x[4],1,6);  	LCD_Display_int(goal_x[5],1,7);//����˳��

//	LCD_Display_int(color[0],1,2); 			LCD_Display_int(color[1],4,2);  			LCD_Display_int(color[2],8,2); 		//ɫ��˳��
//	LCD_Display_int(way_color[0],1,2); 	LCD_Display_int(way_color[1],4,2);  	LCD_Display_int(way_color[2],8,2);//����˳��

	 
}		
#endif				
#if old
/**
	**************************************************************
	** Descriptions:
	** Input: 	
  **						
	**					
	**					
	** Output: NULL
	**************************************************************
**/
void _Start(void)
{
	
		
	if(x_now<1 && Distance<280)
	{
		GM_25_spd_set.dstVmmps_X = 0;
		GM_25_spd_set.dstVmmps_Y = 1500;
		Ready_Get();
		Car_State = y_pos;
	}
  /*��Ҫװ�ϸ�̨������Զ���̨*/
  else  
  {
		See_Color();

		if( x_now<3 &&Distance < 280)  
		{
			GM_25_spd_set.dstVmmps_X = 2500;  
			GM_25_spd_set.dstVmmps_Y_offset = pid_calc(&pid_distance_catuch,Distance,320);
		}	
		else 
		{
			GM_25_spd_set.dstVmmps_X = 2000;  
			GM_25_spd_set.dstVmmps_Y = 0;
		}
	
		if(x_now > 3) 
		{
			GM_25_spd_set.dstVmmps_X=1500;
				GM_25_spd_set.dstVmmps_Y = 0;
		}
  }
	
	if(x_now == 5)
	{
	  Hands_Up();
		GM_25_spd_set.dstVmmps_X = 0;
		GM_25_spd_set.dstVmmps_Y = 0;
		osDelay(200);
		GetQRcode();
	  Open_QRcode();
   if(Distance>400&&Distance<200)
	 {
		 GM_25_spd_set.dstVmmps_Y_offset = pid_calc(&pid_distance_catuch,Distance,320);
		 osDelay(50);
	 }else
	 {
		STATUS = Through;
	 }
	}
}

/**
	**************************************************************
	** Descriptions:
	** Input: 	
  **						
	**					
	**					
	** Output: NULL
	**************************************************************
**/
void _Through(void)
{
  GM_25_spd_set.dstVmmps_X = 0;
  GM_25_spd_set.dstVmmps_Y = 0;

		GetQRcode();
	  Open_QRcode();

	
    STATUS = Get_QR;

}

/**
	**************************************************************
	** Descriptions:
	** Input: 	
  **						
	**					
	**					
	** Output: NULL
	**************************************************************
**/
void _GetQR(void)
{
static uint8_t step_GetQR = 0;
	
      way_color[0]=3;
			way_color[1]=2;
      way_color[2]=1;
  
  if(step_GetQR == 0)
  {
    if( x_now == 5)
    {
			
	    Open_QRcode();
  
			GM_25_spd_set.dstVmmps_X = 0;

//     if(way_color[0]!=1 || way_color[0]!=2 || way_color[0]!=3 )
//		 {
//			 step_GetQR = 0;
//			 osDelay(500);
//		 }else 
		 step_GetQR = 1;
    }
  }
  //����������
  else
  {
    if(x_now > 4)
    {
			
      GM_25_spd_set.dstVmmps_X = -1500;
//      GM_25_spd_set.dstVmmps_Y = -200;
    }
    else if(x_now == 4)
    {
		 select_senor(UP);
			get_flag++;
			GM_25_spd_set.dstVmmps_Y = 0;
			GM_25_spd_set.dstVmmps_X = 0;
			LB_Flag=1;
			
			if(Distance<100) 
			{	
				Corrrct_Flag = 1;
				GM_25_spd_set.dstVmmps_Y = 0;
	
			}else GM_25_spd_set.dstVmmps_Y_offset = pid_calc(&pid_distance_catuch,Distance,80);
			
    }
		
  } 

	   if(get_flag == 50)
				{
					
          STATUS = GetMaterial;
					Corrrct_Flag =0;
					GM_25_spd_set.dstVmmps_Y = 0;
			    get_flag = 0;
			  	Hands_Up();
					
				}
  
}

/**
	**************************************************************
	** Descriptions:
	** Input: 	
  **						
	**					
	**					
	** Output: NULL
	**************************************************************
**/
void _GetMaterial(void)
{

	  static uint8_t QR_flag=0;
	static uint8_t step = 0;


	
	
	switch(/*way_color[QR_flag]*/)//��ɫ˳��
	{
		case 0x01://��
		{
			if(step == 0)
			{
			//ץȡ���
				select_senor(UP);
	     put_flag++;
			if(put_flag<20)Ready_Get_left();
			if(put_flag>80&&put_flag<200) Get_Material_another();
			if(put_flag>200)	Get();
				if(put_flag>250)
			{
				Hands_Up();
				put_flag=0;
				step++;
				GM_25_spd_set.dstVmmps_X = 0;
				GM_25_spd_set.dstVmmps_Y= 0 ;
			}
	
		}
			else if(step == 1 )
			{

				//ѡ������2.����ͣ��������
      

				if(x_now != 3)
				{
		     Car_State = x_nag;
					GM_25_spd_set.dstVmmps_X = -1500;
				GM_25_spd_set.dstVmmps_Y = -130;
					GM_25_spd_set.dstVmmps_Y = 0;

				}	
				else if(x_now == 3)
				{
					LB_Flag=1;
					
					step++;
					
					GM_25_spd_set.dstVmmps_X=0;
          GM_25_spd_set.dstVmmps_Y=0;
					Corrrct_Flag = 1;//����
					osDelay(500);
			
					Corrrct_Flag = 0;
//
					
					GM_25_spd_set.dstVmmps_X=100; //�������֮�����ʣ���x�����ٶ� 

					GM_25_spd_set.dstVmmps_Y = 1500;
					
					Car_State = y_pos;
				}
			}		
			else if(step == 2)
			{	 
				
				Ready_Put();
				if(y_now >= 2)
				{
				
					GM_25_spd_set.dstVmmps_Y = 1300;
			
					if(Distance>680) step++;
				
				}
			}
			else if(step == 3)
			{
				if(y_now==3 ) 					
				{			
//					LB_Flag=2;
					GM_25_spd_set.dstVmmps_X = 0;
					GM_25_spd_set.dstVmmps_Y = 0;
//						Corrrct_Flag=1;
//							osDelay(500); //�ȴ�����
//						Corrrct_Flag = 0;
		
					GM_25_spd_set.dstVmmps_X = 0;
	
					break_flag = 1;
					step = 0;
					QR_flag++;
				STATUS = PutMaterial;
				}
			}
		}
		break;
		
		case 0x02://��
		{
			
			if(step == 0)
			{
				select_senor(UP);
		    put_flag++;
			if(put_flag<20)Ready_Get();
			if(put_flag>120&&put_flag<150) Get_Material();
				if(put_flag>150)	Get();
				if(put_flag>250){
				put_flag=0;
				step++;
					Hands_Up();
			
			} 
		}
				else if(step == 1)
			{

			 if(x_now == 4)   
				{
				
					Corrrct_Flag=1;
						osDelay(500); //�ȴ����

					GM_25_spd_set.dstVmmps_Y=1500;
				  GM_25_spd_set.dstVmmps_X=0;
		  }
				if(y_now == 2)
				{
					Corrrct_Flag=1;
					
					
					GM_25_spd_set.dstVmmps_Y=1300;
					Ready_Put();
//					if(Distance>350)
				
				
			}
					if(y_now == 3)
					{
						step++;			
						
				}
		}
				
		
				else if(step == 2)
				{
				if(y_now==3 ) 				
						{
							
							GM_25_spd_set.dstVmmps_X=0;
							GM_25_spd_set.dstVmmps_Y=0;
							STATUS = PutMaterial;
							break_flag = 2;
							QR_flag++;
							step=0;
						}		
					}
		}
		break;
		
		case 0x03://��
		{
			if(step == 0)
			{
				select_senor(UP);
			put_flag++;
			if(put_flag<80)Ready_Get_right();
			if(put_flag>140&&put_flag<200) Get_Material_another();
				if(put_flag>200)	Get();
				if(put_flag>250){

				put_flag=0;
				step++;
			}
		}
    
			if(step == 1)
			{	
			    Hands_Up();
				osDelay(500);
				if(x_now != 5)
		  	GM_25_spd_set.dstVmmps_X = 1400;
			 if(x_now == 5)   
				{	 
						GM_25_spd_set.dstVmmps_X =0;
					Corrrct_Flag = 1;//����
					
					osDelay(500); //�ȴ�����
	   	
		      Corrrct_Flag = 0;
					GM_25_spd_set.dstVmmps_X = 0; //�������֮����������x�����ٶ�

					GM_25_spd_set.dstVmmps_Y=1500;
						step++;		
			
		  }
				
		}else if(step ==2)
				{
				if(y_now == 2)
				{
							Ready_Put();
					GM_25_spd_set.dstVmmps_Y=1300;
								
				}
				else if(y_now==3 ) 	
						{
							GM_25_spd_set.dstVmmps_X = 0;
					GM_25_spd_set.dstVmmps_Y = 0;
						Corrrct_Flag=1;
							osDelay(500); //�ȴ�����
						Corrrct_Flag = 0;
		
					GM_25_spd_set.dstVmmps_X = 0;
					STATUS = PutMaterial;
					break_flag = 3;
					step = 0;
					//way_color[0]=2;

							if(Distance>650)
							{
							GM_25_spd_set.dstVmmps_Y=0;
								GM_25_spd_set.dstVmmps_X=0;
							 STATUS = PutMaterial;
										break_flag = 3;
							Corrrct_Flag = 0;
							QR_flag++;
							step=0;
							}
							else y_now--;
						}	
		     }
	}
		
	}
  	if(QR_flag==3)	break_flag=4;
}

/**
	**************************************************************
	** Descriptions:
	** Input: 	
  **						
	**					
	**					
	** Output: NULL
	**************************************************************
**/
void _PutMaterial(void)
{
	  LB_Flag=2;
    put_flag++;
	  Put_Material();
	  GM_25_spd_set.dstVmmps_Y=-1000;
	  osDelay(1);

	//���óɹ��󷵻�
	if(put_flag==50)
	{ 	
		GM_25_spd_set.dstVmmps_Y=0;
		Corrrct_Flag=1;
		osDelay(1000);
		Corrrct_Flag=0;
		GM_25_spd_set.dstVmmps_X=0;
	  GM_25_spd_set.dstVmmps_Y=0;
		Open();
    put_flag=0;
		STATUS = Back;
	}		
  
}

/**
	**************************************************************
	** Descriptions:
	** Input: 	
  **						
	**					
	**					
	** Output: NULL
	**************************************************************
**/
void _Back(void)
{
	static uint8_t step = 0;
	
	switch(break_flag)
	{
		case 1://�ص�����
		{   
			select_senor(DOWN); 
			Hands_Up();
		
			if(step == 0)
			{			
			
				if(x_now == 4 )
				{
//					if(Distance<650)
//					{
//					GM_25_spd_set.dstVmmps_X = 0;
//					step++;
//					}
//					else
//					{
//					x_now--;
//					
//					}
					step++;
			 } else GM_25_spd_set.dstVmmps_X = 1300;
			}
			else if(step == 1) 
			{
				GM_25_spd_set.dstVmmps_X = 0;
				Hands_Up();
				if( y_now > 2 && Distance>420)
				{
					GM_25_spd_set.dstVmmps_Y = -1500;
				}
				else
				{			
					
          GM_25_spd_set.dstVmmps_Y=-1300;
//					Corrrct_Flag = 1;
				
		      GM_25_spd_set.dstVmmps_X = 0;

					
				
			 }
					//��ʱ
				if(Distance<180)	
				{
					Corrrct_Flag = 0;
					GM_25_spd_set.dstVmmps_Y=0;
					step=0;
//					Corrrct_Flag = 0;
					select_senor(UP);
					STATUS = Get_QR;
				}
			}
			
		}
		break;
		
		case 2:  //�ص�����
		{
		
			if(step == 0)
			{ 
	      select_senor(DOWN); 
					Hands_Up();
				GM_25_spd_set.dstVmmps_Y=0;
				
				if(x_now == 4)
				{
					GM_25_spd_set.dstVmmps_X = 0;
					step++;
				}
				else
				{
		
					GM_25_spd_set.dstVmmps_X = 1300;
				}
			}
			else if(step == 1) 
			{
				Hands_Up();
				if(y_now > 2 && Distance>420)
				{
					GM_25_spd_set.dstVmmps_Y = -1500;
				}
				else
				{			
					
					GM_25_spd_set.dstVmmps_Y=-1300;
//					Corrrct_Flag = 1;
//					osDelay(100); //����

//				
					
		      GM_25_spd_set.dstVmmps_X = 0;

					

			 }
									//��ʱ
				if( Distance<180)	
				{
						Corrrct_Flag = 0;
					GM_25_spd_set.dstVmmps_Y=0;
				
					step=0;
					select_senor(UP);
					Hands_Up();
	       STATUS = Get_QR;
				}
			}
		}
		break;
		
		case 3: // 
		{
			
			if(step == 0)
			{	
				select_senor(DOWN); 
				Hands_Up();
				
				if(x_now == 4 )
				{
//					if(Distance<650)
//					{
//					GM_25_spd_set.dstVmmps_X = 0;
//					step++;
//				}
//				else
//				{
//					x_now--;
//					
//				}
					step++;
			 } else GM_25_spd_set.dstVmmps_X = -1500;
				
			}
			else if(step == 1) 
			{
				GM_25_spd_set.dstVmmps_X = 0;
				if(y_now > 2)
				{
					GM_25_spd_set.dstVmmps_Y = -1500;
				}
				else
				{			
					
					GM_25_spd_set.dstVmmps_Y=-1300;
//					Corrrct_Flag = 1;
//					osDelay(100); //����
					
//	
					
//					Corrrct_Flag = 0;
		      GM_25_spd_set.dstVmmps_X = 0;

					
			
				}
						//��ʱ
				if( Distance<180)	
				{
						Corrrct_Flag = 0;
					GM_25_spd_set.dstVmmps_Y=0;
				select_senor(UP);
					step=0;
						Hands_Up();
						STATUS = Get_QR;
			 }
			}
		}
		break;
		case 4 :
		{
		
					Hands_Up();
			if(step == 0)
			{	
				select_senor(DOWN);
				if(x_now >1)
				{
					GM_25_spd_set.dstVmmps_X=-2000;
						
				}
				else
				{
					GM_25_spd_set.dstVmmps_X = -100;
					step++;
				}
			}
			else if(step == 1 )
			{
					select_senor(UP);
				if(y_now>0) 
				{
					GM_25_spd_set.dstVmmps_Y =-1500;
				}
				else 
				{
					GM_25_spd_set.dstVmmps_Y=0;
					GM_25_spd_set.dstVmmps_X=0;
				}
			}
		}
		break;
	}
	
	
	

}


void Decision_Task(void const * argument)
{

	PID_struct_init(&pid_distance, POSITION_PID, 1500, 1,
										1.0f,	0.00f,	0.0f ,0.0f ,0.0f	);
	pid_distance.deadband=20;
	PID_struct_init(&pid_distance_catuch, POSITION_PID, 1500, 1,
										25.0f,	0.00f,	300.0f ,0.0f ,0.0f	);
	extern float x_now;
	extern float y_now;
	STATUS=Start;
	servo_set(servo);
  Hands_Up();
	way_color[0]=0;
	servo_set(servo);
  for(;;)
  {

		
//		LCD_Display_int(way_color[0],1,3);
//		LCD_Display_int(way_color[1],1,4);
//		LCD_Display_int(way_color[3],1,5);
		
					LCD_Display_float(jy61_yaw.JY_angle,1,6);

    switch(STATUS)
    {
      case Start:
        {
          _Start();

	    LCD_Display_float(x_now,1,1);  
			LCD_Display_float(y_now,1,2); 
//			LCD_Display_float(GM_25_spd_set.dstVmmps_X,1,3);
//			LCD_Display_float(GM_25_spd_set.dstVmmps_Y,1,4);
//			LCD_Display_float(Distance,1,5);
			LCD_Display_float(local_up.total,1,3);
			LCD_Display_float(local_down.total,1,4);
			LCD_Display_float(local_state,1,5);

		
        }
        break;
      case Through:
        {
          _Through();
				
					LCD_Display_float(x_now,1,1);  
					LCD_Display_float(y_now,1,2); 
//					LCD_Display_float(GM_25_spd_set.dstVmmps_X,1,3);
//					LCD_Display_float(GM_25_spd_set.dstVmmps_Y,1,4);
//         	LCD_Display_float(Distance,1,5);
					LCD_Display_float(local_up.total,1,3);
					LCD_Display_float(local_down.total,1,4);
			LCD_Display_float(local_state,1,5);
//			LCD_Display_float(Car_State,1,6);
        }
        break;
      case Get_QR:
        {
//					LCD_Display_float(Senor1,1,1);
//		LCD_Display_float(Senor2,1,2);
//		LCD_Display_float(Senor3,1,3);
//		LCD_Display_float(Senor4,1,4);
          _GetQR();
					LCD_Display_float(x_now,1,1);  
					LCD_Display_float(y_now,1,2);
//					LCD_Display_float(way_color[0],1,3);
//					LCD_Display_float(way_color[1],1,4);
//					LCD_Display_float(way_color[2],1,5);
					LCD_Display_float(local_up.total,1,3);
					LCD_Display_float(local_down.total,1,4);
			LCD_Display_float(local_state,1,5);
//			LCD_Display_float(Car_State,1,6);
        }
        break;
      case GetMaterial:
        {
					_GetMaterial();
					LCD_Display_float(Distance,1,5);
					LCD_Display_float(x_now,1,1);  
					LCD_Display_float(y_now,1,2);
//					LCD_Display_float(GM_25_spd_set.dstVmmps_X,1,3);
//					LCD_Display_float(GM_25_spd_set.dstVmmps_Y,1,4);			
					LCD_Display_float(local_up.total,1,3);
					LCD_Display_float(local_down.total,1,4);
			LCD_Display_float(local_state,1,5);
//			LCD_Display_float(Car_State,1,6);

        }
        break;
      case PutMaterial:
        {
          _PutMaterial();
					 LCD_Display_float(x_now,1,1);  
					 LCD_Display_float(y_now,1,2);
//					LCD_Display_float(GM_25_spd_set.dstVmmps_X,1,3);
//					LCD_Display_float(GM_25_spd_set.dstVmmps_Y,1,4);
//					LCD_Display_float(Distance,1,5);
					
					LCD_Display_float(local_up.total,1,3);
					LCD_Display_float(local_down.total,1,4);
			LCD_Display_float(local_state,1,5);
//			LCD_Display_float(Car_State,1,6);
        }
        break;
      case Back:
        {
          _Back();
					LCD_Display_float(x_now,1,1);  
					LCD_Display_float(y_now,1,2);
//					LCD_Display_float(GM_25_spd_set.dstVmmps_X,1,3);
//					LCD_Display_float(GM_25_spd_set.dstVmmps_Y,1,4);
//		      LCD_Display_float(Distance,1,5);
										LCD_Display_float(local_up.total,1,3);
					LCD_Display_float(local_down.total,1,4);
			LCD_Display_float(local_state,1,5);
//			LCD_Display_float(Car_State,1,6);
        }
        break;
    }
		
    osDelay(10);
  }
}
#endif
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
