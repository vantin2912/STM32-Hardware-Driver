#include "FAS_EziMOTIONPlusR.h"
#include <string.h>
#if USE_FAS_MoveStop == 1
int FAS_MoveStop(FAS_HandlerStruct* nPortNo, uint8_t iSlaveNo)
{
    const uint8_t FrameType = 0x31;
    const uint8_t SendDataLen = 0;
    const uint8_t RcvDataLen = 1;
    uint8_t ComStatus;
    uint8_t* SendBuffer = (uint8_t*)malloc(15 + SendDataLen);
    uint8_t SendLen;
    uint8_t* RcvBuffer = (uint8_t*)malloc(15 + RcvDataLen);
    uint8_t RcvLen;
    uint8_t* RespData = (uint8_t*)malloc(RcvDataLen + 2);
	uint8_t RespDataLen;

    uint8_t SyncByte = FAS_PackData(iSlaveNo, FrameType, NULL, 0, SendBuffer, &SendLen);
    FAS_Send(nPortNo, SendBuffer, SendLen);
    free(SendBuffer);


    ComStatus = FAS_Receive(nPortNo, RcvBuffer, &RcvLen);
	ComStatus = FAS_UnPackData(RcvBuffer, RcvLen, iSlaveNo, SyncByte, FrameType, RespData, &RespDataLen);
	if(ComStatus != FMM_OK) return ComStatus;

	if(RespDataLen != RcvDataLen)
	{
		free(RcvBuffer);
		free(RespData);
		return FMM_UNKNOWN_ERROR;
	}

	ComStatus = RespData[0];
	free(RcvBuffer);
	free(RespData);
	return ComStatus;
}
#endif

#if USE_FAS_EmergencyStop == 1
int FAS_EmergencyStop(FAS_HandlerStruct* nPortNo, uint8_t iSlaveNo)
{
    const uint8_t FrameType = 0x32;
    const uint8_t SendDataLen = 0;
    const uint8_t RcvDataLen = 1;
    uint8_t ComStatus;

    uint8_t* SendBuffer = (uint8_t*)malloc(15 + SendDataLen);
    uint8_t SendLen;
    uint8_t* RcvBuffer = (uint8_t*)malloc(15 + RcvDataLen);
    uint8_t RcvLen;
    uint8_t* RespData = (uint8_t*)malloc(RcvDataLen + 2);
	uint8_t RespDataLen;

    uint8_t SyncByte = FAS_PackData(iSlaveNo, FrameType, NULL, 0, SendBuffer, &SendLen);
    FAS_Send(nPortNo, SendBuffer, SendLen);
    free(SendBuffer);


    ComStatus = FAS_Receive(nPortNo, RcvBuffer,&RcvLen);
	ComStatus = FAS_UnPackData(RcvBuffer, RcvLen, iSlaveNo, SyncByte, FrameType, RespData, &RespDataLen);
	if(ComStatus != FMM_OK) return ComStatus;

	if(RespDataLen != RcvDataLen)
	{
		free(RcvBuffer);
		free(RespData);
		return FMM_UNKNOWN_ERROR;
	}

	ComStatus = RespData[0];
	free(RcvBuffer);
	free(RespData);
	return ComStatus;
}
#endif

#if USE_FAS_MovePause == 1
int FAS_MovePause(FAS_HandlerStruct* nPortNo, uint8_t iSlaveNo, uint8_t bPause)
{
    const uint8_t FrameType = 0x33;
    const uint8_t SendDataLen = 1;
    const uint8_t RcvDataLen = 1;
    uint8_t ComStatus;

    uint8_t* SendBuffer = (uint8_t*)malloc(15 + SendDataLen);
    uint8_t SendLen;
    uint8_t* RcvBuffer = (uint8_t*)malloc(15 + RcvDataLen);
    uint8_t RcvLen;
    uint8_t* RespData = (uint8_t*)malloc(RcvDataLen + 2);
	uint8_t RespDataLen;

    uint8_t SyncByte = FAS_PackData(iSlaveNo, FrameType, &bPause, SendDataLen, SendBuffer, &SendLen);
    FAS_Send(nPortNo, SendBuffer, SendLen);
    free(SendBuffer);


    ComStatus = FAS_Receive(nPortNo, RcvBuffer,&RcvLen);
	ComStatus = FAS_UnPackData(RcvBuffer, RcvLen, iSlaveNo, SyncByte, FrameType, RespData, &RespDataLen);
	if(ComStatus != FMM_OK) return ComStatus;

	if(RespDataLen != RcvDataLen)
	{
		free(RcvBuffer);
		free(RespData);
		return FMM_UNKNOWN_ERROR;
	}

	ComStatus = RespData[0];
	free(RcvBuffer);
	free(RespData);
	return ComStatus;
}
#endif

