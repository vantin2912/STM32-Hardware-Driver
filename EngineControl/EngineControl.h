/*
 * EngineControl.h
 *
 *  Created on: Mar 12, 2021
 *      Author: vanti
 */

#ifndef INC_EngineCONTROL_H_
#define INC_EngineCONTROL_H_


#include "main.h"
#include "SyncPrintf/SyncPrintf.h"
#include "GPIO/GPIOHandler.h"
//#define MotorTimer 				TIM8
//#define MotorTimer_Channel		LL_TIM_CHANNEL_CH1N
//#define Motor_MaxPWM			10000


/*
 * Engine MoveStatus
 * 		1 = ForbidMove
 * 		0 = AllowMove
 */
#ifdef USE_RTOS
#define Engine_Delay	osDelay
#define	Engine_printf	SyncPrintf
#else
#define Engine_Delay	HAL_Delay
#define	Engine_printf	printf

#endif

#define Engine_MoveState_Stop				0b00
#define Engine_MoveState_Forward			0b01
#define Engine_MoveState_Backward			0b11

#define	Engine_Forbid_Forward				0b00000001
#define Engine_Forbid_Backward				0b00000010
#define Engine_Forbid_ForAndBackward		0b00000011



#define	Engine_Brake_GPIOLevel				0
#define Engine_GasEn_GPIOLevel				1
#define Engine_Forward_GPIOLevel			0

#define Engine_TIM_MaxPulse			10000

typedef enum {
	ENGINE_BRAKE_SET,
	ENGINE_BRAKE_CLEAR
} Engine_Brake_State;

typedef struct Engine_HandlerStruct{
	TIM_HandleTypeDef* PWM_TIM;
	uint32_t 	PWM_TIM_Channel;

	GPIO_HandlerStruct DirectionPin;
	GPIO_HandlerStruct BrakePin;
	GPIO_HandlerStruct GasEnablePin;
	int16_t NegLimit, PosLimit;

	uint8_t ForbidStatus;
	uint8_t MoveState;
} Engine_HandlerStruct;



int Engine_Init(Engine_HandlerStruct* Engine, int16_t NegLimit, int16_t PosLimit);
int Engine_TimerInit(Engine_HandlerStruct* Engine);
int Engine_ConfigControlPin(Engine_HandlerStruct* Engine, GPIO_HandlerStruct BrakePin,
						GPIO_HandlerStruct DirectionPin, GPIO_HandlerStruct GasEnPin);
int Engine_ConfigTimer(Engine_HandlerStruct* Engine, TIM_HandleTypeDef* htim, uint32_t TIM_Channel);

int Engine_SetSpeed(Engine_HandlerStruct* Engine, int16_t PulseVal);

int Engine_Brake(Engine_HandlerStruct* Engine, Engine_Brake_State state);

int Engine_AllowRun(Engine_HandlerStruct* Engine, uint8_t Engine_Direction);
int Engine_ForbidRun(Engine_HandlerStruct* Engine, uint8_t Engine_Direction);


int Engine_inRange(Engine_HandlerStruct* Engine, int Val);

#endif /* INC_EngineCONTROL_H_ */
