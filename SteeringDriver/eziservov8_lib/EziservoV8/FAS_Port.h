#pragma once
#ifndef __FAS_PORT__
#define __FAS_PORT__
#include <stdint.h>
#include "FAS_Port.h"
#include <stdio.h>
#include "cmsis_os.h"
#include <stdlib.h>
#include "SyncPrintf/SyncPrintf.h"



#ifdef USE_RTOS
#include "UARTHandler/UART_Handler.h"

#define FAS_PORT_t 	UART_OS_HandlerStruct*		// UART use with RTOS
#define LOCK_t		osMutexId
#define FAS_printf	SyncPrintf


#else
#include "usart.h"

#define FAS_Port_t	UART_HandleTypeDef*	// HAL UART
#define FAS_printf printf


#endif

typedef struct FAS_HandlerStruct
{
	FAS_PORT_t 	uart;
	LOCK_t		uartLock;
}FAS_HandlerStruct;


uint8_t FAS_Init(FAS_HandlerStruct* nPortNo);
uint8_t FAS_Send(FAS_HandlerStruct* nPortNo, uint8_t* SendBuffer, uint8_t Len);
uint8_t FAS_Receive(FAS_HandlerStruct* nPortNo, uint8_t* RcvBuffer, uint8_t* Len);
uint8_t FAS_Lock(FAS_HandlerStruct* nPortNo, uint32_t timeout);
uint8_t FAS_Unlock(FAS_HandlerStruct* nPortNo);
#endif
