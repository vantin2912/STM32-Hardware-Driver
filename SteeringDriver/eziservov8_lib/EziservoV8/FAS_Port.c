
#include "FAS_Port.h"

__attribute__((weak)) uint8_t FAS_Init(FAS_HandlerStruct* nPortNo)
{
	return 0;
}

__attribute__((weak)) uint8_t FAS_Send(FAS_HandlerStruct* Port, uint8_t* SendBuffer, uint8_t Len)
{
    for(uint8_t i = 0; i < Len; ++i)
    {
    	FAS_printf("0x%.2x ",SendBuffer[i]);
    }
    FAS_printf("\r\n");

    return 0;
}
__attribute__((weak)) uint8_t FAS_Receive(FAS_HandlerStruct* Port, uint8_t* RcvBuffer, uint8_t* RxLen)
{

    return 0;
}

__attribute__((weak)) uint8_t FAS_Lock(FAS_HandlerStruct* nPortNo, uint32_t timeout)
{
	return 0;
}
__attribute__((weak)) uint8_t FAS_Unlock(FAS_HandlerStruct* nPortNo)
{
	return 0;
}
