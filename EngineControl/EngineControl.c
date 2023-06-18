/*
 * CarControl.c
 *
 *  Created on: Mar 12, 2021
 *      Author: vanti
 */
#include "EngineControl.h"

#include "main.h"


//uint16_t	Engine_SpeedMax = Speed_Max_Default;
//uint8_t		Engine_MoveStatus = 0;

int Engine_TimerConfig(Engine_HandlerStruct* Engine)
{
	Engine->PWM_TIM->Instance->PSC = 0;
	Engine->PWM_TIM->Instance->ARR = 9999;

	return HAL_TIM_PWM_Start(Engine->PWM_TIM, Engine->PWM_TIM_Channel);
}

int Engine_Init(Engine_HandlerStruct* Engine)
{
	Engine_TimerConfig(Engine);
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
		Engine_Brake(Engine);

	}
	else if (PulseVal > 0)
	{
		if((Engine->ForbidStatus & Engine_Forbid_Forward) == 0)
		{
			__HAL_TIM_SetCompare(Engine->PWM_TIM, Engine->PWM_TIM_Channel, PulseVal);
			GPIO_WritePin(Engine->BrakePin, !Engine_Brake_GPIOLevel);
			GPIO_WritePin(Engine->GasEnablePin, Engine_GasEn_GPIOLevel);
			GPIO_WritePin(Engine->DirectionPin, Engine_Forward_GPIOLevel);
			Engine->MoveState = Engine_MoveState_Forward;
		}
		else
		{
			Engine_Brake(Engine);
		}

	}
	else if(PulseVal < 0)
	{
		if((Engine->ForbidStatus & Engine_Forbid_Backward) == 0)
		{
			__HAL_TIM_SetCompare(Engine->PWM_TIM, Engine->PWM_TIM_Channel, -PulseVal);
			GPIO_WritePin(Engine->BrakePin, !Engine_Brake_GPIOLevel);
			GPIO_WritePin(Engine->GasEnablePin, Engine_GasEn_GPIOLevel);
			GPIO_WritePin(Engine->DirectionPin, !Engine_Forward_GPIOLevel);
			Engine->MoveState = Engine_MoveState_Backward;
		}
		else
		{
			Engine_Brake(Engine);
		}

	}
	return 0;
}

int Engine_Stop(Engine_HandlerStruct* Engine)
{
	__HAL_TIM_SetCompare(Engine->PWM_TIM, Engine->PWM_TIM_Channel, 0);
	GPIO_WritePin(Engine->BrakePin, Engine_Brake_GPIOLevel);
	GPIO_WritePin(Engine->GasEnablePin, !Engine_GasEn_GPIOLevel);
	GPIO_WritePin(Engine->DirectionPin, Engine_Forward_GPIOLevel);
	Engine->MoveState = Engine_MoveState_Stop;
	return 0;
}

//void Engine_AllowRun()
//{
//	LL_TIM_CC_EnableChannel(MotorTimer, MotorTimer_Channel);
//	LL_GPIO_SetOutputPin(Engine_Break_GPIO_Port, Engine_Break_Pin);
////	LL_mDelay()
//	LL_GPIO_ResetOutputPin(Engine_Break_GPIO_Port, Engine_Break_Pin);
//	LL_GPIO_ResetOutputPin(Gas_Enable_GPIO_Port, Gas_Enable_Pin);
//}

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
		Engine_Brake(Engine);
		Engine_SetSpeed(Engine, 0);
	}

	if((CurrentDir == Engine_MoveState_Backward) && ((Engine->ForbidStatus & Engine_Forbid_Backward) != 0))
	{
		Engine_Brake(Engine);
		Engine_SetSpeed(Engine, 0);

	}
//	printf("ForbidRun \r\n");
	return 0;
}




void Engine_Test(Engine_HandlerStruct* Engine)
{
//	for(uint16_t i = -Motor_MaxPWM; i < Motor_MaxPWM; i+= 100)
//	{
//		Engine_SetSpeed(i);
//		LL_mDelay(500);
//	}
//	for(uint16_t i = Motor_MaxPWM; i > -Motor_MaxPWM; i-= 100)
//	{
//		Engine_SetSpeed(i);
//		LL_mDelay(500);
//	}
}