// FAS_Ezi_SERVO.h:
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FAS_EZI_SERVO_H__9185E608_0EDA_4C3B_8E92_B518968D037B__INCLUDED_)
#define AFX_FAS_EZI_SERVO_H__9185E608_0EDA_4C3B_8E92_B518968D037B__INCLUDED_

#ifdef EZI_SERVO_PLUSR_EXPORTS
	#define EZI_SERVO_PLUSR_API __declspec(dllexport)

	#include "../MotionCommon/MOTION_DEFINE.h"
#else
	#include "FAS_EZISettings.h"
	#include "FAS_Util.h"	
	#include "ReturnCodes_Define.h"
	#include "MOTION_DEFINE.h"
	#include "COMM_Define.h"
	#include "MOTION_EziSERVO_DEFINE.h"
	#include <stdlib.h>
	#include <string.h>
#endif


uint8_t 	FAS_Connect(FAS_HandlerStruct* nPortNo, uint32_t dwBaud);

uint8_t 	FAS_OpenPort(FAS_HandlerStruct* nPortNo, uint32_t dwBaud);
uint8_t 	FAS_AttachSlave(FAS_HandlerStruct* nPortNo, uint8_t iSlaveNo);

void 	FAS_Close(FAS_HandlerStruct* nPortNo);

void 	FAS_EnableLog(uint8_t bEnable);
uint8_t 	FAS_SetLogPath(char* lpPath);

uint8_t 	FAS_IsSlaveExist(FAS_HandlerStruct* nPortNo, uint8_t iSlaveNo);

int 	FAS_GetSlaveInfo(FAS_HandlerStruct* nPortNo, uint8_t iSlaveNo, DRIVE_INFO* lpDriveInfo);

int 	FAS_SaveAllParameters(FAS_HandlerStruct* nPortNo, uint8_t iSlaveNo);
int 	FAS_SetParameter(FAS_HandlerStruct* nPortNo, uint8_t iSlaveNo, uint8_t iParamNo, int32_t lParamValue);
int 	FAS_GetParameter(FAS_HandlerStruct* nPortNo, uint8_t iSlaveNo, uint8_t iParamNo, int32_t* lParamValue);
int 	FAS_GetROMParameter(FAS_HandlerStruct* nPortNo, uint8_t iSlaveNo, uint8_t iParamNo, int32_t* lRomParam);

//------------------------------------------------------------------------------
//					IO Functions
//------------------------------------------------------------------------------
int 	FAS_SetIOInput(FAS_HandlerStruct* nPortNo, uint8_t iSlaveNo, uint64_t uIOSETMask, uint64_t uIOCLRMask);
int 	FAS_SetIOInputEx(FAS_HandlerStruct* nPortNo, uint8_t iSlaveNo, uint32_t dwIOSETMaskLow, uint32_t dwIOSETMaskHigh, uint32_t dwIOCLRMaskLow, uint32_t dwIOCLRMaskHigh);
int 	FAS_GetIOInput(FAS_HandlerStruct* nPortNo, uint8_t iSlaveNo, uint64_t* uIOInput);
int 	FAS_GetIOInputEx(FAS_HandlerStruct* nPortNo, uint8_t iSlaveNo, uint32_t* dwIOInputLow, uint32_t* dwIOInputHigh);

int 	FAS_SetIOOutput(FAS_HandlerStruct* nPortNo, uint8_t iSlaveNo, uint32_t dwIOSETMask, uint32_t dwIOCLRMask);
int 	FAS_GetIOOutput(FAS_HandlerStruct* nPortNo, uint8_t iSlaveNo, uint32_t* dwIOOutput);

int 	FAS_GetInputAssignMap(FAS_HandlerStruct* nPortNo, uint8_t iSlaveNo, uint8_t iInPinNo, uint8_t* nInLogicNo, uint8_t* bLevel);
int 	FAS_GetOutputAssignMap(FAS_HandlerStruct* nPortNo, uint8_t iSlaveNo, uint8_t iOutPinNo, uint8_t* nOutLogicNo, uint8_t* bLevel);
int 	FAS_SetInputAssignMap(FAS_HandlerStruct* nPortNo, uint8_t iSlaveNo, uint8_t iInPinNo, uint8_t nInLogicNo, uint8_t bLevel);
int 	FAS_SetOutputAssignMap(FAS_HandlerStruct* nPortNo, uint8_t iSlaveNo, uint8_t iOutPinNo, uint8_t nOutLogicNo, uint8_t bLevel);

