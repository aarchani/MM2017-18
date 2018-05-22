#include "irled.h"
#include "adc.h"

void IR_Init() {
	// TODO
}

// whichLed is 0-3
double IR_GetDistance(uint8_t whichLed) {
	return ADC_readValue(whichLed);
}
