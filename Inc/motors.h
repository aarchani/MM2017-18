#ifndef MOTORS_H
#define MOTORS_H

#include "main.h"
#include "stm32f4xx_hal.h"
#include "tim.h"

#define PWM_LEFT_REV  LL_TIM_CHANNEL_CH1
#define PWM_LEFT_FWD  LL_TIM_CHANNEL_CH2
#define PWM_RIGHT_FWD LL_TIM_CHANNEL_CH3
#define PWM_RIGHT_REV LL_TIM_CHANNEL_CH4

void PWM_SetPWM(uint32_t channel, uint16_t val);
void PWM_StopPWM(uint32_t channel);

void PWM_SetPrescaler(uint32_t prescaler);

#endif