int FAS_MoveOriginSingleAxis(FAS_HandlerStruct* nPortNo, uint8_t iSlaveNo)
{
    const uint8_t FrameType = 0x33;
    const uint8_t SendDataLen = 0;
    const uint8_t RcvDataLen = 1;
    uint8_t ComStatus;

    uint8_t* SendBuffer = (uint8_t*)malloc(15 + SendDataLen);
    uint8_t SendLen;
    uint8_t* RcvBuffer = (uint8_t*)malloc(15 + RcvDataLen);
    uint8_t RcvLen;
    uint8_t* RespData = (uint8_t*)malloc(RcvDataLen + 2);
	uint8_t RespDataLen;

    uint8_t SyncByte = FAS_PackData(iSlaveNo, FrameType, NULL, 0, SendBuffer, &SendLen);
    FAS_Send(nPortNo, SendBuffer, SendLen);
    free(SendBuffer);


    ComStatus = FAS_Receive(nPortNo, RcvBuffer,&RcvLen);
	ComStatus = FAS_UnPackData(RcvBuffer, RcvLen, iSlaveNo, SyncByte, FrameType, RespData, &RespDataLen);
	if(ComStatus != FMM_OK) return ComStatus;

	if(RespDataLen != RcvDataLen)
	{
		free(RcvBuffer);
		free(RespData);
		return FMM_UNKNOWN_ERROR;
	}

	ComStatus = RespData[0];
	free(RcvBuffer);
	free(RespData);
	return ComStatus;
}
int FAS_MoveSingleAxisAbsPos(FAS_HandlerStruct* nPortNo, uint8_t iSlaveNo, int32_t lAbsPos, uint32_t lVelocity)
{
    const uint8_t FrameType = 0x34;
    const uint8_t SendDataLen = 8;
    const uint8_t RcvDataLen = 1;
    uint8_t ComStatus;

    uint8_t* SendBuffer = (uint8_t*)malloc(15 + 2*SendDataLen);
    uint8_t SendLen;
    uint8_t* RcvBuffer = (uint8_t*)malloc(15 + RcvDataLen);
    uint8_t RcvLen;
    uint8_t* RespData = (uint8_t*)malloc(RcvDataLen + 2);
	uint8_t RespDataLen;

    uint8_t* Data = (uint8_t*)malloc(SendDataLen);
    memcpy(Data, &lAbsPos, 4);
    memcpy(Data + 4, &lVelocity, 4);
    uint8_t SyncByte = FAS_PackData(iSlaveNo, FrameType, Data, SendDataLen, SendBuffer, &SendLen);
    FAS_Send(nPortNo, SendBuffer, SendLen);
    free(SendBuffer);
    free(Data);


    ComStatus = FAS_Receive(nPortNo, RcvBuffer,&RcvLen);
	ComStatus = FAS_UnPackData(RcvBuffer, RcvLen, iSlaveNo, SyncByte, FrameType, RespData, &RespDataLen);
	if(ComStatus != FMM_OK) return ComStatus;

	if(RespDataLen != RcvDataLen)
	{
		free(RcvBuffer);
		free(RespData);
		return FMM_UNKNOWN_ERROR;
	}

	ComStatus = RespData[0];
	free(RcvBuffer);
	free(RespData);
	return ComStatus;
}

