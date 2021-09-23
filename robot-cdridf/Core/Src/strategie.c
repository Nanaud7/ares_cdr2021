/*
 * strategie.c
 *
 * "ui"
 *
 * Generated by Ares ENSEA Simulator.
 * https://ares.asso-ensea.fr/simulateur/
 * 
 * Created at 16:53 on 23/09/2021.
 */

#include <strategie.h>

int nb_points = 6;

CONSIGNE consigneBleu[6] = {
    {
      .x = 211, .y = 1040, .dir = FORWARD, 
      .pinces = { FALSE, FALSE, FALSE, FALSE },
      .bras = FALSE
    }, {
      .x = 530, .y = 1040, .dir = FORWARD, 
      .pinces = { FALSE, FALSE, FALSE, FALSE },
      .bras = FALSE
    }, {
      .x = 693, .y = 1324, .dir = FORWARD, 
      .pinces = { FALSE, FALSE, FALSE, FALSE },
      .bras = FALSE
    }, {
      .x = 859, .y = 1090, .dir = FORWARD, 
      .pinces = { FALSE, FALSE, FALSE, FALSE },
      .bras = FALSE
    }, {
      .x = 799, .y = 835, .dir = FORWARD, 
      .pinces = { FALSE, FALSE, FALSE, FALSE },
      .bras = FALSE
    }, {
      .x = 537, .y = 712, .dir = FORWARD, 
      .pinces = { FALSE, FALSE, FALSE, FALSE },
      .bras = FALSE
    }
};

CONSIGNE consigneJaune[6] = {
    {
      .x = 2789, .y = 1040, .dir = BACKWARD, 
      .pinces = { FALSE, FALSE, FALSE, FALSE },
      .bras = FALSE
    }, {
      .x = 2470, .y = 1040, .dir = BACKWARD, 
      .pinces = { FALSE, FALSE, FALSE, FALSE },
      .bras = FALSE
    }, {
      .x = 2307, .y = 1324, .dir = BACKWARD, 
      .pinces = { FALSE, FALSE, FALSE, FALSE },
      .bras = FALSE
    }, {
      .x = 2141, .y = 1090, .dir = BACKWARD, 
      .pinces = { FALSE, FALSE, FALSE, FALSE },
      .bras = FALSE
    }, {
      .x = 2201, .y = 835, .dir = BACKWARD, 
      .pinces = { FALSE, FALSE, FALSE, FALSE },
      .bras = FALSE
    }, {
      .x = 2463, .y = 712, .dir = BACKWARD, 
      .pinces = { FALSE, FALSE, FALSE, FALSE },
      .bras = FALSE
    }
};
