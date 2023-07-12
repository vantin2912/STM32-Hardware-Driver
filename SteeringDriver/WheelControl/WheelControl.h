/*
 * WheelControl.h
 *
 *  Created on: Aug 23, 2022
 *      Author: vanti
 */

#ifndef WHEELCONTROL_H_
#define WHEELCONTROL_H_
#include "main.h"
#include "SteeringDriver/eziservov8_lib/EziservoV8/FAS_EziMOTIONPlusR.h"


#define Angle2Pulse(Ang) (Ang*12000.0)
#define Pulse2Angle(Pulse) (Pulse/12000.0)

#define Wheel_MaxVeloPul	100000
//#define Wheel_MaxVeloPul	100000

//#define Wheel_StableVelPul	80000
#define Wheel_StableVelPul	50000


#define Wheel_MaxAngle 			25									// 		Degree
#define Wheel_MaxSpeed			Pulse2Angle(Wheel_MaxVeloPul)		//		Degree/sec
#define Wheel_AccTime			1000								//		msec
#define Wheel_DecTime			1000								//		msec



typedef enum Wheel_Error
{
	Wheel_OK,
	Wheel_Failed,
	Wheel_Timeout
} Wheel_Error;

typedef enum Wheel_Mode
{
	WHEEL_CMD_MODE,
	WHEEL_BTN_MODE,
} Wheel_Mode;

typedef struct Wheel_HandlerStruct
{
	FAS_HandlerStruct EziHandler ;
	uint8_t devID;
	float letfLimit, RightLimit;
	uint8_t Mode;
} Wheel_HandlerStruct;


uint8_t Wheel_Init(Wheel_HandlerStruct* WheelHandler, UART_OS_HandlerStruct* uart);
uint8_t Wheel_setLimit(Wheel_HandlerStruct* WheelHandler, float LeftLimit, float RightLimit);
uint8_t Wheel_Start(Wheel_HandlerStruct* WheelHandler);
uint8_t Wheel_Stop(Wheel_HandlerStruct* WheelHandler);

uint8_t Wheel_ChangeMode(Wheel_HandlerStruct* SteerWheel, Wheel_Mode mode);

uint8_t Wheel_SetAngle_ABS(Wheel_HandlerStruct* WheelHandler, float Angle);
uint8_t Wheel_SetAngle_INC(Wheel_HandlerStruct* WheelHandler, float Angle);

uint8_t Wheel_SetAngleEx_ABS(Wheel_HandlerStruct* WheelHandler, float Angle, uint16_t AccTime, uint16_t DecTime);
uint8_t Wheel_SetAngleEx_INC(Wheel_HandlerStruct* WheelHandler, float Angle, uint16_t AccTime, uint16_t DecTime);

uint8_t Wheel_ClearPos(Wheel_HandlerStruct* WheelHandler);
uint8_t Wheel_MoveOrigin(Wheel_HandlerStruct* WheelHandler);
uint8_t Wheel_Move2Limit(Wheel_HandlerStruct* WheelHandler, uint8_t Limit);

uint8_t Wheel_EmergencyStop(Wheel_HandlerStruct* WheelHandler);
uint8_t Wheel_MoveStop(Wheel_HandlerStruct* WheelHandler);
uint8_t Wheel_MovePause(Wheel_HandlerStruct* WheelHandler);

uint8_t Wheel_SetActualPos(Wheel_HandlerStruct* WheelHandler, float ActualPos);
uint8_t Wheel_GetActualPos(Wheel_HandlerStruct* WheelHandler, float* ActualPos);
uint8_t Wheel_SetCommandPos(Wheel_HandlerStruct* WheelHandler, float CmdPos);
uint8_t Wheel_GetCommandPos(Wheel_HandlerStruct* WheelHandler, float* CmdPos);

uint8_t Wheel_GetPosErr(Wheel_HandlerStruct* WheelHandler, float* PosErr);
uint8_t Wheel_GetActualVel(Wheel_HandlerStruct* WheelHandler, float Vel);

uint8_t Wheel_GetMotionStatus(Wheel_HandlerStruct* WheelHandler);
uint8_t Wheel_GetAllStatus(Wheel_HandlerStruct* WheelHandler);
uint8_t Wheel_ClearError(Wheel_HandlerStruct* WheelHandler);


#endif /* WHEELCONTROL_H_ */