int FAS_MoveSingleAxisIncPos(FAS_HandlerStruct* nPortNo, uint8_t iSlaveNo, int32_t lIncPos, uint32_t lVelocity)
{
	static const uint8_t FrameType = 0x35;
    static const uint8_t SendDataLen = 8;
    static const uint8_t RcvDataLen = 1;
    uint8_t ComStatus = 0;
//    uint8_t* RespData = (uint8_t*)malloc(RcvDataLen + 2);
    uint8_t RespData[3] = {0};

	uint8_t RespDataLen;

//	uint8_t* SendBuffer = (uint8_t*)malloc(15 + 2 * SendDataLen);
	uint8_t SendBuffer[30] = {0};

    uint8_t SendLen;
//    uint8_t* RcvBuffer = (uint8_t*)malloc(15 + RcvDataLen);
    uint8_t RcvBuffer[16] = {0};

    uint8_t RcvLen;

//    uint8_t* Data = (uint8_t*)malloc(SendDataLen);
    uint8_t Data[10] = {0};

    memcpy(Data, &lIncPos, 4);
    memcpy(Data + 4, &lVelocity, 4);
    uint8_t SyncByte = FAS_PackData(iSlaveNo, FrameType, Data, SendDataLen, SendBuffer, &SendLen);
    FAS_Send(nPortNo, SendBuffer, SendLen);
//    free(SendBuffer);
//    free(Data);


    ComStatus = FAS_Receive(nPortNo, RcvBuffer,&RcvLen);
	ComStatus = FAS_UnPackData(RcvBuffer, RcvLen, iSlaveNo, SyncByte, FrameType, RespData, &RespDataLen);
	if(ComStatus != FMM_OK) return ComStatus;

	if(RespDataLen != RcvDataLen)
	{
		ComStatus = FMM_UNKNOWN_ERROR;
	}
	else
	{
		ComStatus = RespData[0];
	}
//	free(RcvBuffer);
//	free(RespData);
	return ComStatus;
}

