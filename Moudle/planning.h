/*************************************************************************************
*	@file			planning.h
* @author	 	
*	@version 	V1.0
*	@date			
* @brief		
*************************************************************************************/
/* Includes ------------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
/* External variables --------------------------------------------------------*/
#define RED        1
#define GREEN      2
#define BLUE       3

#define POS1_X     3.5f
#define POS1_Y     1

#define POS2_X     4
#define POS2_Y     1

#define POS3_X     4.5f
#define POS3_Y     1

#define RED_X      3
#define RED_Y      2.5f

#define GREEN_X    4
#define GREEN_Y    2.5f

#define BLUE_X     5
#define BLUE_Y     2.5f

#define BEGIN_X    5
#define BEGIN_Y    5
/* Internal variables --------------------------------------------------------*/
typedef struct
{
	float          x1;
	float          y1;
	float          x2;
	float          y2;
	uint8_t     color;
}way;

typedef struct
{
	float          x;
	float          y;
}posi;
/* Private function prototypes -----------------------------------------------*/

void way_planning(void);













/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
