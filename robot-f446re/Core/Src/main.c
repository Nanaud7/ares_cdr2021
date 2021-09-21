/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
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
#include "adc.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include <string.h>
#include "retarget.h" 			// Ajout de la fonction printf()

#include "actionneurs.h"
#include "asserv.h"
#include "config.h" 			// Fichier de configuration
#include "ihm.h"
#include "lidar.h"
#include "moteurs.h"
#include "strategie.h"
#include "HC-SR04.h"
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
int cptTempsMatch = 0;	// Compteur temps match
float g_ADCValue = 0;	// Tension mesurée tirette
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
int initTimers();
int initSerials();
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
  MX_TIM1_Init();
  MX_TIM8_Init();
  MX_TIM11_Init();
  MX_UART4_Init();
  MX_UART5_Init();
  MX_USART3_UART_Init();
  MX_TIM3_Init();
  MX_TIM7_Init();
  MX_USART1_UART_Init();
  MX_TIM2_Init();
  MX_ADC1_Init();
  MX_TIM6_Init();
  MX_TIM4_Init();
  /* USER CODE BEGIN 2 */
  initSerials();

  port_depart = BLEU;
  initStrategie();

  Motor_Init();
  initPinces();
  initBras();
  initFlag();
  initUltrasons();

  indexStrategie = 1; // Variable parcourant le tableau de stratégie
  initTimers();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

  // Tirette
  float voltage = 0;
  do{
	#if MODULE_TIRETTE
	  HAL_ADC_Start(&hadc1);
	  if (HAL_ADC_PollForConversion(&hadc1, 1000000) == HAL_OK)
	  {
		  g_ADCValue = HAL_ADC_GetValue(&hadc1);
		  voltage = g_ADCValue * (3.3 / 4096.0);
		  #if MODULE_DEBUG && DEBUG_TIRETTE
		  	  printf("%f\r\n",voltage);
		  #endif
	  }

	  if((voltage < (float)TIRETTE_SEUIL) == TRUE && match_started == FALSE){
		  match_started = TRUE;
		  initStrategie();
	  }
	#else
	match_started = TRUE;

	#endif
  } while(match_started == FALSE);
  // Fin tirette

  #if MODULE_LIDAR
  	  HAL_UART_Receive_IT(&huart5, (uint8_t*)&buff_lidar, 1);
  #endif

  cptTempsMatch = 0;

  while (1)
  {
	  #if MODULE_DEBUG
	  	  debugUltrasons();
	  	  HAL_Delay(100);
	  #endif
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

int initTimers(){

	#if MODULE_ODOMETRIE
		HAL_TIM_Encoder_Start(&CODEUR_D, TIM_CHANNEL_ALL); // htim1
		HAL_TIM_Encoder_Start(&CODEUR_G, TIM_CHANNEL_ALL); // htim3
	#endif

	#if MODULE_ASSERVISSEMENT
		HAL_TIM_Base_Start_IT(&htim2); 	// Period : 15ms
	#endif

	#if MODULE_ULTRASONS
		HAL_TIM_Base_Start_IT(&htim4); 	// Period : 1us
	#endif

	#if MODULE_LIDAR
		HAL_TIM_Base_Start_IT(&htim6); 	// Period : 10ms
	#endif

	#if MODULE_COMPTEUR
		HAL_TIM_Base_Start_IT(&htim7); 	// Period : 1sec
	#endif

	return 0;
}

int initSerials(){
	#if MODULE_DEBUG == 1
		RetargetInit(&huart2);
		printf("Mode debug actif\r\n");
	#endif

	/*
	#if MODULE_LIDAR
		// uart5 n'est plus initialisé ici
		HAL_UART_Receive_IT(&huart5, (uint8_t*)&buff_lidar, 1);
	#endif
	*/

	#if MODULE_IHM
		HAL_UART_Receive_IT(&huart4, (uint8_t*)&buff_ihm, 1);
	#endif

	return 0;
}

int initStrategie(){
	if(port_depart == BLEU){
		ODO_setAngle(START_BLEU_ANGLE);
		ODO_setX(consigneBleu[0].x);
		ODO_setY(consigneBleu[0].y);
		consigne = consigneBleu;
	}
	else if(port_depart == JAUNE){
		ODO_setAngle(START_JAUNE_ANGLE);
		ODO_setX(consigneJaune[0].x);
		ODO_setY(consigneJaune[0].y);
		consigne = consigneJaune;
	}

	return 0;
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){

	if(htim->Instance == TIM2){
		if(indexStrategie < nb_points && match_started == 1)
			ASSERV_update(consigne[indexStrategie]);
		//printf("TIM2\r\n");
	}

	if(htim->Instance == TIM4){
		cpt_us_global++;

		if(cpt_us_global >= 0 && cpt_us_global < 10){ // && stepUS == STEP_RESET
//			HAL_GPIO_WritePin(Sensors[indexUS].Trigger_GPIO_Port,
//					Sensors[indexUS].Trigger_GPIO_Port, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_SET);
		}
		else {
//			HAL_GPIO_WritePin(Sensors[indexUS].Trigger_GPIO_Port,
//					Sensors[indexUS].Trigger_GPIO_Port, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_RESET);

			if(stepUS == STEP_RESET) stepUS = STEP_TRIG;
		}

		if(cpt_us_global >= 10000){
			cpt_us_global = 0;
			distUS[indexUS]=999;
			indexUS++;
			if(indexUS >= NB_OF_US_SENSORS) indexUS = 0;
		}
	}


	if(htim->Instance == TIM6){
		//printf("TIM6\r\n");
		cpt_back++;
		cpt_front++;
		//printf("cpt_front = %d\r\n",cpt_front);

		if (cpt_back > 250){
			StopBack = 0;
		}

		if (cpt_front > 250){
			StopFront = 0;
		}
	}

	if(htim->Instance == TIM7){
		if(match_started == TRUE){
			cptTempsMatch++;

			if (cptTempsMatch >= TEMPS_PAVILLONS){
				raiseFlag();
			}

			if (cptTempsMatch >= 98){
				Motor_Disable();
				initBras();
				initPinces();
				match_started = 0;
			}
		}
	}
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef* huart){
	if(huart->Instance == UART5){
		strcat(lidarRawData,&buff_lidar);
		if(buff_lidar == '\n'){
			//getLidarData();
			getLidarData2();
			memset(lidarRawData,0,sizeof(lidarRawData));
		}
		HAL_UART_Receive_IT(&huart5, (uint8_t*)&buff_lidar, 1);
	}

	if(huart->Instance == UART4){
		if(match_started == FALSE){
			strcat(ihmRawData,&buff_ihm);
			if(buff_ihm == '\n'){
				decodeMsgIHM(ihmRawData);
				memset(ihmRawData,0,sizeof(ihmRawData));
			}
			HAL_UART_Receive_IT(&huart4, (uint8_t*)&buff_ihm, 1);
		}
	}
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{

  if(GPIO_Pin == GPIO_PIN_1 && indexUS == US_FRONT_LEFT)
  {
	  processUltrasons(Sensors[US_FRONT_LEFT]);
  }

  if(GPIO_Pin == GPIO_PIN_15 && indexUS == US_FRONT_RIGHT)
  {
	  processUltrasons(Sensors[US_FRONT_RIGHT]);
  }

  if(GPIO_Pin == GPIO_PIN_14 && indexUS == US_BACK_LEFT)
  {
	  processUltrasons(Sensors[US_BACK_LEFT]);
  }

  if(GPIO_Pin == GPIO_PIN_13 && indexUS == US_BACK_RIGHT)
  {
	  processUltrasons(Sensors[US_BACK_RIGHT]);
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
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
