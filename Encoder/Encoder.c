/*
 * Encoder.c
 *
 *  Created on: Mar 30, 2023
 *      Author: vanti
 */


#include "Encoder.h"



void Encoder_Start(Encoder_HandlerStruct* Encoder)
{
	Encoder_configPeriod(Encoder);

	HAL_TIM_Encoder_Start(Encoder->EncoderTIM, Encoder->Encoder_Channel);
	HAL_TIM_Base_Start_IT(Encoder->ReadTIM);
}

float Encoder_GetCount(Encoder_HandlerStruct* Encoder)
{
	return Encoder->CurrentCnt;
}

void Encoder_Run(Encoder_HandlerStruct* Encoder)
{
	int16_t Cnt = Encoder->EncoderTIM->Instance->CNT;
	Encoder->CurrentCnt = Cnt;
	Encoder->CurrentSpd -= Encoder->LPF_Beta*(Encoder->CurrentSpd - Cnt);
	Encoder->EncoderTIM->Instance->CNT = 0;
	if(Encoder->EnCntTraveled)
	{
		Encoder->Travelled += Encoder->CurrentCnt;
	}
}


float Encoder_GetSpeed_PPS(Encoder_HandlerStruct* Encoder)
{
	return ((float)Encoder->CurrentCnt/Encoder->Period) * 1000; // Pulse Per Sec
}

float Encoder_GetSpeed_MPS(Encoder_HandlerStruct* Encoder)
{
	return Encoder_GetSpeed_PPS(Encoder)/ Encoder->PulsePerMeter;
}

void Encoder_startTravelled(Encoder_HandlerStruct* Encoder)
{
	Encoder->EnCntTraveled = 1;
}
void Encoder_clearTravelled(Encoder_HandlerStruct* Encoder)
{
	Encoder->EnCntTraveled = 0;
	Encoder->Travelled = 0;
}

float Encoder_getTravelled(Encoder_HandlerStruct* Encoder)
{
	return (float) Encoder->Travelled;
}

void Encoder_configPeriod(Encoder_HandlerStruct* Encoder)
{
	TIM_TypeDef* TIM = Encoder->ReadTIM->Instance;
	TIM->ARR = Encoder->Period * 10 - 1;
	TIM->PSC = 8399;
}


