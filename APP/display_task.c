/*************************************************************************************
*	@file			display_task.c
* @author	 	Ekko
*	@version 	V1.0
*	@date			2018/9/22
* @brief		NONE
*************************************************************************************/
/* Includes ------------------------------------------------------------------------*/
#include "display_task.h"

/* External variables --------------------------------------------------------*/
extern float Distance;				 //距离
extern uint8_t mode;

extern float x_now; //初始值为0.5
extern float y_now;

/* Internal variables --------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

void Display_Task(void const * argument)
{
	static int arm_step = 0;
  static uint8_t step[] = "step";
  static uint8_t A1[] = "A1";
  static uint8_t A2[] = "A2";
  static uint8_t A3[] = "A3";
  static uint8_t A4[] = "A4";
	static uint8_t A5[] = "A5";
  static uint8_t x[] = "x";
  static uint8_t servo_num = 0; 
  static uint8_t key3_num = 0;
  //??:??:????0~300
	//      RPM:????114RPM
  				/*  1   2  3   4   5  speed*/
					
		static float servo[12][6] = {
					{ 110,   210,      55,    180 ,   155, 40},//准备夹取0
					{ 0,   119,      111,   119,   0, 40},//抓取物块1
					{0,    81,      132,   113,   0, 40},//放下物块2
					{334,   0,      0,   0  , 0, 40},//准备放下3
					{  0 ,     0,       0,    0  ,   163, 40},//放开爪子4
					{  0,     0,       0,     0 ,   198, 40},//抓紧爪子5
					{225,    110,      70,   169,   163, 40},//二维码6
					{0  ,    243,      21,    203,  0 ,  40},  //抬起爪子7
					{ 110,    164,      129,    112,  86 ,  40},  //识别物体8
					{ 157,   242,      55,    180 ,   155, 40},//准备夹取左9
					{ 81,   242,      55,    180 ,   155, 40},//准备夹取右10
					{ 0,   110,      89,   142,   0, 40},//抓取物块zuo/you11
				};
  /*?????:??-????-????-??-????-????-??*/
