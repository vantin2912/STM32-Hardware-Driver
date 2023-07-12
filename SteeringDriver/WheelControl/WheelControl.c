/*
 * WheelControl.c
 *
 *  Created on: Aug 23, 2022
 *      Author: vanti
 */

#include "WheelControl.h"

//#define nPortNo 0
#define FAS_MaxRcvByte	100

uint8_t FAS_Send(FAS_HandlerStruct* Port, uint8_t* SendBuffer, uint8_t Len)
{

    int Status = HAL_ERROR;
	Status = UART_OS_Transmit(Port->uart, SendBuffer, Len);
	if(Status !=  osOK)
	{
		SyncPrintf("EZI UART Transmit Error \r\n");
		return FMC_TIMEOUT_ERROR;

	}
	return FMM_OK;

}

uint8_t FAS_Receive(FAS_HandlerStruct* Port, uint8_t* RcvBuffer, uint8_t* RxLen)
{
	int Status = 0;
	Status = UART_OS_Receive_ToIdle(Port->uart, RcvBuffer,(uint16_t*) RxLen, FAS_MaxRcvByte, 100);
//	Status = HAL_UARTEx_ReceiveToIdle(&EZI_UART, RcvBuffer, 255, (uint16_t*)RxLen, 1000);
	if(Status == HAL_TIMEOUT)
	{
		SyncPrintf("Rcv Timeout \r\n");
		return FMC_TIMEOUT_ERROR;
	}
	else
	{
	}

	if(Status != osOK)
		return FMC_TIMEOUT_ERROR;
	else
		return FMM_OK;
}
uint8_t FAS_Lock(FAS_HandlerStruct* nPortNo, uint32_t timeout)
{
	return osMutexAcquire(nPortNo->uartLock, timeout);
}
uint8_t FAS_Unlock(FAS_HandlerStruct* nPortNo)
{
	return osMutexRelease(nPortNo->uartLock);
}
uint8_t FAS_Init(FAS_HandlerStruct* nPortNo)
{
	nPortNo->uartLock = osMutexNew(NULL);
	return 0;
}

uint8_t Wheel_Init(Wheel_HandlerStruct* SteerWheel, UART_OS_HandlerStruct* uart)
{
	SteerWheel->EziHandler.uart = uart;
	FAS_Init(&SteerWheel->EziHandler);

	Wheel_setLimit(SteerWheel, 25, 25);
	Wheel_ClearPos(SteerWheel);

	return Wheel_OK;
}
uint8_t Wheel_setLimit(Wheel_HandlerStruct* SteerWheel, float LeftLimit, float RightLimit)
{
	SteerWheel->RightLimit = RightLimit;
	SteerWheel->letfLimit = LeftLimit;
	return Wheel_OK;
}
uint8_t Wheel_Start(Wheel_HandlerStruct* SteerWheel)
{
	uint8_t Status;
	Status = FAS_ServoAlarmReset(&SteerWheel->EziHandler, SteerWheel->devID);

	if(Status != FMM_OK) return Wheel_Failed;
	Status = FAS_ServoEnable(&SteerWheel->EziHandler, SteerWheel->devID, 1);

	if(Status != FMM_OK) return Wheel_Failed;

	return Wheel_OK;
}

uint8_t Wheel_Stop(Wheel_HandlerStruct* SteerWheel)
{
	uint8_t Status;
	Status = FAS_MoveStop(&SteerWheel->EziHandler, SteerWheel->devID);
	if(Status != FMM_OK) return Wheel_Failed;
	FAS_ServoEnable(&SteerWheel->EziHandler, SteerWheel->devID, 1);
	if(Status != FMM_OK) return Wheel_Failed;

	return Wheel_OK;
}

uint8_t Wheel_ChangeMode(Wheel_HandlerStruct* SteerWheel, Wheel_Mode mode)
{
	return FAS_SetInputAssignMap(&SteerWheel->EziHandler, SteerWheel->devID, 7, 18, mode);
}


uint8_t Wheel_SetAngle_ABS(Wheel_HandlerStruct* SteerWheel, float Angle)
{
	int32_t Pos = Angle2Pulse(Angle);
	uint32_t Vel = Wheel_MaxVeloPul;
	uint8_t Status =0;
	EZISERVO_AXISSTATUS AxisStatus ={0};

	Status = FAS_GetAxisStatus(&SteerWheel->EziHandler, SteerWheel->devID,(uint32_t*) &AxisStatus);
	if(Status != FMM_OK) return Wheel_Failed;
	if(AxisStatus.FFLAG_MOTIONING == 1)
	{
		Status = FAS_PositionAbsOverride(&SteerWheel->EziHandler, SteerWheel->devID, Pos);
	}else
	{
		Status = FAS_MoveSingleAxisAbsPos(&SteerWheel->EziHandler, SteerWheel->devID, Pos, Vel);
	}

	if(Status != FMM_OK) return Wheel_Failed;

	return Wheel_OK;
}
uint8_t Wheel_SetAngle_INC(Wheel_HandlerStruct* SteerWheel, float Angle)
{
	int32_t Pos = -Angle2Pulse(Angle);
	uint32_t Vel = Wheel_StableVelPul;
	uint8_t Status =0;
	EZISERVO_AXISSTATUS AxisStatus= {0};

	Status = FAS_GetAxisStatus(&SteerWheel->EziHandler, SteerWheel->devID,(uint32_t*) &AxisStatus);

	if(Status != FMM_OK) return Wheel_Failed;
	if(AxisStatus.FFLAG_MOTIONING == 1)
	{
		Status = FAS_PositionIncOverride(&SteerWheel->EziHandler, SteerWheel->devID, Pos);
		SyncPrintf("Pos Override \r\n");
	}else
	{
		SyncPrintf("Axis Inc \r\n");
		Status = FAS_MoveSingleAxisIncPos(&SteerWheel->EziHandler, SteerWheel->devID, Pos, Vel);
	}
	if(Status != FMM_OK) return Wheel_Failed;

	return Wheel_OK;
}

