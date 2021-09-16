#include "ihm.h"

int decodeMsgIHM(char *trame){

	char header = trame[0];

	switch(header){
		case 'J' :
			port_depart = JAUNE;
			initStrategie();
			#if MODULE_DEBUG == 1
				printf("Changement de depart : Jaune\r\n");
			#endif
			break;

		case 'B' :
			port_depart = BLEU;
			initStrategie();
			#if MODULE_DEBUG == 1
				printf("Changement de depart : Bleu\r\n");
			#endif
			break;

		case 'M' :
			initStrategie();
			//HAL_TIM_Base_Start_IT(&htim2);
			match_started = TRUE;
			#if MODULE_DEBUG == 1
				printf("Go!\r\n");
			#endif
			break;

		default :
			break;
	}

	return 0;
}

int sendMsgIHM(int idMsg){

	uint8_t data[8];

	switch(idMsg){
		case 0 :
			data[0] = 'I';
			data[1] = '\n';

			#if MODULE_DEBUG == 1
				//printf("%s\r\n",data);
			#endif

			HAL_UART_Transmit(&huart4, (uint8_t*)data, sizeof(data), 0xFFFF);
			//HAL_UART_Transmit_IT(&huart4, (uint8_t*)data, sizeof(data));
			break;

		default :
			break;
	}

	return 0;
}
