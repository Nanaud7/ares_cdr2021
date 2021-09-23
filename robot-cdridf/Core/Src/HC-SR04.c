#include <HC-SR04.h>

SensorUS Sensors[NB_OF_US_SENSORS] = {
		{
				.sensorID = US_FRONT_LEFT,
				//.Trigger_GPIO_Port = GPIOB, .Trigger_GPIO_Pin = GPIO_PIN_2,
				.Echo_GPIO_Port = GPIOB, .Echo_GPIO_Pin = GPIO_PIN_1
		},{
				.sensorID = US_FRONT_RIGHT,
				//.Trigger_GPIO_Port = GPIOA, .Trigger_GPIO_Pin = GPIO_PIN_11,
				.Echo_GPIO_Port = GPIOB, .Echo_GPIO_Pin = GPIO_PIN_15
		},{
				.sensorID = US_BACK_LEFT,
				//.Trigger_GPIO_Port = GPIOB, .Trigger_GPIO_Pin = GPIO_PIN_2,
				.Echo_GPIO_Port = GPIOB, .Echo_GPIO_Pin = GPIO_PIN_14
		},{
				.sensorID = US_BACK_RIGHT,
				//.Trigger_GPIO_Port = GPIOB, .Trigger_GPIO_Pin = GPIO_PIN_12,
				.Echo_GPIO_Port = GPIOB, .Echo_GPIO_Pin = GPIO_PIN_13
		}
};

uint8_t initUltrasons(void){
	save_cpt_rising = 0;
	cpt_us_global = 0;
	indexUS = 0;
	stepUS = STEP_RESET;

	for(int i=0; i<NB_OF_US_SENSORS; i++){
		distUS[i] = 999;
	}

	return 0;
}

uint8_t processUltrasons(SensorUS Sensor){
	if(HAL_GPIO_ReadPin(Sensor.Echo_GPIO_Port, Sensor.Echo_GPIO_Pin)
			&& stepUS == STEP_TRIG){

			save_cpt_rising = cpt_us_global;
			stepUS = STEP_RISE;
	}
	else if (!HAL_GPIO_ReadPin(Sensor.Echo_GPIO_Port, Sensor.Echo_GPIO_Pin)
			&& stepUS == STEP_RISE){

	    	distUS[Sensor.sensorID] = ((float)(cpt_us_global - save_cpt_rising) * 0.034) / 2.0;

	    	if(distUS[Sensor.sensorID] <= 0) distUS[Sensor.sensorID] = 999;

	    	indexUS++;
	    	if(indexUS >= NB_OF_US_SENSORS) indexUS = 0;
	    	stepUS = STEP_RESET;
	    	cpt_us_global = 0;
	    	save_cpt_rising = 0;
	    	checkUltrasons();
	    }

	return 0;
}

uint8_t checkUltrasons(void){
	if((distUS[US_FRONT_LEFT] <= 5) || (distUS[US_FRONT_RIGHT] <= 10)){
		StopFront = 1;
		cpt_front = 0;
	}

	if((distUS[US_BACK_LEFT] <= 10) || (distUS[US_BACK_RIGHT] <= 10)){
		StopBack = 1;
		cpt_back = 0;
	}

	return 0;
}

uint8_t debugUltrasons(void){
#if DEBUG_ULTRASONS
	//printf("dist us %.3f\t%.3f\t%.3f\t%.3f\r\n", distUS[0], distUS[1], distUS[2], distUS[3]);
	printf("dist us %d\t%d\r\n", StopFront, StopBack);
	//HAL_Delay(100);
#endif
	return 0;
}
