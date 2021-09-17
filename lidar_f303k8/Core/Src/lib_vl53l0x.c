/*
 * lib_vl53l0x.c
 *
 *      Author: Arnaud CHOBERT
 */

#include "lib_vl53l0x.h"

/* Fonctions utilisateurs */

void vl_xshut_init(VL53L0X_Struct* vl53l0x, GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin){
	vl53l0x->xshut.GPIOx = GPIOx;
	vl53l0x->xshut.GPIO_Pin = GPIO_Pin;
	HAL_GPIO_WritePin(vl53l0x->xshut.GPIOx, vl53l0x->xshut.GPIO_Pin, GPIO_PIN_RESET);
	HAL_Delay(TOGGLE_GPIO_TIME);
}

void vl_sensors_init(VL53L0X_Struct vl53l0x[], I2C_HandleTypeDef* i2c, uint8_t nbOfSensors){

	for(int i=0; i<nbOfSensors; i++){
		vl53l0x[i].i2c = i2c;
		HAL_Delay(TOGGLE_GPIO_TIME);

		HAL_GPIO_WritePin(vl53l0x[i].xshut.GPIOx, vl53l0x[i].xshut.GPIO_Pin, GPIO_PIN_SET);
		HAL_Delay(TOGGLE_GPIO_TIME);

		vl53l0x_Init(&vl53l0x[i].VL53L0X_Dev_t, vl53l0x->i2c);
		vl53l0x_SetDeviceAddress(&vl53l0x[i].VL53L0X_Dev_t, 0x54+i*2);
		HAL_Delay(TOGGLE_GPIO_TIME);
	}
}

void vl_clear_it_mask(VL53L0X_Struct* vl53l0x){
	VL53L0X_ClearInterruptMask(&vl53l0x->VL53L0X_Dev_t, 0);
}

uint16_t vl_perform_ranging(VL53L0X_Struct* vl53l0x){
	return vl53l0x_PerformRangingMeasurement(&vl53l0x->VL53L0X_Dev_t);
}

uint16_t vl_perform_ranging_it(VL53L0X_Struct* vl53l0x){
	return vl53l0x_PerformRangingMeasurement_IT(&vl53l0x->VL53L0X_Dev_t);
}



/* Fonctions intermédiaires */

uint8_t vl53l0x_Init(VL53L0X_Dev_t* dev, I2C_HandleTypeDef* i2c){

	dev->I2cHandle = i2c;
	dev->I2cDevAddr = 0x52;
	dev->comms_speed_khz = 400;
	dev->comms_type = 1;

	// Device initialization
	vl53l0x_Device_Initialization(dev);

	// Calibration data loading
	vl53l0x_Calibration_Data_Load(dev);

	// System settings
	vl53l0x_System_Settings(dev);

	/* Polling and interrupt mode */
#if INTERRUPT_MODE == 1
	VL53L0X_SetGpioConfig(dev, 0, VL53L0X_DEVICEMODE_CONTINUOUS_RANGING,
			VL53L0X_GPIOFUNCTIONALITY_NEW_MEASURE_READY, VL53L0X_INTERRUPTPOLARITY_HIGH);
#endif

	// Start Measurement
	VL53L0X_StartMeasurement(dev);

	return 0;
}

uint8_t vl53l0x_PerformMeasurement(VL53L0X_Dev_t* dev, VL53L0X_RangingMeasurementData_t* VL53L0X_RangingMeasurementData){
	uint8_t status = VL53L0X_ERROR_NONE;

	VL53L0X_WaitDeviceReadyForNewMeasurement(dev, 100);

	if(VL53L0X_ERROR_NONE != (status = VL53L0X_GetRangingMeasurementData(dev, VL53L0X_RangingMeasurementData))){
		//printf("Error GetRangingMeasurementData() : %d\r\n",status);
		return 1;
	}

	return 0;
}

uint16_t vl53l0x_PerformRangingMeasurement(VL53L0X_Dev_t* dev){
	VL53L0X_RangingMeasurementData_t VL53L0X_RangingMeasurementData;

	vl53l0x_PerformMeasurement(dev, &VL53L0X_RangingMeasurementData);

	return VL53L0X_RangingMeasurementData.RangeMilliMeter;
}

uint8_t vl53l0x_SetDeviceAddress(VL53L0X_Dev_t* dev, uint8_t deviceAddress){
	VL53L0X_SetDeviceAddress(dev, deviceAddress);
	dev->I2cDevAddr = deviceAddress;

	return 0;
}

uint16_t vl53l0x_PerformRangingMeasurement_IT(VL53L0X_Dev_t* dev){
	uint8_t status = VL53L0X_ERROR_NONE;
	VL53L0X_RangingMeasurementData_t VL53L0X_RangingMeasurementData;

	if(VL53L0X_ERROR_NONE != (status = VL53L0X_GetRangingMeasurementData(dev, &VL53L0X_RangingMeasurementData))){
		//printf("Error GetRangingMeasurementData() : %d\r\n",status);
		return 1;
	}

	return VL53L0X_RangingMeasurementData.RangeMilliMeter;
}


/* DEVICE FUNCTIONS */

