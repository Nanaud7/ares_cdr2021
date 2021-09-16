#ifndef DRV8825
#define DRV8825

#include <config.h>
#include "stm32f4xx_hal.h"
#include <stdlib.h>
#include "tim.h"

#define M_TO_S 60
#define E3 1000

#define FORWARD 1
#define BACKWARD 0

#define START 0
#define STOP 1


typedef struct {
    uint16_t pin_DIR;
    GPIO_TypeDef * gpio_DIR;
    uint16_t pin_STEP;
    uint16_t pin_EN;
    GPIO_TypeDef * gpio_EN;
    TIM_HandleTypeDef* timer;
    uint8_t chanel;
}Moteur;


/**
 * @brief initDRV8825
 * @param numéro de pin de enable
 * @param GPIO de la pin enable
 * @param numéro de pin de DIR
 * @param GPIO de la pin DIR
 * @param Timer liée au moteur
 * @param Chanel du timer (TIM_CHANNEL_x) avec x le numéro de chanel
 * @return
 */
void DRV8825_init(Moteur* drv8825,uint16_t PIN_EN, GPIO_TypeDef * GPIO_EN, uint16_t PIN_DIR,
		GPIO_TypeDef * GPIO_DIR, TIM_HandleTypeDef* timer, uint8_t chanel);

/**
 * @brief permet d'initialiser la direction du moteur
 * @brief la structure qui contien les PIN du module
 * @param FORWARD = le robot avance | BACKWARD = le robot recule
 */
void DRV8825_setDir(Moteur* drv8825,uint8_t dir);

/**
 * @brief permet de bloquer le moteur
 * @param la structure qui contien les PIN du module
 * @param START = le moteur tourne | STOP = le moteur est bloqué
 */
void DRV8825_setStart(Moteur* drv8825,uint8_t enable);

/**
 * @brief Permet de définir une vitesse au moteur (RPM)
 * @param la structure qui contien les pin du module
 * @param vitesse de rotation du moteur
 */
void DRV8825_moveMotorRPM(Moteur* drv8825,float rpm);

/**
 * @brief Permet de définir une vitesse linéaire (m/s)
 * @param la structure qui contien les pin du module
 * @param vitesse linéaire de la roue (m/s)
 */
void DRV8825_moveMotorLineSpeed(Moteur* drv8825,float vitesse);



/**
 * @brief permet de modifier la fréquence de notre signal PWM
 * @param le timer de notre moteur
 * @param la structure qui contien les pin du module
 */
void DRV8825_setFrequency(Moteur* drv8825,uint16_t frequency);


#endif
