#include "FAS_EziMOTIONPlusR.h"
#include <stdlib.h>

#if USE_FAS_ServoEnable == 1
int FAS_ServoEnable(FAS_HandlerStruct* nPortNo, uint8_t iSlaveNo, uint8_t bOnOff)
{
    const uint8_t FrameType = 0x2A;
//    const uint8_t SendDataLen = 1;
    const uint8_t RcvDataLen = 1;
    uint8_t ComStatus;
    uint8_t SendBuffer[20] = {0};
//    uint8_t *SendBuffer = (uint8_t*) malloc(15 + SendDataLen);

    uint8_t SendLen;
    uint8_t RcvBuffer[20] = {0};
//    uint8_t *RcvBuffer = (uint8_t*)malloc(15 + 2*RcvDataLen);

    uint8_t RcvLen;
    uint8_t RespData[4] = {0};
//    uint8_t* RespData = (uint8_t*)malloc(RcvDataLen + 2);

    uint8_t RespDataLen;

    uint8_t SyncByte = FAS_PackData(iSlaveNo, FrameType, &bOnOff, 1, SendBuffer, &SendLen);
    FAS_Lock(nPortNo, 10);
    ComStatus = FAS_Send(nPortNo, SendBuffer, SendLen);
//    free(SendBuffer);
    ComStatus = FAS_Receive(nPortNo, RcvBuffer,&RcvLen);
    FAS_Unlock(nPortNo);

    ComStatus = FAS_UnPackData(RcvBuffer, RcvLen, iSlaveNo, SyncByte, FrameType, RespData, &RespDataLen);

	ComStatus =(ComStatus != FMM_OK) || (RespDataLen != RcvDataLen) ? FMC_RECVPACKET_ERROR : RespData[0];

    ComStatus = RespData[0];
//    free(RcvBuffer);
//	free(RespData);
    return ComStatus;
}
#endif

#if USE_FAS_ServoAlarmReset == 1
int FAS_ServoAlarmReset(FAS_HandlerStruct* nPortNo, uint8_t iSlaveNo)
{
    const uint8_t FrameType = 0x2B;
//    const uint8_t SendDataLen = 0;
    const uint8_t RcvDataLen = 1;
    uint8_t ComStatus;

    uint8_t SendBuffer[16] = {0};
//    uint8_t* SendBuffer = (uint8_t*)malloc(15 + SendDataLen);

    uint8_t SendLen;
    uint8_t RcvBuffer[20] = {0};
//    uint8_t* RcvBuffer = (uint8_t*)malloc(15 + 2*RcvDataLen);

    uint8_t RcvLen;
    uint8_t RespData[4] = {0};
//    uint8_t* RespData = (uint8_t*)malloc(RcvDataLen + 2);

    uint8_t RespDataLen;

    uint8_t SyncByte = FAS_PackData(iSlaveNo, FrameType, NULL, 0, SendBuffer, &SendLen);

    FAS_Lock(nPortNo, 10);

    FAS_Send(nPortNo, SendBuffer, SendLen);
//    free(SendBuffer);

    ComStatus = FAS_Receive(nPortNo, RcvBuffer,&RcvLen);

    FAS_Unlock(nPortNo);
	ComStatus = FAS_UnPackData(RcvBuffer, RcvLen, iSlaveNo, SyncByte, FrameType, RespData, &RespDataLen);
	if(ComStatus != FMM_OK) return ComStatus;

	if(RespDataLen != RcvDataLen)
	{
		ComStatus =  FMM_UNKNOWN_ERROR;
	}
	else{
		ComStatus = RespData[0];
	}

//	free(RcvBuffer);
//	free(RespData);
	return ComStatus;
}
#endif

int FAS_StepAlarmReset(FAS_HandlerStruct* nPortNo, uint8_t iSlaveNo, uint8_t bReset)
{
    return FMM_UNKNOWN_ERROR;
}
int FAS_BrakeSet(FAS_HandlerStruct* nPortNo, uint8_t iSlaveNo, uint8_t bSet, int* nResult)
{
    return FMM_UNKNOWN_ERROR;
}
