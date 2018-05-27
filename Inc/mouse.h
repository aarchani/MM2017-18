/*
 * 	High Level interface for the micromouse
 *
 * 	Makes use of the PWM and IR interfaces
 */

#ifndef MOUSE_H
#define MOUSE_H

#define min(a,b) ((a)<(b)?(a):(b))
#define constrain(amt,low,high) ((amt)<(low)?(low):((amt)>(high)?(high):(amt)))

#include "motors.h"
#include "encoders.h"
#include "irled.h"

// For the maze array
#define HORZ	0
#define VERT	1

#define CLOCKWISE			0
#define COUNTERCLOCKWISE	1

// The left/right wheel speed ratio needed to go straight
#define SPEED_LR_RATIO 10.0/12

typedef enum {WALL_LEFT, WALL_RIGHT, WALL_FRONT} wallDirection;
typedef enum {NORTH, WEST, SOUTH, EAST} direction;


void MOUSE_Init();

void MOUSE_MoveUntilWall();

void MOUSE_MoveDistanceCM(float distance);
void MOUSE_Rotate90Deg(uint8_t direction);

void MOUSE_LeftHandFollowStep();

typedef struct {
	uint16_t x, y;
	uint8_t dir;
} mouse_t;

#endif
