#include "Maze.hpp"
#include <algorithm>

using namespace std;
const unsigned char directions[4] = {'N', 'E', 'S', 'W'};

class RandomMaze
{
	public:
		Maze* maze;
		unsigned short visited[16];

RandomMaze()//class constructer
{
	maze = new Maze();
	maze->MazeFull();
	for(int i = 0; i < 16; i++)
		visited[i] = 0;
	int x = rand() % 16;
	int y = rand() % 16;
	randomizer((unsigned short) x ,(unsigned short) y );
}

~RandomMaze()//class deconstructer
{
	//delete maze;
}

//Recursive depth-first search maze genorator
void randomizer( unsigned short posH , unsigned short posV)
{
//	cout << "Randomizer: " << posH << ", " << posV << endl;
	unsigned short mod = pow(2, posH);//updating the visieted array with the current position
	visited[posV] = (visited [posV] | mod);
	unsigned char dir[] = {'N', 'E', 'S', 'W'};
//	random_shuffle(dir[0], dir[3]);//generating a random array of directions to be visited
	for(int i =0; i<4; i++)//iterated through every direction in the random array
	{
		int random = rand() % (4-i);
		unsigned char d = dir[random];
//		cout << d << endl;
		if((d == 'N') && (posV != 0) )//checking if North can be or has been visited
		{	
			unsigned short m = pow(2, posH);
			if((visited[posV-1] & m) == 0)
			{
				maze->removeHWall(posV-1, posH); //remove the north wall
				randomizer(posH, posV-1);
			}	
		}
	
		if((d == 'E') && (posH != 15) )//checking if East can be or has been visited
		{	
			unsigned short m = pow(2, posH+1);
			if((visited[posV] & m) == 0)
			{
				maze->removeVWall(posV, posH); //remove the east wall
				randomizer(posH+1, posV);
			}
		}
		if((d == 'S') && (posV != 15) )//checking if south can be or has been visited
		{	
			unsigned short m = pow(2, posH);
			if((visited[posV+1] & m) == 0)
			{
				maze->removeHWall(posV, posH); //remove the south wall
				randomizer(posH, posV+1);
			}
		}
	
		if((d == 'W') && (posH != 0) )//checking if west can be or has been visited
		{	
			unsigned short m = pow(2, posH-1);
			if((visited[posV] & m) == 0)
			{
				maze->removeVWall(posV, posH-1); //remove the west wall
				randomizer(posH-1, posV);
			}
		}
		for(int i = random; i < 4; i++)
		{
			dir[i] = dir[i+1];
		}
		
	}
}

bool getWall( unsigned short vert, unsigned short horiz, unsigned char c)
{
	if( c == 'N' )
	{
		if( vert == 0 )
			return true;
		else
			return maze->getHWall(vert-1, horiz);
	}
	else if( c == 'E' )
	{
		if( horiz == 15 )
			return true;
		else
			return maze->getVWall(vert, horiz);
	}
	else if( c == 'S' )
	{
		if(vert == 15 )
			return true;
		else 
			return maze->getHWall(vert, horiz);
	}
	else if( c == 'W' )
	{
		if( horiz == 0 )
			return true;
		else
			return maze->getVWall(vert, horiz-1);
	}
	else 
		return true;
}
void ieeeMaze()
{
	maze->addHWall(0,0);
	maze->removeVWall(0,0);
	maze->removeHWall(7,7);
	maze->removeHWall(7,8);
	maze->removeVWall(7,7);
	maze->removeVWall(8,7);

}
 
};
