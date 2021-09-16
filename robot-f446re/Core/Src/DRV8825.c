#include "DRV8825.h"

void DRV8825_init(Moteur *drv8825,uint16_t PIN_EN, GPIO_TypeDef * GPIO_EN, uint16_t PIN_DIR, GPIO_TypeDef * GPIO_DIR,TIM_HandleTypeDef* timer, uint8_t chanel){

	/*****************************************
	 * nous récupérons les numéros des pins  *
	 * et les intégrons dans notre structure *
	 * DRV8825                               *
	 *****************************************/
	drv8825->pin_EN = PIN_EN;
	drv8825->pin_DIR = PIN_DIR;

	/*****************************************
	 * nous récupérons les GPIO des pins     *
	 * et les intégrons dans notre structure *
	 * DRV8825                               *
	 *****************************************/
	drv8825->gpio_EN= GPIO_EN;
	drv8825->gpio_DIR= GPIO_DIR;

	/**********************************************
	 * nous initialisatons le timer et récupérons *
	 * à quelle chanel il est racroché 			  *
	 **********************************************/
	drv8825->timer = timer;
	drv8825->chanel = chanel;

}

void DRV8825_setDir(Moteur* drv8825,uint8_t dir){

	HAL_GPIO_WritePin(drv8825->gpio_DIR,drv8825->pin_DIR,dir);
}

void DRV8825_setStart(Moteur* drv8825,uint8_t enable){
	HAL_GPIO_WritePin(drv8825->gpio_EN,drv8825->pin_EN,enable);
}

void DRV8825_moveMotorRPM(Moteur* drv8825,float rpm){
	rpm = rpm/M_TO_S;
	uint16_t f = PAS*rpm;
	DRV8825_setFrequency(drv8825, f);
}

void DRV8825_moveMotorLineSpeed(Moteur* drv8825,float vitesse){
	vitesse= vitesse*1000;
	uint16_t f = (PAS*vitesse)/(2*M_PI*RAYON);
	DRV8825_setFrequency(drv8825, f);
}

void DRV8825_setFrequency(Moteur* drv8825, uint16_t freq){
	/************************************************
	 * nous modifions ARR pour modifier la période  *
	 * pour cela nous utilisons la formule suivante *
	 *                                              *
	 * freq = (clock)/{(PSC+1)(ARR+1)})             *
	 *												*
	 * clock = 180Mhz   PSC = 179                   *
	 * ARR = la valeur que l'on souhaite appliquer  *
	 ************************************************/
	if(freq != 0){
	drv8825->timer->Init.Prescaler = 179;
	drv8825->timer->Init.Period = (uint32_t)1000000/freq;
	}
	else{
		drv8825->timer->Init.Prescaler = 0xFFFE;
		drv8825->timer->Init.Period = 0xFFFE;
	}
	/************************************************
	 * si l'initialisation du timerc'est bien passé *
	 ************************************************/
	if (HAL_TIM_Base_Init(drv8825->timer) != HAL_OK)
	{
		//nous affichons l'erreur qui c'est produit
		Error_Handler();
	}

	/******************************************************
	 * si l'initialisation du signal PWM c'est bien passé *
	 ******************************************************/
	if (HAL_TIM_PWM_Init(drv8825->timer) != HAL_OK)
	{
		//nous affichons l'erreur qui c'est produit
		Error_Handler();
	}

	/**********************************
	 * nous déclanchons le signal PWM *
	 **********************************/
	HAL_TIM_PWM_Start(drv8825->timer, drv8825->chanel);

	/****************************************
	 * nous configurons le rapport cyclique *
	 * pour qu'il soit à 50%                *
	 ****************************************/
	switch(drv8825->chanel){
	case(TIM_CHANNEL_1):drv8825->timer->Instance->CCR1 = (50*drv8825->timer->Init.Period)/100;break;
	case(TIM_CHANNEL_2):drv8825->timer->Instance->CCR2 = (50*drv8825->timer->Init.Period)/100;break;
	case(TIM_CHANNEL_3):drv8825->timer->Instance->CCR3 = (50*drv8825->timer->Init.Period)/100;break;
	case(TIM_CHANNEL_4):drv8825->timer->Instance->CCR4 = (50*drv8825->timer->Init.Period)/100;break;
	}
}
