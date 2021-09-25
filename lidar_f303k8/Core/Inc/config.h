/*
 * global.h
 *
 *  Created on: 8 avr. 2021
 *      Author: arnau
 */

#ifndef INC_CONFIG_H_
#define INC_CONFIG_H_

#include <stdio.h>
#include "retarget.h"
#include "lib_vl53l0x.h"
#include "servoAX12.h"

/* Broches :
 *
 * I2C_SDA :
 * I2C_SCL :
 *
 * Capteur n°1
 * 	XSHUT1 :
 * 	GPIO1 :
 *
 * Capteur n°2
 * 	XSHUT2 :
 * 	GPIO2 :
 *
 * AX-12 :
 *
 */


// VL53L0X
#define NB_OF_SENSORS 2
#define IT_MODE 0
extern VL53L0X_Struct vl53l0x[NB_OF_SENSORS];
uint16_t results[2];

// AX-12
#define AX12_ENABLE 1

#define LIDAR_STEP 10
#define LIDAR_FOV 100
#define LIDAR_POS_MID 60
#define LIDAR_POS_MIN LIDAR_POS_MID-(LIDAR_FOV/2)
#define LIDAR_POS_MAX LIDAR_POS_MID+(LIDAR_FOV/2)

#define LIDAR_STEP_WAIT 60 //

#endif /* INC_CONFIG_H_ */
