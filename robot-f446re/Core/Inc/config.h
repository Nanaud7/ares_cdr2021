#ifndef CONFIGPARAM_H
#define CONFIGPARAM_H

#include <math.h>
typedef int bool;
#define TRUE 1
#define FALSE 0

// Fonctions du robot
#define MODULE_ACTIONNEURS 1		// Actionneurs utilisant un AX-12
#define MODULE_ASSERVISSEMENT 1
#define MODULE_COMPTEUR 1			// Compteur temps match
#define MODULE_DEBUG 1
#define MODULE_IHM 0
#define MODULE_LIDAR 1
#define MODULE_ULTRASONS 1
#define MODULE_MOTEURS 1
#define MODULE_ODOMETRIE 1
#define MODULE_STRATEGIE 1
#define MODULE_TIRETTE 0

/* Module Debug */
#define DEBUG_ASSERVISSEMENT 0
#define DEBUG_CPT 0
#define DEBUG_FAULT 0
#define DEBUG_LIDAR 0
#define DEBUG_ODOMETRIE 0
#define DEBUG_TIRETTE 0
#define DEBUG_ULTRASONS 1

// Config Sail The World
#define BLEU 0
#define JAUNE 1
#define START_BLEU_ANGLE 0
#define START_BLEU_X 150
#define START_BLEU_Y 1071
#define START_JAUNE_ANGLE 0 // M_PI
#define START_JAUNE_X 2850
#define START_JAUNE_Y 1071
#define DUREE_MATCH 100
#define TEMPS_PAVILLONS 96

// Config AX-12A
#define ANGLE_STARTUP 110
#define ANGLE_PINCE_RELEASE 22
#define ANGLE_PINCE_CATCH 5
#define ANGLE_FLAG_REPOS 96 // 105
#define ANGLE_FLAG_DEPLOY 15
#define ANGLE_BRAS_RAISE 110
#define ANGLE_BRAS_DEPLOY 10

// Config Asserv
#define ASSERV_ROTATION_EN 1
#define ASSERV_DISTANCE_EN 1

// Config Vitesses
#define STEPS_PER_REV   200
#define MICROSTEPS      32
#define ROT_RPM_MAX     30
#define MOV_RPM_MAX     50

// Config Lidar
#define LIDAR_STEP 10
#define LIDAR_FOV 80
#define LIDAR_POS_MID 60
//#define LIDAR_POS_MIN LIDAR_POS_MID-(LIDAR_FOV/2)
//#define LIDAR_POS_MAX LIDAR_POS_MID+(LIDAR_FOV/2)
#define LIDAR_POS_MIN 20
#define LIDAR_POS_MAX 100
//#define LIDAR_ARRAY_SIZE (LIDAR_FOV/LIDAR_STEP)+1
#define LIDAR_ARRAY_SIZE 9
#define LIDAR_SEUIL 500

// Config Odométrie
#define COEFF_CODEUR_L 0.0405726153
#define COEFF_CODEUR_R 0.0403868872
#define ENTRAXE 251

// Config Tirette
#define TIRETTE_SEUIL 3.05

/* Variables et prototypes partagées */
bool match_started;
bool port_depart;
int initStrategie();

#endif /* INC_CONFIGPARAM_H_ */