int 	FAS_IOAssignMapReadROM(FAS_HandlerStruct* nPortNo, uint8_t iSlaveNo);

//------------------------------------------------------------------------------
//					Servo Driver Control Functions
//------------------------------------------------------------------------------		
int 	FAS_ServoEnable(FAS_HandlerStruct* nPortNo, uint8_t iSlaveNo, uint8_t bOnOff);
int 	FAS_ServoAlarmReset(FAS_HandlerStruct* nPortNo, uint8_t iSlaveNo);
int 	FAS_StepAlarmReset(FAS_HandlerStruct* nPortNo, uint8_t iSlaveNo, uint8_t bReset);
int 	FAS_BrakeSet(FAS_HandlerStruct* nPortNo, uint8_t iSlaveNo, uint8_t bSet, int* nResult);

//------------------------------------------------------------------------------
//					Read Status and Position
//------------------------------------------------------------------------------
int 	FAS_GetAxisStatus(FAS_HandlerStruct* nPortNo, uint8_t iSlaveNo, uint32_t* dwAxisStatus);
int 	FAS_GetIOStatus(FAS_HandlerStruct* nPortNo, uint8_t iSlaveNo, uint64_t* uInStatus, uint32_t* dwOutStatus);
int 	FAS_GetIOStatusEx(FAS_HandlerStruct* nPortNo, uint8_t iSlaveNo, uint32_t* dwInStatusLow, uint32_t* dwInStatusHigh, uint32_t* dwOutStatus);
int 	FAS_GetMotionStatus(FAS_HandlerStruct* nPortNo, uint8_t iSlaveNo, int32_t* lCmdPos, int32_t* lActPos, int32_t* lPosErr, int32_t* lActVel, uint32_t* dwAxisStatus);
int 	FAS_GetAllStatus(FAS_HandlerStruct* nPortNo, uint8_t iSlaveNo, uint64_t* uInStatus, uint32_t* dwOutStatus, uint32_t* dwAxisStatus, int32_t* lCmdPos, int32_t* lActPos, int32_t* lPosErr, int32_t* lActVel, uint16_t* wPosItemNo);

int 	FAS_GetAllABSStatus(FAS_HandlerStruct* nPortNo, uint8_t iSlaveNo, uint64_t* uInStatus, uint32_t* dwOutStatus, uint32_t* dwAxisStatus, int32_t* lCmdPos, int32_t* lActPos, int32_t* lPosErr, int32_t* lActVel, uint16_t* wCurrentPosItemNo);
int 	FAS_GetAllStatusEx(FAS_HandlerStruct* nPortNo, uint8_t iSlaveNo, uint8_t* pTypes, int32_t* pDatas);

int 	FAS_SetCommandPos(FAS_HandlerStruct* nPortNo, uint8_t iSlaveNo, int32_t lCmdPos);
int 	FAS_SetActualPos(FAS_HandlerStruct* nPortNo, uint8_t iSlaveNo, int32_t lActPos);
int 	FAS_ClearPosition(FAS_HandlerStruct* nPortNo, uint8_t iSlaveNo);
int 	FAS_GetCommandPos(FAS_HandlerStruct* nPortNo, uint8_t iSlaveNo, int32_t* lCmdPos);
int 	FAS_GetActualPos(FAS_HandlerStruct* nPortNo, uint8_t iSlaveNo, int32_t* lActPos);
int 	FAS_GetPosError(FAS_HandlerStruct* nPortNo, uint8_t iSlaveNo, int32_t* lPosErr);
int 	FAS_GetActualVel(FAS_HandlerStruct* nPortNo, uint8_t iSlaveNo, int32_t* lActVel);

int 	FAS_GetAlarmType(FAS_HandlerStruct* nPortNo, uint8_t iSlaveNo, uint8_t* nAlarmType);
int 	FAS_GetRunPTStatus(FAS_HandlerStruct* nPortNo, uint8_t iSlaveNo, uint16_t* wPosItemNo);

//------------------------------------------------------------------
//					Motion Functions.
//------------------------------------------------------------------
int 	FAS_MoveStop(FAS_HandlerStruct* nPortNo, uint8_t iSlaveNo);
int 	FAS_EmergencyStop(FAS_HandlerStruct* nPortNo, uint8_t iSlaveNo);

