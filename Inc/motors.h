#ifndef MOTORS_H
#define MOTORS_H

#include "main.h"
#include "stm32f4xx_hal.h"
#include "tim.h"

#define PWM_LEFT_REV  LL_TIM_CHANNEL_CH1
#define PWM_LEFT_FWD  LL_TIM_CHANNEL_CH2
#define PWM_RIGHT_FWD LL_TIM_CHANNEL_CH3
#define PWM_RIGHT_REV LL_TIM_CHANNEL_CH4

#define DIR_FWD	0
#define DIR_REV	1

#define MOTOR_LEFT	0
#define MOTOR_RIGHT 1

void PWM_Init();

void PWM_SetPWM(uint32_t channel, uint16_t val);
void PWM_SetPWMVector(uint32_t leftRight, uint16_t val);
void PWM_StopPWM(uint32_t channel);

void PWM_SetSpeed(uint8_t direction, uint16_t speed);
void PWM_StopMotors();

void PWM_SetPrescaler(uint32_t prescaler);
void PWM_SetFrequency(float freq);

#endif
