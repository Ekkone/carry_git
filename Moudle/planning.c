/*************************************************************************************
*	@file			planning.c
* @author	 	
*	@version 	V1.0
*	@date			
* @brief		
*************************************************************************************/
/* Includes ------------------------------------------------------------------------*/
#include "planning.h"

/* External variables --------------------------------------------------------*/
uint8_t  color[3] = {0};       //从左到右扫描到的物块颜色顺序
extern uint8_t way_color[3];
uint8_t  goal_x[7] = {0};
uint8_t  goal_y[7] = {0};      //生成的七个目标点的坐标顺序

/* Internal variables --------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

void way_planning(void)
{
  	static posi posi[4];
    static way  way[3];
    /*将三个位置的坐标点与颜色匹配*/
    posi[color[0]].x = POS1_X;
    
  
    posi[color[1]].x = POS2_X;
  
    posi[color[2]].x = POS3_X;
    /*按照二维码顺序生成颜色坐标对应路径*/
    for(int i = 1;i < 4;i++)
    {
      switch(way_color[i])
      {
        case RED:
        {
          way[i].x1 = posi[RED].x;
          way[i].x2 = RED_X;
        }break;
        case GREEN:
        {
          way[i].x1 = posi[GREEN].x;
          way[i].x2 = GREEN_X;
        }break;
        case BLUE:
        {
          way[i].x1 = posi[BLUE].x;
          way[i].x2 = BLUE_X;
        }break;
      }
    }
    /*将生成的坐标赋值给全局变量*/
      goal_x[0] = way[0].x1;
      goal_x[1] = way[0].x2;
      goal_x[2] = way[1].x1;
      goal_x[3] = way[1].x2;
      goal_x[4] = way[2].x1;
      goal_x[5] = way[2].x2;

}










/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
