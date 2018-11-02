/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
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

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"

/* USER CODE BEGIN Includes */     

/* USER CODE END Includes */

/* Variables -----------------------------------------------------------------*/
osThreadId defaultTaskHandle;

/* USER CODE BEGIN Variables */
osThreadId correct_taskHandle;
osThreadId decision_taskHandle;
osThreadId location_taskHandle;
osThreadId test_taskHandle;
osThreadId display_taskHandle;
osThreadId run_taskHandle;

/* USER CODE END Variables */

/* Function prototypes -------------------------------------------------------*/
void StartDefaultTask(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* USER CODE BEGIN FunctionPrototypes */
extern void Correct_Task(void const * argument);
extern void Decision_Task(void const * argument);
extern void Location_Task(void const * argument);
extern void Test_Task(void const * argument);
extern void Display_Task(void const * argument);
extern void Run_Task(void const * argument);

/* USER CODE END FunctionPrototypes */

/* Hook prototypes */

/* Init FreeRTOS */

void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */
       
  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the thread(s) */
  /* definition and creation of defaultTask */
  osThreadDef(defaultTask, StartDefaultTask, osPriorityBelowNormal, 0, 128);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  osThreadDef(run_task, Run_Task, osPriorityHigh, 0, 128);
  run_taskHandle = osThreadCreate(osThread(run_task), NULL);
	
  osThreadDef(correct_task, Correct_Task, osPriorityNormal, 0, 128);
  correct_taskHandle = osThreadCreate(osThread(correct_task), NULL);
  
  osThreadDef(decision_task, Decision_Task, osPriorityHigh, 0, 128);
  decision_taskHandle = osThreadCreate(osThread(decision_task), NULL);
  
  osThreadDef(location_task, Location_Task, osPriorityAboveNormal, 0, 128);
  location_taskHandle = osThreadCreate(osThread(location_task), NULL);
  
  osThreadDef(test_task, Test_Task, osPriorityBelowNormal, 0, 128);
  test_taskHandle = osThreadCreate(osThread(test_task), NULL);

  osThreadDef(display_task, Display_Task, osPriorityNormal, 0, 512);
  display_taskHandle = osThreadCreate(osThread(display_task), NULL);
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */
}

/* StartDefaultTask function */
void StartDefaultTask(void const * argument)
{

  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
  for(;;)
  {
		
//		printf("\n\n");
//		printf("a629          169       13222222247    028         b561   132222222257     8225b            0229\n");
//		printf("a63347        169     a66a       025b  028         b561   1347      8247   82669           a6669\n");
//		printf("a697528       169    a65b              028         b561   1347       829   820020         139069\n");
//		printf("a69  829      169   b56a               028         b561   1347       020   820 96a       7447a69\n");
//		printf("a69   1331    169   1347               028         b561   1347     1320    820 b561     b531 a69\n");
//		printf("a69     928   169   1347               028         b561   1322662238b      820  7447    96a  a69\n");
//		printf("a69      825b 169   b56a               028         b561   1347   825       820   135b  828   a69\n");
//		printf("a69       7461139    a647         71   a25         1347   1347    1331     820    a69 a60    a69\n");
//		printf("a69         92369     166a       929    025b      a661    1347     b528    820     82435b    a69\n");
//		printf("a69          a629       1322222229b      b922222223a      1347       025   820      0247     a69\n");
//		printf("\n\n");
		
    osDelay(1);
  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Application */
     
/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