//	See_Color();
	servo_set(servo);
	//GetQR();	//0 
  for(;;)
  {
		static uint8_t LED1_NUM = 0;
    /*KEY1???*/
//    if(KEY1 == 0)
//    {
//      osDelay(50);
//      if(KEY1 == 0)
//      {
//        if(arm_step != 0)
//        arm_step--;
//      }
//      
//    }
    /*KEY2???*/
    if(KEY2 == 0)
    {
      osDelay(50);
      if(KEY2 == 0)
      {
        arm_step++;				
      }
      
    }
    switch(arm_step)
    {
			case 0:
      {
        Ready_Get_left();
        servo_num = 9;
        osDelay(100);
      }
			break;
      case 1:
      {
        Get_Material_another();
        servo_num = 11;
        osDelay(100);
      }
      break;
      case 2:
      {
        Get();
        servo_num = 5;
        osDelay(100);
      }
      break;
      case 3:
      {
        Hands_Up();
        servo_num = 7;
        osDelay(100);
      }
      break;
      case 4:
      {
        Ready_Get_right();;
        servo_num = 10;
        osDelay(100);
      }
      break;
			case 5:
      {
        Get_Material_another();
        servo_num = 11;
        osDelay(100);
      }
      case 6:
      {
        Get();
        servo_num = 5;
        osDelay(100);;
      }
      break;
      case 7:
      {
        Hands_Up();
        servo_num = 7;
        osDelay(100);
      }
      break;
      case 8:
      {
        osDelay(100);
        arm_step = 0;
      }
//      break;
//			case 9:
//      {
//        Hands_Up();
//        servo_num = 7;
//        osDelay(100);
//      }
//			case 10:
//      {
//        Ready_Get_left();
//        servo_num = 9;
//        osDelay(100);
//      }
//      break;
//      case 11:
//      {
//        Get_Material();
//        servo_num = 1;
//        osDelay(100);
//      }
//      break;
//      case 12:
//      {
//        Get();
//        servo_num = 5;
//        osDelay(100);
//      }
//      break;
//			case 13:
//      {
//        Hands_Up();
//        servo_num = 7;
//        osDelay(100);
//      }
//      break;
//			case 14:
//      {
//        Ready_Get_right();
//        servo_num = 10;
//        osDelay(100);
//      }
//      break;
//      case 15:
//      {
//        Get_Material();
//        servo_num = 1;
//        osDelay(100);
//      }
//      break;
//      case 16:
//      {
//        Get();
//        servo_num = 5;
//        osDelay(100);
//      }
//      break;
//			case 17:
//      {
//        Hands_Up();
//        servo_num = 7;
//        osDelay(100);
//      }
//      case 18:
//      {
//				osDelay(100);
//        arm_step = 2;
//      }
//      break;
    }
    /*?????:??-????-????-??-????-????-??*/
//    switch(arm_step)
//    {
//			case 0:
//      {
//        See_Color();
//        servo_num = 8;
//        osDelay(100);
//      }
//			break;
//      case 1:
//      {
//        GetQRcode();
//        servo_num = 6;
//        osDelay(100);
//      }
//      break;
//      case 2:
//      {
//        Ready_Get();
//        servo_num = 0;
//        osDelay(100);
//      }
//      break;
//      case 3:
//      {
//        Get_Material();
//        servo_num = 1;
//        osDelay(100);
//      }
//      break;
//      case 4:
//      {
//        Get();
//        servo_num = 5;
//        osDelay(100);
//      }
//      break;
//			case 5:
//      {
//        Hands_Up();
//        servo_num = 7;
//        osDelay(100);
//      }
//      case 6:
//      {
//        Ready_Put();
//        servo_num = 3;
//        osDelay(100);
//      }
//      break;
//      case 7:
//      {
//        Put_Material();
//        servo_num = 2;
//        osDelay(100);
//      }
//      break;
//      case 8:
//      {
//        Open();
//        servo_num = 4;
//        osDelay(100);
//      }
//      break;
//			case 9:
//      {
//        Hands_Up();
//        servo_num = 7;
//        osDelay(100);
//      }
//			case 10:
//      {
//        Ready_Get_left();
//        servo_num = 9;
//        osDelay(100);
//      }
//      break;
//      case 11:
//      {
//        Get_Material();
//        servo_num = 1;
//        osDelay(100);
//      }
//      break;
//      case 12:
//      {
//        Get();
//        servo_num = 5;
//        osDelay(100);
//      }
//      break;
//			case 13:
//      {
//        Hands_Up();
//        servo_num = 7;
//        osDelay(100);
//      }
//      break;
//			case 14:
//      {
//        Ready_Get_right();
//        servo_num = 10;
//        osDelay(100);
//      }
//      break;
//      case 15:
//      {
//        Get_Material();
//        servo_num = 1;
//        osDelay(100);
//      }
//      break;
//      case 16:
//      {
//        Get();
//        servo_num = 5;
//        osDelay(100);
//      }
//      break;
//			case 17:
//      {
//        Hands_Up();
//        servo_num = 7;
//        osDelay(100);
//      }
//      case 18:
//      {
//				osDelay(100);
//        arm_step = 2;
//      }
//      break;
//    }
  servo_set(servo);

    
    /*LCD??*/
    LCD_Write_string(step,1,1);    LCD_Display_int(arm_step,7,1);
    LCD_Write_string(A1,1,2);      LCD_Display_float(servo[servo_num][0],4,2);     LCD_Display_int(key3_num + 1,15,1);
    LCD_Write_string(A2,1,3);      LCD_Display_float(servo[servo_num][1],4,3);
    LCD_Write_string(A3,1,4);      LCD_Display_float(servo[servo_num][2],4,4);
    LCD_Write_string(A4,1,5);      LCD_Display_float(servo[servo_num][3],4,5);
		LCD_Write_string(A5,1,6);      LCD_Display_float(servo[servo_num][4],4,6);
    /*KEY3??????? 0-2*/
    if(KEY3 == 0)
    {
      osDelay(50);
      if(KEY3 == 0)
      {
        key3_num++;
        if(key3_num == 5)
        {
          key3_num = 0;
        }
      }
      
    }
    /*KEY4++,KEY5--*/
    if(KEY4 == 0)
    {
      osDelay(50);
      if(KEY4 == 0)
      {
        servo[servo_num][key3_num]++;				
      }
      
    }
    if(KEY1 == 0)
    {
      osDelay(50);
      if(KEY1 == 0)
      {
        servo[servo_num][key3_num]--;				
      }
      
    }
    if(LED1_NUM > 30)
		{
			HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_14);
			LED1_NUM = 0;
		}
		LED1_NUM++;

    osDelay(5);
  }
