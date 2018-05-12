#include "gpio.h"
#include "spi.h"

#include "gyro.h"


double GYRO_GetAngle() {

}

void GYRO_ResetAngle() {

}

uint8_t GYRO_ReadStatusReg() {
	HAL_GPIO_WritePin(GYRO_CS_PORT, GYRO_CS_PIN, GPIO_PIN_RESET);

	// TODO

	HAL_GPIO_WritePin(GYRO_CS_PORT, GYRO_CS_PIN, GPIO_PIN_SET);
}
