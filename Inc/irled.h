#ifndef IR_LED_H
#define IR_LED_H

#include "main.h"
#include "stm32f4xx_hal.h"

// TODO These might have to change
#define IR_LED_LEFT			0
#define IR_LED_RIGHT		1
#define IR_LED_FRONT_LEFT	2
#define IR_LED_FRONT_RIGHT	3

void 	IR_Init();
double 	IR_GetDistance(uint8_t whichLed);

#endif