uint8_t Wheel_SetAngleEx_ABS(Wheel_HandlerStruct* SteerWheel, float Angle, uint16_t AccTime, uint16_t DecTime)
{
	int32_t Pos = -Angle2Pulse(Angle);
//	uint32_t Vel = Wheel_MaxVeloPul;
	uint32_t Vel = Wheel_StableVelPul;

	uint8_t Status =0;
	EZISERVO_AXISSTATUS AxisStatus = {0};
	MOTION_OPTION_EX PosOption;
	PosOption.wCustomAccelTime = AccTime;
	PosOption.wCustomDecelTime = DecTime;
	PosOption.flagOption.BIT_USE_CUSTOMACCEL = AccTime > 0;
	PosOption.flagOption.BIT_USE_CUSTOMDECEL = DecTime > 0;
	Status = FAS_GetAxisStatus(&SteerWheel->EziHandler, SteerWheel->devID,(uint32_t*) &AxisStatus);
	if(Status != FMM_OK) return Wheel_Failed;
	if(AxisStatus.FFLAG_MOTIONING == 1)
	{
		Status = FAS_PositionAbsOverride(&SteerWheel->EziHandler, SteerWheel->devID, Pos);
	}else
	{
		Status = FAS_MoveSingleAxisAbsPosEx(&SteerWheel->EziHandler, SteerWheel->devID, Pos, Vel, &PosOption);
	}

	if(Status != FMM_OK) return Wheel_Failed;

	return Wheel_OK;
}

uint8_t Wheel_SetAngleEx_INC(Wheel_HandlerStruct* SteerWheel, float Angle, uint16_t AccTime, uint16_t DecTime)
{
	int32_t Pos = Angle2Pulse(Angle);
	uint32_t Vel = Wheel_StableVelPul;
	uint8_t Status =0;
	EZISERVO_AXISSTATUS AxisStatus ={0};
	MOTION_OPTION_EX PosOption;
	PosOption.wCustomAccelTime = AccTime;
	PosOption.wCustomDecelTime = DecTime;
	PosOption.flagOption.BIT_USE_CUSTOMACCEL = AccTime > 0;
	PosOption.flagOption.BIT_USE_CUSTOMDECEL = DecTime > 0;
	Status = FAS_GetAxisStatus(&SteerWheel->EziHandler, SteerWheel->devID,(uint32_t*) &AxisStatus);
	if(Status != FMM_OK) return Wheel_Failed;
	if(AxisStatus.FFLAG_MOTIONING == 1)
	{
		Status = FAS_PositionIncOverride(&SteerWheel->EziHandler, SteerWheel->devID, Pos);
//		SyncPrintf("Pos Override Status 0x%.2x \r\n", Status);

	}else
	{
//		SyncPrintf("Axis Inc \r\n");
		Status = FAS_MoveSingleAxisIncPosEx(&SteerWheel->EziHandler, SteerWheel->devID, Pos, Vel, &PosOption);
	}

	if(Status != FMM_OK) return Wheel_Failed;

	return Wheel_OK;
}

uint8_t Wheel_ClearPos(Wheel_HandlerStruct* SteerWheel)
{
	uint8_t Status = FAS_ClearPosition(&SteerWheel->EziHandler, SteerWheel->devID);
	if(Status != FMM_OK) return Wheel_Failed;
	return Wheel_OK;
}
uint8_t Wheel_MoveOrigin(Wheel_HandlerStruct* SteerWheel);
uint8_t Wheel_Move2Limit(Wheel_HandlerStruct* SteerWheel, uint8_t Limit);

uint8_t Wheel_EmergencyStop(Wheel_HandlerStruct* SteerWheel);
uint8_t Wheel_MoveStop(Wheel_HandlerStruct* SteerWheel);
uint8_t Wheel_MovePause(Wheel_HandlerStruct* SteerWheel);

uint8_t Wheel_SetActualPos(Wheel_HandlerStruct* SteerWheel, float ActualPos);
uint8_t Wheel_GetActualPos(Wheel_HandlerStruct* SteerWheel, float* ActualPos);
uint8_t Wheel_SetCommandPos(Wheel_HandlerStruct* SteerWheel, float CmdPos);
uint8_t Wheel_GetCommandPos(Wheel_HandlerStruct* SteerWheel, float* CmdPos)
{
	int32_t CmdPulsePos = 0;

	int CommStatus =  FAS_GetCommandPos(&SteerWheel->EziHandler, SteerWheel->devID, &CmdPulsePos);
	if(CommStatus == FMM_OK)
	{
		*CmdPos = Pulse2Angle(CmdPulsePos);
		return Wheel_OK;
	}
	return Wheel_Failed;

}

uint8_t Wheel_GetPosErr(Wheel_HandlerStruct* SteerWheel, float* PosErr);
uint8_t Wheel_GetActualVel(Wheel_HandlerStruct* SteerWheel, float Vel);

uint8_t Wheel_GetMotionStatus(Wheel_HandlerStruct* SteerWheel);
uint8_t Wheel_GetAllStatus(Wheel_HandlerStruct* SteerWheel);
uint8_t Wheel_ClearError(Wheel_HandlerStruct* SteerWheel);

