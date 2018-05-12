#include "motors.h"

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
			break;
		case LL_TIM_CHANNEL_CH2:
			LL_TIM_CC_DisableChannel(TIM4, LL_TIM_CHANNEL_CH2);
			break;
		case LL_TIM_CHANNEL_CH3:
			LL_TIM_CC_DisableChannel(TIM4, LL_TIM_CHANNEL_CH3);
			break;
		case LL_TIM_CHANNEL_CH4:
			LL_TIM_CC_DisableChannel(TIM4, LL_TIM_CHANNEL_CH4);
			break;
	}
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
