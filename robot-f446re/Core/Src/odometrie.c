#include <asservissement.h>


int16_t getTickRight(){
	return (int16_t)(CODEUR_D.Instance->CNT);
	//return (int16_t)(~CODEUR_D.Instance->CNT + 1);
}

int16_t getTickLeft(){
	//return (int16_t)(CODEUR_G.Instance->CNT);
	return (int16_t)(~CODEUR_G.Instance->CNT + 1);
}

void resetTickRight(){
	CODEUR_D.Instance->CNT = 0;
}
void resetTickLeft(){
	CODEUR_G.Instance->CNT = 0;
}

void ODO_odometrie(){

#if MODULE_DEBUG == 1 && DEBUG_ODOMETRIE == 1
	printf("Position actuelle : \n\r"
			"x : %lf \n\r"
			"y : %lf \n\r"
			"o : %lf \n\n\r",g_x, g_y, g_angle);
#endif


	int valCodG = getTickLeft();
	int valCodD = getTickRight();

	dDistance =  (valCodG * COEFF_CODEUR_L + valCodD*COEFF_CODEUR_R)/2;
	dAngle = (valCodD*COEFF_CODEUR_R - valCodG*COEFF_CODEUR_L)/ENTRAXE;

	g_x += dDistance * cos(g_angle);
	g_y += dDistance * sin(g_angle);
	g_angle += dAngle;

	if(g_angle > M_PI)
		g_angle = g_angle - (M_PI * 2.0f);

	if(g_angle < (-1) * M_PI)
		g_angle = g_angle + (M_PI * 2.0f);

	resetTickRight();
	resetTickLeft();

}

void ODO_setX(double x){
	g_x =x;
}

void ODO_setY(double y){
	g_y = y;
}
void ODO_setPosition(double x, double y){
	g_x = x;g_y = y;
}
void ODO_setAngle(double angle){
	g_angle = angle;
}
void ODO_setPositionOrientation(double x, double y, double angle){
	g_angle = angle; g_x = x; g_y = y;
}
