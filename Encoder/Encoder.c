/*
 * Encoder.c
 *
 *  Created on: Mar 30, 2023
 *      Author: vanti
 */


#include "Encoder.h"
#include "string.h"

const osThreadAttr_t EncoderTask_attributes = {
  .name = "EncoderRead",
  .stack_size = 64 * 4,
  .priority = (osPriority_t) osPriorityHigh4,
};

void Encoder_Thread(void* arg)
{
	Encoder_HandlerStruct* Encoder = (Encoder_HandlerStruct*) arg;
	uint32_t startTime;
	int delayTime;
	while(1)
	{
		if(Encoder->isEnable)
		{
			HAL_TIM_Encoder_Stop(Encoder->EncoderTIM, TIM_CHANNEL_ALL);
			osThreadSuspend(Encoder->readTh);
		}
		startTime = osKernelGetTickCount();
		Encoder_Run(Encoder);
		delayTime = Encoder->interval - (osKernelGetTickCount() - startTime);
		osDelay(delayTime);
	}
}
void Encoder_Init(Encoder_HandlerStruct* Encoder, TIM_HandleTypeDef* EncTIM, float LPF_Beta, uint32_t interval)
{
	memset(Encoder,0, sizeof(Encoder_HandlerStruct));
	Encoder->readTh = osThreadNew(Encoder_Thread, Encoder, &EncoderTask_attributes);
	Encoder->EncLock = osMutexNew(NULL);
	Encoder->LPF_Beta = LPF_Beta;
	Encoder->interval = interval;
	Encoder->EncoderTIM = EncTIM;
}



void Encoder_Start(Encoder_HandlerStruct* Encoder, uint8_t State)
{
	Encoder->isEnable = State;
	if(State)
	{
		HAL_TIM_Encoder_Start(Encoder->EncoderTIM, TIM_CHANNEL_ALL);
		osThreadResume(Encoder->readTh);
	}
}


float Encoder_GetCount(Encoder_HandlerStruct* Encoder)
{
	osMutexAcquire(Encoder->EncLock, 2);
	float cnt = Encoder->CurrentCnt;
	osMutexRelease(Encoder->EncLock);

	return cnt;
}



void Encoder_Run(Encoder_HandlerStruct* Encoder)
{
	int16_t Cnt = Encoder->EncoderTIM->Instance->CNT;
	osMutexAcquire(Encoder->EncLock, 0);
	Encoder->CurrentCnt = Cnt;
	Encoder->CurrentSpd -= Encoder->LPF_Beta*(Encoder->CurrentSpd - Cnt);
	Encoder->EncoderTIM->Instance->CNT = 0;
	if(Encoder->EnCntTraveled)
	{
		Encoder->Travelled += Encoder->CurrentCnt;
	}
	osMutexRelease(Encoder->EncLock);
}


float Encoder_GetSpeed_PPS(Encoder_HandlerStruct* Encoder)
{
	return (Encoder_GetCount(Encoder)/Encoder->interval) * 1000; // Pulse Per Sec
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
	osMutexAcquire(Encoder->EncLock, 2);
	float travelled = Encoder->Travelled;
	osMutexRelease(Encoder->EncLock);
	return travelled;
}



