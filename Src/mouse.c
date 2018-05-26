#include "mouse.h"
#include "stdbool.h"

// maze[0] is the horizantal walls
// maze[1] is the vertical walls
uint16_t maze[2][16] = {0};
mouse_t mouse = {0, 0, EAST};
uint16_t distance[16][16] = {-1};

void MOUSE_Init( uint16_t maze[2][16], mouse_t *mouse) {
	

	for(int i=0; i<16; i=i+1)
	{
		maze[HORZ][i] = 0;
		maze[VERT][i] = 32768;
	}
	maze[HORZ] = 65535;
	mouse = {0, 0, EAST};
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

bool MOUSE_GetWall(uint16_t* walls, uint16_t x, uint16_t y ) {
	return (walls[y] & ( 1 << x ));
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

bool MOUSE_IsMazeSolved(mouse_t mouse) {
	if( (mouse.x == 7 || mouse.x == 8) && (mouse.y == 7 || mouse.y == 8) )
		return true;
	return false;
}

bool MOUSE_HasMouseReturned(mouse_t mouse) {
	if( mouse.x == 0 && mouse.y == 0 )
		return true;
	return false;
}

void MOUSE_PathfinderFloodFill(uint16_t* distance[16][16], uint16_t* maze[2][16]) {
	distance[7][7] = 0;
	distance[7][8] = 0;
	distance[8][7] = 0;
	distance[8][8] = 0;

	floodFill(7, 7, 0, &distance, &maze);
	floodFill(7, 8, 0, &distance, &maze);
	floodFill(8, 7, 0, &distance, &maze);
	floodFill(8, 8, 0, &distance, &maze);
}

void floodFill(uint16_t x, uint16_t y, uint16_t dist, uint16_t distance[16][16], uint16_t* maze) {
	distance[x][y] = dist;
	//Right
	if( !(MOUSE_GetWall( &maze[VERT], x, y)) && (x != 15) && (distance[x+1][y] == -1)) 
		floodFill(x+1, y, dist+1, &distance[16][16], &maze);
	//Left
	if( !(MOUSE_GetWall( &maze[VERT], x-1, y)) && (x != 0) && (distance[x-1][y] == -1)) 
		floodFill(x-1, y, dist+1, &distance[16][16], &maze);
	//Up
	if( !(MOUSE_GetWall( &maze[HORZ], x, y-1)) && (y != 0) && (distance[x][y-1] == -1)) 
		floodFill(x, y-1, dist+1, &distance[16][16], &maze);
	//Down
	if( !(MOUSE_GetWall( &maze[HORZ], x, y)) && (y != 15) && (distance[x][y+1] == -1)) 
		floodFill(x, y+1, dist+1, &distance[16][16], &maze);
}

void MOUSE_PathfinderSolveMaze() {

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
