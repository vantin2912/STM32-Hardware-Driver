/*
 * LightSpeakerControl.h
 *
 *  Created on: Jun 29, 2023
 *      Author: vanti
 */

#ifndef LEDSPEAKERCONTROL_LEDSPEAKERCONTROL_H_
#define LEDSPEAKERCONTROL_LEDSPEAKERCONTROL_H_

#include "main.h"
#include "GPIO/GPIOHandler.h"

#define LED_LEFT_ON_GPIOLEVEL		1
#define LED_RIGHT_ON_GPIOLEVEL		1
#define LED_FRONT_ON_GPIOLEVEL		1
#define LED_STOP_ON_GPIOLEVEL		1

#define SPEAKER_ON_GPIOLEVEL		1

typedef struct LEDSpeaker_HandleStruct{

	GPIO_HandlerStruct *LeftPin, *RightPin;
	GPIO_HandlerStruct *FrontPin, *StopPin;
	GPIO_HandlerStruct *SpeakerPin;
} LEDSpeaker_HandleStruct;

int LEDSpeaker_SetLED(LEDSpeaker_HandleStruct* handler, uint8_t LeftState, uint8_t RightState,
						uint8_t FrontState, uint8_t StopState);

int LEDSpeaker_setSpeaker(LEDSpeaker_HandleStruct* handler, uint8_t SpeakerState);

#endif /* LEDSPEAKERCONTROL_LEDSPEAKERCONTROL_H_ */
