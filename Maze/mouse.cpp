#include "Maze.hpp"
#include "RandomMaze.hpp"
#include <iostream>
#include <iomanip>
#include <stack>
using namespace std;

struct coord
{
	public:
	unsigned short x;
	unsigned short y;
	
coord(unsigned short a, unsigned short b)
{
	x = a;
	y = b;
}
	
vector<coord> adjacent(Maze inMaze)
{
	vector<coord> adj;
	if( x != 0)
		if(!inMaze.getHWall(this->x-1, this->y))
			adj.push_back( coord(this->x-1, this->y) );
	if( x != 15 )
		if(!inMaze.getHWall(this->x, this->y) )
			adj.push_back( coord(this->x+1, this->y) );
	if( y != 0 )
		if(!inMaze.getVWall(this->x, this->y-1))
			adj.push_back( coord(this->x, this->y-1) );
	if( y != 15 )
		if(!inMaze.getVWall(this->x, this->y))
			adj.push_back( coord(this->x, this->y+1) );
	return adj;
}
};

class mouse
{
   public:
	unsigned char direction;//Which direction the mouse is facing
	unsigned short vert;//Verticle position in maze, 0-15
	unsigned short horz;//Horizontal position, 0-15
	Maze inMaze;
	unsigned short distance[16][16];//floodfill distance 
//Constructer
mouse()
{
	direction = 'E';//Initial direction in maze is east
	vert = 0;//Starting at position 0,0
	horz = 0;
	inMaze.MazeFull();//Initiallizing a fullmaze for dfs algorithm
	for(int i = 0; i < 16; i++)
	{
		for(int j = 0; j < 15; j++)
		{
			distance[i][j] = -1;
		}
	}
}
mouse(int x)
{

	direction = 'E';//Initial direction in maze is east
	vert = 0;//Starting at position 0,0
	horz = 0;
	//Initiallizing an empty maze for floodfill algorithm
	for( int i = 0; i < 8; i++)
	{
		for( int j = 0; j < 8; j++ )
		{
			distance[i][j] = abs( i-7 ) + abs( j-7 );
		//	cout << "i= " << i << " j= " << j << " : " << distance[i][j] << endl;
			distance[15-i][j] = distance[i][j];
		//	cout << "i= " << 15-i << " j= " << j << " : " << distance[15-i][j] << endl;
			distance[15-i][15-j] = distance[i][j];
		//	cout << "i= " << 15-i << " j= " << 15-j << " : " << distance[15-i][15-j] << endl;
			distance[i][15-j] = distance[i][j];
		//	cout << "i= " << i << " j= " << 15-j << " : " << distance[i][15-j] << endl;
		}
	}

}

void print()
{
	cout << "Verticle: " << vert << " Horizontal: " << horz;
	cout << " Direction: " << direction << endl;
	for( int i=0; i<16; i++)
	{
		for( int j=0; j<16; j++)
		{
			cout << distance[j][i] << "	";
		}
		cout << endl;
	}
}
bool notDone()
{
	if( vert == 7 && horz == 7 )
		return false;
	else if ( vert == 7 && horz == 8 )
		return false;
	else if ( vert == 8 && horz == 7 )
		return false;
	else if ( vert == 8 && horz == 8 )
		return false;
	else
		return true;
}
/*	Function that updates the mouses position in the maze
	Accepts no parameters, increments the vert and horz positions
	based on the mouses current direction
*/
void moveForward()
{
	if(direction == 'N' && vert != 0)
	{
		vert = vert - 1;
	}
	else if(direction == 'E' && horz != 15)
	{
		horz = horz + 1;
	}
	else if(direction == 'S' && vert != 15)
	{
		vert = vert + 1;
	}
	else if(direction == 'W' && horz != 0)
	{
		horz = horz - 1;
	}
	
}
//	Function to change the mouses stored dircection member
//	Accepts a unsigned short variable
//	0 is left turn, 1 is right turn, 2 is uturn
void turn(unsigned short x)
{
	if( x == 0 )
	{
		if( direction == 'N' )
			direction = 'W';
		else if( direction == 'E' )
			direction = 'N';
		else if (direction == 'S' )
			direction = 'E';
		else if( direction == 'W' )
			direction = 'S';
	}
	else if( x == 1 )
	{
		if( direction == 'N' )
			direction = 'E';
		else if( direction == 'E' )
			direction = 'S';
		else if (direction == 'S' )
			direction = 'W';
		else if( direction == 'W' )
			direction = 'N';
	}
	else if( x == 2 )
	{
		if( direction == 'N' )
			direction = 'S';
		else if( direction == 'E' )
			direction = 'W';
		else if (direction == 'S' )
			direction = 'N';
		else if( direction == 'W' )
			direction = 'E';
	}
}

//Gets the direction to the mouses left
unsigned char left()
{

		if( direction == 'N' )
			return'W';
		else if( direction == 'E' )
			return 'N';
		else if (direction == 'S' )
			return 'E';
		else //if( direction == 'W' )
			return 'S';

	
}
unsigned char right()
{

		if( direction == 'N' )
			return'E';
		else if( direction == 'E' )
			return 'S';
		else if (direction == 'S' )
			return 'W';
		else //if( direction == 'W' )
			return 'N';

	
}
//Function that adds the walls around the mouse
//Accepts three ints that represent the front, left and right walls
//0 for no wall, 1 for wall
void updateWallsAdd(unsigned short front, unsigned short right, unsigned short left)
{

	if( direction == 'N' )
	{
	 if( front && vert != 0 )
		inMaze.addHWall( vert - 1, horz );
	 if( left && horz != 0 )
		inMaze.addVWall( vert , horz - 1 );
	 if( right )
		inMaze.addVWall( vert, horz );
	}	
	else if( direction == 'E' )
	{
	 if( front )
		inMaze.addVWall( vert , horz );
	 if( left && vert != 0 )
		inMaze.addHWall( vert - 1 , horz );
	 if( right )
		inMaze.addHWall( vert, horz );

	}
	else if (direction == 'S' )
	{
	 if( front )
		inMaze.addHWall( vert , horz );
	 if( left )
		inMaze.addVWall( vert , horz );
	 if( right && horz != 0 )
		inMaze.addVWall( vert, horz - 1);

	}
	else if( direction == 'W' )
	{
	 if( front && horz != 0 )
		inMaze.addVWall( vert, horz - 1 );
	 if( left )
		inMaze.addHWall( vert , horz );
	 if( right && vert != 0 )
		inMaze.addHWall( vert - 1, horz );

	}	

}

//Function that removes the walls around the mouse in floodfill algorithm
//Accepts three ints that represent the front, left and right walls
//0 for no wall, 1 for wall
void updateWallsRemove(unsigned short front, unsigned short right, unsigned short left)
{
	
	if( direction == 'N' )
	{
	 if( !front )
		inMaze.removeHWall( vert - 1, horz );
	 if( !left )
		inMaze.removeVWall( vert , horz - 1 );
	 if( !right )
		inMaze.removeVWall( vert, horz );
	}	
	else if( direction == 'E' )
	{
	 if( !front )
		inMaze.removeVWall( vert , horz );
	 if( !left )
		inMaze.removeHWall( vert - 1 , horz );
	 if( !right )
		inMaze.removeHWall( vert, horz );

	}
	else if (direction == 'S' )
	{
	 if( !front )
		inMaze.removeHWall( vert , horz );
	 if( !left )
		inMaze.removeVWall( vert , horz );
	 if( !right )
		inMaze.removeVWall( vert, horz - 1);

	}
	else if( direction == 'W' )
	{
	 if( !front )
		inMaze.removeVWall( vert, horz - 1 );
	 if( !left )
		inMaze.removeHWall( vert , horz );
	 if( !right )
		inMaze.removeHWall( vert - 1, horz );

	}	

}

void dfs()
{
	
	int dist = 0;
	stack<coord> list;
	list.push(coord(vert, horz));
	distance[vert][horz] = dist;
	while(!list.empty())
	{
		coord next = list.top();
		list.pop();
		vector<coord> adj = next.adjacent(inMaze);
		for(unsigned short i = 0; i < adj.size(); i++)
		{
			if(distance[adj[i].x][adj[i].y] > distance[next.x][next.y] + 1)
				distance[adj[i].x][adj[i].y] = distance[next.x][next.y] + 1;
			list.push(adj[i]);
		}
	}

}

};

