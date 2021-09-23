#include <moteurs.h>

void initMoteurs(){
	//DRV8825_moveMotorLineSpeed(&moteur_D, 0);
	//DRV8825_moveMotorLineSpeed(&moteur_G, 0);

	DRV8825_init(&moteur_D, EN_D_Pin, EN_D_GPIO_Port, Dir_D_Pin, Dir_D_GPIO_Port, &STEP_D, TIM_CHANNEL_4);
	DRV8825_init(&moteur_G, EN_G_Pin, EN_G_GPIO_Port, Dir_G_Pin, Dir_G_GPIO_Port, &STEP_G, TIM_CHANNEL_1);

	DRV8825_setStart(&moteur_D, STOP);
	DRV8825_setStart(&moteur_G, STOP);

	//DRV8825_setStart(&moteur_D, START);
	//DRV8825_setStart(&moteur_G, START);

}

void runForward(float speed){
	DRV8825_setDir(&moteur_D, FORWARD);
	DRV8825_setDir(&moteur_G, FORWARD);

	DRV8825_moveMotorLineSpeed(&moteur_D, speed);
	DRV8825_moveMotorLineSpeed(&moteur_G, speed);
}

void runBackward(float speed){
	DRV8825_setDir(&moteur_D, BACKWARD);
	DRV8825_setDir(&moteur_G, BACKWARD);

	DRV8825_moveMotorLineSpeed(&moteur_D, speed);
	DRV8825_moveMotorLineSpeed(&moteur_G, speed);
}

void stopMoteurs(){
	DRV8825_setStart(&moteur_D, STOP);
	DRV8825_setStart(&moteur_G, STOP);
}

void startMoteurs(){
	DRV8825_setStart(&moteur_D, START);
	DRV8825_setStart(&moteur_G, START);
}

void rotateG(float speed_L, float speed_R){
	DRV8825_setDir(&moteur_D, BACKWARD);
	DRV8825_setDir(&moteur_G, FORWARD);

	DRV8825_moveMotorLineSpeed(&moteur_D, speed_R);
	DRV8825_moveMotorLineSpeed(&moteur_G, speed_L);
}

void rotateD(float speed_L, float speed_R){
	DRV8825_setDir(&moteur_D, FORWARD);
	DRV8825_setDir(&moteur_G, BACKWARD);

	DRV8825_moveMotorLineSpeed(&moteur_D, speed_R);
	DRV8825_moveMotorLineSpeed(&moteur_G, speed_L);
}

void setMotors(double left, double right) {
    // vitesses absolues
    DRV8825_moveMotorLineSpeed(&moteur_G, fabs(left));
    DRV8825_moveMotorLineSpeed(&moteur_D, fabs(right));

    // directions
    DRV8825_setDir(&moteur_G, (left < 0)?BACKWARD:FORWARD);
    DRV8825_setDir(&moteur_D, (right < 0)?BACKWARD:FORWARD);

    // activer ou non les moteurs
    if (left == 0 && right == 0)
        stopMoteurs();
    else
    	startMoteurs();
}