int 	FAS_MovePause(FAS_HandlerStruct* nPortNo, uint8_t iSlaveNo, uint8_t bPause);

int 	FAS_MoveOriginSingleAxis(FAS_HandlerStruct* nPortNo, uint8_t iSlaveNo);
int 	FAS_MoveSingleAxisAbsPos(FAS_HandlerStruct* nPortNo, uint8_t iSlaveNo, int32_t lAbsPos, uint32_t lVelocity);
int 	FAS_MoveSingleAxisIncPos(FAS_HandlerStruct* nPortNo, uint8_t iSlaveNo, int32_t lIncPos, uint32_t lVelocity);
int 	FAS_MoveToLimit(FAS_HandlerStruct* nPortNo, uint8_t iSlaveNo, uint32_t lVelocity, int iLimitDir);
int 	FAS_MoveVelocity(FAS_HandlerStruct* nPortNo, uint8_t iSlaveNo, uint32_t lVelocity, int iVelDir);

int 	FAS_PositionAbsOverride(FAS_HandlerStruct* nPortNo, uint8_t iSlaveNo, int32_t lOverridePos);
int 	FAS_PositionIncOverride(FAS_HandlerStruct* nPortNo, uint8_t iSlaveNo, int32_t lOverridePos);
int 	FAS_VelocityOverride(FAS_HandlerStruct* nPortNo, uint8_t iSlaveNo, uint32_t lVelocity);

int 	FAS_MoveLinearAbsPos(FAS_HandlerStruct* nPortNo, uint8_t nNoOfSlaves, uint8_t* iSlavesNo, int32_t* lAbsPos, uint32_t lFeedrate, uint16_t wAccelTime);
int 	FAS_MoveLinearIncPos(FAS_HandlerStruct* nPortNo, uint8_t nNoOfSlaves, uint8_t* iSlavesNo, int32_t* lIncPos, uint32_t lFeedrate, uint16_t wAccelTime);

int 	FAS_MovePush(FAS_HandlerStruct* nPortNo, uint8_t iSlaveNo, uint32_t dwStartSpd, uint32_t dwMoveSpd, int32_t lPosition, uint16_t wAccel, uint16_t wDecel, uint16_t wPushRate, uint32_t dwPushSpd, int32_t lEndPosition, uint16_t wPushMode);
int 	FAS_GetPushStatus(FAS_HandlerStruct* nPortNo, uint8_t iSlaveNo, uint8_t* nPushStatus);

//------------------------------------------------------------------
//					Ex-Motion Functions.
//------------------------------------------------------------------
int 	FAS_MoveSingleAxisAbsPosEx(FAS_HandlerStruct* nPortNo, uint8_t iSlaveNo, int32_t lAbsPos, uint32_t lVelocity, MOTION_OPTION_EX* lpExOption);
int 	FAS_MoveSingleAxisIncPosEx(FAS_HandlerStruct* nPortNo, uint8_t iSlaveNo, int32_t lIncPos, uint32_t lVelocity, MOTION_OPTION_EX* lpExOption);
int 	FAS_MoveVelocityEx(FAS_HandlerStruct* nPortNo, uint8_t iSlaveNo, uint32_t lVelocity, int iVelDir, VELOCITY_OPTION_EX* lpExOption);

//------------------------------------------------------------------
//					All-Motion Functions.
//------------------------------------------------------------------
int 	FAS_AllMoveStop(FAS_HandlerStruct* nPortNo);
int 	FAS_AllEmergencyStop(FAS_HandlerStruct* nPortNo);
int 	FAS_AllMoveOriginSingleAxis(FAS_HandlerStruct* nPortNo);
int 	FAS_AllMoveSingleAxisAbsPos(FAS_HandlerStruct* nPortNo, int32_t lAbsPos, uint32_t lVelocity);
int 	FAS_AllMoveSingleAxisIncPos(FAS_HandlerStruct* nPortNo, int32_t lIncPos, uint32_t lVelocity);

