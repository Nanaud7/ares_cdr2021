#include "asservissement.h"

/* Variables */
int state = 0;
double distanceCibleInitiale = 0;
double relativeAngleInitial = 0;

double toZeroTwoPi(double angle) {
	return fmod(fmod(angle, M_TWOPI) + M_TWOPI, M_TWOPI);
}

double toPiPi(double angle) {
	return toZeroTwoPi(angle + M_PI) - M_PI;
}

void ASSERV_update(CONSIGNE point){

	// Odométrie
	ODO_odometrie();

	// Calcul de la consigne de distance
	double distanceCible = sqrt(pow(point.x-g_x,2) + pow(point.y-g_y,2));

	// Calcul de la consigne d'orientation
	double consigneAngle = ASSERV_calculAngle(point);

	#if MODULE_DEBUG == 1 && DEBUG_ASSERVISSEMENT == 1 && 0
		printf("distanceCible = %f\n\r"
				"consigneAngle = %f\n\r",distanceCible, consigneAngle);
	#endif

	switch(state){
		case(0) : // État d'attente

			#if MODULE_DEBUG && DEBUG_ASSERVISSEMENT
					printf("indexStrategie = %d\r\n", indexStrategie);
			#endif

			if(indexStrategie < nb_points && match_started == 1){
				state = 1;
			}
			else{
				stopMoteurs();
			}

			break;

		case(1) : // Rotation
			#if ASSERV_ROTATION_EN
					ASSERV_rotation(point, consigneAngle);
			#else
					state = 2;
			#endif
			break;

		case(2) : // Déplacement en ligne droite
			#if ASSERV_DISTANCE_EN
					//ASSERV_distance(point, distanceCible);
					ASSERV_distance_new(point, distanceCible, consigneAngle);
			#else
					state = 0;
					indexStrategie++;
			#endif
			break;

		default :
			stopMoteurs();
			break;
	}

}

void ASSERV_reset(){
	// Réinitialisation des valeurs avant de changer d'étapes
	distanceCibleInitiale = 0;
	relativeAngleInitial = 0;
}

double ASSERV_calculAcceleration(double x, double _, double __){
	double a = 0.1;
	double v = atan(-x*(x-1)*a)/atan(0.25*a);
	return v>0?v:0;
}

double ASSERV_calculAngle(CONSIGNE point){
	return atan2(point.y - g_y, point.x - g_x);
}

void ASSERV_rotation(CONSIGNE point, double consigneAngle){
	// Calcul de l'angle relatif
	double relativeAngle = consigneAngle - g_angle;
	if (point.dir == BACKWARD)
		relativeAngle = relativeAngle - M_PI;
	// Optimisation de la rotation à effectuer
	// (pas plus de 180° de rotation dans chaque sens)
	relativeAngle = toPiPi(relativeAngle);

	// Enregistrement de la consigne relative initiale
	if (relativeAngleInitial == 0)
		relativeAngleInitial = relativeAngle;

	// Calcul de la progression (pourcentage d'avancement de la rotation)
	double progression = 1 - relativeAngle/relativeAngleInitial;
	progression = progression<=1?progression:1;
	progression = progression>=0?progression:0;


	// Si 'relativeAngleInitial' est toujours nul, on skip le point
    if (relativeAngleInitial == 0)
    	progression = 1;

    // Sens de rotation
    //if (relativeAngle < 0) {
    if (relativeAngle > 0) {
        DRV8825_setDir(&moteur_D, BACKWARD);
        DRV8825_setDir(&moteur_G, FORWARD);
    } else {
        DRV8825_setDir(&moteur_D, FORWARD);
        DRV8825_setDir(&moteur_G, BACKWARD);
    }

    //double a = 1000 + angleCibleInitiale * 2000;
    //double a = 1000 + relativeAngleInitial / M_PI * 5000;
    double a = 1000;
    double vitesse = VMAX_ROTATION * ASSERV_calculAcceleration(progression, a, 45)
    	+ VMIN_ROTATION;

    // Commandes des moteurs
	#if MODULE_DEBUG && DEBUG_ASSERVISSEMENT == 1
		printf("relativeAngleInitial = %f\r\n",relativeAngleInitial);
		printf("relativeAngle = %f\r\n",relativeAngle);
		printf("progression = %f\r\n",progression);
		printf("p_x = %f\r\n", point.x);
		printf("p_y = %f\r\n", point.y);
		//printf("indexStrategie = %d\r\n", indexStrategie);
	#endif
	DRV8825_moveMotorLineSpeed(&moteur_D, vitesse);
	DRV8825_moveMotorLineSpeed(&moteur_G, vitesse);
	startMoteurs();

	// Condition d'arrêt
    if (progression > 0.95) {
    	stopMoteurs();
    	ASSERV_reset();
    	state = 2;
    }
}


