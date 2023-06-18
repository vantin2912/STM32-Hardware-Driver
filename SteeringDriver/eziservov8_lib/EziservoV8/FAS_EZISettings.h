/*
 * FAS_EZISettings.h
 *
 *  Created on: Jun 12, 2023
 *      Author: vanti
 */

#ifndef STEERINGDRIVER_EZISERVOV8_LIB_EZISERVOV8_FAS_EZISETTINGS_H_
#define STEERINGDRIVER_EZISERVOV8_LIB_EZISERVOV8_FAS_EZISETTINGS_H_
/*
 * FAS Servo Driver Control
 */

#define 	USE_FAS_ServoEnable 	1
#define 	USE_FAS_ServoAlarmReset 1

/*
 * FAS Motion Control
 */
#define 	USE_FAS_MoveStop		0
#define 	USE_FAS_EmergencyStop	0
#define		USE_FAS_MovePause		0




/*
 * FAS Status Pos Function
 */
#define		USE_FAS_GetAxisStatus
#define 	USE_FAS_GetIOStatus

#define 	USE_FAS_GetMotionStatus 0
#define 	USE_FAS_GetAllStatus 	0
#define		USE_FAS_SetCommandPos	0
#define		USE_FAS_SetActualPos	0
#define		USE_FAS_ClearPosition	1
#define		USE_FAS_GetCommandPos	0
#define 	USE_FAS_GetActualPos	0
#define 	USE_FAS_GetPosError		0
#define 	USE_FAS_GetActualVel	0
#define 	USE_FAS_GetAlarmType	0


#endif /* STEERINGDRIVER_EZISERVOV8_LIB_EZISERVOV8_FAS_EZISETTINGS_H_ */