int FAS_MoveToLimit(FAS_HandlerStruct* nPortNo, uint8_t iSlaveNo, uint32_t lVelocity, int iLimitDir)
{
    const uint8_t FrameType = 0x36;
    const uint8_t SendDataLen = 5;
    const uint8_t RcvDataLen = 1;
    uint8_t ComStatus;

    uint8_t* SendBuffer = (uint8_t*)malloc(15 + 2 * SendDataLen);
//    uint8_t SendBuffer[28] = {0};

    uint8_t SendLen;
//    uint8_t* RcvBuffer = (uint8_t*)malloc(15 + RcvDataLen);
    uint8_t* RcvBuffer = (uint8_t*)malloc(15 + RcvDataLen);

    uint8_t RcvLen;
//    uint8_t* RespData = (uint8_t*)malloc(RcvDataLen + 2);
    uint8_t* RespData = (uint8_t*)malloc(RcvDataLen + 2);

	uint8_t RespDataLen;

    uint8_t* Data = (uint8_t*)malloc(SendDataLen);
    memcpy(Data, &lVelocity, 4);
    memcpy(Data + 4, &iLimitDir, 1);
    uint8_t SyncByte = FAS_PackData(iSlaveNo, FrameType, Data, SendDataLen, SendBuffer, &SendLen);
    FAS_Send(nPortNo, SendBuffer, SendLen);
    free(SendBuffer);
    free(Data);


    ComStatus = FAS_Receive(nPortNo, RcvBuffer,&RcvLen);
	ComStatus = FAS_UnPackData(RcvBuffer, RcvLen, iSlaveNo, SyncByte, FrameType, RespData, &RespDataLen);
	if(ComStatus != FMM_OK) return ComStatus;

	if(RespDataLen != RcvDataLen)
	{
		free(RcvBuffer);
		free(RespData);
		return FMM_UNKNOWN_ERROR;
	}

	ComStatus = RespData[0];
	free(RcvBuffer);
	free(RespData);
	return ComStatus;
}
int FAS_MoveVelocity(FAS_HandlerStruct* nPortNo, uint8_t iSlaveNo, uint32_t lVelocity, int iVelDir)
{
    const uint8_t FrameType = 0x37;
    const uint8_t SendDataLen = 5;
    const uint8_t RcvDataLen = 1;
    uint8_t ComStatus;

    uint8_t* SendBuffer = (uint8_t*)malloc(15 + 2 * SendDataLen);
    uint8_t SendLen;
    uint8_t* RcvBuffer = (uint8_t*)malloc(15 + 2*RcvDataLen);
    uint8_t RcvLen;
    uint8_t* RespData = (uint8_t*)malloc(RcvDataLen + 2);
	uint8_t RespDataLen;

    uint8_t* Data = (uint8_t*)malloc(SendDataLen);
    memcpy(Data, &lVelocity, 4);
    memcpy(Data + 4, &iVelDir, 1);
    uint8_t SyncByte = FAS_PackData(iSlaveNo, FrameType, Data, SendDataLen, SendBuffer, &SendLen);
    FAS_Send(nPortNo, SendBuffer, SendLen);
    free(SendBuffer);
    free(Data);


    ComStatus = FAS_Receive(nPortNo, RcvBuffer,&RcvLen);
	ComStatus = FAS_UnPackData(RcvBuffer, RcvLen, iSlaveNo, SyncByte, FrameType, RespData, &RespDataLen);
	if(ComStatus != FMM_OK) return ComStatus;

	if(RespDataLen != RcvDataLen)
	{
		free(RcvBuffer);
		free(RespData);
		return FMM_UNKNOWN_ERROR;
	}

	ComStatus = RespData[0];
	free(RcvBuffer);
	free(RespData);
	return ComStatus;
}
int FAS_PositionAbsOverride(FAS_HandlerStruct* nPortNo, uint8_t iSlaveNo, int32_t lOverridePos)
{
    const uint8_t FrameType = 0x38;
    const uint8_t SendDataLen = 4;
    const uint8_t RcvDataLen = 1;
    uint8_t ComStatus;

    uint8_t RcvBuffer[20];
//    uint8_t* RcvBuffer = (uint8_t*)malloc(15 + 2*RcvDataLen);
    uint8_t RcvLen;

    uint8_t RespData[8];
//    uint8_t* RespData = (uint8_t*)malloc(RcvDataLen + 2);
	uint8_t RespDataLen;

    uint8_t Data[8];
//    uint8_t* Data = (uint8_t*)malloc(SendDataLen);

    uint8_t SendBuffer[24];
//    uint8_t* SendBuffer = (uint8_t*)malloc(15 + 2 * SendDataLen);
    uint8_t SendLen;

    memcpy(Data, &lOverridePos, 4);
    uint8_t SyncByte = FAS_PackData(iSlaveNo, FrameType, Data, SendDataLen, SendBuffer, &SendLen);
    FAS_Lock(nPortNo, 10);
    FAS_Send(nPortNo, SendBuffer, SendLen);
    ComStatus = FAS_Receive(nPortNo, RcvBuffer,&RcvLen);
	FAS_Unlock(nPortNo);
	ComStatus = FAS_UnPackData(RcvBuffer, RcvLen, iSlaveNo, SyncByte, FrameType, RespData, &RespDataLen);
	if(ComStatus != FMM_OK) return ComStatus;

	ComStatus = RespDataLen != RcvDataLen ? FMM_UNKNOWN_ERROR:RespData[0];

	return ComStatus;
}
int FAS_PositionIncOverride(FAS_HandlerStruct* nPortNo, uint8_t iSlaveNo, int32_t lOverridePos)
{
    const uint8_t FrameType = 0x39;
    const uint8_t SendDataLen = 4;
    const uint8_t RcvDataLen = 1;
    uint8_t ComStatus;

    uint8_t SendBuffer[24] = {0};
//    uint8_t* SendBuffer = (uint8_t*)malloc(15 + 2 * SendDataLen);

    uint8_t SendLen;
    uint8_t RcvBuffer[24] = {0};
//    uint8_t* RcvBuffer = (uint8_t*)malloc(15 + 2*RcvDataLen);

    uint8_t RcvLen;
    uint8_t RespData[4] = {0};
//    uint8_t* RespData = (uint8_t*)malloc(RcvDataLen + 2);

	uint8_t RespDataLen;

	uint8_t Data[4] = {0};
//	uint8_t* Data = (uint8_t*)malloc(SendDataLen);

    memcpy(Data, &lOverridePos, 4);
    uint8_t SyncByte = FAS_PackData(iSlaveNo, FrameType, Data, SendDataLen, SendBuffer, &SendLen);
    FAS_Send(nPortNo, SendBuffer, SendLen);
//    free(SendBuffer);
//    free(Data);


    ComStatus = FAS_Receive(nPortNo, RcvBuffer,&RcvLen);
	ComStatus = FAS_UnPackData(RcvBuffer, RcvLen, iSlaveNo, SyncByte, FrameType, RespData, &RespDataLen);
	if(ComStatus != FMM_OK) return ComStatus;

	if(RespDataLen != RcvDataLen)
	{
		ComStatus =  FMM_UNKNOWN_ERROR;
	}
	else
	{
		ComStatus = RespData[0];

	}
//	free(RcvBuffer);
//	free(RespData);
	return ComStatus;
}

