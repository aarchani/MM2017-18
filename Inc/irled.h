#ifndef IR_LED_H
#define IR_LED_H

#include "main.h"
#include "stm32f4xx_hal.h"

#define IR_LED_RIGHT		0
#define IR_LED_FRONT_RIGHT	1
#define IR_LED_FRONT_LEFT	2
#define IR_LED_LEFT			3

#define IR_RIGHT_THRESHOLD  400
#define IR_RIGHT_SETPOINT   500

#define IR_FRONT_THRESHOLD  850
#define IR_LEFT_THRESHOLD   300

void 	IR_Init();
float 	IR_GetDistance(uint8_t whichLed);

#endif
