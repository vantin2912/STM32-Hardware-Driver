#include "FAS_EziMOTIONPlusR.h"

#ifdef USE_FAS_GetAxisStatus
int FAS_GetAxisStatus(FAS_HandlerStruct* nPortNo, uint8_t iSlaveNo, uint32_t* dwAxisStatus)
{
    const uint8_t FrameType = 0x40;
//    const uint8_t SendDataLen = 0;
    const uint8_t RcvDataLen = 5;
//    uint8_t *SendBuffer = (uint8_t*) malloc(15 + 2*SendDataLen);
    uint8_t SendBuffer[16] = {0};

    uint8_t SendLen;
//    uint8_t *RcvBuffer = (uint8_t*)malloc(15 + SendDataLen);
    uint8_t RcvBuffer[16] = {0};

    uint8_t RcvLen;
//    uint8_t* RespData = (uint8_t*)malloc(RcvDataLen + 2);
    uint8_t RespData[10] = {0};

	uint8_t RespDataLen;

    uint8_t SyncByte = FAS_PackData(iSlaveNo, FrameType, 0, 0, SendBuffer, &SendLen);
    uint8_t ComStatus;
    FAS_Lock(nPortNo, 10);
    FAS_Send(nPortNo, SendBuffer, SendLen);
    ComStatus = FAS_Receive(nPortNo, RcvBuffer,&RcvLen);
    FAS_Unlock(nPortNo);

	if(ComStatus != FMM_OK) return ComStatus;
	ComStatus = FAS_UnPackData(RcvBuffer, RcvLen, iSlaveNo, SyncByte, FrameType, RespData, &RespDataLen);
	if(ComStatus != FMM_OK) return ComStatus;


	ComStatus = RespDataLen != RcvDataLen ? FMM_UNKNOWN_ERROR:RespData[0];

	memcpy(dwAxisStatus, RespData+1,4);
//	free(RcvBuffer);
//	free(RespData);
	return ComStatus;
}
#endif

#ifdef USE_FAS_GetIOStatus
int FAS_GetIOStatus(FAS_HandlerStruct* nPortNo, uint8_t iSlaveNo, uint64_t* uInStatus, uint32_t* dwOutStatus)
{
    const uint8_t FrameType = 0x41;
    const uint8_t SendDataLen = 0;
    const uint8_t RcvDataLen = 10;
    uint8_t *SendBuffer = (uint8_t*) malloc(15 + 2*SendDataLen);
    uint8_t SendLen;
    uint8_t *RcvBuffer = (uint8_t*)malloc(15 + 2*RcvDataLen);
    uint8_t RcvLen;
    uint8_t* RespData = (uint8_t*)malloc(RcvDataLen + 2);
	uint8_t RespDataLen;

    uint8_t SyncByte = FAS_PackData(iSlaveNo, FrameType, 0, SendDataLen, SendBuffer, &SendLen);
    uint8_t ComStatus;

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
	*uInStatus=0;
	*dwOutStatus=0;
	memcpy(uInStatus, RespData+1,5);
	memcpy(dwOutStatus, RespData+6,4);
	free(RcvBuffer);
	free(RespData);
	return ComStatus;
}

#endif
int FAS_GetIOStatusEx(FAS_HandlerStruct* nPortNo, uint8_t iSlaveNo, uint32_t* dwInStatusLow, uint32_t* dwInStatusHigh, uint32_t* dwOutStatus);

#if USE_FAS_GetMotionStatus == 1
int FAS_GetMotionStatus(FAS_HandlerStruct* nPortNo, uint8_t iSlaveNo, int32_t* lCmdPos, int32_t* lActPos, int32_t* lPosErr, int32_t* lActVel, uint32_t* dwAxisStatus)
{
	const uint8_t FrameType = 0x42;
	const uint8_t SendDataLen = 0;
	const uint8_t RcvDataLen = 21;
	uint8_t *SendBuffer = (uint8_t*) malloc(15 + 2*SendDataLen);
	uint8_t SendLen;
	uint8_t *RcvBuffer = (uint8_t*)malloc(15 + 2*RcvDataLen);
	uint8_t RcvLen;
	uint8_t* RespData = (uint8_t*)malloc(RcvDataLen + 2);
	uint8_t RespDataLen;

	uint8_t SyncByte = FAS_PackData(iSlaveNo, FrameType, 0, SendDataLen, SendBuffer, &SendLen);
	uint8_t ComStatus;

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
	*lCmdPos=0;
	*lActPos=0;
	*lPosErr=0;
	*lActVel=0;
	*dwAxisStatus=0;
	memcpy(lCmdPos, RespData+1,4);
	memcpy(lActPos, RespData+5,4);
	memcpy(lPosErr, RespData+9,4);
	memcpy(lActVel, RespData+13,4);
	memcpy(dwAxisStatus, RespData+17,4);

	free(RcvBuffer);
	free(RespData);
	return ComStatus;
}

