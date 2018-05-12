#ifndef GYRO_H
#define GYRO_H

// TODO these are probably not connected on the PCB ...
#define GYRO_CS_PIN GPIO_PIN_12
#define GYRO_CS_PORT GPIOD

#define READ_STATUS_REG = 0x0200;

double GYRO_GetAngle();
void GYRO_ResetAngle();

uint8_t GYRO_ReadStatusReg();

#endif
