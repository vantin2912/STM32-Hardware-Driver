/*
 * GPSHandler.c
 *
 *  Created on: Jun 22, 2023
 *      Author: vanti
 */
#include "GPSHandler.h"
#include "string.h"
#include "cmsis_os.h"

const osThreadAttr_t GPSTask_attributes = {
  .name = "GPSTask",
  .stack_size = 200 * 4,
  .priority = (osPriority_t) osPriorityNormal2,
};

void GPS_ReadThread(void* Handler)
{
	GPS_HandlerStruct* gpsHandler = (GPS_HandlerStruct*) Handler;
	lwgps_t lwgps_parser;
	lwgps_init(&lwgps_parser);
	static char rcvBuffer[GPS_RcvBufferSize];
	int Status;
	uint16_t rcvLen = 0;
	while(1)
	{
		if(!gpsHandler->readEnable)
		{
			osThreadSuspend(gpsHandler->readThread);
		}
		Status = UART_OS_Receive_ToIdle(gpsHandler->uart,(uint8_t*) rcvBuffer, &rcvLen, GPS_RcvBufferSize, osWaitForever);
		if(Status == osOK)
		{
			lwgps_process(&lwgps_parser, rcvBuffer, rcvLen);
			gpsHandler->GPSData.Lat = lwgps_parser.latitude;
			gpsHandler->GPSData.Long = lwgps_parser.longitude;
		}
	}
}

int GPS_Init(GPS_HandlerStruct* gps, UART_OS_HandlerStruct* uart, uint32_t UpdateTime)
{
	memset(gps, 0, sizeof(GPS_HandlerStruct));
	gps->dataLock = osMutexNew(NULL);
	gps->readThread = osThreadNew(GPS_ReadThread, gps, &GPSTask_attributes);

	gps->uart = uart;
	gps->updateTime = UpdateTime;
	return osOK;
}
int GPS_Start(GPS_HandlerStruct* gps, uint8_t state)
{
	gps->readEnable = 1;
	osThreadResume(gps->readThread);
	return osOK;
}

int GPS_GetData(GPS_HandlerStruct* gps, GPS_DataStruct* Data)
{
	int Status = osMutexAcquire(gps->dataLock, 10);
	Data->Long = gps->GPSData.Long;
	Data->Lat = gps->GPSData.Lat;
	osMutexRelease(gps->dataLock);
	return Status;
}
