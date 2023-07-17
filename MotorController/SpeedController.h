/*
 * PIDController.h
 *
 *  Created on: Jul 5, 2023
 *      Author: vanti
 */

#ifndef MOTORCONTROLLER_SPEEDCONTROLLER_H_
#define MOTORCONTROLLER_SPEEDCONTROLLER_H_


#include "Encoder/Encoder.h"
#include <EngineControl/EngineControl.h>
#include "string.h"
#include "cmsis_os.h"

typedef struct SpeedControler_HandlerStruct
{
	Encoder_HandlerStruct* Encoder;
	Engine_HandlerStruct* Engine;

	float Kp, Ki, Kd;
	uint32_t dt;

	float SetPoint;
	float Prev_Error;
	float Integration_Error;

	float PulsePerMeter;

	osThreadId_t RunTh;
	uint8_t isEnable;
}SpeedControler_HandlerStruct;

void SpeedController_Init(SpeedControler_HandlerStruct* Controller, Encoder_HandlerStruct *Encoder, Engine_HandlerStruct *Engine, uint32_t interval);

void SpeedController_Start(SpeedControler_HandlerStruct* Controller, uint8_t State);

void SpeedController_Run(SpeedControler_HandlerStruct* Controller);
void SpeedController_ClearErr(SpeedControler_HandlerStruct* Controller);
void SpeedController_SetSpeed(SpeedControler_HandlerStruct* Controller, float newSpeed);
float SpeedController_GetSpeed(SpeedControler_HandlerStruct* Controller);
void SpeedController_SetTunings(SpeedControler_HandlerStruct* Controller, float Kp, float Ki, float Kd);
#endif /* MOTORCONTROLLER_SPEEDCONTROLLER_H_ */
