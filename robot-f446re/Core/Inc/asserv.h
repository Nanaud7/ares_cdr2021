#ifndef ASSERVISSEMENT_H_
#define ASSERVISSEMENT_H_

#include <math.h>
#include "odometrie.h"
#include "lidar.h"
#include "moteurs.h"
#include "odometrie.h"
#include "strategie.h"

#define STAND_BY    0
#define ROTATION    1
#define MOVE        2

// Variables
int indexStrategie;

// Prototypes
void ASSERV_update(CONSIGNE point);
double robotControlSpeed(double x, double a);
uint8_t controlRotation(double angleToTarget);
uint8_t controlMove(CONSIGNE point, double distanceToTarget, double angleToTarget);
double angleToZeroTwoPi(double angle);
double angleToPiPi(double angle);

#endif /* ASSERVISSEMENT_H_ */
