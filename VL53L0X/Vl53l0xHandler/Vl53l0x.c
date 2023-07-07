/*
 * Vl53l0x.c
 */

#include "Vl53l0x.h"
#include "cmsis_os.h"

VL53L0X_Error Vl53l0x_Init(Vl53l0x_HandlerStruct* Dev_t, I2C_OS_HandlerStruct * i2c, uint8_t Adress, GPIO_HandlerStruct xShutPin)
{
//    printf("VL53L0X init...\n\r");
    uint32_t refSpadCount;
    uint8_t isApertureSpads;
    uint8_t VhvSettings;
    uint8_t PhaseCal;

    Dev_t->XshutPin = xShutPin;
    Dev_t->Address = Adress;
    Dev_t->Dev.I2cHandle = i2c;
    Dev_t->Dev.I2cDevAddr = VL53L0X_DEFAULT_ADDRESS;

    GPIO_WritePin(Dev_t->XshutPin, GPIO_PIN_RESET); // Disable XSHUT
	osDelay(10);
	GPIO_WritePin(Dev_t->XshutPin, GPIO_PIN_SET); // Enable XSHUT
	osDelay(10);

	VL53L0X_Error Status = VL53L0X_ERROR_NONE;

//    Status = VL53L0X_DataInit( &Dev_t->Dev );
//    if (Status != VL53L0X_ERROR_NONE) return Status;
//    Status = VL53L0X_StaticInit( &Dev_t->Dev );
//    if (Status != VL53L0X_ERROR_NONE) return Status;
//    Status = VL53L0X_PerformRefCalibration(&Dev_t->Dev, &VhvSettings, &PhaseCal);
//    if (Status != VL53L0X_ERROR_NONE) return Status;
//    Status = VL53L0X_PerformRefSpadManagement(&Dev_t->Dev, &refSpadCount, &isApertureSpads);
//    if (Status != VL53L0X_ERROR_NONE) return Status;

    Status = VL53L0X_SetDeviceMode(&Dev_t->Dev, VL53L0X_DEVICEMODE_SINGLE_RANGING);
    if (Status != VL53L0X_ERROR_NONE) return Status;

    // Enable/Disable Sigma and Signal check
    Status = VL53L0X_SetLimitCheckEnable(&Dev_t->Dev, VL53L0X_CHECKENABLE_SIGMA_FINAL_RANGE, 1);
    if (Status != VL53L0X_ERROR_NONE) return Status;
    Status = VL53L0X_SetLimitCheckEnable(&Dev_t->Dev, VL53L0X_CHECKENABLE_SIGNAL_RATE_FINAL_RANGE, 1);
    if (Status != VL53L0X_ERROR_NONE) return Status;
    Status = VL53L0X_SetLimitCheckValue(&Dev_t->Dev, VL53L0X_CHECKENABLE_SIGMA_FINAL_RANGE, (FixPoint1616_t)(60*65536));
    if (Status != VL53L0X_ERROR_NONE) return Status;
    Status = VL53L0X_SetLimitCheckValue(&Dev_t->Dev, VL53L0X_CHECKENABLE_SIGNAL_RATE_FINAL_RANGE, (FixPoint1616_t)(0.1*65536));
    if (Status != VL53L0X_ERROR_NONE) return Status;
    Status = VL53L0X_SetMeasurementTimingBudgetMicroSeconds(&Dev_t->Dev, 20000);
    if (Status != VL53L0X_ERROR_NONE) return Status;
    Status = VL53L0X_SetVcselPulsePeriod(&Dev_t->Dev, VL53L0X_VCSEL_PERIOD_PRE_RANGE, 18);
    if (Status != VL53L0X_ERROR_NONE) return Status;
    Status = VL53L0X_SetVcselPulsePeriod(&Dev_t->Dev, VL53L0X_VCSEL_PERIOD_FINAL_RANGE, 14);

    Status = VL53L0X_SetDeviceAddress(&Dev_t->Dev, Dev_t->Address);
    Dev_t->Dev.I2cDevAddr = Dev_t->Address;
    osDelay(10);

    Dev_t->isInit = 1;
    return Status;


};

uint16_t Vl53l0x_ReadMeasure(Vl53l0x_HandlerStruct* Dev_t)
{
//		if (!Dev_t->isInit)
//		{
//			return -1;
//		}
        VL53L0X_PerformSingleRangingMeasurement(&Dev_t->Dev, &Dev_t->RangingData);
		if(Dev_t->RangingData.RangeStatus == 0)
		{
			return Dev_t->RangingData.RangeMilliMeter;
		}
        else return -1;
};
