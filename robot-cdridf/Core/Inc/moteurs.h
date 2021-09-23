#ifndef MOTEUR_H
#define MOTEUR_H

#include "DRV8825.h"
#include "gpio.h"
#include "tim.h"


Moteur moteur_G;
Moteur moteur_D;

void initMoteurs();
void runForward(float  speed);
void runBackward(float speed);
void stopMoteurs();
void startMoteurs();
void rotateG(float speed_L, float speed_R);
void rotateD(float speed_L, float speed_R);
void setMotors(double left, double right);

#endif /* INC_MOTEUR_H_ */
