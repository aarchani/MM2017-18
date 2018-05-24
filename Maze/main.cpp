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
		myMouse.inMaze.print(myMouse.vert, myMouse.horz, myMouse.direction);
		usleep(50000);
	}
//	cout << "\n I am the champion\n";
}

int main()
{
	
	mouse ffMouse = mouse(1);
	ffMouse.inMaze.printFF(7,7,'E',ffMouse.distance);
	RandomMaze myRandom;
	myRandom.getWall(0,0,'N');
	myRandom.getWall(15,15,'E');
	myRandom.getWall(15,15,'S');
	myRandom.getWall(0,0,'W');
	lhf( ffMouse, myRandom);
}
