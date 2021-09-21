#include <HC-SR04.h>

uint8_t initUltrasons(void){
	cpt_trigger = 0;
	cpt_shared = 0;
	us_done_total = 0;

	for(int i=0; i<NB_OF_US_SENSORS; i++){
		time_rising[i] = 0;
		us_distance[i] = 999;
		us_done[i] = 0;
	}

	return 0;
}

uint8_t checkUltrasons(void){
	if((us_distance[US_FRONT_LEFT] <= 10) || (us_distance[US_FRONT_RIGHT] <= 10)){
		StopFront = 1;
		cpt_front = 0;
	}

	if((us_distance[US_BACK_LEFT] <= 10) || (us_distance[US_BACK_RIGHT] <= 10)){
		StopBack = 1;
		cpt_back = 0;
	}

	return 0;
}

uint8_t debugUltrasons(void){
#if DEBUG_ULTRASONS
	printf("dist us %lf %lf %lf %lf\r\n", us_distance[0], us_distance[1], us_distance[2], us_distance[3]);
	//HAL_Delay(100);
#endif
	return 0;
}
