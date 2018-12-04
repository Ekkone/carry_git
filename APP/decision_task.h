/*************************************************************************************
*	@file			run_task.h
* @author	 	Ekko
*	@version 	V1.0
*	@date			2018/9/22
* @brief		NONE
*************************************************************************************/
#ifndef __DECISIONTASK_H
#define __DECISIONTASK_H

/* Includes ------------------------------------------------------------------*/
#include "cmsis_os.h"
#include "bsp.h"
#include "QR_Code.h"
#include "Mechanical_arm.h"
/* Private function prototypes -----------------------------------------------*/
#define old  0
#define _new 1
#if _new
typedef enum {
  Start = 1,
  Get__,
  MoveUp,
	MoveDown,
	Put,
	Back
}status;

#endif
#if old

typedef enum {
  Start = 1,
  Through,
  Get_QR,
	GetMaterial,
	PutMaterial,
	Back
}status;

#endif
extern pid_t pid_distance;
extern pid_t pid_distance_catuch;
//extern enum status STATUS;
#if old
void _Start(void);
void _Through(void);
void _GetQR(void);
void _GetMaterial(void);
void _PutMaterial(void);
void _Back(void);
#endif

#if _new
void Start_(void);
void Get_(uint8_t goal);
void Move_Up(void);
void Move_Down(void);
void Put_(uint8_t goal);
void Back_home(void);
#endif
	


void set_speed(float vx,float vy,enum car_state state);

void Decision_Task(void const * argument);




#endif
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
