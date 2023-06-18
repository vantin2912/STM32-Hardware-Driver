#pragma once
#ifndef __FAS_UTIL__
#define __FAS_UTIL__
#include "FAS_Port.h"

uint8_t FAS_PackData(uint8_t SlaveID, uint8_t FrameType ,uint8_t* Data, uint8_t Len, uint8_t* PackedData, uint8_t* PackedLen);
uint8_t FAS_UnPackData(uint8_t* Buffer, uint8_t BufferLen, uint8_t SlaveID, uint8_t Sync, uint8_t FrameType, uint8_t* Data, uint8_t* DataLen);
#endif
