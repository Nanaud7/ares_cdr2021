#ifndef INC_HC_SR04_H_
#define INC_HC_SR04_H_

#define NB_OF_US_SENSORS 4

#include <stdint.h>
#include "lidar.h"
#include "config.h"

// Variables
long cpt_trigger;
long cpt_shared;
int us_done;

long time_rising[NB_OF_US_SENSORS];
double us_distance[NB_OF_US_SENSORS];

// Prototypes
uint8_t initUltrasons(void);
uint8_t checkUltrasons(void);
uint8_t debugUltrasons(void);

#endif /* INC_HC_SR04_H_ */
