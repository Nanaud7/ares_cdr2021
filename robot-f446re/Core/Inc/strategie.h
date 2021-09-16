#ifndef STRATEGIE_H_
#define STRATEGIE_H_

/* Includes */
#include "config.h"
#include "DRV8825.h"

/* Typedef */
typedef struct{
	double x;
	double y;
	bool dir;
	bool pinces[4];
	bool flag;
	bool bras;
} CONSIGNE;

/* Variables */
extern int nb_points;
CONSIGNE *consigne;
extern CONSIGNE consigneBleu[];
extern CONSIGNE consigneJaune[];

//void strategieInit();

#endif /* STRATEGIE_H_ */
