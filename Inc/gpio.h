/**
  ******************************************************************************
  * File Name          : gpio.h
  * Description        : This file contains all the functions prototypes for 
  *                      the gpio  
  ******************************************************************************
  * This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * Copyright (c) 2018 STMicroelectronics International N.V. 
  * All rights reserved.
  *
  * Redistribution and use in source and binary forms, with or without 
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice, 
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other 
  *    contributors to this software may be used to endorse or promote products 
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this 
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under 
  *    this license is void and will automatically terminate your rights under 
  *    this license. 
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS" 
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT 
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT 
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __gpio_H
#define __gpio_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "main.h"

/* USER CODE BEGIN Includes */
#define QTI1_Pin 				GPIO_PIN_1
#define QTI1_GPIO_Port  GPIOA
#define QTI1_EXTI_IRQn  EXTI1_IRQn
	 
#define QTI2_Pin			  GPIO_PIN_2
#define QTI2_GPIO_Port  GPIOA
#define QTI2_EXTI_IRQn  EXTI2_IRQn
	 
#define LED1_Pin 				GPIO_PIN_13
#define	LED1_GPIO_Port	GPIOB
	 
#define LED2_Pin 				GPIO_PIN_15
#define	LED2_GPIO_Port	GPIOE
	 
#define LED3_Pin 				GPIO_PIN_12
#define	LED3_GPIO_Port	GPIOE

#define LED4_Pin 				GPIO_PIN_12
#define	LED4_GPIO_Port	GPIOF

#define LED5_Pin 				GPIO_PIN_11
#define	LED5_GPIO_Port	GPIOF

#define LED6_Pin 				GPIO_PIN_2
#define	LED6_GPIO_Port	GPIOB

#define LED7_Pin 				GPIO_PIN_1
#define	LED7_GPIO_Port	GPIOB

#define LED8_Pin 				GPIO_PIN_0
#define	LED8_GPIO_Port	GPIOB

#define KEY1   				HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_0)
#define KEY2   				HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_1)
#define KEY3   				HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_2)
#define KEY4   				HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_4)
#define KEY5   				HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_4)
/* USER CODE END Includes */

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

void MX_GPIO_Init(void);

/* USER CODE BEGIN Prototypes */
void LED_Init(void);
void EXIT_Iint(void);
void KEY_Init(void);
/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif /*__ pinoutConfig_H */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
