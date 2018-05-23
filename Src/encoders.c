#include "encoders.h"

/*
 * Returns the actual "ticks" that the encoder has rotated, in
 * raw format.
 *
 * Checks to see if the input is a valid TIM Type,
 * otherwise returns 0.
 *
 * Parameters:
 * 	- encoderSide: One of ENCODER_LEFT or ENCODER_RIGHT, a TIM_TypeDef pointer
 *
 * Returns: The number of ticks that the encoder has made since it was last reset,
 * 			or 0 if an invalid encoderSide was specified
 */
uint16_t ENC_GetEncoderTicks(TIM_TypeDef* encoderSide) {
	if(encoderSide == ENCODER_LEFT)	 return 0xFFFF & ENCODER_LEFT->CNT;
	if(encoderSide == ENCODER_RIGHT) return 0xFFFF & ENCODER_RIGHT->CNT;

	return 0;
}

/*
 * Returns the distance that the wheel has rotated, in floating point format.
 *
 * Checks to see if the input is a valid TIM Type, otherwise returns 0.
 *
 * Parameters:
 * 	- encoderSide: One of ENCODER_LEFT or ENCODER_RIGHT, a TIM_TypeDef pointer
 *
 * Returns: The distance in centimeters that the wheel has rotated
 */
double ENC_GetEncoderDistanceCM(TIM_TypeDef* encoderSide) {
	int ticks = ENC_GetEncoderTicks(encoderSide);

	if (encoderSide == ENCODER_LEFT)  return ticks * CM_PER_TICK_LEFT;
	if (encoderSide == ENCODER_RIGHT) return ticks * CM_PER_TICK_RIGHT;

	return 0;
}

/*
 * Resets the encoder internal counter for a given wheel.
 *
 * Does nothing if an invalid encoderSide is specified.
 *
 * Parameters:
 * 	- encoderSide: One of ENCODER_LEFT or ENCODER_RIGHT, a TIM_TypeDef pointer
 */
void ENC_ResetEncoder(TIM_TypeDef* encoderSide) {
	if(encoderSide == ENCODER_LEFT)	 ENCODER_LEFT->CNT  = 0;
	if(encoderSide == ENCODER_RIGHT) ENCODER_RIGHT->CNT = 0;
}

/*
 * Resets both encoders.
 *
 */
void ENC_ResetEncoders() {
	ENCODER_LEFT->CNT  = 0;
	ENCODER_RIGHT->CNT = 0;
}
