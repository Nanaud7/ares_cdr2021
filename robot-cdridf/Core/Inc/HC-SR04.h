#ifndef INC_HC_SR04_H_
#define INC_HC_SR04_H_

#define NB_OF_US_SENSORS 4

#include <stdint.h>
#include "stm32f4xx_hal.h"
#include "lidar.h"
#include "config.h"

// Define
#define STEP_RESET 0
#define STEP_TRIG 1
#define STEP_RISE 2

#define US_FRONT_LEFT 0
#define US_FRONT_RIGHT 3
#define US_BACK_LEFT 1
#define US_BACK_RIGHT 2

// Variables

typedef struct {
	uint8_t sensorID;
	//GPIO_TypeDef* Trigger_GPIO_Port;
	//uint16_t Trigger_GPIO_Pin;
	GPIO_TypeDef* Echo_GPIO_Port;
	uint16_t Echo_GPIO_Pin;
} SensorUS;

SensorUS Sensors[NB_OF_US_SENSORS];
uint16_t save_cpt_rising;
uint16_t cpt_us_global;			// Compteur du TIM4
uint8_t indexUS;				// Indice du capteur en cours d'utilisation
uint8_t stepUS;
float distUS[NB_OF_US_SENSORS];

// Prototypes
uint8_t initUltrasons(void);
uint8_t processUltrasons(SensorUS Sensor);
uint8_t checkUltrasons(void);
uint8_t debugUltrasons(void);

#endif /* INC_HC_SR04_H_ */
