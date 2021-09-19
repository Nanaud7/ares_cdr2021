#ifndef MOTEUR_H
#define MOTEUR_H

#include "DRV8825.h"
#include "gpio.h"
#include "tim.h"

Moteur moteur_G;
Moteur moteur_D;

// Prototypes
uint8_t Motor_Init();
uint8_t Motor_Enable();
uint8_t Motor_Disable();
uint8_t Motor_setSpeedLeft(float RPM);
uint8_t Motor_setSpeedRight(float RPM);
uint8_t Motor_setSpeed(float speed);
uint8_t Motor_robotForward();
uint8_t Motor_robotBackward();
uint8_t Motor_robotRotLeft();
uint8_t Motor_robotRotRight();

#endif /* INC_MOTEUR_H_ */
