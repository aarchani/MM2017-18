#ifndef ENCODERS_H
#define ENCODERS_H

#include "stm32f4xx_hal.h"

// Almost perfectly calibrated at 5.0 CM, TODO test for larger distances
#define CM_PER_TICK_LEFT	0.00090
#define CM_PER_TICK_RIGHT	0.00090

#define ENCODER_LEFT	TIM2
#define ENCODER_RIGHT	TIM8

uint16_t ENC_GetEncoderTicks(TIM_TypeDef* encoderSide);
float ENC_GetEncoderDistanceCM(TIM_TypeDef* encoderSide);

void ENC_ResetEncoder(TIM_TypeDef* encoderSide);
void ENC_ResetEncoders();

#endif
