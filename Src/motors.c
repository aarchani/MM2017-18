#include "motors.h"
#include "encoders.h"

/*
 *	Performs some post-TIM initialization for the motors
 */
void PWM_Init() {
	LL_TIM_EnableCounter(TIM4);
	LL_TIM_SetAutoReload(TIM4, 100);
	PWM_StopPWM(LL_TIM_CHANNEL_CH1);
	PWM_StopPWM(LL_TIM_CHANNEL_CH2);
	PWM_StopPWM(LL_TIM_CHANNEL_CH3);
	PWM_StopPWM(LL_TIM_CHANNEL_CH4);
}

/*
 * Sets the PWM for a channel of TIM4
 *
 * Parameters:
 * 	- channel: The TIM4 channel to use; Can be any of LL_TIM_CHANNEL_CHx
 * 			   or any of the macros defined in motors.h
 * 	- val:	The value of the Capture Compare Register to set, to set the
 * 			duty cycle. MUST be a value in range [0, 100]
 *
 */
void PWM_SetPWM(uint32_t channel, uint16_t val) {
	switch (channel) {
		case LL_TIM_CHANNEL_CH1:
			LL_TIM_CC_EnableChannel(TIM4, LL_TIM_CHANNEL_CH1);
			LL_TIM_OC_SetCompareCH1(TIM4, val);
			break;
		case LL_TIM_CHANNEL_CH2:
			LL_TIM_CC_EnableChannel(TIM4, LL_TIM_CHANNEL_CH2);
			LL_TIM_OC_SetCompareCH2(TIM4, val);
			break;
		case LL_TIM_CHANNEL_CH3:
			LL_TIM_CC_EnableChannel(TIM4, LL_TIM_CHANNEL_CH3);
			LL_TIM_OC_SetCompareCH3(TIM4, val);
			break;
		case LL_TIM_CHANNEL_CH4:
			LL_TIM_CC_EnableChannel(TIM4, LL_TIM_CHANNEL_CH4);
			LL_TIM_OC_SetCompareCH4(TIM4, val);
			break;
	}
}

/*
 * Kills the PWM for a channel of TIM4
 *
 * Parameters:
 * 	- channel: The TIM4 channel to use; Can be any of LL_TIM_CHANNEL_CHx
 * 			   or any of the macros defined in motors.h
 *
 */
void PWM_StopPWM(uint32_t channel) {
	switch (channel) {
		case LL_TIM_CHANNEL_CH1:
			LL_TIM_CC_DisableChannel(TIM4, LL_TIM_CHANNEL_CH1);
			LL_TIM_OC_SetCompareCH1(TIM4, 0);
			break;
		case LL_TIM_CHANNEL_CH2:
			LL_TIM_CC_DisableChannel(TIM4, LL_TIM_CHANNEL_CH2);
			LL_TIM_OC_SetCompareCH2(TIM4, 0);
			break;
		case LL_TIM_CHANNEL_CH3:
			LL_TIM_CC_DisableChannel(TIM4, LL_TIM_CHANNEL_CH3);
			LL_TIM_OC_SetCompareCH3(TIM4, 0);
			break;
		case LL_TIM_CHANNEL_CH4:
			LL_TIM_CC_DisableChannel(TIM4, LL_TIM_CHANNEL_CH4);
			LL_TIM_OC_SetCompareCH4(TIM4, 0);
			break;
	}
}

void PWM_MoveForwards(uint16_t speed, double distanceCM) {
	ENC_ResetEncoders();

	PWM_SetSpeed(DIR_FWD, speed);

	// TODO Replace with PID
	while (ENC_GetEncoderDistanceCM(ENCODER_LEFT) < distanceCM);

	PWM_StopMotors();
}

/*
 * Sets the prescaler for the TIM4 Timer
 *
 * Parameters:
 *  - prescaler: The new value of the prescaler
 */
void PWM_SetPrescaler(uint32_t prescaler) {
	LL_TIM_SetPrescaler(TIM4, prescaler);
}

/*
 * Sets the prescaler such that a certain frequency is achieved.
 *
 * The value for the prescaler is calculated with a formula obtained
 * from experimental data. There is a small error between expected output
 * frequency and actual output frequency.
 */
void PWM_SetFrequency(float freq) {
	uint32_t prescaler = (1000000 / (6 * freq)) - 10.0/6;
	LL_TIM_SetPrescaler(TIM4, prescaler);
}

/*
 * Sets the speed of both motors such that the mouse can move forwards.
 *
 * Not PID-tuned, should not be used.
 *
 * Parameters:
 * 	- direction: The direction to move in. Can be one of DIR_FWD or DIR_REV
 * 	- speed: The speed to move both motors by
 */
void PWM_SetSpeed(uint8_t direction, uint16_t speed) {
	switch(direction) {
		case DIR_FWD:
			PWM_SetPWM(PWM_LEFT_FWD, speed);
			PWM_SetPWM(PWM_RIGHT_FWD, speed);
			break;
		case DIR_REV:
			PWM_SetPWM(PWM_LEFT_REV, speed);
			PWM_SetPWM(PWM_RIGHT_REV, speed);
			break;
	}
}

/*
 * Stops all motors from moving.
 */
void PWM_StopMotors() {
	PWM_StopPWM(LL_TIM_CHANNEL_CH1);
	PWM_StopPWM(LL_TIM_CHANNEL_CH2);
	PWM_StopPWM(LL_TIM_CHANNEL_CH3);
	PWM_StopPWM(LL_TIM_CHANNEL_CH4);
}
