#include <tgmath.h>

#include "mouse.h"
#include "stdbool.h"

// maze[0] is the horizantal walls
// maze[1] is the vertical walls
uint16_t maze[2][16] = {0};
mouse_t mouse = {0, 0, EAST};
uint16_t distance[16][16] = {-1};

void MOUSE_Init() {


	//for(int i=0; i<16; i=i+1)
	//{
	//	maze[HORZ][i] = 0;
	//	maze[VERT][i] = 32768;
	//}
	//maze[HORZ] = 65535;
	//mouse = {0, 0, EAST};
}

void MOUSE_MoveDistanceCM(float distance) {
	ENC_ResetEncoders();

	float maxSpeed = 0.15;
	float errorMargin = 0.001;

	float turnKP = 0.01;
	float turnKD = 0.0;

	float avgDist = ENC_GetAvgDistCM();
	float turnError = ENC_GetEncoderDistanceCM(ENCODER_LEFT) - ENC_GetEncoderDistanceCM(ENCODER_RIGHT);
	float turnErrorP;
	float turnErrorD;
	float turnErrOld = turnError;
	float turnControlSignal;

	float distKP = 0.50;
	float distKD = 0.0;

	float distError = distance - avgDist;
	float distErrOld = distError;
	float distErrorP;
	float distErrorD;
	float distControlSignal;

	float speedLeft, speedRight;

	while (fabs(distError) > errorMargin) {
	//while (1) {
		distError = distance - avgDist;
		distErrorP = distError * distKP;

		distErrorD = distError - distErrOld;
		distErrorD *= distKD;

		turnError = ENC_GetEncoderDistanceCM(ENCODER_LEFT) - ENC_GetEncoderDistanceCM(ENCODER_RIGHT);
		turnErrorP = turnError * turnKP;

		turnErrorD = turnError - turnErrOld;
		turnErrorD *= turnKD;

		distControlSignal = distErrorP + distErrorD;
		turnControlSignal = turnErrorP + turnErrorD;

		speedLeft  = maxSpeed ; // - turnControlSignal;
		speedRight = maxSpeed ; // + turnControlSignal;

		//speedLeft = constrain(speedLeft * distErrTotal, -maxSpeed, maxSpeed);
		//speedRight = constrain(speedRight * distErrTotal, -maxSpeed, maxSpeed);

		speedLeft =  min(speedLeft * distControlSignal, maxSpeed);
		speedRight = min(speedRight * distControlSignal, maxSpeed);

		PWM_SetPWMVector(MOTOR_LEFT,  speedLeft);
		PWM_SetPWMVector(MOTOR_RIGHT, speedRight);

		avgDist = ENC_GetAvgDistCM();
		turnErrOld = turnError;
		distErrOld = distError;
	}

	//PWM_StopMotors();
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

mouse_t aboveCoord() {
	mouse_t ret;
	ret.x = mouse.x;
	ret.y = mouse.y - 1;
	ret.dir = mouse.dir;

	return ret;
}

mouse_t leftCoord() {
	mouse_t ret;
	ret.x = mouse.x - 1;
	ret.y = mouse.y - 1;
	ret.dir = mouse.dir;

	return ret;
}

void MOUSE_AddWall(uint16_t* walls, mouse_t mouse) {
	walls[mouse.y] = (walls[mouse.y] | ( 1 << mouse.x ));
}

bool MOUSE_GetWall(uint16_t* walls, uint16_t x, uint16_t y ) {
	return (walls[y] & ( 1 << x ));
}

void MOUSE_UpdateWalls(bool front, bool right, bool left) {
	if( mouse.dir == NORTH )
	{
		if( front && mouse.y != 0 )
			MOUSE_AddWall( &maze[HORZ], aboveCoord());
		if( left && mouse.x != 0 )
			MOUSE_AddWall( &maze[VERT], leftCoord());
		if( right )
			MOUSE_AddWall( &maze[VERT], mouse);
	}
	else if( mouse.dir == EAST )
	{
		if( left && mouse.y != 0 )
			MOUSE_AddWall( &maze[HORZ], aboveCoord());
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
			MOUSE_AddWall( &maze[VERT], leftCoord());
		if( left )
			MOUSE_AddWall( &maze[VERT], mouse);
	}
	else if( mouse.dir == WEST )
	{
		if( right && mouse.y != 0 )
			MOUSE_AddWall( &maze[HORZ], aboveCoord());
		if( front && mouse.x != 0 )
			MOUSE_AddWall( &maze[VERT], leftCoord());
		if( left )
			MOUSE_AddWall( &maze[HORZ], mouse);
	}
}

bool MOUSE_IsMazeSolved() {
	if( (mouse.x == 7 || mouse.x == 8) && (mouse.y == 7 || mouse.y == 8) )
		return true;
	return false;
}

bool MOUSE_HasMouseReturned() {
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

void floodFill(uint16_t x, uint16_t y) {
	/*distance[x][y] = dist;
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
*/
	uint16_t min = 999;
	if( !((x == 7 || x == 8 ) && ( y == 7 || y == 8 )) )
	{
		if( y != 0 )
			if( !MOUSE_GetWall(&maze[HORZ],x, y-1))
				if( distance[x][y-1] < min )
					min = distance[x][y-1];
		if( y != 15 )
			if( !MOUSE_GetWall(&maze[HORZ],x, y))
				if( distance[x][y+1] < min )
					min = distance[x][y+1];
		if( x != 0 )
			if( !MOUSE_GetWall(&maze[VERT],x-1, y))
				if( distance[x-1][y] < min )
					min = distance[x-1][y];
		if( x != 15 )
			if( !MOUSE_GetWall(&maze[VERT],x, y))
				if( distance[x+1][y] < min )
					min = distance[x+1][y];
		if( distance[x][y] != min + 1 )
		{
			distance[x][y] = min +1;
			if( x != 15 )
				floodFill(x+1, y);
			if( x != 0 )
				floodFill(x-1, y);
			if( y != 0 )
				floodFill(x, y-1);
			if( y != 15 )
				floodFill(x, y+1);
		}
	}
}

void MOUSE_FloodFill() {
	
	uint16_t frontWall = 0;
    uint16_t rightWall = 0;
    uint16_t leftWall = 0;
    uint16_t next;
    bool hasStarted = false;
    while( !(mouse.x == 0 && mouse.y == 0) || !hasStarted) //myMouse->notDone())
    {
		//Add IR sensor calls
        MOUSE_UpdateWalls(frontWall, rightWall, leftWall);
        next = myMouse->getSmallestNeighbor();
        myMouse->floodFill(mouse.x, mouse.y);
        if( next == 0 )
        {
            //MoveForward
            hasStarted = true;
        }
        else if( next == 1 )
        {
            //TurnLeft
            //MoveForward
            hasStarted = true;
        }
        else if( next == 2)
        {
            //TurnRight
            //MoveForward
            hasStarted = true;
        }
        else
        {
            //Turn Around
        }
}
//0-forward, 1-left, 2-right, 3-uturn

int getSmallestNeighbor()
{
    uint16_t dist = 999;
    uint16_t ret;
    if( mouse.dir == NORTH)
    {
        if( mouse.y != 0)
            if( !MOUSE_GetWall(&maze[HORZ], mouse.x,mouse.y-1) && (distance[mouse.x][mouse.y-1] < dist))
            {
                dist = distance[mouse.x][mouse.y-1];
                ret = 0;
            }
        if( mouse.x != 0)
            if( !MOUSE_GetWall(&maze[VERT], mouse.x-1,mouse.y) && (distance[mouse.x-1][mouse.y] < dist))
            {
                dist = distance[mouse.x-1][mouse.y];
                ret =  1;
            }
        if( mouse.x != 15)
            if( !MOUSE_GetWall(&maze[VERT], mouse.x,mouse.y) && ( distance[mouse.x+1][mouse.y] < dist))
            {
                dist = distance[mouse.x+1][mouse.y];
                ret =  2;
            }
    }

    if( direction == 'S')
    {
        if( mouse.y != 15)
            if( !MOUSE_GetWall(&maze[HORZ] , mouse.x, mouse.y) && (distance[mouse.x][mouse.y+1] < dist))
            {
                dist = distance[mouse.x][mouse.y+1];
                ret = 0;
            }
        if( mouse.x != 0)
            if( !MOUSE_GetWall(&maze[VERT], mouse.x-1,mouse.y) && (distance[mouse.x-1][mouse.y] < dist))
            {
                dist = distance[mouse.x-1][mouse.y];
                ret = 2;
            }
        if( mouse.x != 15)
            if( !MOUSE_GetWall(&maze[VERT], mouse.x,mouse.y) && (distance[mouse.x+1][mouse.y] < dist))
            {
                dist = distance[mouse.x+1][mouse.y];
                ret = 1;
            }
    }

 if( direction == 'E')
    {
        if( mouse.y != 0)
            if( !MOUSE_GetWall(&maze[HORZ] , mouse.x, mouse.y-1) && (distance[mouse.x][mouse.y-1] < dist))
            {
                dist = distance[mouse.x][mouse.y-1];
                ret =  1;
            }
        if( mouse.y != 15)
            if( !MOUSE_GetWall(&maze[HORZ] , mouse.x, mouse.y) && (distance[mouse.x][mouse.y+1] < dist))
            {
                dist = distance[mouse.x][mouse.y+1];
                ret = 2;
            }
        if( mouse.x != 15)
            if( !MOUSE_GetWall(&maze[VERT], mouse.x,mouse.y) && (distance[mouse.x+1][mouse.y] < dist))
            {
                dist = distance[mouse.x+1][mouse.y];
                ret = 0;
            }
    }

    if( direction == 'W')
    {
        if( mouse.y != 0)
            if( !MOUSE_GetWall(&maze[HORZ] , mouse.x,mouse.y-) && (distance[mouse.x][mouse.y-1] < dist ))
            {
                dist = distance[mouse.x][mouse.y-1];
                ret = 2;
            }
        if( mouse.x != 0)
            if( !MOUSE_GetWall(&maze[VERT] , mouse.x-1,mouse.y) && (distance[mouse.x-1][mouse.y] <dist ))
            {
                dist = distance[mouse.x-1][mouse.y];
                ret =  0;
            }
        if( mouse.y != 15)
            if( !MOUSE_GetWall(&maze[HORZ] , mouse.x,mouse.y) && (distance[mouse.x][mouse.y+1] < dist))
            {
                dist = distance[mouse.x][mouse.y+1];
                ret = 1;
            }
    }
    if( dist == 999 )
        ret = 3;
    return ret;
}



void pathFollower(){
	//myMouse->turn(2); turn 180
	uint16_t next;
	while(!MOUSE_IsMazeSolved())
	{
		next = getNextMove(); //TODO: implement getNextMove
		distance[mouse.x][mouse.y] = 999;
		if (next == 0 )
		{
		//	myMouse->moveForward();
		}
		else if( next == 1 )
		{
			//myMouse->turn(0); :turn left
			//myMouse->moveForward();
		}
		else if( next == 2)
		{
			//myMouse->turn(1); : turn right
			//myMouse->moveForward();
		}
	}
	//myMouse->turn(2); : turn 180 degree
	int x = 1;
	while( !(mouse.y == 0 && mouse.x == 0 ))
	{
		next = myMouse->getNextReturnMove();
		distance[mouse.x][mouse.y] = x;
		x++;
		if (next == 0 )
		{
		//	myMouse->moveForward();
		}
		else if( next == 1 )
		{
			//myMouse->turn(0); : :turn right
		//	myMouse->moveForward();
		}
		else if( next == 2)
		{
			//myMouse->turn(1); :turn right
			//myMouse->moveForward(); :self explanatory
		}
	}
}


/*
 * Moves the mouse by a single cell
 *
 */
void MOUSE_LeftHandFollowStep() {
	//MOUSE_UpdateWalls();

	// If there isn't a wall on the left, move to the left cell
	//if (!MOUSE_GetWall(WALL_LEFT)) {
	//	MOUSE_Rotate90Deg(COUNTERCLOCKWISE);
	//	MOUSE_MoveForwardCell();
	//}
	//else if (!MOUSE_GetWall(WALL_FRONT)) {
	//	MOUSE_MoveForwardCell();
	//}
	//else {
	//	MOUSE_Rotate90Deg(CLOCKWISE);
	//}
}