//int FAS_VelocityOverride(FAS_HandlerStruct* nPortNo, uint8_t iSlaveNo, uint32_t lVelocity)
//{
//    const uint8_t FrameType = 0x3A;
//    const uint8_t SendDataLen = 4;
//    const uint8_t RcvDataLen = 1;
//    uint8_t ComStatus;
//
//    uint8_t* SendBuffer = (uint8_t*)malloc(15 + 2 * SendDataLen);
//    uint8_t SendLen;
//    uint8_t* RcvBuffer = (uint8_t*)malloc(15 + 2*RcvDataLen);
//    uint8_t RcvLen;
//    uint8_t* RespData = (uint8_t*)malloc(RcvDataLen + 2);
//	uint8_t RespDataLen;
//
//    uint8_t* Data = (uint8_t*)malloc(SendDataLen);
//    memcpy(Data, &lVelocity, 4);
//    uint8_t SyncByte = FAS_PackData(iSlaveNo, FrameType, Data, SendDataLen, SendBuffer, &SendLen);
//    FAS_Send(nPortNo, SendBuffer, SendLen);
//    free(SendBuffer);
//    free(Data);
//
//
//    ComStatus = FAS_Receive(nPortNo, RcvBuffer,&RcvLen);
//	ComStatus = FAS_UnPackData(RcvBuffer, RcvLen, iSlaveNo, SyncByte, FrameType, RespData, &RespDataLen);
//	if(ComStatus != FMM_OK) return ComStatus;
//
//	if(RespDataLen != RcvDataLen)
//	{
//		free(RcvBuffer);
//		free(RespData);
//		return FMM_UNKNOWN_ERROR;
//	}
//
//	ComStatus = RespData[0];
//	free(RcvBuffer);
//	free(RespData);
//	return ComStatus;
//}

int FAS_MoveLinearAbsPos(FAS_HandlerStruct* nPortNo, uint8_t nNoOfSlaves, uint8_t* iSlavesNo, int32_t* lAbsPos, uint32_t lFeedrate, uint16_t wAccelTime)
{
    return FMM_UNKNOWN_ERROR;
}
int FAS_MoveLinearIncPos(FAS_HandlerStruct* nPortNo, uint8_t nNoOfSlaves, uint8_t* iSlavesNo, int32_t* lIncPos, uint32_t lFeedrate, uint16_t wAccelTime)
{
    return FMM_UNKNOWN_ERROR;
}

int FAS_MovePush(FAS_HandlerStruct* nPortNo, uint8_t iSlaveNo, uint32_t dwStartSpd, uint32_t dwMoveSpd, int32_t lPosition, uint16_t wAccel, uint16_t wDecel, uint16_t wPushRate, uint32_t dwPushSpd, int32_t lEndPosition, uint16_t wPushMode)
{
    return FMM_UNKNOWN_ERROR;
}
int FAS_GetPushStatus(FAS_HandlerStruct* nPortNo, uint8_t iSlaveNo, uint8_t* nPushStatus)
{
    return FMM_UNKNOWN_ERROR;
}


