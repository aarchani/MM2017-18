#include "mouse.h"
#include "stdbool.h"

// maze[0] is the horizantal walls
// maze[1] is the vertical walls
uint16_t maze[2][16] = {0};
mouse_t mouse = {0, 0, EAST};

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

void MOUSE_MoveForwardCell(mouse_t* mouse) {
	if(mouse->dir == NORTH && mouse->y != 0) {

		mouse->y = mouse->y-1;
	}
	else if(mouse->dir == SOUTH && mouse->y != 15) {

		mouse->y = mouse->y+1;
	}
	else if(mouse->dir == EAST && mouse->x != 15) {

		mouse->x = mouse->x+1;
	}
	else if(mouse->dir == WEST && mouse->x != 0) {

		mouse->x = mouse->x-1;
	}
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

mouse_t aboveCoord(mouse_t mouse) {
	return { mouse.x, mouse.y-1, mouse.dir};
}

mouse_t leftCoord(mouse_t mouse) {
	return { mouse.x-1, mouse.y, mouse.dir};
}

void MOUSE_AddWall(uint16_t* walls, mouse_t mouse) {
	walls[mouse.y] = (walls[mouse.y] | ( 1 << mouse.x ));
}

bool MOUSE_GetWall(uint16_t *walls, mouse_t mouse ) {
	return (walls[mouse.y] & ( 1 << mouse.x ));
}

void MOUSE_UpdateWalls(uint16_t *maze, mouse_t mouse, bool front, bool right, bool left) {
	if( mouse.dir == NORTH )
	{
		if( front && mouse.y != 0 )
			MOUSE_AddWall( &maze[HORZ], aboveCoord(mouse));
		if( left && mouse.x != 0 )
			MOUSE_AddWall( &maze[VERT], leftCoord(mouse));
		if( right )
			MOUSE_AddWall( &maze[VERT], mouse);
	}
	else if( mouse.dir == EAST )
	{
		if( left && mouse.y != 0 )
			MOUSE_AddWall( &maze[HORZ], aboveCoord(mouse));
		if( right )
			MOUSE_AddWall( &maze[HORZ], mouse);
		if( front )
			MOUSE_AddWall( &maze[VERT], mouse);
	}
	else if( mouse.dir == SOUTH )
	{
		if( front )
			MOUSE_AddWall( &maze[HORZ], mouse);
		if( right && mouse.x != 0 )
			MOUSE_AddWall( &maze[VERT], leftCoord(mouse));
		if( left )
			MOUSE_AddWall( &maze[VERT], mouse);
	}
	else if( mouse.dir == WEST )
	{
		if( right && mouse.y != 0 )
			MOUSE_AddWall( &maze[HORZ], aboveCoord(mouse));
		if( front && mouse.x != 0 )
			MOUSE_AddWall( &maze[VERT], leftCoord(mouse));
		if( left )
			MOUSE_AddWall( &maze[HORZ], mouse);
	}
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
