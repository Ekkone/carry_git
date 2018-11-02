/*************************************************************************************
*	@file			run_task.h
* @author	 	Ekko
*	@version 	V1.0
*	@date			2018/9/22
* @brief		NONE
*************************************************************************************/
#ifndef __LOCATIONTASK_H
#define __LOCATIONTASK_H

/* Includes ------------------------------------------------------------------*/
#include "cmsis_os.h"
#include "string.h"
#include "bsp.h"
/* Private function prototypes -----------------------------------------------*/

//定位状态
#define Location_Busy 0     //定位任务繁忙(当前qti正在黑线正上方，处于不能被中断的状态)
#define Location_Ok		1

//qit操作和状态
#define QTI1 			HAL_GPIO_ReadPin(QTI1_GPIO_Port,QTI1_Pin)
#define QTI2 			HAL_GPIO_ReadPin(QTI2_GPIO_Port,QTI2_Pin) 
#define Black     GPIO_PIN_SET
#define	White			GPIO_PIN_RESET										 //临时

 //与标准状态变化比较，返回0表示相等
#define CMP_X(x)		memcmp(std_x,x,3)								
#define CMP_Y(y)		memcmp(std_y,y,5)

<<<<<<< HEAD



=======
extern float x_now;
extern float y_now;
extern float Qti1_flag[5];
extern float Qti2_flag[5];
>>>>>>> upstream/location&run

//所有函数不供外调用
void Location_Task(void const * argument);





#endif
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
