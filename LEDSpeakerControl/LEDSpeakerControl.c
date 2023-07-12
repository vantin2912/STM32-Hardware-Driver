/*
 * LightSpeakerControl.c
 *
 *  Created on: Jun 29, 2023
 *      Author: vanti
 */
#include "LEDSpeakerControl.h"

int LEDSpeaker_SetLED(LEDSpeaker_HandleStruct* handler, uint8_t LeftState, uint8_t RightState,
						uint8_t FrontState, uint8_t StopState)
{
	uint8_t GPIOLevel;
	GPIOLevel = LeftState ? LED_LEFT_ON_GPIOLEVEL : !LED_LEFT_ON_GPIOLEVEL;
	GPIO_WritePin(*handler->LeftPin, GPIOLevel);

	GPIOLevel = RightState ? LED_RIGHT_ON_GPIOLEVEL : !LED_RIGHT_ON_GPIOLEVEL;
	GPIO_WritePin(*handler->RightPin, GPIOLevel);

	GPIOLevel = FrontState ? LED_FRONT_ON_GPIOLEVEL : !LED_FRONT_ON_GPIOLEVEL;
	GPIO_WritePin(*handler->FrontPin, GPIOLevel);

	GPIOLevel = StopState ? LED_STOP_ON_GPIOLEVEL : !LED_STOP_ON_GPIOLEVEL;
	GPIO_WritePin(*handler->StopPin, GPIOLevel);
	return 0;
}

int LEDSpeaker_setSpeaker(LEDSpeaker_HandleStruct* handler, uint8_t SpeakerState)
{
	uint8_t GPIOLevel = SpeakerState ? SPEAKER_ON_GPIOLEVEL : !SPEAKER_ON_GPIOLEVEL;
	GPIO_WritePin(*handler->SpeakerPin, GPIOLevel);
	return 0;
}
