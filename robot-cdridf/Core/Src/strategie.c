/*
 * strategie.c
 *
 * "ui"
 *
 * Generated by Ares ENSEA Simulator.
 * https://ares.asso-ensea.fr/simulateur/
 * 
 * Created at 18:20 on 24/09/2021.
 */

#include <strategie.h>

int nb_points = 2;

CONSIGNE consigneBleu[2] = {
    {
      .x = 125, .y = 1070, .dir = FORWARD,
      .pinces = { FALSE, FALSE, FALSE, FALSE },
      .bras = FALSE
    }, {
      .x = 396, .y = 1070, .dir = FORWARD,
      .pinces = { FALSE, FALSE, FALSE, FALSE },
      .bras = TRUE
    }
};

CONSIGNE consigneJaune[2] = {
    {
      .x = 2875, .y = 1070, .dir = BACKWARD,
      .pinces = { FALSE, FALSE, FALSE, FALSE },
      .bras = FALSE
    }, {
      .x = 2604, .y = 1070, .dir = BACKWARD,
      .pinces = { FALSE, FALSE, FALSE, FALSE },
      .bras = TRUE
    }
};
