#ifndef ASSERVISSEMENT_H_
#define ASSERVISSEMENT_H_

/* Includes */
#include "tim.h"
#include "config.h"
#include "moteurs.h"
#include "strategie.h"
#include "lidar.h"
#include "actionneurs.h"

#if MODULE_DEBUG == 1
	#include <stdio.h>
	#include "retarget.h"
#endif

//Valeur en radiant pour 1 deg
#define D_RAD 0.017453

int indexStrategie;

// Odométrie
double dDistance;
double dAngle;
double g_angle;
double g_x;
double g_y;

int16_t getTickRight();
int16_t getTickLeft();

void resetTickRight();
void resetTickLeft();


void ODO_odometrie();
void ODO_setX(double x);
void ODO_setY(double y);
void ODO_setPosition(double x, double y);
void ODO_setAngle(double angle);
void ODO_setPositionOrientation(double x, double y, double angle);

/* Prototypes */
//void ASSERV_update2(CONSIGNE point, CONSIGNE previous);
void ASSERV_update2(CONSIGNE point, CONSIGNE* previous);
void ASSERV_reset();

#endif /* ASSERVISSEMENT_H_ */
