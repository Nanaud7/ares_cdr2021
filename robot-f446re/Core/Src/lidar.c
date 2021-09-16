#include "lidar.h"

void getLidarData(){
	char* pt = NULL;

    lidarData[0] = strtol(lidarRawData, &pt, 10);
    lidarData[1] = strtol(pt, &pt, 10); // Back
    lidarData[2] = strtol(pt, &pt, 10); // Front

    int indexLidar = (lidarData[0] - LIDAR_POS_MIN) / LIDAR_STEP;

    // Back
    if(lidarData[1] < 500){
    	lidarAlarmBack[indexLidar] = 1;
    }
    else lidarAlarmBack[indexLidar] = 0;

    // Front
    if(lidarData[2] < 500){
    	lidarAlarmFront[indexLidar] = 1;
    }
    else lidarAlarmFront[indexLidar] = 0;

    /*
	#if MODULE_DEBUG && DEBUG_LIDAR
		printf("%d\t%d\t%d\n\r", lidarData[0],lidarData[1],lidarData[2]);
		printf("%d\n\r",(int)indexLidar);
	#endif
	*/

    /*
	#if MODULE_DEBUG == 1 && DEBUG_LIDAR == 1
		printf("StopFront = %d\r\n", StopFront);
		//printf("StopBack = %d\r\n", StopBack);
	#endif
	*/

}

void getLidarData2(){
	char header = lidarRawData[0];

	//#if MODULE_DEBUG == 1 && DEBUG_LIDAR
	//printf("header = %c\r\n",header);
	//#endif

	switch(header){
		case 'B' :
			StopBack = 1;
			cpt_back = 0;
			break;

		case 'F' :
			StopFront = 1;
			cpt_front = 0;
			break;

		default :
			break;
	}
}
