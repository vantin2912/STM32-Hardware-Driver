/*
 * PowerControl.c
 *
 *  Created on: Jun 28, 2023
 *      Author: vanti
 */

#include <PowerControl/PowerControl.h>

const osThreadAttr_t pwerReadTh_attributes = {
  .name = "pwrReadTh",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityRealtime,
};

void PowerControl_Task(void* arg)
{
	PowerControl_HandlerStruct* pwrHandler = (PowerControl_HandlerStruct*) arg;
	int Current, Voltage;
	while(1)
	{
		if(!pwrHandler->isEnableRead)
		{
			osThreadSuspend(pwrHandler->readThread);
		}
		Current = INA219_ReadCurrent(pwrHandler->ina219);
		Voltage = INA219_ReadBusVoltage(pwrHandler->ina219);
		if((pwrHandler->CurrentThres != 0) && (Current > pwrHandler->CurrentThres))
		{
			PowerControl_setState(pwrHandler, POWER_DISABLE);

		}
		else if((pwrHandler->VoltageThres != 0) && (Voltage > pwrHandler->VoltageThres))
		{
			PowerControl_setState(pwrHandler, POWER_DISABLE);
		}else
		{
			PowerControl_setState(pwrHandler, POWER_ENABLE);
		}
		osDelay(pwrHandler->checkInterval);
	}
}

int PowerControl_Init(PowerControl_HandlerStruct* pwrHandler, INA219_t* ina219, GPIO_HandlerStruct ctrlPin, uint32_t checkInterval)
{
	memset(pwrHandler, 0, sizeof(PowerControl_HandlerStruct));
	pwrHandler->ctrlPin = ctrlPin;
	pwrHandler->ina219 = ina219;
	pwrHandler->checkInterval = checkInterval;
	pwrHandler->readThread = osThreadNew(PowerControl_Task, pwrHandler, &pwerReadTh_attributes);
	pwrHandler->isEnableRead = 1;
	return 0;
}
int PowerControl_setThreshold(PowerControl_HandlerStruct* pwrHandler, int VoltageThres, int CurrentThres)
{
	pwrHandler->CurrentThres = CurrentThres;
	pwrHandler->VoltageThres = VoltageThres;
	return 0;
}
int PowerControl_enableControl(PowerControl_HandlerStruct* pwrHandler, PowerControl_State State)
{
	pwrHandler->isEnableRead = State;
	if(pwrHandler->isEnableRead)
	{
		osThreadResume(pwrHandler->readThread);
	}
	return 0;
}

int PowerControl_setState(PowerControl_HandlerStruct* pwrHandler, PowerControl_State State)
{
	switch (State) {
		case POWER_DISABLE:
			GPIO_WritePin(pwrHandler->ctrlPin, !POWERCONTROL_ENABLE_GPIOLEVEL);
			return 0;
		case POWER_ENABLE:
			GPIO_WritePin(pwrHandler->ctrlPin, POWERCONTROL_ENABLE_GPIOLEVEL);
			return 0;
	}
	return 0;
}

