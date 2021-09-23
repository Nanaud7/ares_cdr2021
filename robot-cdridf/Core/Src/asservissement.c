#include "asservissement.h"

#define VALID_RADIUS 10
#define VALID_ANGLE 0.01

#define VMAX_RECT 10 // 10 c'est pas mal
#define VMIN_DISTANCE 0.5
#define VMAX_ROTATION 5
#define VMIN_ROTATION 0.1

double initialAngleError = 0;

int isRotating = 0;

/**
 * Borne une valeur donnée dans [0, 1].
 * @param x La valeur à borner.
 * @return Si possible x, 0 ou 1 sinon.
 */
double toZeroOne(double x) {
	if (x < 0) return 0;
	if (x > 1) return 1;
	return x;
}

/**
 * Ramène un angle donné vers l'intervalle [0, 2PI].
 * @param angle L'angle.
 * @return L'angle ramené à [0, 2PI].
 */
double toZeroTwoPi(double angle) {
    return fmod(fmod(angle, M_TWOPI) + M_TWOPI, M_TWOPI);
}

/**
 * Permet de calculer la plus petite rotation à effectuer pour une orientation donnée.
 * @param angle L'orientation voulue.
 * @return L'angle ramené à [-PI, PI].
 */
double optimalAngle(double angle) {
    return toZeroTwoPi(angle + M_PI) - M_PI;
}

/**
 * Courbe de vitesse parabolique.
 * @param progress Un flottant entre 0 et 1 qui indique où en est le mouvement.
 * @return Une vitesse normalisée entre 0 et 1.
 */
double speedCurve1(double progress) {
    double speed = -4*progress*(progress-1);
    return (speed<0)?0:speed;
}

//double speedCurve2(double progress) {
//    double speed = 27/4*progress*(1-progress)*(1-progress);
//    return (speed<0)?0:speed;
//}
//
//double speedCurve3(double progress) {
//    double speed = 10*progress*(1-progress)*(1-progress)*(1-progress);
//    return (speed<0)?0:speed;
//}

/**
 * Cette fonction est appelée à intervalles réguliers pour piloter le robot.
 * @param point Le point visé.
 * @param point Le point où le robot commence son déplacement.
 */
void ASSERV_update2(CONSIGNE point, CONSIGNE previous) {
    if (indexStrategie >= nb_points || !match_started) {
    	//stopMoteurs();
    	setMotors(0, 0);
    	return;
    }

    ODO_odometrie();

    // calculs préliminaires
    double pointDistance = sqrt(pow(point.x - g_x, 2) + pow(point.y - g_y, 2));
    double previousDistance = sqrt(pow(previous.x - g_x, 2) + pow(previous.y - g_y, 2));
    double segmentLength = sqrt(pow(point.x - previous.x, 2) + pow(point.y - previous.y, 2));
    double moveProgress = toZeroOne(previousDistance/segmentLength);
    if (segmentLength == 0) moveProgress = 1; // pour éviter NaN en cas de divison par zéro

    // point à viser (je peux t'expliquer IRL, en commentaire ça passe pas mdr)
    double t = 1.1 - (1 - moveProgress)*0.6;
    CONSIGNE subAimPoint = {
    	x: (1-t)*previous.x + t*point.x,
		y: (1-t)*previous.y + t*point.y
    };

    double pointDirection = atan2(subAimPoint.y - g_y, subAimPoint.x - g_x);
    double angleError = optimalAngle( pointDirection - g_angle - ((point.dir==BACKWARD)?M_PI:0) );
    if (isnan(initialAngleError)) initialAngleError = angleError; // analogue à segmentLength
    double rotateProgress = toZeroOne(1 - angleError/initialAngleError);
    if (fabs(initialAngleError) < 0.001) rotateProgress = 1; // pour éviter NaN en cas de divison par zéro

    // si le robot est très mal orienté, lancer la séquence de rotation pure
    if (fabs(angleError) > VALID_ANGLE*10)
    	isRotating = 1;

    // si le robot est bien orienté, arreter la séquence de rotation pure
    if (fabs(angleError) < VALID_ANGLE)
    	isRotating = 0;

    // (le cas entre VALID_ANGLE et VALID_ANGLE*10 est géré par l'asservissement
    // en distance qui corrige aussi l'angle en permanance)

    if (isRotating) { // le robot est mal orienté
    	double spin = VMAX_ROTATION*speedCurve1(rotateProgress)/2;

    	// aller plus vite sur les rotations longues
    	spin *= fabs(initialAngleError)/M_PI;

    	// imposer une vitesse min au début de la rotation
    	spin += VMIN_ROTATION*(1-rotateProgress);

    	// imposer un sens de rotation
    	spin *= -angleError/fabs(angleError);

    	setMotors(-spin, spin);
    } else if (moveProgress < 1) { // le robot est loin
    	double speed = VMAX_RECT*speedCurve1(moveProgress);

    	// aller plus vite sur les longs segments
    	speed *= toZeroOne(segmentLength/1000);

    	// ralentir si l'angle est mauvais
    	speed *= 1/(1+pow(fabs(angleError/VALID_ANGLE/5), 2));

    	// imposer une vitesse min
    	speed += VMIN_DISTANCE;

    	// imposer le sens
    	speed *= (point.dir==FORWARD)?1:-1;

    	double spin = VMAX_ROTATION*(speedCurve1(rotateProgress)*fabs(initialAngleError)/M_PI + speedCurve1(moveProgress)*fabs(angleError))/2;

    	// imposer une vitesse min au début de la rotation
    	spin += VMIN_ROTATION*(1-rotateProgress);

    	// imposer un sens de rotation
    	spin *= -angleError/fabs(angleError);

        if((StopFront == TRUE && point.dir == FORWARD) || (StopBack == TRUE && point.dir == BACKWARD)){
        	speed = 0;
        	spin = 0;
        	previous.x = g_x; previous.y = g_y;
        }

    	setMotors(speed - spin, speed + spin);
    } else {
        // le robot est arrivé au point visé
    	actionneursUpdate(point);
    	indexStrategie++;
    	initialAngleError = NAN;
    	stopMoteurs();
    }
}

/*
// pour tester l'odo
int first = 0;
void ASSERV_update_test(CONSIGNE point, CONSIGNE previous) {
	ODO_odometrie();

	double spin;
	if (first == 0) {
		spin = (M_PI/2 - g_angle) * 3;
		if (fabs(M_PI/2 - g_angle)*360.0/M_TWOPI < 0.1) {
			first = 1;
		}
	} else {
		spin = -g_angle * 3;
	}

	setMotors(spin, -spin);

	printf("angle: %f\r\n", g_angle/M_PI/2*360);
}
*/
