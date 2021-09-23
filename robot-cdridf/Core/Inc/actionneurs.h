#ifndef ACTIONNEUR_H_
#define ACTIONNEUR_H_

#include <usart.h>
#include "config.h"
#include "AX12.h"
#include "strategie.h"

#define NB_AX12_BRAS 4
AX12 pinces[NB_AX12_BRAS];
AX12 bras;
AX12 flag;

void actionneursUpdate(CONSIGNE strategie);

void initPinces();
void catchObject(AX12 *ax12);
void releasObject(AX12* ax12);

void initFlag();
void raiseFlag();
void lowerFlag();

void initBras();
void raiseBras();
void deployBras();

#endif /* INC_ACTIONNEUR_H_ */
