#ifndef UARTDEVICE_H_
#define UARTDEVICE_H_

#include <usart.h>
#include <stdlib.h>
#include "config.h"

#if MODULE_DEBUG == 1 && DEBUG_LIDAR == 1
	#include <stdio.h>
#endif

/* Variables */
char buff_lidar;
char lidarRawData[64];
//float lidarData[3]; // Orientation - Data1 - Data2
int lidarData[3];
bool StopFront;
bool StopBack;

int cpt_front;
int cpt_back;

bool lidarAlarmFront[LIDAR_ARRAY_SIZE];
bool lidarAlarmBack[LIDAR_ARRAY_SIZE];


void getLidarData();
void getLidarData2();

#endif /* UARTDEVICE_H_ */