//------------------------------------------------------------------
//					Position Table Functions.
//------------------------------------------------------------------
int 	FAS_PosTableReadItem(FAS_HandlerStruct* nPortNo, uint8_t iSlaveNo, uint16_t wItemNo, LPITEM_NODE lpItem);
int 	FAS_PosTableWriteItem(FAS_HandlerStruct* nPortNo, uint8_t iSlaveNo, uint16_t wItemNo, LPITEM_NODE lpItem);
int 	FAS_PosTableWriteROM(FAS_HandlerStruct* nPortNo, uint8_t iSlaveNo);
int 	FAS_PosTableReadROM(FAS_HandlerStruct* nPortNo, uint8_t iSlaveNo);
int 	FAS_PosTableRunItem(FAS_HandlerStruct* nPortNo, uint8_t iSlaveNo, uint16_t wItemNo);

int 	FAS_PosTableReadOneItem(FAS_HandlerStruct* nPortNo, uint8_t iSlaveNo, uint16_t wItemNo, uint16_t wOffset, int32_t* lPosItemVal);
int 	FAS_PosTableWriteOneItem(FAS_HandlerStruct* nPortNo, uint8_t iSlaveNo, uint16_t wItemNo, uint16_t wOffset, int32_t lPosItemVal);
int 	FAS_PosTableSingleRunItem(FAS_HandlerStruct* nPortNo, uint8_t iSlaveNo, uint8_t bNextMove, uint16_t wItemNo);

//------------------------------------------------------------------
//					I/O Module Functions.
//------------------------------------------------------------------
int 	FAS_GetInput(FAS_HandlerStruct* nPortNo, uint8_t iSlaveNo, uint32_t* uInput, uint32_t* uLatch);

int 	FAS_ClearLatch(FAS_HandlerStruct* nPortNo, uint8_t iSlaveNo, uint32_t uLatchMask);
int 	FAS_GetLatchCount(FAS_HandlerStruct* nPortNo, uint8_t iSlaveNo, unsigned char iInputNo, uint32_t* uCount);
int 	FAS_GetLatchCountAll(FAS_HandlerStruct* nPortNo, uint8_t iSlaveNo, uint32_t** ppuAllCount);
int 	FAS_ClearLatchCount(FAS_HandlerStruct* nPortNo, uint8_t iSlaveNo, uint32_t uInputMask);

int 	FAS_GetOutput(FAS_HandlerStruct* nPortNo, uint8_t iSlaveNo, uint32_t* uOutput, uint32_t* uStatus);
int 	FAS_SetOutput(FAS_HandlerStruct* nPortNo, uint8_t iSlaveNo, uint32_t uSetMask, uint32_t uClearMask);

int 	FAS_SetTrigger(FAS_HandlerStruct* nPortNo, uint8_t iSlaveNo, unsigned char uOutputNo, TRIGGER_INFO* pTrigger);
int 	FAS_SetRunStop(FAS_HandlerStruct* nPortNo, uint8_t iSlaveNo, uint32_t uRunMask, uint32_t uStopMask);
int 	FAS_GetTriggerCount(FAS_HandlerStruct* nPortNo, uint8_t iSlaveNo, unsigned char uOutputNo, uint32_t* uCount);

int 	FAS_GetIOLevel(FAS_HandlerStruct* nPortNo, uint8_t iSlaveNo, uint32_t* uIOLevel);
int 	FAS_SetIOLevel(FAS_HandlerStruct* nPortNo, uint8_t iSlaveNo, uint32_t uIOLevel);
int 	FAS_LoadIOLevel(FAS_HandlerStruct* nPortNo, uint8_t iSlaveNo);
int 	FAS_SaveIOLevel(FAS_HandlerStruct* nPortNo, uint8_t iSlaveNo);

int 	FAS_GetInputFilter(FAS_HandlerStruct* nPortNo, uint8_t iSlaveNo, unsigned short* filter);
int 	FAS_SetInputFilter(FAS_HandlerStruct* nPortNo, uint8_t iSlaveNo, unsigned short filter);

//------------------------------------------------------------------
//					Ezi-IO AD Functions
//------------------------------------------------------------------
int 	FAS_GetAllADResult(FAS_HandlerStruct* nPortNo, uint8_t iSlaveNo, AD_RESULT* result);
int 	FAS_GetADResult(FAS_HandlerStruct* nPortNo, uint8_t iSlaveNo, uint8_t channel, float* adresult);
int 	FAS_SetADRange(FAS_HandlerStruct* nPortNo, uint8_t iSlaveNo, uint8_t channel, AD_RANGE range);

#endif // !defined(AFX_FAS_EZI_SERVO_H__9185E608_0EDA_4C3B_8E92_B518968D037B__INCLUDED_)