void ASSERV_distance(CONSIGNE point, double distanceCible){

	/*
	#if MODULE_LIDAR
		bool StopFront = 0; StopBack = 0;

		for(int i = 0; i<LIDAR_ARRAY_SIZE; i++){
			if(lidarAlarmFront[i] == 1) StopFront = 1;
		}

		for(int i = 0; i<LIDAR_ARRAY_SIZE; i++){
			if(lidarAlarmBack[i] == 1) StopBack = 1;
		}

	#endif
	*/

	// Asservissement
    if (distanceCibleInitiale == 0)
    	distanceCibleInitiale = distanceCible;

    double progression = 1 - (distanceCible / distanceCibleInitiale);
    progression = progression<=1?progression:1;
    progression = progression>=0?progression:0;

    //double a = 1000 + distanceCibleInitiale / 1000 * 10000;
    double a = 1000 + distanceCible / 300 * 6000;
    double vitesse = VMAX_DISTANCE * ASSERV_calculAcceleration(progression, a, 45)
    		+ VMIN_DISTANCE * (1 - progression);
    		//+ VMIN_DISTANCE;

	// Commandes des moteurs
	#if MODULE_DEBUG && DEBUG_ASSERVISSEMENT == 1
    	printf("distanceCibleInitiale = %f\r\n",distanceCibleInitiale);
    	printf("distanceCible = %f\r\n",distanceCible);
    	printf("progression = %f\r\n",progression);
    	printf("p_x = %f\r\n", point.x);
    	printf("p_y = %f\r\n", point.y);
    	//printf("indexStrategie = %d\r\n", indexStrategie);
	#endif
	DRV8825_moveMotorLineSpeed(&moteur_D, vitesse);
	DRV8825_moveMotorLineSpeed(&moteur_G, vitesse);

	// Choix du sens
	if(point.dir == FORWARD){
		if(StopFront == 0){
			DRV8825_setDir(&moteur_G, FORWARD);
			DRV8825_setDir(&moteur_D, FORWARD);
			startMoteurs();
		}
		else {
			stopMoteurs();
			ASSERV_reset();
			progression = 0;
			//state = 0;
			//DRV8825_moveMotorLineSpeed(&moteur_D, 0);
			//DRV8825_moveMotorLineSpeed(&moteur_G, 0);
		}
	}

	else if (point.dir == BACKWARD){
		if(StopBack == 0){
			DRV8825_setDir(&moteur_G, BACKWARD);
			DRV8825_setDir(&moteur_D, BACKWARD);
			startMoteurs();
		}
		else{
			stopMoteurs();
			ASSERV_reset();
			progression = 0;
			//state = 0;
			//DRV8825_moveMotorLineSpeed(&moteur_D, 0);
			//DRV8825_moveMotorLineSpeed(&moteur_G, 0);
		}
	}

	//printf("StopFront = %d\r\n",StopFront);
	//printf("BackFront = %d\r\n",StopBack);

	// Condition d'arrêt
	//if (distanceCible < 20){

	if (progression >= 0.95 || distanceCible < 30){
	//if (progression > 0.95){
		actionneursUpdate(point);
		stopMoteurs();
		//DRV8825_moveMotorLineSpeed(&moteur_D, 0);
		//DRV8825_moveMotorLineSpeed(&moteur_G, 0);
		state = 0;
		actionneursUpdate(point);
		indexStrategie++;
		ASSERV_reset();
	}
}

void ASSERV_distance_new(CONSIGNE point, double distanceCible, double consigneAngle){

    if (distanceCibleInitiale == 0)
    	distanceCibleInitiale = distanceCible;

    double progression = 1 - (distanceCible / distanceCibleInitiale);
    progression = progression<=1?progression:1;
    progression = progression>=0?progression:0;

    double a = 1000 + distanceCible / 300 * 6000;
    double vitesse = VMAX_DISTANCE * ASSERV_calculAcceleration(progression, a, 45)
    		+ VMIN_DISTANCE * (1 - progression);

    double erreur_angle = toPiPi(consigneAngle - g_angle) / M_PI;

	// Commandes des moteurs
	#if MODULE_DEBUG && DEBUG_ASSERVISSEMENT == 1
    	printf("distanceCibleInitiale = %f\r\n",distanceCibleInitiale);
    	printf("distanceCible = %f\r\n",distanceCible);
    	printf("progression = %f\r\n",progression);
    	printf("p_x = %f\r\n", point.x);
    	printf("p_y = %f\r\n", point.y);
    	printf("erreur_angle = %f\r\n\r\n", erreur_angle);
	#endif

    if(distanceCible < 100 || 1){
    	erreur_angle = 0;
    }

    if(erreur_angle > 0){ // != (point.dir == BACKWARD)
    	DRV8825_moveMotorLineSpeed(&moteur_G, vitesse);
    	DRV8825_moveMotorLineSpeed(&moteur_D, vitesse * (1 - erreur_angle));
    } else {
    	DRV8825_moveMotorLineSpeed(&moteur_G, vitesse * (1 - erreur_angle));
    	DRV8825_moveMotorLineSpeed(&moteur_D, vitesse);
    }

	// Choix du sens
	if(point.dir == FORWARD){
		if(StopFront == 0){
			DRV8825_setDir(&moteur_G, FORWARD);
			DRV8825_setDir(&moteur_D, FORWARD);
			startMoteurs();
		}
		else {
			stopMoteurs();
			ASSERV_reset();
			progression = 0;
		}
	}

	else if (point.dir == BACKWARD){
		if(StopBack == 0){
			DRV8825_setDir(&moteur_G, BACKWARD);
			DRV8825_setDir(&moteur_D, BACKWARD);
			startMoteurs();
		}
		else{
			stopMoteurs();
			ASSERV_reset();
			progression = 0;
		}
	}

	if (progression >= 0.95 || distanceCible < 30){
		stopMoteurs();
		state = 0;
		actionneursUpdate(point);
		indexStrategie++;
		ASSERV_reset();
	}
}
