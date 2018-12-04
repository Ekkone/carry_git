#ifndef __Mechanical_arm_h
#define __Mechanical_arm_h

/* Includes ------------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "main.h"
#include "cmsis_os.h"
#include "AX-12A.h"
#include "stdarg.h"



void servo_set(float buff[9][6]);
void Ready_Get(void);  	 	//id:0 ×¼±¸¼ÐÈ¡
void Ready_Get_left(void);
void Ready_Get_right(void);
void Get_Material(void);	 	//id:1  
void Get_Material_another(void);
void Put_Material(void);	 	//id:2
void Ready_Put(void);    	//id:3
void Open(void);   		   	//id:4
void Get(void);		       	//id:5
void GetQRcode(void); 	//id:6  
void Hands_Up(void);      
void See_Color(void);
#endif