//	static unsigned char common[] = "COMMON ";
//  static unsigned char high[] = "HIGH   ";
//  static unsigned char quickly[] = "QUICKLY";
//  static unsigned char llong[] = "LONG   ";
 // static uint8_t instruct[3] = {0xa5,0,0};
//  static uint8_t set_mode = 0;	
//	static uint8_t data[4] = {0,1,2,3};
//  static uint16_t look = 1111;
//  for(;;)
//  {
		
//		
//		LCD_Display_float(GM_25_spd_set.dstVmmps_X,1,1);
//		LCD_Display_float(GM_25_spd_set.dstVmmps_W,1,2);
//		LCD_Display_float(GM_25_spd_set.dstVmmps_Y,1,3);
//		LCD_Display_float(Distance,1,4);
//		LCD_Display_int(STATUS,1,3);
//		printf("%d\t%d\t%d\t%d\t%d\r\n",call_message[0],call_message[1],call_message[2],call_message[3],call_status);
//    LCD_Display_float(x_now,1,1);
//		LCD_Display_float(y_now,1,2);
//    LCD_Display_int(call_message[2],1,3);
//    LCD_Display_int(call_message[3],1,4);
//    LCD_Display_int(look,1,5);
//    LCD_Display_float(Distance,1,1);
//    //LCD_Display_int(angle * 0.293,1,1);
//    /*返回的当前模式*/
//    switch(mode)
//    {
//      case 0x0:
//        LCD_Write_string(llong,1,2);
//        break;
//      case 0x1:
//        LCD_Write_string(quickly,1,2);
//        break;
//      case 0x2:
//        LCD_Write_string(high,1,2);
//        break;
//      case 0x3:
//        LCD_Write_string(common,1,2);
//        break;
//      
//    }
//    switch(set_mode)
//    {
//      case 0:
//        instruct[0] = 0xa5;
//        instruct[1] = 0x50;
//        instruct[2] = 0xf5;
//        HAL_UART_Transmit(&huart4,instruct,3,1);
//        break;
//      case 1:
//        instruct[0] = 0xa5;
//        instruct[1] = 0x51;
//        instruct[2] = 0xf6;
//        HAL_UART_Transmit(&huart4,instruct,3,1);
//        break;
//      case 2:
//        instruct[0] = 0xa5;
//        instruct[1] = 0x52;
//        instruct[2] = 0xf7;
//        HAL_UART_Transmit(&huart4,instruct,3,1);
//        break;
////      case 3:
//        instruct[0] = 0xa5;
//        instruct[1] = 0x53;
//        instruct[2] = 0xf8;
//        HAL_UART_Transmit(&huart4,instruct,3,1);
//        break;
//    }
//    /*KEY1改变模式*/   
//		if(KEY1 == 0)
//		{
//			osDelay(100);
//			if(KEY1 == 0)
//			{
//				set_mode++;
//        if(set_mode == 4)
//        {
//          set_mode = 0;
//        }
//			}
//		}
//    
//    if(KEY2 == 0)
//		{
//			osDelay(50);
//			if(KEY2 == 0)
//			{
//				HAL_GPIO_TogglePin(LED2_GPIO_Port,LED2_Pin);
//			}
//		}
//    if(KEY3 == 0)
//		{
//			osDelay(50);
//			if(KEY3 == 0)
//			{
//				HAL_GPIO_TogglePin(LED3_GPIO_Port,LED3_Pin);
//			}
//		}
//    if(KEY4 == 0)
//		{
//			osDelay(50);
//			if(KEY4 == 0)
//			{
//				HAL_GPIO_TogglePin(LED4_GPIO_Port,LED4_Pin);
//			}
//		}
//    if(KEY5 == 0)
//		{
//			osDelay(50);
//			if(KEY5 == 0)
//			{
//				HAL_GPIO_TogglePin(LED5_GPIO_Port,LED5_Pin);
//			}
//		}
//     osDelay(5);
//  }
  
//}

}


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

