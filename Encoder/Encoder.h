/*
 * Encoder.h
 *
 *  Created on: Mar 30, 2023
 *      Author: vanti
 */

#ifndef ENCODERHANDLER_ENCODER_H_
#define ENCODERHANDLER_ENCODER_H_
#include "main.h"
#include "cmsis_os.h"
typedef struct Encoder_HandlerStruct
{
	TIM_HandleTypeDef* EncoderTIM;
	uint32_t interval;
	float CurrentCnt;
	float CurrentSpd;
	uint32_t PulsePerMeter;
	uint8_t EnCntTraveled;
	int Travelled;
	float LPF_Beta;

	osThreadId_t readTh;

	uint8_t isEnable;
	osMutexId_t EncLock;
}Encoder_HandlerStruct;

void Encoder_Init(Encoder_HandlerStruct* Encoder, TIM_HandleTypeDef* EncTIM, float LPF_Beta, uint32_t interval);
void Encoder_Start(Encoder_HandlerStruct* Encoder, uint8_t State);
void Encoder_Run(Encoder_HandlerStruct* Encoder);

float Encoder_GetCount(Encoder_HandlerStruct* Encoder);
float Encoder_GetSpeed_PPS(Encoder_HandlerStruct* Encoder);
float Encoder_GetSpeed_MPS(Encoder_HandlerStruct* Encoder);

void Encoder_startTravelled(Encoder_HandlerStruct* Encoder);
void Encoder_clearTravelled(Encoder_HandlerStruct* Encoder);

float Encoder_getTravelled(Encoder_HandlerStruct* Encoder);


#endif /* ENCODERHANDLER_ENCODER_H_ */
