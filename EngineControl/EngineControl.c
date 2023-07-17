/*
 * CarControl.c
 *
 *  Created on: Mar 12, 2021
 *      Author: vanti
 */
#include <EngineControl/EngineControl.h>
#include "main.h"
#include "string.h"

//uint16_t	Engine_SpeedMax = Speed_Max_Default;
//uint8_t		Engine_MoveStatus = 0;

int Engine_ConfigTimer(Engine_HandlerStruct* Engine, TIM_HandleTypeDef* htim, uint32_t TIM_Channel)
{
	Engine->PWM_TIM_Channel = TIM_Channel;
	Engine->PWM_TIM = htim;
	Engine->PWM_TIM->Instance->PSC = 0;
	Engine->PWM_TIM->Instance->ARR = HAL_RCC_GetHCLKFreq()/Engine_TIM_MaxPulse - 1;

	return HAL_TIM_PWM_Start(Engine->PWM_TIM, Engine->PWM_TIM_Channel);
}

int Engine_ConfigControlPin(Engine_HandlerStruct* Engine, GPIO_HandlerStruct BrakePin, GPIO_HandlerStruct DirectionPin, GPIO_HandlerStruct GasEnPin)
{
	Engine->BrakePin = BrakePin;
	Engine->DirectionPin = DirectionPin;
	Engine->GasEnablePin = GasEnPin;
	return 0;
}

int Engine_Init(Engine_HandlerStruct* Engine, int16_t NegLimit, int16_t PosLimit)
{
	memset(Engine,0,sizeof(Engine_HandlerStruct));
	Engine->NegLimit = NegLimit;
	Engine->PosLimit = PosLimit;

	return 0;
}

int Engine_SetSpeed(Engine_HandlerStruct* Engine, int16_t PulseVal)
{

	if(PulseVal > Engine->PosLimit)
	{
		PulseVal = Engine->PosLimit;
	}else if(PulseVal < Engine->NegLimit)
	{
		PulseVal = Engine->NegLimit;
	}
	if (PulseVal == 0)
	{
		Engine_Brake(Engine, ENGINE_BRAKE_SET);

	}
	else if (PulseVal > 0)
	{
		if((Engine->ForbidStatus & Engine_Forbid_Forward) == 0)
		{
			__HAL_TIM_SetCompare(Engine->PWM_TIM, Engine->PWM_TIM_Channel, PulseVal);
			Engine_Brake(Engine, ENGINE_BRAKE_CLEAR);
			GPIO_WritePin(Engine->DirectionPin, Engine_Forward_GPIOLevel);
			Engine->MoveState = Engine_MoveState_Forward;
		}
		else
		{
			Engine_Brake(Engine, ENGINE_BRAKE_SET);
		}

	}
	else if(PulseVal < 0)
	{
		if((Engine->ForbidStatus & Engine_Forbid_Backward) == 0)
		{
			__HAL_TIM_SetCompare(Engine->PWM_TIM, Engine->PWM_TIM_Channel, -PulseVal);
			Engine_Brake(Engine, ENGINE_BRAKE_CLEAR);
			GPIO_WritePin(Engine->DirectionPin, !Engine_Forward_GPIOLevel);
			Engine->MoveState = Engine_MoveState_Backward;
		}
		else
		{
			Engine_Brake(Engine, ENGINE_BRAKE_SET);
		}

	}
	return 0;
}

int Engine_Brake(Engine_HandlerStruct* Engine, Engine_Brake_State State)
{
	if (State == ENGINE_BRAKE_SET)
	{
		__HAL_TIM_SetCompare(Engine->PWM_TIM, Engine->PWM_TIM_Channel, 0);
		GPIO_WritePin(Engine->BrakePin, Engine_Brake_GPIOLevel);
		GPIO_WritePin(Engine->GasEnablePin, !Engine_GasEn_GPIOLevel);
		Engine->MoveState = Engine_MoveState_Stop;
	}
	else
	{
		GPIO_WritePin(Engine->BrakePin, !Engine_Brake_GPIOLevel);
		GPIO_WritePin(Engine->GasEnablePin, Engine_GasEn_GPIOLevel);
	}

	return 0;
}

int Engine_AllowRun(Engine_HandlerStruct* Engine, uint8_t Engine_Direction)
{
	CLEAR_BIT(Engine->ForbidStatus, Engine_Direction);
	return 0;
}

int Engine_GetMoveDir(Engine_HandlerStruct* Engine)
{
	return Engine->MoveState;
}

int Engine_ForbidRun(Engine_HandlerStruct* Engine, uint8_t Engine_Direction)
{
	SET_BIT(Engine->ForbidStatus,Engine_Direction);
	uint8_t CurrentDir = Engine_GetMoveDir(Engine);
	if((CurrentDir == Engine_MoveState_Forward) && ((Engine->ForbidStatus & Engine_Forbid_Forward) != 0))
	{
		Engine_Brake(Engine, ENGINE_BRAKE_SET);
		Engine_SetSpeed(Engine, 0);
	}

	if((CurrentDir == Engine_MoveState_Backward) && ((Engine->ForbidStatus & Engine_Forbid_Backward) != 0))
	{
		Engine_Brake(Engine, ENGINE_BRAKE_SET);
		Engine_SetSpeed(Engine, 0);

	}
//	printf("ForbidRun \r\n");
	return 0;
}

int Engine_inRange(Engine_HandlerStruct* Engine, int Val)
{
	return (Val > Engine->NegLimit) && (Val < Engine->PosLimit);
}
