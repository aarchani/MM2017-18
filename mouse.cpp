#include "Maze.hpp"
#include "RandomMaze.hpp"

using namespace std;

class mouse()
{
   public:
	unsigned char direction;//Which direction the mouse is facing
	unsigned short vert;//Verticle position in maze, 0-15
	unsigned short horz;//Horizontal position, 0-15
	Maze inMaze;
//Constructer
mouse()
{
	direction = 'E';//Initial direction in maze is east
	vert = 0;//Starting at position 0,0
	horz = 0;
	inMaze.FullMaze();//Initiallizing a fullmaze for dfs algorithm
}
mouse(int x)
{

	direction = 'E';//Initial direction in maze is east
	vert = 0;//Starting at position 0,0
	horz = 0;
	//Initiallizing an empty maze for floodfill algorithm

}
/*	Function that updates the mouses position in the maze
	Accepts no parameters, increments the vert and horz positions
	based on the mouses current direction
*/
moveForward()
{
	if(direction == 'N' && vert != 0)
	{
		vert = vert - 1;
	}
	else if(direction == 'E' && vert != 0)
	{
		horz = horz + 1;
	}
	else if(direction == 'S' && vert != 0)
	{
		vert = vert + 1;
	}
	else if(direction == 'W' && vert != 0)
	{
		horz = horz - 1;
	}
	
}
//	Function to change the mouses stored dircection member
//	Accepts a unsigned short variable
//	0 is left turn, 1 is right turn, 2 is uturn
turn(unsigned short x)
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
	if( x == 1 )
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
	if( x == 2 )
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
//Function that adds the walls around the mouse
//Accepts three ints that represent the front, left and right walls
//0 for no wall, 1 for wall
detectWallsAdd(unsigned short front, unsigned short right, unsigned short left)
{

	if( direction == 'N' )
	{
	 if( front )
		addHWall( vert - 1, horz );
	 if( left )
		addVWall( vert , horz - 1 );
	 if( right )
		addVWall( vert, horz );
	}	
	else if( direction == 'E' )
	{
	 if( front )
		addVWall( vert , horz );
	 if( left )
		addHWall( vert - 1 , horz );
	 if( right )
		addHWall( vert, horz );

	}
	else if (direction == 'S' )
	{
	 if( front )
		addHWall( vert , horz );
	 if( left )
		addVWall( vert , horz );
	 if( right )
		addVWall( vert, horz - 1);

	}
	else if( direction == 'W' )
	{
	 if( front )
		addVWall( vert, horz - 1 );
	 if( left )
		addHWall( vert , horz );
	 if( right )
		addHWall( vert - 1, horz );

	}	

}

//Function that removes the walls around the mouse in floodfill algorithm
//Accepts three ints that represent the front, left and right walls
//0 for no wall, 1 for wall
detectWallsRemove(unsigned short front, unsigned short right, unsigned short left)
{
	
	if( direction == 'N' )
	{
	 if( !front )
		removeHWall( vert - 1, horz );
	 if( !left )
		removeVWall( vert , horz - 1 );
	 if( !right )
		removeVWall( vert, horz );
	}	
	else if( direction == 'E' )
	{
	 if( !front )
		removeVWall( vert , horz );
	 if( !left )
		removeHWall( vert - 1 , horz );
	 if( !right )
		removeHWall( vert, horz );

	}
	else if (direction == 'S' )
	{
	 if( !front )
		removeHWall( vert , horz );
	 if( !left )
		removeVWall( vert , horz );
	 if( !right )
		removeVWall( vert, horz - 1);

	}
	else if( direction == 'W' )
	{
	 if( !front )
		removeVWall( vert, horz - 1 );
	 if( !left )
		removeHWall( vert , horz );
	 if( !right )
		removeHWall( vert - 1, horz );

	}	

}

dfs()
{
	

}

};
