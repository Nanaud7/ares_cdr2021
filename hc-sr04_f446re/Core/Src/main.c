/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include "retarget.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
uint32_t cpt_trigger = 0;
uint32_t cpt_us = 0;
uint8_t us_ended = 0;

uint32_t time_cpt_rising[4] = {0};
double us_dist[4] = {0};
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART2_UART_Init();
  MX_TIM4_Init();
  /* USER CODE BEGIN 2 */
  RetargetInit(&huart2);

  HAL_TIM_Base_Start_IT(&htim4); // 1us
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  printf("dist us1 : %lf cm\r\n", us_dist[0]);
	  printf("dist us2 : %lf cm\r\n", us_dist[1]);
	  printf("dist us3 : %lf cm\r\n", us_dist[2]);
	  printf("dist us4 : %lf cm\r\n", us_dist[3]);
	  printf("\r\n");

	  HAL_Delay(100);
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 360;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Activate the Over-Drive mode
  */
  if (HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	if(htim->Instance == TIM4){
		cpt_us++;
		cpt_trigger++;
		//printf("cpt_trigger = %d\r\n", cpt_trigger);

		if(cpt_trigger >= 0 && cpt_trigger < 10){
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_SET);
		}
		else if(cpt_trigger >= 20) {
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_RESET);
		}

		if(us_ended < 4 && cpt_us >= 1000){
			cpt_us = 0;
			cpt_trigger = 0;
		}
	}

}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  if(GPIO_Pin == GPIO_PIN_1)
  {
    if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_1)){
    	time_cpt_rising[0] = cpt_us;
    	//printf("time_cpt_rising : %ld\r\n", time_cpt_rising);
    } else{
    	us_dist[0] = ((float)(cpt_us - time_cpt_rising[0]) * 0.034) / 2.0;
    	//printf("time_diff : %ld\r\n", time_cpt_rising - cpt_us);

    	us_ended++;
    	if (us_ended >= 3){
        	cpt_us = 0;
        	cpt_trigger = 0;
    	}

    }
  }

  if(GPIO_Pin == GPIO_PIN_15)
  {
    if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_15)){
    	time_cpt_rising[1] = cpt_us;
    	//printf("time_cpt_rising : %ld\r\n", time_cpt_rising);
    } else{
    	us_dist[1] = ((float)(cpt_us - time_cpt_rising[1]) * 0.034) / 2.0;
    	//printf("time_diff : %ld\r\n", time_cpt_rising - cpt_us);

    	us_ended++;
    	if (us_ended >= 3){
        	cpt_us = 0;
        	cpt_trigger = 0;
    	}
    }
  }

  if(GPIO_Pin == GPIO_PIN_14)
  {
    if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_14)){
    	time_cpt_rising[2] = cpt_us;
    	//printf("time_cpt_rising : %ld\r\n", time_cpt_rising);
    } else{
    	us_dist[2] = ((float)(cpt_us - time_cpt_rising[2]) * 0.034) / 2.0;
    	//printf("time_diff : %ld\r\n", time_cpt_rising - cpt_us);

    	us_ended++;
    	if (us_ended >= 3){
        	cpt_us = 0;
        	cpt_trigger = 0;
    	}
    }
  }

  if(GPIO_Pin == GPIO_PIN_13)
  {
    if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_13)){
    	time_cpt_rising[3] = cpt_us;
    	//printf("time_cpt_rising : %ld\r\n", time_cpt_rising);
    } else{
    	us_dist[3] = ((float)(cpt_us - time_cpt_rising[2]) * 0.034) / 2.0;
    	//printf("time_diff : %ld\r\n", time_cpt_rising - cpt_us);

    	us_ended++;
    	if (us_ended >= 3){
        	cpt_us = 0;
        	cpt_trigger = 0;
    	}
    }
  }
}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
