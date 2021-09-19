#include <moteurs.h>

uint8_t Motor_Init(void){
	DRV8825_init(&moteur_D, EN_D_Pin, EN_D_GPIO_Port, Dir_D_Pin, Dir_D_GPIO_Port, &STEP_D, TIM_CHANNEL_4);
	DRV8825_init(&moteur_G, EN_G_Pin, EN_G_GPIO_Port, Dir_G_Pin, Dir_G_GPIO_Port, &STEP_G, TIM_CHANNEL_1);

	//Motor_Disable();
	Motor_Enable();
	return 0;
}

uint8_t Motor_Enable(){
	DRV8825_setStart(&moteur_D, START);
	DRV8825_setStart(&moteur_G, START);
	return 0;
}

uint8_t Motor_Disable(){
	DRV8825_setStart(&moteur_D, STOP);
	DRV8825_setStart(&moteur_G, STOP);
	return 0;
}

uint8_t Motor_setSpeedLeft(float RPM){
    if (RPM > MOV_RPM_MAX){
        RPM = MOV_RPM_MAX;
    }
    else if(RPM < 0){
        RPM = 0;
    }

    DRV8825_moveMotorRPM(&moteur_G, RPM);
    return 0;
}

uint8_t Motor_setSpeedRight(float RPM){
    if (RPM > MOV_RPM_MAX){
        RPM = MOV_RPM_MAX;
    }
    else if(RPM < 0){
        RPM = 0;
    }

    DRV8825_moveMotorRPM(&moteur_D, RPM);
    return 0;
}

uint8_t Motor_setSpeed(float RPM){
    Motor_setSpeedLeft(RPM);
    Motor_setSpeedRight(RPM);

    return 0;
}

uint8_t Motor_robotForward(){
    DRV8825_setDir(&moteur_G, FORWARD);
    DRV8825_setDir(&moteur_D, FORWARD);
    return 0;
}

uint8_t Motor_robotBackward(){
    DRV8825_setDir(&moteur_G, BACKWARD);
    DRV8825_setDir(&moteur_D, BACKWARD);
    return 0;
}

uint8_t Motor_robotRotLeft(){
    DRV8825_setDir(&moteur_G, FORWARD);
    DRV8825_setDir(&moteur_D, BACKWARD);
    return 0;
}

uint8_t Motor_robotRotRight(){
    DRV8825_setDir(&moteur_G, BACKWARD);
    DRV8825_setDir(&moteur_D, FORWARD);
    return 0;
}
