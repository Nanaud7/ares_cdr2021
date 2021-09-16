/*
 * lib_vl53l0x.h
 *
 *      Author: Arnaud CHOBERT
 */

#ifndef INC_LIB_VL53L0X_H_
#define INC_LIB_VL53L0X_H_


#include <stdio.h>
#include "retarget.h"
#include "vl53l0x_api.h"
#include "vl53l0x_platform.h"
#include "vl53l0x_device.h"

#define INTERRUPT_MODE 1
#define TOGGLE_GPIO_TIME 20

// RANGE_PROFILE
#define HIGH_ACCURACY 0
#define LONG_RANGE 1
#define HIGH_SPEED 2
#define RANGE_PROFILE_SELECTED HIGH_SPEED

typedef struct GPIO_Struct{
	GPIO_TypeDef* GPIOx;
	uint16_t GPIO_Pin;

} GPIO_Struct;

typedef struct VL53L0X_Struct{
	VL53L0X_Dev_t VL53L0X_Dev_t;
	I2C_HandleTypeDef* i2c;
	uint8_t status;
	GPIO_Struct xshut;
	//GPIO_Struct gpio;

} VL53L0X_Struct;

/* Prototypes des fonctions */

// vl_xshut_init : Associer un gpio à un capteur
void vl_xshut_init(VL53L0X_Struct* vl53l0x, GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
// vl_sensors_init : Initialiser les capteurs
void vl_sensors_init(VL53L0X_Struct vl53l0x[], I2C_HandleTypeDef* i2c, uint8_t nbOfSensors);
void vl_clear_it_mask(VL53L0X_Struct* vl53l0x);
// vl_sensors_init : Faire une mesure
uint16_t vl_perform_ranging(VL53L0X_Struct* vl53l0x);
uint16_t vl_perform_ranging_it(VL53L0X_Struct* vl53l0x);

/* USER FUNCTIONS */
uint8_t vl53l0x_Init(VL53L0X_Dev_t* dev, I2C_HandleTypeDef* i2c);
uint8_t vl53l0x_PerformMeasurement(VL53L0X_Dev_t* dev, VL53L0X_RangingMeasurementData_t* VL53L0X_RangingMeasurementData);
uint16_t vl53l0x_PerformRangingMeasurement(VL53L0X_Dev_t* dev);
uint16_t vl53l0x_PerformRangingMeasurement_IT(VL53L0X_Dev_t* dev);
uint8_t vl53l0x_SetDeviceAddress(VL53L0X_Dev_t* dev, uint8_t deviceAddress);

/* DEVICE FUNCTIONS */
uint8_t vl53l0x_Device_Initialization(VL53L0X_Dev_t* dev);
uint8_t vl53l0x_Calibration_Data_Load(VL53L0X_Dev_t* dev);
uint8_t vl53l0x_System_Settings(VL53L0X_Dev_t* dev);
uint8_t vl53l0x_Range_Profiles(VL53L0X_Dev_t* dev);

/* MANUFACTURING FUNCTIONS */
uint8_t vl53l0x_Manufacturing_Calibration(VL53L0X_Dev_t* dev);


#endif /* INC_LIB_VL53L0X_H_ */
