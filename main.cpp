#include "RandomMaze.hpp"
#include "Maze.hpp"
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <unistd.h>
using namespace std;



int main()
{
	
	unsigned char n = 'N';
//	unsigned char s = 'S';
	unsigned char e = 'E';
//	unsigned char w = 'W';
	unsigned short x = 0;
	unsigned short y = 0;
	
	Maze newMaze = Maze();
	mouse myMouse = mouse();
	
/*	newMaze.MazeFull();
	for(x=0; x<16; x++)
	{
		for(y=0;y<16;y++)
		{
		sleep(1);
		newMaze.removeVWall(x,y);
		newMaze.removeHWall(x,y);
		newMaze.print(x,y,n);
		}
	}
	RandomMaze myRandom = RandomMaze();
	myRandom.maze->print(x,y,e);
	myRandom.ieeeMaze();
	myRandom.maze->print(x,y,e);*/
}