int FAS_MoveSingleAxisAbsPosEx(FAS_HandlerStruct* nPortNo, uint8_t iSlaveNo, int32_t lAbsPos, uint32_t lVelocity, MOTION_OPTION_EX* lpExOption)
{
    const uint8_t FrameType = 0x80;
    const uint8_t SendDataLen = 40;
    const uint8_t RcvDataLen = 1;
    uint8_t ComStatus;

    uint8_t SendBuffer[96] = {0};
    uint8_t SendLen;
    uint8_t RcvBuffer[96] = {0};
    uint8_t RcvLen;
    uint8_t RespData[44] =  {0};
	uint8_t RespDataLen;

    uint8_t Data[44] = {0};
    memcpy(Data, &lAbsPos, 4);
    memcpy(Data + 4, &lVelocity, 4);
    memcpy(Data + 8, lpExOption, 10);
    uint8_t SyncByte = FAS_PackData(iSlaveNo, FrameType, Data, SendDataLen, SendBuffer, &SendLen);
    FAS_Send(nPortNo, SendBuffer, SendLen);
//    free(SendBuffer);
//    free(Data);


    ComStatus = FAS_Receive(nPortNo, RcvBuffer,&RcvLen);
	ComStatus = FAS_UnPackData(RcvBuffer, RcvLen, iSlaveNo, SyncByte, FrameType, RespData, &RespDataLen);
	if(ComStatus != FMM_OK) return ComStatus;

	if(RespDataLen != RcvDataLen)
	{
		ComStatus = FMM_UNKNOWN_ERROR;
	}
	else
	{
		ComStatus = RespData[0];
	}
//	free(RcvBuffer);
//	free(RespData);
	return ComStatus;
}
int FAS_MoveSingleAxisIncPosEx(FAS_HandlerStruct* nPortNo, uint8_t iSlaveNo, int32_t lIncPos, uint32_t lVelocity, MOTION_OPTION_EX* lpExOption)
{
    const uint8_t FrameType = 0x81;
    const uint8_t SendDataLen = 40;
    const uint8_t RcvDataLen = 1;
    uint8_t ComStatus;

    uint8_t* SendBuffer = (uint8_t*)malloc(15 + 2 * SendDataLen);
    uint8_t SendLen;
    uint8_t* RcvBuffer = (uint8_t*)malloc(15 + 2*RcvDataLen);
    uint8_t RcvLen;
    uint8_t* RespData = (uint8_t*)malloc(RcvDataLen + 2);
	uint8_t RespDataLen;

    uint8_t* Data = (uint8_t*)malloc(SendDataLen);
    memcpy(Data, &lIncPos, 4);
    memcpy(Data + 4, &lVelocity, 4);
    memcpy(Data + 8, lpExOption, 10);
    uint8_t SyncByte = FAS_PackData(iSlaveNo, FrameType, Data, SendDataLen, SendBuffer, &SendLen);
    FAS_Send(nPortNo, SendBuffer, SendLen);
    free(SendBuffer);
    free(Data);


    ComStatus = FAS_Receive(nPortNo, RcvBuffer,&RcvLen);
	ComStatus = FAS_UnPackData(RcvBuffer, RcvLen, iSlaveNo, SyncByte, FrameType, RespData, &RespDataLen);
	if(ComStatus != FMM_OK) return ComStatus;

	if(RespDataLen != RcvDataLen)
	{
		free(RcvBuffer);
		free(RespData);
		return FMM_UNKNOWN_ERROR;
	}

	ComStatus = RespData[0];
	free(RcvBuffer);
	free(RespData);
	return ComStatus;
}
int FAS_MoveVelocityEx(FAS_HandlerStruct* nPortNo, uint8_t iSlaveNo, uint32_t lVelocity, int iVelDir, VELOCITY_OPTION_EX* lpExOption)
{
    const uint8_t FrameType = 0x82;
    const uint8_t SendDataLen = 40;
    const uint8_t RcvDataLen = 1;
    uint8_t ComStatus;

    uint8_t* SendBuffer = (uint8_t*)malloc(15 + 2 * SendDataLen);
    uint8_t SendLen;
    uint8_t* RcvBuffer = (uint8_t*)malloc(15 + SendDataLen);
    uint8_t RcvLen;
    uint8_t* RespData = (uint8_t*)malloc(RcvDataLen + 2);
	uint8_t RespDataLen;

    uint8_t* Data = (uint8_t*)malloc(SendDataLen);
    memcpy(Data, &lVelocity, 4);
    memcpy(Data + 4, &iVelDir, 1);
    memcpy(Data + 5, lpExOption, 6);
    uint8_t SyncByte = FAS_PackData(iSlaveNo, FrameType, Data, SendDataLen, SendBuffer, &SendLen);
    FAS_Send(nPortNo, SendBuffer, SendLen);
    free(SendBuffer);
    free(Data);


    ComStatus = FAS_Receive(nPortNo, RcvBuffer,&RcvLen);
	ComStatus = FAS_UnPackData(RcvBuffer, RcvLen, iSlaveNo, SyncByte, FrameType, RespData, &RespDataLen);
	if(ComStatus != FMM_OK) return ComStatus;

	if(RespDataLen != RcvDataLen)
	{
		free(RcvBuffer);
		free(RespData);
		return FMM_UNKNOWN_ERROR;
	}

	ComStatus = RespData[0];
	free(RcvBuffer);
	free(RespData);
	return ComStatus;
}
