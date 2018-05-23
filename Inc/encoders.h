#ifndef ENCODERS_H
#define ENCODERS_H

#include "stm32f4xx_hal.h"

// TODO Find proper value through trial and error
#define CM_PER_TICK_LEFT	0.0001
#define CM_PER_TICK_RIGHT	0.0001

#define ENCODER_LEFT	TIM2
#define ENCODER_RIGHT	TIM8

uint16_t ENC_GetEncoderTicks(TIM_TypeDef* encoderSide);
double ENC_GetEncoderDistanceCM(TIM_TypeDef* encoderSide);

void ENC_ResetEncoder(TIM_TypeDef* encoderSide);
void ENC_ResetEncoders();

#endif
