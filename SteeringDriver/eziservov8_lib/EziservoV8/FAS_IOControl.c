/*
 * FAS_IOControl.c
 *
 *  Created on: May 18, 2023
 *      Author: vanti
 */
#include "FAS_EziMOTIONPlusR.h"
#include <string.h>

int 	FAS_SetIOInput(FAS_HandlerStruct* nPortNo, uint8_t iSlaveNo, uint64_t uIOSETMask, uint64_t uIOCLRMask);
int 	FAS_SetIOInputEx(FAS_HandlerStruct* nPortNo, uint8_t iSlaveNo, uint32_t dwIOSETMaskLow, uint32_t dwIOSETMaskHigh, uint32_t dwIOCLRMaskLow, uint32_t dwIOCLRMaskHigh);
int 	FAS_GetIOInput(FAS_HandlerStruct* nPortNo, uint8_t iSlaveNo, uint64_t* uIOInput);
int 	FAS_GetIOInputEx(FAS_HandlerStruct* nPortNo, uint8_t iSlaveNo, uint32_t* dwIOInputLow, uint32_t* dwIOInputHigh);

int 	FAS_SetIOOutput(FAS_HandlerStruct* nPortNo, uint8_t iSlaveNo, uint32_t dwIOSETMask, uint32_t dwIOCLRMask);
int 	FAS_GetIOOutput(FAS_HandlerStruct* nPortNo, uint8_t iSlaveNo, uint32_t* dwIOOutput);

int 	FAS_GetInputAssignMap(FAS_HandlerStruct* nPortNo, uint8_t iSlaveNo, uint8_t iInPinNo, uint8_t* nInLogicNo, uint8_t* bLevel);
int 	FAS_GetOutputAssignMap(FAS_HandlerStruct* nPortNo, uint8_t iSlaveNo, uint8_t iOutPinNo, uint8_t* nOutLogicNo, uint8_t* bLevel);
int 	FAS_SetInputAssignMap(FAS_HandlerStruct* nPortNo, uint8_t iSlaveNo, uint8_t iInPinNo, uint8_t nInLogicNo, uint8_t bLevel)
{
    const uint8_t FrameType = 0x24;
    const uint8_t SendDataLen = 3;
    const uint8_t RcvDataLen = 1;
    uint8_t ComStatus;
    uint8_t* RespData = (uint8_t*)malloc(RcvDataLen + 2);
	uint8_t RespDataLen;

    uint8_t* SendBuffer = (uint8_t*)malloc(15 + 2 * SendDataLen);
    uint8_t SendLen;
    uint8_t* RcvBuffer = (uint8_t*)malloc(15 + RcvDataLen);
    uint8_t RcvLen;

    uint8_t* Data = (uint8_t*)malloc(SendDataLen);
    memcpy(Data, &iInPinNo, 1);
    memcpy(Data + 1, &nInLogicNo, 1);
    memcpy(Data + 2, &bLevel, 1);

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
int 	FAS_SetOutputAssignMap(FAS_HandlerStruct* nPortNo, uint8_t iSlaveNo, uint8_t iOutPinNo, uint8_t nOutLogicNo, uint8_t bLevel)
{
	const uint8_t FrameType = 0x25;
	const uint8_t SendDataLen = 3;
	const uint8_t RcvDataLen = 1;
	uint8_t ComStatus;
	uint8_t* RespData = (uint8_t*)malloc(RcvDataLen + 2);
	uint8_t RespDataLen;

	uint8_t* SendBuffer = (uint8_t*)malloc(15 + 2 * SendDataLen);
	uint8_t SendLen;
	uint8_t* RcvBuffer = (uint8_t*)malloc(15 + RcvDataLen);
	uint8_t RcvLen;

	uint8_t* Data = (uint8_t*)malloc(SendDataLen);
	memcpy(Data, &iOutPinNo, 1);
	memcpy(Data + 1, &nOutLogicNo, 1);
	memcpy(Data + 2, &bLevel, 1);

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
int 	FAS_IOAssignMapReadROM(FAS_HandlerStruct* nPortNo, uint8_t iSlaveNo);