#endif

#if USE_FAS_GetAllStatus == 1
int FAS_GetAllStatus(FAS_HandlerStruct* nPortNo, uint8_t iSlaveNo, uint64_t* uInStatus, uint32_t* dwOutStatus, uint32_t* dwAxisStatus, int32_t* lCmdPos, int32_t* lActPos, int32_t* lPosErr, int32_t* lActVel, uint16_t* wPosItemNo)
{
	const uint8_t FrameType = 0x43;
	const uint8_t SendDataLen = 0;
	const uint8_t RcvDataLen = 34;
	uint8_t *SendBuffer = (uint8_t*) malloc(15 + 2*SendDataLen);
	uint8_t SendLen;
	uint8_t *RcvBuffer = (uint8_t*)malloc(15 + 2*RcvDataLen);
	uint8_t RcvLen;
	uint8_t* RespData = (uint8_t*)malloc(RcvDataLen + 2);
	uint8_t RespDataLen;

	uint8_t SyncByte = FAS_PackData(iSlaveNo, FrameType, 0, SendDataLen, SendBuffer, &SendLen);
	uint8_t ComStatus;

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
	*uInStatus=0;
	*dwOutStatus=0;
	*lCmdPos=0;
	*lActPos=0;
	*lPosErr=0;
	*lActVel=0;
	*dwAxisStatus=0;
	*wPosItemNo=0;
	memcpy(uInStatus, RespData+1,5);
	memcpy(dwOutStatus, RespData+6,4);
	memcpy(dwAxisStatus, RespData+10,4);
	memcpy(lCmdPos, RespData+14,4);
	memcpy(lActPos, RespData+18,4);
	memcpy(lPosErr, RespData+22,4);
	memcpy(lActVel, RespData+26,4);
	memcpy(wPosItemNo, RespData+30,4);

	free(RcvBuffer);
	free(RespData);
	return ComStatus;
}
#endif


int FAS_GetAllABSStatus(FAS_HandlerStruct* nPortNo, uint8_t iSlaveNo, uint64_t* uInStatus, uint32_t* dwOutStatus, uint32_t* dwAxisStatus, int32_t* lCmdPos, int32_t* lActPos, int32_t* lPosErr, int32_t* lActVel, uint16_t* wCurrentPosItemNo);
int FAS_GetAllStatusEx(FAS_HandlerStruct* nPortNo, uint8_t iSlaveNo, uint8_t* pTypes, int32_t* pDatas);

