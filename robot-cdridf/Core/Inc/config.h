#ifndef CONFIGPARAM_H
#define CONFIGPARAM_H

#include <math.h>
typedef int bool;


// Configuration Sail The World
#define DUREE_MATCH 100
#define TEMPS_PAVILLONS 96 // 95

// Activation des modules
#define MODULE_ACTIONNEURS 1
#define MODULE_ASSERVISSEMENT 1
#define MODULE_COMPTEUR 1
#define MODULE_DEBUG 0
#define MODULE_IHM 1
#define MODULE_LIDAR 1
#define MODULE_MOTEURS 1
#define MODULE_ODOMETRIE 1
#define MODULE_STRATEGIE 1
#define MODULE_TIRETTE 1
#define MODULE_ULTRASONS 0

/* Module actionneurs */
#define ANGLE_STARTUP 110

#define ANGLE_PINCE_RELEASE 30
#define ANGLE_PINCE_CATCH 5

#define ANGLE_FLAG_REPOS 96 // 105
#define ANGLE_FLAG_DEPLOY 15

#define ANGLE_BRAS_RAISE 90
#define ANGLE_BRAS_DEPLOY 50 // 10

/* Module asservissement */
#define ASSERV_ROTATION_EN 1
#define ASSERV_DISTANCE_EN 1

// Vitesses et accélérations max


/* Module Debug */
#define DEBUG_ODOMETRIE 0
#define DEBUG_ASSERVISSEMENT 0
#define DEBUG_LIDAR 0
#define DEBUG_CPT 0
#define DEBUG_FAULT 0
#define DEBUG_TIRETTE 1
#define DEBUG_ULTRASONS 0

/* Module Lidar */
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


/* Module Moteurs */
#define RAYON 51.45/2
#define PAS 200


/* Module Odométrie */
//#define COEFF_CODEUR_L 0.0405726153
//#define COEFF_CODEUR_R 0.0403868872
//#define COEFF_CODEUR_L 0.04127157978967
//#define COEFF_CODEUR_R 0.04127157978967
// calibré
#define COEFF_CODEUR_L 0.0400751912679162
#define COEFF_CODEUR_R 0.0400751912679162

#define ENTRAXE 256 // reel = 253


/* Module Stratégie */
#define BLEU 0
#define JAUNE 1

#define START_BLEU_ANGLE 0
#define START_BLEU_X 150
#define START_BLEU_Y 1071
#define START_JAUNE_ANGLE 0 // M_PI
#define START_JAUNE_X 2850
#define START_JAUNE_Y 1071


/* Module tirette*/
#define TIRETTE_SEUIL 3.15 // 3.05


/* Autres */
#define TRUE 1
#define FALSE 0

/* Variables et prototypes partagées */
bool match_started;
bool port_depart;
int initStrategie();


#endif /* INC_CONFIGPARAM_H_ */