uint8_t vl53l0x_Device_Initialization(VL53L0X_Dev_t* dev){
	uint8_t status = VL53L0X_ERROR_NONE;

	/* DataInit */
	if(VL53L0X_ERROR_NONE != (status = VL53L0X_DataInit(dev))){
		//printf("Error DataInit() : %d\r\n",status);
		return 1;
	}

	/* StaticInit */
	if(VL53L0X_ERROR_NONE != (status = VL53L0X_StaticInit(dev))){
		//printf("Error StaticInit() : %d\r\n",status);
		return 1;
	}

	return 0;
}


uint8_t vl53l0x_Calibration_Data_Load(VL53L0X_Dev_t* dev){
	//uint8_t status = VL53L0X_ERROR_NONE;

	/* Reference SPADs */
	uint32_t count; uint8_t isApertureSpads;
	VL53L0X_PerformRefSpadManagement(dev, &count, &isApertureSpads);
	//VL53L0X_SetReferenceSpads(dev, count, isApertureSpads);
	//VL53L0X_GetReferenceSpads(dev, &count, &isApertureSpads);

	/* Ref calibration */
    uint8_t VhvSettings, PhaseCal;
	VL53L0X_PerformRefCalibration(dev, &VhvSettings, &PhaseCal);
	//VL53L0X_SetRefCalibration(dev, VhvSettings, PhaseCal);

	/* Offset calibration */

	/* Cross-talk correction */

	return 0;
}


uint8_t vl53l0x_System_Settings(VL53L0X_Dev_t* dev){
	/* Device Mode */
	VL53L0X_SetDeviceMode(dev, VL53L0X_DEVICEMODE_CONTINUOUS_RANGING);

	/* API range profiles */
	vl53l0x_Range_Profiles(dev);

	return 0;
}


uint8_t vl53l0x_Range_Profiles(VL53L0X_Dev_t* dev){
	FixPoint1616_t signalLimit = (FixPoint1616_t)(0.25*65536);
	FixPoint1616_t sigmaLimit = (FixPoint1616_t)(18*65536);
	uint32_t timingBudget = 33000;
	uint8_t preRangeVcselPeriod = 14;
	uint8_t finalRangeVcselPeriod = 10;

	switch(RANGE_PROFILE_SELECTED) {
	case LONG_RANGE:
		signalLimit = (FixPoint1616_t)(0.1*65536);
		sigmaLimit = (FixPoint1616_t)(60*65536);
		timingBudget = 33000;
		preRangeVcselPeriod = 18;
		finalRangeVcselPeriod = 14;
		break;
	case HIGH_ACCURACY:
		signalLimit = (FixPoint1616_t)(0.25*65536);
		sigmaLimit = (FixPoint1616_t)(18*65536);
		timingBudget = 200000;
		preRangeVcselPeriod = 14;
		finalRangeVcselPeriod = 10;
		break;
	case HIGH_SPEED:
		signalLimit = (FixPoint1616_t)(0.25*65536);
		sigmaLimit = (FixPoint1616_t)(32*65536);
		timingBudget = 20000;
		preRangeVcselPeriod = 14;
		finalRangeVcselPeriod = 10;
		break;
	default:
		//printf("Not Supported");
		break;
	}

	VL53L0X_SetLimitCheckValue(dev, VL53L0X_CHECKENABLE_SIGNAL_RATE_FINAL_RANGE, signalLimit);
	VL53L0X_SetLimitCheckValue(dev, VL53L0X_CHECKENABLE_SIGMA_FINAL_RANGE, sigmaLimit);
	VL53L0X_SetMeasurementTimingBudgetMicroSeconds(dev, timingBudget);
	VL53L0X_SetVcselPulsePeriod(dev, VL53L0X_VCSEL_PERIOD_PRE_RANGE, preRangeVcselPeriod);
	VL53L0X_SetVcselPulsePeriod(dev, VL53L0X_VCSEL_PERIOD_FINAL_RANGE, finalRangeVcselPeriod);

	return 0;
}


/* MANUFACTURING FUNCTIONS */

uint8_t vl53l0x_Manufacturing_Calibration(VL53L0X_Dev_t* dev){
	/* Manufacturing calibration flow*/

	// Device initialization and settings
	vl53l0x_Device_Initialization(dev);

	// SPADs calibration
	uint32_t refSpadCount; uint8_t isApertureSpads;
	VL53L0X_PerformRefSpadManagement(dev, &refSpadCount, &isApertureSpads);

	// Temperature calibration
    uint8_t VhvSettings, PhaseCal;
	VL53L0X_PerformRefCalibration(dev, &VhvSettings, &PhaseCal);

	// Offset calibration (il faut utiliser un obstacle blanc)
	FixPoint1616_t CalDistanceMilliMeter; int32_t OffsetMicroMeter;
	VL53L0X_PerformOffsetCalibration(dev, CalDistanceMilliMeter, &OffsetMicroMeter);

	// CrossTalk calibration
	FixPoint1616_t XTalkCalDistance, XTalkCompensationRateMegaCps;
	VL53L0X_PerformXTalkCalibration(dev, XTalkCalDistance, &XTalkCompensationRateMegaCps);

	return 0;
}
