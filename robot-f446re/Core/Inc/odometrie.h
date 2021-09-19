#ifndef INC_ODOMETRIE_H_
#define INC_ODOMETRIE_H_

#include <stdint.h>
#include <tim.h>
#include "config.h"

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

#endif /* INC_ODOMETRIE_H_ */
