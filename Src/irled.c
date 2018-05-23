#include "irled.h"
#include "adc.h"

double IR_MULTIPLIER = 1.0;

void IR_Init() {
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, GPIO_PIN_SET);
}

// whichLed is 0-3
double IR_GetDistance(uint8_t whichLed) {
	return ADC_readValue(whichLed) * IR_MULTIPLIER;
}
