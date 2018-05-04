#ifndef MOTORS_H
#define MOTORS_H

#include "main.h"
#include "stm32f4xx_hal.h"
#include "tim.h"

#define PWM_LEFT_FWD TIM_CHANNEL_1;
#define PWM_RIGHT_FWD TIM_CHANNEL_2;
#define PWM_LEFT_REV TIM_CHANNEL_3;
#define PWM_RIGHT_REV TIM_CHANNEL_4;

void setPWM(uint32_t channel, uint32_t val);

#endif
