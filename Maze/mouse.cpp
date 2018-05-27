#include "Maze.hpp"
#include "RandomMaze.hpp"
#include <iostream>
#include <iomanip>
#include <stack>
#include <unistd.h>

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
		for(int j = 0; j < 16; j++)
		{
			distance[i][j] = 999;
		}
	}
//	distance[16][16] = {999};
}

mouse(int x)
{

	direction = 'E';//Initial direction in maze is east
	vert = 0;//Starting at position 0,0
	horz = 0;
	/*for(int i = 0; i < 16; i++)
	{
		for(int j = 0; j < 16; j++)
		{
			distance[i][j] = 999;
		}
	}*/
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
// distance[16][16] = {999};
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

void floodFill(unsigned short x, unsigned short y, unsigned short dist)
{
	distance[x][y] = dist;
//	inMaze.printFF(0, 0, 'N', distance);
//	usleep(90000);
	if( x != 15 )
		if( !inMaze.getVWall(y,x) && (dist < distance[x+1][y]))
			floodFill(x+1, y, dist+1);
	if( x != 0 )
		if( !inMaze.getVWall(y,x-1) && (dist < distance[x-1][y] ))
			floodFill(x-1, y, dist+1);
	if( y != 15 )
		if( !inMaze.getHWall(y,x)  && (dist < distance[x][y+1]))
			floodFill(x, y+1, dist+1);
	if( y != 0 )
		if( !inMaze.getHWall(y-1,x)  && (dist < distance[x][y-1] ))
			floodFill(x, y-1, dist+1); 
}

void FF()
{
	distance[7][7] = 0;
	distance[7][8] = 0;
	distance[8][7] = 0;
	distance[8][8] = 0;

	floodFill(7, 7, 0);
	floodFill(7, 8, 0);
	floodFill(8, 7, 0);
	floodFill(8, 8, 0);

}

//return 0 for moveForward, 1 for left turn, 2 for right turn, 3 for uturn
int getNextMove()
{
	unsigned short x = horz;
	unsigned short y = vert;
	if( direction == 'N')
	{
		if( vert != 0)
			if( !inMaze.getHWall(vert-1, horz) && (distance[x][y] == distance[x][y-1]+1))
			{
				return 0;
			}
		if( horz != 0)
			if( !inMaze.getVWall(vert, horz-1) && (distance[x][y] == distance[x-1][y]+1))
			{
				return 1;
			}
		if( horz != 15)
			if( !inMaze.getVWall(vert, horz) && (distance[x][y] == distance[x+1][y]+1))
			{
				return 2;
			}
	}

	if( direction == 'S')
	{
		if( vert != 15)
			if( !inMaze.getHWall(vert, horz) && (distance[x][y] == distance[x][y+1]+1))
			{
				return 0;
			}
		if( horz != 0)
			if( !inMaze.getVWall(vert, horz-1) && (distance[x][y] == distance[x-1][y]+1))
			{
				return 2;
			}
		if( horz != 15)
			if( !inMaze.getVWall(vert, horz) && (distance[x][y] == distance[x+1][y]+1))
			{
				return 1;
			}
	}

	if( direction == 'E')
	{
		if( vert != 0)
			if( !inMaze.getHWall(vert-1, horz) && (distance[x][y] == distance[x][y-1]+1))
			{
				return 1;
			}
		if( vert != 15)
			if( !inMaze.getHWall(vert, horz) && (distance[x][y] == distance[x][y+1]+1))
			{
				return 2;
			}
		if( horz != 15)
			if( !inMaze.getVWall(vert, horz) && (distance[x][y] == distance[x+1][y]+1))
			{
				return 0;
			}
	}

	if( direction == 'W')
	{
		if( vert != 0)
			if( !inMaze.getHWall(vert-1, horz) && (distance[x][y] == distance[x][y-1]+1))
			{
				return 2;
			}
		if( horz != 0)
			if( !inMaze.getVWall(vert, horz-1) && (distance[x][y] == distance[x-1][y]+1))
			{
				return 0;
			}
		if( vert != 15)
			if( !inMaze.getHWall(vert, horz) && (distance[x][y] == distance[x][y+1]+1))
			{
				return 1;
			}
	}
	return 3;
}

//return 0 for moveForward, 1 for left turn, 2 for right turn, 3 for uturn
int getNextReturnMove()
{
	unsigned short x = horz;
	unsigned short y = vert;
	if( direction == 'N')
	{
		if( vert != 0)
			if( !inMaze.getHWall(vert-1, horz) && (distance[x][y-1] == 999))
			{
				return 0;
			}
		if( horz != 0)
			if( !inMaze.getVWall(vert, horz-1) && (distance[x-1][y] == 999))
			{
				return 1;
			}
		if( horz != 15)
			if( !inMaze.getVWall(vert, horz) && ( distance[x+1][y] == 999))
			{
				return 2;
			}
	}

	if( direction == 'S')
	{
		if( vert != 15)
			if( !inMaze.getHWall(vert, horz) && (distance[x][y+1] == 999))
			{
				return 0;
			}
		if( horz != 0)
			if( !inMaze.getVWall(vert, horz-1) && (distance[x-1][y] == 999))
			{
				return 2;
			}
		if( horz != 15)
			if( !inMaze.getVWall(vert, horz) && (distance[x+1][y] == 999))
			{
				return 1;
			}
	}

	if( direction == 'E')
	{
		if( vert != 0)
			if( !inMaze.getHWall(vert-1, horz) && (distance[x][y-1] == 999))
			{
				return 1;
			}
		if( vert != 15)
			if( !inMaze.getHWall(vert, horz) && (distance[x][y+1] == 999))
			{
				return 2;
			}
		if( horz != 15)
			if( !inMaze.getVWall(vert, horz) && (distance[x+1][y] == 999))
			{
				return 0;
			}
	}

	if( direction == 'W')
	{
		if( vert != 0)
			if( !inMaze.getHWall(vert-1, horz) && (distance[x][y-1] == 999))
			{
				return 2;
			}
		if( horz != 0)
			if( !inMaze.getVWall(vert, horz-1) && (distance[x-1][y] == 999))
			{
				return 0;
			}
		if( vert != 15)
			if( !inMaze.getHWall(vert, horz) && (distance[x][y+1] == 999))
			{
				return 1;
			}
	}
	return 3;
}

void floodDistance(unsigned short x, unsigned short y)
{
	stack<coord> list;
	list.push(coord(x, y));
	unsigned short min;
	while(!list.empty())
	{
		min = 999;
		coord next = list.top();
		list.pop();
		if( !((next.x == 7 || next.x == 8 ) && ( next.y == 7 || next.y == 8 )) )
		{
			if( next.y != 0 )
				if( !inMaze.getHWall(next.y-1, next.x))
					if( distance[next.x][next.y-1] < min )
						min = distance[next.x][next.y-1];
			if( next.y != 15 )
				if( !inMaze.getHWall(next.y, next.x))
					if( distance[next.x][next.y+1] < min )
						min = distance[next.x][next.y+1];
			if( next.x != 0 )
				if( !inMaze.getVWall(next.y, next.x-1))
					if( distance[next.x-1][next.y] < min )
						min = distance[next.x-1][next.y];
			if( next.x != 15 )
				if( !inMaze.getVWall(next.y, next.x))
					if( distance[next.x+1][next.y] < min )
						min = distance[next.x+1][next.y];
			if( distance[next.x][next.y] != min + 1 )
			{
				distance[next.x][next.y] = min +1;
				if( next.x != 15 )
					list.push(coord(next.x+1, next.y));
				if( next.x != 0 )
					list.push(coord(next.x-1, next.y));
				if( next.y != 0 )
					list.push(coord(next.x, next.y-1));
				if( next.y != 15 )
					list.push(coord(next.x, next.y+1));
			}
		}
	}
	
}
//0-forward, 1-left, 2-right, 3-uturn
int getSmallestNeighbor()
{
	unsigned short x = horz;
	unsigned short y = vert;
	unsigned short dist = 999;
	unsigned short ret;
	if( direction == 'N')
	{
		if( vert != 0)
			if( !inMaze.getHWall(vert-1, horz) && (distance[x][y-1] < dist))
			{
				dist = distance[x][y-1];
				ret = 0;
			}
		if( horz != 0)
			if( !inMaze.getVWall(vert, horz-1) && (distance[x-1][y] < dist))
			{
				dist = distance[x-1][y];
				ret =  1;
			}
		if( horz != 15)
			if( !inMaze.getVWall(vert, horz) && ( distance[x+1][y] < dist))
			{
				dist = distance[x+1][y];
				ret =  2;
			}
	}

	if( direction == 'S')
	{
		if( vert != 15)
			if( !inMaze.getHWall(vert, horz) && (distance[x][y+1] < dist))
			{
				dist = distance[x][y+1];
				ret = 0;
			}
		if( horz != 0)
			if( !inMaze.getVWall(vert, horz-1) && (distance[x-1][y] < dist))
			{
				dist = distance[x-1][y];
				ret = 2;
			}
		if( horz != 15)
			if( !inMaze.getVWall(vert, horz) && (distance[x+1][y] < dist))
			{
				dist = distance[x+1][y];
				ret = 1;
			}
	}

	if( direction == 'E')
	{
		if( vert != 0)
			if( !inMaze.getHWall(vert-1, horz) && (distance[x][y-1] < dist))
			{
				dist = distance[x][y-1];
				ret =  1;
			}
		if( vert != 15)
			if( !inMaze.getHWall(vert, horz) && (distance[x][y+1] < dist))
			{
				dist = distance[x][y+1];
				ret = 2;
			}
		if( horz != 15)
			if( !inMaze.getVWall(vert, horz) && (distance[x+1][y] < dist))
			{
				dist = distance[x+1][y];
				ret = 0;
			}
	}

	if( direction == 'W')
	{
		if( vert != 0)
			if( !inMaze.getHWall(vert-1, horz) && (distance[x][y-1] < dist ))
			{
				dist = distance[x][y-1];
				ret = 2;
			}
		if( horz != 0)
			if( !inMaze.getVWall(vert, horz-1) && (distance[x-1][y] <dist ))
			{
				dist = distance[x-1][y];
				ret =  0;
			}
		if( vert != 15)
			if( !inMaze.getHWall(vert, horz) && (distance[x][y+1] < dist))
			{
				dist = distance[x][y+1];
				ret = 1;
			}
	}
	if( dist == 999 )
		ret = 3;
	return ret;
}

void dfs()
{
	
	int dist = 0;
	stack<coord> list;
	list.push(coord(horz, vert));
	distance[horz][vert] = dist;
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

