#include <usart.h>
#include <string.h>
#include "config.h"
#include "strategie.h"

#if MODULE_DEBUG == 1
	#include <stdio.h>
	#include "retarget.h"
#endif

/* Variables */
char ihmRawData[64];
char buff_ihm;

/* Prototypes */
int sendMsgIHM(int idMsg);
int decodeMsgIHM(char *trame);
