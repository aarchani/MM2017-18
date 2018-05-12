//#include "RandomMaze.hpp"
//#include "Maze.hpp"
#include "mouse.cpp"
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <unistd.h>
using namespace std;

void lhf(mouse myMouse, RandomMaze myRandom)
{
	unsigned short f = 0;
	unsigned short r = 0;
	unsigned short l = 0;
	while(myMouse.notDone())
	{
		cout <<  myRandom.getWall( myMouse.vert, myMouse.horz, myMouse.direction) << endl; 
		f = myRandom.getWall( myMouse.vert, myMouse.horz, myMouse.direction);
		l = myRandom.getWall( myMouse.vert, myMouse.horz, myMouse.left());
		r = myRandom.getWall( myMouse.vert, myMouse.horz, myMouse.right());
		myMouse.updateWallsAdd(f, r, l);
		if( !l )
		{
			myMouse.turn(0);
			myMouse.moveForward();
		}
		else if( !f )
		{
			myMouse.moveForward();
		}
		else
		{
			myMouse.turn(1);
		}
//	myMouse.print();
		//myRandom.maze->print( myMouse.vert, myMouse.horz, myMouse.direction );
		myMouse.inMaze.print(myMouse.vert, myMouse.horz, myMouse.direction);
		usleep(90000);
	}
	cout << "\n I am the champion\n";
}

int main()
{
	
/*	unsigned char n = 'N';
//	unsigned char s = 'S';
	unsigned char e = 'E';
//	unsigned char w = 'W';
	unsigned short x = 0;
	unsigned short y = 0;
*/
//	Maze newMaze = Maze();
//	mouse myMouse = mouse();
//	myMouse.inMaze.print(x,y,e);
	mouse ffMouse = mouse(1);
//	ffMouse.print();
//	ffMouse.inMaze.print(x,y,e);
	ffMouse.inMaze.printFF(7,7,'E',ffMouse.distance);
	RandomMaze myRandom;
//	bool x = ffMouse.notDone();
	myRandom.getWall(0,0,'N');
	myRandom.getWall(15,15,'E');
	myRandom.getWall(15,15,'S');
	myRandom.getWall(0,0,'W');
//	lhf( ffMouse, myRandom);

/*		
	for( int i =0; i < 5; i++ )
	{
		myMouse.print();
		myMouse.turn(0);
	}
	newMaze.MazeFull();
	newMaze.print(x,y,e);

	for(x=0; x<16; x++)
	{
		for(y=0;y<16;y++)
		{
		sleep(1);
		cout << "N: " << newMaze.getVWall( x, y ) << "	";
		cout << "E: " << newMaze.getHWall( x, y ) << "	";
		newMaze.removeVWall(x,y);
		newMaze.removeHWall(x,y);
		cout << "N: " << newMaze.getVWall( x, y) << "	";
		cout << "E: " << newMaze.getHWall( x, y) << endl;
		
		newMaze.print(x,y,n);
		}
	}
*/		
//	myRandom.maze->print(x,y,e);
/*	for( int i = 0; i < 16; i++)
	{
		for( int j = 0; j < 16; j++ )
		{
			cout << "N: " << myRandom.getWall( i, j, 'N') << "	";
			cout << "E: " << myRandom.getWall( i, j, 'E') << "	";
			cout << "S: " << myRandom.getWall( i, j, 'S') << "	";
			cout << "W: " << myRandom.getWall( i, j, 'W') << endl;
			myRandom.maze->print( i, j, 'E');
			sleep(1);
		}

	}
	myRandom.ieeeMaze();
	myRandom.maze->print(x,y,e);
	while(1)
	{
		cout <<  myRandom.getWall( myMouse.vert, myMouse.horz, myMouse.direction) << endl; 
		
		if( !myRandom.getWall( myMouse.vert, myMouse.horz, myMouse.left()) )
		{
			myMouse.turn(0);
			myMouse.moveForward();
		}
		else if( !myRandom.getWall( myMouse.vert, myMouse.horz, myMouse.direction) )
		{
		//	myMouse.
			myMouse.moveForward();
		}
		else
		{
			myMouse.turn(1);
		}
	myMouse.print();
	myRandom.maze->print( myMouse.vert, myMouse.horz, myMouse.direction );
	usleep(20000);
	}*/
}