#if USE_FAS_SetCommandPos == 1
int FAS_SetCommandPos(FAS_HandlerStruct* nPortNo, uint8_t iSlaveNo, int32_t lCmdPos)
{
	const uint8_t FrameType = 0x50;
	const uint8_t SendDataLen = 4;
	const uint8_t RcvDataLen = 1;
	uint8_t *SendBuffer = (uint8_t*) malloc(15 + 2*SendDataLen);
	uint8_t SendLen;
	uint8_t* SendData = (uint8_t*) malloc(SendDataLen);
	uint8_t *RcvBuffer = (uint8_t*)malloc(15 + 2*RcvDataLen);
	uint8_t RcvLen;
	uint8_t* RespData = (uint8_t*)malloc(RcvDataLen + 2);
	uint8_t RespDataLen;

	memcpy(SendData,&lCmdPos,4);
	uint8_t SyncByte = FAS_PackData(iSlaveNo, FrameType, SendData, SendDataLen, SendBuffer, &SendLen);
	uint8_t ComStatus;

	FAS_Send(nPortNo, SendBuffer, SendLen);
	free(SendData);
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

#if USE_FAS_SetActualPos == 1
int FAS_SetActualPos(FAS_HandlerStruct* nPortNo, uint8_t iSlaveNo, int32_t lActPos)
{
	const uint8_t FrameType = 0x52;
	const uint8_t SendDataLen = 4;
	const uint8_t RcvDataLen = 1;
	uint8_t *SendBuffer = (uint8_t*) malloc(15 + 2*SendDataLen);
	uint8_t SendLen;
	uint8_t* SendData = (uint8_t*) malloc(SendDataLen);
	uint8_t *RcvBuffer = (uint8_t*)malloc(15 + 2*RcvDataLen);
	uint8_t RcvLen;
	uint8_t* RespData = (uint8_t*)malloc(RcvDataLen + 2);
	uint8_t RespDataLen;

	memcpy(SendData,&lActPos,4);
	uint8_t SyncByte = FAS_PackData(iSlaveNo, FrameType, SendData, SendDataLen, SendBuffer, &SendLen);
	uint8_t ComStatus;

	FAS_Send(nPortNo, SendBuffer, SendLen);
	free(SendData);
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

#if USE_FAS_ClearPosition == 1
int FAS_ClearPosition(FAS_HandlerStruct* nPortNo, uint8_t iSlaveNo)
{
	const uint8_t FrameType = 0x56;
	const uint8_t SendDataLen = 0;
	const uint8_t RcvDataLen = 1;
	uint8_t SendBuffer[16] = {0};
//	uint8_t *SendBuffer = (uint8_t*) malloc(15 + 2*SendDataLen);

	uint8_t SendLen;
	uint8_t* SendData = NULL;
//	uint8_t SendData[] = (uint8_t*) malloc(SendDataLen);

//	uint8_t *RcvBuffer = (uint8_t*)malloc(15 + 2*RcvDataLen);
	uint8_t RcvBuffer[20] ={0} ;

	uint8_t RcvLen;
//	uint8_t* RespData = (uint8_t*)malloc(RcvDataLen + 2);
	uint8_t RespData[4] = {0};

	uint8_t RespDataLen;

	uint8_t SyncByte = FAS_PackData(iSlaveNo, FrameType, SendData, SendDataLen, SendBuffer, &SendLen);
	uint8_t ComStatus;
	FAS_Lock(nPortNo, 20);
	FAS_Send(nPortNo, SendBuffer, SendLen);
//	free(SendData);
//	free(SendBuffer);
	ComStatus = FAS_Receive(nPortNo, RcvBuffer,&RcvLen);
 	FAS_Unlock(nPortNo);

	ComStatus = FAS_UnPackData(RcvBuffer, RcvLen, iSlaveNo, SyncByte, FrameType, RespData, &RespDataLen);
	ComStatus = RespDataLen != RcvDataLen? FMC_RECVPACKET_ERROR: RespData[0];

//	free(RcvBuffer);
//	free(RespData);
	return ComStatus;
}
#endif

#if USE_FAS_GetCommandPos == 1

int FAS_GetCommandPos(FAS_HandlerStruct* nPortNo, uint8_t iSlaveNo, int32_t* lCmdPos)
{
	const uint8_t FrameType = 0x51;
	const uint8_t SendDataLen = 0;
	const uint8_t RcvDataLen = 5;

	uint8_t SendBuffer[16] = {0};
//	uint8_t *SendBuffer = (uint8_t*) malloc(15 + 2*SendDataLen);

	uint8_t SendLen;
	uint8_t RcvBuffer[28] = {0};
//	uint8_t *RcvBuffer = (uint8_t*)malloc(15 + 2*RcvDataLen);

	uint8_t RcvLen;
	uint8_t RespData[8] = {0};
//	uint8_t* RespData = (uint8_t*)malloc(RcvDataLen + 2);

	uint8_t RespDataLen;

	uint8_t SyncByte = FAS_PackData(iSlaveNo, FrameType, 0, SendDataLen, SendBuffer, &SendLen);
	uint8_t ComStatus;

	FAS_Send(nPortNo, SendBuffer, SendLen);
//	free(SendBuffer);

	ComStatus = FAS_Receive(nPortNo, RcvBuffer,&RcvLen);
	ComStatus = FAS_UnPackData(RcvBuffer, RcvLen, iSlaveNo, SyncByte, FrameType, RespData, &RespDataLen);

	ComStatus =(ComStatus != FMM_OK) || (RespDataLen != RcvDataLen) ? FMC_RECVPACKET_ERROR : RespData[0];

	if(ComStatus == FMM_OK)
	{
		*lCmdPos=0;
		memcpy(lCmdPos, RespData+1,4);
	}

//	free(RcvBuffer);
//	free(RespData);
	return ComStatus;
}

#endif

#if USE_FAS_GetActualPos == 1
int FAS_GetActualPos(FAS_HandlerStruct* nPortNo, uint8_t iSlaveNo, int32_t* lActPos)
{
	const uint8_t FrameType = 0x53;
	const uint8_t SendDataLen = 0;
	const uint8_t RcvDataLen = 5;

	uint8_t *SendBuffer = (uint8_t*) malloc(15 + 2*SendDataLen);
	uint8_t SendLen;
	uint8_t *RcvBuffer = (uint8_t*)malloc(15 + 2*RcvDataLen);
	uint8_t RcvLen;
	uint8_t* RespData = (uint8_t*)malloc(RcvDataLen + 2);
	uint8_t RespDataLen;

	uint8_t SyncByte = FAS_PackData(iSlaveNo, FrameType, 0, SendDataLen, SendBuffer, &SendLen);
	uint8_t ComStatus;

	FAS_Send(nPortNo, SendBuffer, SendLen);
	free(SendBuffer);

	ComStatus = FAS_Receive(nPortNo, RcvBuffer,&RcvLen);
	ComStatus = FAS_UnPackData(RcvBuffer, RcvLen, iSlaveNo, SyncByte, FrameType, RespData, &RespDataLen);

	ComStatus =(ComStatus != FMM_OK) || (RespDataLen != RcvDataLen) ? FMC_RECVPACKET_ERROR : RespData[0];

	if(ComStatus == FMM_OK)
	{
		*lActPos=0;
		memcpy(lActPos, RespData+1,4);
	}


	free(RcvBuffer);
	free(RespData);
	return ComStatus;
}
#endif

#if USE_FAS_GetPosError	== 1
int FAS_GetPosError(FAS_HandlerStruct* nPortNo, uint8_t iSlaveNo, int32_t* lPosErr)
{
	const uint8_t FrameType = 0x54;
	const uint8_t SendDataLen = 0;
	const uint8_t RcvDataLen = 5;

	uint8_t *SendBuffer = (uint8_t*) malloc(15 + 2*SendDataLen);
	uint8_t SendLen;
	uint8_t *RcvBuffer = (uint8_t*)malloc(15 + 2*RcvDataLen);
	uint8_t RcvLen;
	uint8_t* RespData = (uint8_t*)malloc(RcvDataLen + 2);
	uint8_t RespDataLen;

	uint8_t SyncByte = FAS_PackData(iSlaveNo, FrameType, 0, SendDataLen, SendBuffer, &SendLen);
	uint8_t ComStatus;

	FAS_Send(nPortNo, SendBuffer, SendLen);
	free(SendBuffer);

	ComStatus = FAS_Receive(nPortNo, RcvBuffer,&RcvLen);
	ComStatus = FAS_UnPackData(RcvBuffer, RcvLen, iSlaveNo, SyncByte, FrameType, RespData, &RespDataLen);

	ComStatus = (ComStatus != FMM_OK) || (RespDataLen != RcvDataLen) ? FMC_RECVPACKET_ERROR : RespData[0];

	if(ComStatus == FMM_OK)
	{
		*lPosErr=0;
		memcpy(lPosErr, RespData+1,4);
	}
	free(RcvBuffer);
	free(RespData);
	return ComStatus;
}
#endif

#if USE_FAS_GetActualVel == 1
int FAS_GetActualVel(FAS_HandlerStruct* nPortNo, uint8_t iSlaveNo, int32_t* lActVel)
{
	const uint8_t FrameType = 0x55;
	const uint8_t SendDataLen = 0;
	const uint8_t RcvDataLen = 5;

	uint8_t *SendBuffer = (uint8_t*) malloc(15 + 2*SendDataLen);
	uint8_t SendLen;
	uint8_t *RcvBuffer = (uint8_t*)malloc(15 + 2*RcvDataLen);
	uint8_t RcvLen;
	uint8_t* RespData = (uint8_t*)malloc(RcvDataLen + 2);
	uint8_t RespDataLen;

	uint8_t SyncByte = FAS_PackData(iSlaveNo, FrameType, 0, SendDataLen, SendBuffer, &SendLen);
	uint8_t ComStatus;

	FAS_Send(nPortNo, SendBuffer, SendLen);
	free(SendBuffer);

	ComStatus = FAS_Receive(nPortNo, RcvBuffer,&RcvLen);
	ComStatus = FAS_UnPackData(RcvBuffer, RcvLen, iSlaveNo, SyncByte, FrameType, RespData, &RespDataLen);

	ComStatus = (ComStatus != FMM_OK) || (RespDataLen != RcvDataLen) ? FMC_RECVPACKET_ERROR : RespData[0];

	if(ComStatus == FMM_OK)
	{
		*lActVel=0;
		memcpy(lActVel, RespData+1,4);
	}
	free(RcvBuffer);
	free(RespData);
	return ComStatus;
}
#endif

#if USE_FAS_GetAlarmType == 1
int FAS_GetAlarmType(FAS_HandlerStruct* nPortNo, uint8_t iSlaveNo, uint8_t* nAlarmType)
{
	const uint8_t FrameType = 0x2E;
	const uint8_t SendDataLen = 0;
	const uint8_t RcvDataLen = 2;

	uint8_t *SendBuffer = (uint8_t*) malloc(15 + 2*SendDataLen);
	uint8_t SendLen;
	uint8_t *RcvBuffer = (uint8_t*)malloc(15 + 2*RcvDataLen);
	uint8_t RcvLen;
	uint8_t* RespData = (uint8_t*)malloc(RcvDataLen + 2);
	uint8_t RespDataLen;

	uint8_t SyncByte = FAS_PackData(iSlaveNo, FrameType, 0, SendDataLen, SendBuffer, &SendLen);
	uint8_t ComStatus;

	FAS_Send(nPortNo, SendBuffer, SendLen);
	free(SendBuffer);

	ComStatus = FAS_Receive(nPortNo, RcvBuffer,&RcvLen);
	ComStatus = FAS_UnPackData(RcvBuffer, RcvLen, iSlaveNo, SyncByte, FrameType, RespData, &RespDataLen);

	ComStatus = (ComStatus != FMM_OK) || (RespDataLen != RcvDataLen) ? FMC_RECVPACKET_ERROR : RespData[0];

	if(ComStatus == FMM_OK)
	{
		*nAlarmType=0;
		memcpy(nAlarmType, RespData+1,1);
	}

	free(RcvBuffer);
	free(RespData);
	return ComStatus;
}
#endif

#if USE_FAS_GetRunPTStatus == 1
int FAS_GetRunPTStatus(FAS_HandlerStruct* nPortNo, uint8_t iSlaveNo, uint16_t* wPosItemNo)
{
	const uint8_t FrameType = 0x2E;
	const uint8_t SendDataLen = 0;
	const uint8_t RcvDataLen = 5;

	uint8_t *SendBuffer = (uint8_t*) malloc(15 + 2*SendDataLen);
	uint8_t SendLen;
	uint8_t *RcvBuffer = (uint8_t*)malloc(15 + 2*RcvDataLen);
	uint8_t RcvLen;
	uint8_t* RespData = (uint8_t*)malloc(RcvDataLen + 2);
	uint8_t RespDataLen;

	uint8_t SyncByte = FAS_PackData(iSlaveNo, FrameType, 0, SendDataLen, SendBuffer, &SendLen);
	uint8_t ComStatus;

	FAS_Send(nPortNo, SendBuffer, SendLen);
	free(SendBuffer);

	ComStatus = FAS_Receive(nPortNo, RcvBuffer,&RcvLen);
	ComStatus = FAS_UnPackData(RcvBuffer, RcvLen, iSlaveNo, SyncByte, FrameType, RespData, &RespDataLen);

	ComStatus = (ComStatus != FMM_OK) || (RespDataLen != RcvDataLen) ? FMC_RECVPACKET_ERROR : RespData[0];

	if (ComStatus == FMM_OK)
	{
		*wPosItemNo=0;
		uint32_t PTNumber;
		memcpy(&PTNumber, RespData+1,4);
		*wPosItemNo = PTNumber;
	}
	free(RcvBuffer);
	free(RespData);
	return ComStatus;
}
#endif
