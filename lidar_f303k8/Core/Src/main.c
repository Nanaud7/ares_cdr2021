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
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "config.h"
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
VL53L0X_Struct vl53l0x[NB_OF_SENSORS];
AX12 ax12;
uint8_t sens = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
int LIDAR_Main();
int LIDAR_Main2();
int LIDAR_SendDatas(float pos);
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
  MX_I2C1_Init();
  MX_USART1_UART_Init();
  MX_TIM3_Init();
  /* USER CODE BEGIN 2 */
  RetargetInit(&huart1);
  printf("lidar_f303k8\r\n");
  HAL_TIM_Base_Start_IT(&htim3);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

  ///// VL53L0X /////

  // Initialisation du capteur n°1
#if NB_OF_SENSORS == 1
	vl_xshut_init(&vl53l0x[0], GPIOB, GPIO_PIN_5); 			// XSHUT = PB5
	//vl_xshut_init(&vl53l0x[0], GPIOB, GPIO_PIN_4); 			// XSHUT = PB4
    vl_sensors_init(&vl53l0x[0], &hi2c1, NB_OF_SENSORS);
#endif
#if NB_OF_SENSORS == 2
    vl_xshut_init(&vl53l0x[0], GPIOB, GPIO_PIN_5); 			// XSHUT = PB5
    vl_xshut_init(&vl53l0x[1], GPIOB, GPIO_PIN_4); 			// XSHUT = PB4
    vl_sensors_init(vl53l0x, &hi2c1, NB_OF_SENSORS);
#endif

    results[0] = 999;
    results[1] = 999;

  ///// AX-12 /////
#if AX12_ENABLE
    AX12_Init(&ax12, &huart2, 1, BR_250K);
    AX12_TorqueE_D(&ax12, TRUE);
    AX12_setMaxTorque(&ax12,50);

    AX12_setRangeAngle(&ax12,LIDAR_POS_MIN,LIDAR_POS_MAX);
    AX12_setMovingSpeed(&ax12, 114);
    AX12_setPosition(&ax12, 0);
#endif

  while (1)
    {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

#if IT_MODE == 0
	  LIDAR_Main();

#elif IT_MODE == 1
	  //printf("1: %d\r\n", results[0]);
	  //printf("%d %d\r\n", results[0], results[1]);

	  printf("L\n");

	  if(results[0] < 350){
			  printf("B\n");
	  }

	  if(results[1] < 350){
			  printf("F\n");
	  }
  #endif

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
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART1|RCC_PERIPHCLK_I2C1;
  PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK1;
  PeriphClkInit.I2c1ClockSelection = RCC_I2C1CLKSOURCE_HSI;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){
	if(GPIO_Pin == GPIO_PIN_3){
		vl_clear_it_mask(&vl53l0x[1]);
		results[1] = vl_perform_ranging_it(&vl53l0x[1]);

		results[0] = vl_perform_ranging(&vl53l0x[0]);
		//printf("1: %d 2: %d\r\n", results[0], results[1]);
	}

	/*
	if(GPIO_Pin == GPIO_PIN_11){
		//vl_clear_it_mask(&vl53l0x[0]);
		//results[0] = vl_perform_ranging_it(&vl53l0x[0]);
	}
	*/
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	if(htim->Instance == TIM3){

		#if AX12_ENABLE
			if(sens == 0){
				AX12_setPosition(&ax12, LIDAR_POS_MIN);
				sens = 1;
			}
			else if(sens == 1){
				AX12_setPosition(&ax12, LIDAR_POS_MAX);
				sens = 0;
			}
			else sens = 0;
		#endif
	}
}

int LIDAR_Main(){
	for(float k = LIDAR_POS_MIN+LIDAR_STEP; k <= LIDAR_POS_MAX; k += LIDAR_STEP){
		for(int i=0; i<NB_OF_SENSORS; i++){
			//results[i] = (float)vl_perform_ranging(&vl53l0x[i]);
			results[i] = vl_perform_ranging(&vl53l0x[i]);
		}

		LIDAR_SendDatas(k);

		#if AX12_ENABLE
			AX12_setPosition(&ax12, k);
			HAL_Delay(LIDAR_STEP_WAIT);
		#endif
	}

	for(float k = LIDAR_POS_MAX-LIDAR_STEP; k >= LIDAR_POS_MIN; k -= LIDAR_STEP){

		for(int i=0; i<NB_OF_SENSORS; i++){
			//results[i] = (float)vl_perform_ranging(&vl53l0x[i]);
			results[i] = vl_perform_ranging(&vl53l0x[i]);
		}

		LIDAR_SendDatas(k);

		#if AX12_ENABLE
			AX12_setPosition(&ax12, k);
			HAL_Delay(LIDAR_STEP_WAIT);
		#endif

	}

	//AX12_setPosition(&ax12, LIDAR_POS_MIN);
	//HAL_Delay(500);

	return 0;
}

int LIDAR_Main2(){
	for(int j=0; j<1000; j++){
		for(int i=0; i<NB_OF_SENSORS; i++){
			//results[i] = (float)vl_perform_ranging(&vl53l0x[i]);
			results[i] = vl_perform_ranging(&vl53l0x[i]);
		}
	}

	AX12_setPosition(&ax12, LIDAR_POS_MIN);

	for(int j=0; j<1000; j++){
		for(int i=0; i<NB_OF_SENSORS; i++){
			//results[i] = (float)vl_perform_ranging(&vl53l0x[i]);
			results[i] = vl_perform_ranging(&vl53l0x[i]);
		}
	}

	AX12_setPosition(&ax12, LIDAR_POS_MAX);

	return 0;
}

int LIDAR_SendDatas(float pos){
	#if NB_OF_SENSORS == 1
			  printf("%f %f\r\n", pos, results[0]);
	#endif

	#if NB_OF_SENSORS == 2
			  //printf("%f %f %f\r\n", pos, results[0], results[1]);
			  //printf("%f %f %f\n", pos, results[0], results[1]);
			  //printf("%d %d %d\n", (int)pos, (int)results[0], (int)results[1]);

			  if(results[0] < 350){
					  printf("B\n");
			  }

			  if(results[1] < 350){
					  printf("F\n");
			  }
	#endif

	return 0;
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
