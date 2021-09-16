/*
 * global.h
 *
 *  Created on: 8 avr. 2021
 *      Author: arnau
 */

#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_

#include <stdio.h>
#include "retarget.h"
#include "lib_vl53l0x.h"
#include "servoAX12.h"

/* Broches :
 *
 * USART2
 * I2C_SDA : PB9
 * I2C_SCL : PB8
 *
 * Capteur n°1
 * 	XSHUT1 : PC0
 * 	GPIO1 : PC1
 *
 * Capteur n°2
 * 	XSHUT2 : PB0
 * 	GPIO2 : PA4
 *
 * AX-12 :
 * 	USART3
 *
 */


// VL53L0X
#define NB_OF_SENSORS 2
#define IT_MODE 0
extern VL53L0X_Struct vl53l0x[NB_OF_SENSORS];
extern float results[NB_OF_SENSORS];

// AX-12
#define AX12_ENABLE 1

#define AX12_POS_MIN 0
#define AX12_POS_MAX 120
#define AX12_POS_JUMP 5
#define AX12_POS_MID 60
#define AX12_TIME_JUMP 100 // 0.25

#endif /* INC_GLOBAL_H_ */
