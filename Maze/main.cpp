#include "mouse.cpp"
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <unistd.h>
using namespace std;

void ff(mouse *myMouse, RandomMaze myRandom)
{
	unsigned short f = 0;
	unsigned short r = 0;
	unsigned short l = 0;
	int next;
	int count = 0;
	bool hasStarted = false;
	while( !(myMouse->vert == 0 && myMouse->horz == 0) || !hasStarted) //myMouse->notDone())
	{
		//cout <<  myRandom.getWall( myMouse.vert, myMouse.horz, myMouse.direction) << endl; 
		f = myRandom.getWall( myMouse->vert, myMouse->horz, myMouse->direction);
		l = myRandom.getWall( myMouse->vert, myMouse->horz, myMouse->left());
		r = myRandom.getWall( myMouse->vert, myMouse->horz, myMouse->right());
		myMouse->updateWallsAdd(f, r, l);
		next = myMouse->getSmallestNeighbor();
		myMouse->floodDistance(myMouse->horz, myMouse->vert);
		if( next == 0 )
		{
			myMouse->moveForward();
			hasStarted = true;
			count++;
		}
		else if( next == 1 )
		{
			myMouse->turn(0);
			myMouse->moveForward();
			hasStarted = true;
			count++;
		}
		else if( next == 2)
		{
			myMouse->turn(1);
			myMouse->moveForward();
			hasStarted = true;
			count ++;
		}
		else
		{
			myMouse->turn(2);
			count++;
		}
		myMouse->inMaze.printFF(myMouse->vert, myMouse->horz, myMouse->direction, myMouse->distance);
		usleep(30000);
	}
		//myMouse->turn(2);
		//myMouse->moveForward();
		//myMouse->floodDistance(myMouse->horz, myMouse->vert);

		cout << "Number of steps to map: " << count << endl;
//	cout << "\n I am the champion\n";
}
void lhf(mouse *myMouse, RandomMaze myRandom)
{
	unsigned short f = 0;
	unsigned short r = 0;
	unsigned short l = 0;
	bool hasStarted = false;
	while( !(myMouse->vert == 0 && myMouse->horz == 0) || !hasStarted)
	{
		
		//cout <<  myRandom.getWall( myMouse.vert, myMouse.horz, myMouse.direction) << endl; 
		f = myRandom.getWall( myMouse->vert, myMouse->horz, myMouse->direction);
		l = myRandom.getWall( myMouse->vert, myMouse->horz, myMouse->left());
		r = myRandom.getWall( myMouse->vert, myMouse->horz, myMouse->right());
		myMouse->updateWallsAdd(f, r, l);
		if( !l )
		{
			myMouse->turn(0);
			myMouse->moveForward();
			hasStarted = true;
		}
		else if( !f )
		{
			myMouse->moveForward();
			hasStarted = true;
		}
		else
		{
			myMouse->turn(1);
		}
		myMouse->inMaze.print(myMouse->vert, myMouse->horz, myMouse->direction);
		usleep(50000);
	}
//	cout << "\n I am the champion\n";
}

void pathFollower(mouse *myMouse)
{
	myMouse->turn(2);
	int next;
	int count = 0;
	while( myMouse->notDone())
	{
		next = myMouse->getNextMove();
		myMouse->distance[myMouse->horz][myMouse->vert] = 999;
		if (next == 0 )
		{
			myMouse->moveForward();
			count++;
		}
		else if( next == 1 )
		{
			myMouse->turn(0);
			myMouse->moveForward();
			count++;
		}
		else if( next == 2)
		{
			myMouse->turn(1);
			myMouse->moveForward();
			count++;
		}
		myMouse->inMaze.printFF(myMouse->vert, myMouse->horz, myMouse->direction, myMouse->distance);
		usleep(100000);
	}
	myMouse->turn(2);
	count++;
	//myMouse->inMaze.printFF(myMouse->vert, myMouse->horz, myMouse->direction, myMouse->distance); 
	int x = 1;
	while( !(myMouse->vert == 0 && myMouse->horz == 0 ))
	{
		next = myMouse->getNextReturnMove();
		myMouse->distance[myMouse->horz][myMouse->vert] = x;
		x++;
		if (next == 0 )
		{
			myMouse->moveForward();
		}
		else if( next == 1 )
		{
			myMouse->turn(0);
			myMouse->moveForward();
		}
		else if( next == 2)
		{
			myMouse->turn(1);
			myMouse->moveForward();
		}
		myMouse->inMaze.printFF(myMouse->vert, myMouse->horz, myMouse->direction, myMouse->distance);
		usleep(100000);
	}
		cout << "Steps to solve maze and return: " << x + count << endl;
}

int main()
{
	
	mouse ffMouse = mouse(1);
	//ffMouse.inMaze.printFF(7,7,'E',ffMouse.distance);

	RandomMaze myRandom;
	ff( &ffMouse, myRandom);
	//ffMouse.inMaze.removeVWall(7,6);
	//ffMouse.FF();
	ffMouse.inMaze.printFF(ffMouse.vert, ffMouse.horz, ffMouse.direction, ffMouse.distance); 
	pathFollower(&ffMouse);
//	ffMouse.dfs();
}
