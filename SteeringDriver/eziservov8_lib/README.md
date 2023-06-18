# EziServoV8_Lib


## Description
Unofficially C library source for Fastech Eziservo V8


## Installation

Add library to your build system

Include Library Header
```c
#include "FAS_EziMOTIONPlusR.h"
```

Implement send and receive function

```c
uint8_t FAS_Send(uint8_t Port, uint8_t* SendBuffer, uint8_t Len)
{
    /*
        Your Send function
        return FMM_OK           if Port is open and available to send
        return FMM_NOT_OPEN     if Port is not open and unavailable to send
    
    */
	return FMM_OK;
}

uint8_t FAS_Receive(uint8_t Port, uint8_t* RcvBuffer, uint8_t* RxLen)
{
    /*
        Your Receive function
        return FMM_OK           if Port is open and available to send
        return FMM_NOT_OPEN     if Port is not open and unavailable to send
    
    */
	return FMM_OK;
}
```

## Project status
Working on Progress
Just only implement ServoControl, Motion, and get Status function
