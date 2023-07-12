/*
 * PowerControl.h
 *
 *  Created on: Jun 28, 2023
 *      Author: vanti
 */

#ifndef POWERCONTROL_POWERCONTROL_H_
#define POWERCONTROL_POWERCONTROL_H_

#include "GPIO/GPIOHandler.h"
#include "INA219/INA219.h"
#include "cmsis_os.h"
#include "main.h"
#include "string.h"

#define POWERCONTROL_ENABLE_GPIOLEVEL			GPIO_PIN_SET
#define POWERCONTROL_VOLTAGE_DEFAULT_THRES 		14000
#define POWERCONTROL_CURRENT_DEFAULT_THRES		1000

typedef struct PowerControl_HandlerStruct{
	GPIO_HandlerStruct ctrlPin;
	INA219_t* ina219;
	uint32_t checkInterval;

	uint8_t isEnableRead;
	osThreadId_t readThread;

	int VoltageThres;
	int CurrentThres;
}PowerControl_HandlerStruct;

typedef enum {
	POWER_DISABLE,
	POWER_ENABLE
}PowerControl_State;

int PowerControl_Init(PowerControl_HandlerStruct* pwrHandler, INA219_t* ina219, GPIO_HandlerStruct srrPin, uint32_t checkInterval);
int PowerControl_setThreshold(PowerControl_HandlerStruct* pwrHandler, int VoltageThres, int CurrentThres);

int PowerControl_enableControl(PowerControl_HandlerStruct* pwrHandler, PowerControl_State State);
int PowerControl_setState(PowerControl_HandlerStruct* pwrHandler, PowerControl_State State);

#endif /* POWERCONTROL_POWERCONTROL_H_ */
