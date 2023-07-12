/*
 * GPSHandler.h
 *
 *  Created on: Jun 22, 2023
 *      Author: vanti
 */

#ifndef GPSHANDLER_GPSHANDLER_H_
#define GPSHANDLER_GPSHANDLER_H_

#include "GPSHandler.h"
#include "lwgps/lwgps.h"
#include "main.h"
#include "cmsis_os.h"
#include "UARTHandler/UART_Handler.h"

#define GPS_RcvBufferSize	300

typedef struct GPS_DataStruct{
	float Long, Lat;
}GPS_DataStruct;

typedef struct GPS_HandlerStruct{
	UART_OS_HandlerStruct* uart;
	GPS_DataStruct GPSData;
	uint32_t updateTime;

	osMutexId_t dataLock;
	osThreadId_t readThread;
	uint8_t readEnable;
} GPS_HandlerStruct;


int GPS_Init(GPS_HandlerStruct* gps, UART_OS_HandlerStruct* uart, uint32_t UpdateTime);
int GPS_Start(GPS_HandlerStruct* gps, uint8_t state);
int GPS_GetData(GPS_HandlerStruct* gps, GPS_DataStruct* Data);
void GPS_ReadThread(void* Handler);
#endif /* GPSHANDLER_GPSHANDLER_H_ */
