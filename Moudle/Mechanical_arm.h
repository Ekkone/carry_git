#ifndef __Mechanical_arm_h
#define __Mechanical_arm_h

/* Includes ------------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "main.h"
#include "AX-12A.h"
#include "stdarg.h"





void servo_set(float buff[7][6]);
void StablePose(void);  	 	//id:0
void GetMaterial(void);	 	//id:1
void PutMaterial(void);	 	//id:2
void MiddlePose(void);    	//id:3
void Open(void);   		   	//id:4
void Get(void);		       	//id:5
void StretchPose(void); 	//id:6

#endif
