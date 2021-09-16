#include "actionneurs.h"

void actionneursUpdate(CONSIGNE strategie){

	// Bras
	if(strategie.bras == FALSE){
		raiseBras(&bras);
	}
	else if (strategie.bras == TRUE){
		deployBras(&bras);
	}

	// Pinces
	for(int i=0; i<NB_AX12_BRAS; i++){
		if(strategie.pinces[i] == FALSE){
			releasObject(&pinces[i]);
		}
		else if (strategie.pinces[i] == TRUE){
			catchObject(&pinces[i]);
		}
	}

}

/* Pinces */

uint8_t id_pinces[4] = {3,7,1,2}; // 1,2,3,7
void initPinces(){
	for(int i = 0; i < NB_AX12_BRAS ; i++){
		AX12_Init(&pinces[i],&huart3,id_pinces[i],BR_250K);
		AX12_setMaxTorque(&pinces[i],100);
		AX12_setRangeAngle(&pinces[i], ANGLE_PINCE_CATCH,ANGLE_STARTUP);
		AX12_setMovingSpeed(&pinces[i], 80);
		AX12_TorqueE_D(&pinces[i],TRUE);
		HAL_Delay(250);
		AX12_setPosition(&pinces[i], ANGLE_STARTUP);
	}
	HAL_Delay(250);
}

void catchObject(AX12 *ax12){
	AX12_setPosition(ax12, ANGLE_PINCE_CATCH);
}
void releasObject(AX12* ax12){
	AX12_setPosition(ax12, ANGLE_PINCE_RELEASE);
}

/* Pavillons */

void initFlag(){
	AX12_Init(&flag,&huart3,9,BR_250K); // 9
	AX12_setMaxTorque(&flag,100);
	AX12_setRangeAngle(&flag, ANGLE_FLAG_DEPLOY,ANGLE_FLAG_REPOS);
	AX12_setMovingSpeed(&flag, 80);
	AX12_TorqueE_D(&flag,TRUE);
	HAL_Delay(250);
	AX12_setPosition(&flag, ANGLE_FLAG_REPOS);
	HAL_Delay(250);
}

void raiseFlag(){
	AX12_setPosition(&flag, ANGLE_FLAG_DEPLOY);
}

void lowerFlag(){
	AX12_setPosition(&flag, ANGLE_FLAG_DEPLOY);
}

/* Bras */

void initBras(){
	AX12_Init(&bras,&huart3,4,BR_250K);
	AX12_setMaxTorque(&bras,100);
	AX12_setRangeAngle(&bras, 0,ANGLE_STARTUP);
	AX12_setMovingSpeed(&bras, 80);
	AX12_TorqueE_D(&bras,TRUE);
	HAL_Delay(250);
	AX12_setPosition(&bras, ANGLE_STARTUP);
	HAL_Delay(250);
}

void raiseBras(){
	AX12_setPosition(&bras, ANGLE_BRAS_RAISE);
}

void deployBras(){
	AX12_setPosition(&bras, ANGLE_BRAS_DEPLOY);
}

