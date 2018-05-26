#include "mouse.h"
#include "stdbool.h"

// maze[0] is the horizantal walls
// maze[1] is the vertical walls
uint16_t maze[2][16] = {0};
coord_t currentCoord = {0};
uint8_t currentDirection = NORTH;

void MOUSE_Init() {
}

void MOUSE_MoveDistanceCM(float distance) {
	ENC_ResetEncoders();

	uint32_t speed = 13;

	PWM_SetPWM(PWM_LEFT_FWD, speed * SPEED_LR_RATIO);
	PWM_SetPWM(PWM_RIGHT_FWD, speed);

	// TODO Replace with PID
	while (ENC_GetEncoderDistanceCM(ENCODER_LEFT) < distance);

	PWM_StopMotors();
}

void MOUSE_MoveForwardCell() {
}

// FIXME
void MOUSE_Rotate90Deg(uint8_t direction) {
	ENC_ResetEncoders();
	float distance = 5;
	uint32_t speed = 20;

	float distLeft  = ENC_GetEncoderDistanceCM(ENCODER_LEFT);
	float distRight = ENC_GetEncoderDistanceCM(ENCODER_RIGHT);

	switch (direction) {
		case CLOCKWISE:
			PWM_SetPWM(PWM_LEFT_FWD, speed * SPEED_LR_RATIO);
			PWM_SetPWM(PWM_RIGHT_REV, speed);
			while (distLeft < distance
				   || -distRight > -distance) {

				distLeft  = ENC_GetEncoderDistanceCM(ENCODER_LEFT);
				distRight = ENC_GetEncoderDistanceCM(ENCODER_RIGHT);
			}
			break;

		case COUNTERCLOCKWISE:
			break;
	}

	PWM_StopMotors();
}

void MOUSE_UpdateWalls() {
}

bool MOUSE_GetWall(uint8_t whichWall) {
	return false;
}

bool MOUSE_IsMazeSolved() {
	return false;
}

/*
 * Moves the mouse by a single cell
 *
 */
void MOUSE_LeftHandFollowStep() {
	MOUSE_UpdateWalls();

	// If there isn't a wall on the left, move to the left cell
	if (!MOUSE_GetWall(WALL_LEFT)) {
		MOUSE_Rotate90Deg(COUNTERCLOCKWISE);
		MOUSE_MoveForwardCell();
	}
	else if (!MOUSE_GetWall(WALL_FRONT)) {
		MOUSE_MoveForwardCell();
	}
	else {
		MOUSE_Rotate90Deg(CLOCKWISE);
	}
}
