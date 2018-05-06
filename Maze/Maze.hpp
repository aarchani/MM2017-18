#ifndef MAZE_HPP
#define MAZE_HPP
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

const string vWall = "|";
const string hWall = "---";
const string node = "+";
const string goal = " # ";
const string empty = "   ";
const string N = " ^ ";
const string S = " V ";
const string W = " < ";
const string E = " > ";
const string TOP = "+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+";

class Maze
{

 public:

	unsigned short verticle[16];

	unsigned short horizontal[16];
	
  Maze()
{
	for(int i = 0; i < 16; i++)
	{
		verticle[i] = 32768;
		horizontal[i] = 0;
	}
	horizontal[15] = 65535;

}
void MazeFull()
{
	for(int i = 0; i < 16; i++)
	{
		verticle[i] = 65535;
		horizontal[i] = 65535;
	}

}

//given the position and orientation of the mouse prints the maze
void print(unsigned short vert, unsigned short horz, unsigned char orientation)
{
	cout << TOP << endl;

	for(int x = 0; x < 16; x++)//For loop to iterate through the 16 rows of the maze
	{
		cout << vWall;
		for(int y = 0; y < 16; y++)//For loop to iterate through the 16 horizontal blocks
		{
			if( (x == vert) && ( y == horz))//check for mouse
				{
					if(orientation == 'N') cout << N;//print mouse with orientation
					if(orientation == 'S') cout << S;
					if(orientation == 'W') cout << W;
					if(orientation == 'E') cout << E;

				}
				
			else if( ( (x == 7) || (x == 8) ) && ((y == 7) || (y == 8)) )//print the goal 
				cout << goal;

			else cout << empty;//print empty

			if( (verticle[x] & pow(2,y)) != 0)// check if there is a wall here
			{
				cout << vWall;//if wall print line
			}
			else cout << " ";//if no wall print blank
		}
	
		cout << x << endl;	//switch to next line of horizontal walls
		cout << node;
		for(unsigned short y = 0; y < 16; y++)
		{
			if( (horizontal[x] & pow(2,y) )!= 0)//check for wall
			{
				cout << hWall;
			}
			else cout << empty;
			cout << node;
		}
		//cout << vWall;
		cout << endl;
	}
/*	cout << vWall;
	for(unsigned short y = 0; y < 14; y++)//For loop to iterate through the 16 columns
	{
		cout << empty;//need logic to check if mouse is here
		if( (verticle[15] & pow(2,y)) != 0)// check if there is a wall here
		{
			cout << vWall;//if wall print line
		}
		else cout << " ";//if no wall print blank
	}
	
	cout << empty << vWall << endl;	

	cout << TOP << endl;
*/
}

//Print with flood values
void printFF(unsigned short vert, unsigned short horz, unsigned char orientation, unsigned short flood[15][15])
{
	cout << TOP << endl;

	for(int x = 0; x < 16; x++)//For loop to iterate through the 16 rows of the maze
	{
		cout << vWall;
		for(int y = 0; y < 16; y++)//For loop to iterate through the 16 horizontal blocks
		{
			if( (x == vert) && ( y == horz))//check for mouse
				{
					if(orientation == 'N') cout << N;//print mouse with orientation
					if(orientation == 'S') cout << S;
					if(orientation == 'W') cout << W;
					if(orientation == 'E') cout << E;

				}
				
			else if( ( (x == 7) || (x == 8) ) && ((y == 7) || (y == 8)) )//print the goal 
				cout << goal;

			else cout << setfill('0') << setw(3) << flood[y][x];//print flood value

			if( (verticle[x] & pow(2,y)) != 0)// check if there is a wall here
			{
				cout << vWall;//if wall print line
			}
			else cout << " ";//if no wall print blank
		}
	
		cout << x << endl;	//switch to next line of horizontal walls
		cout << node;
		for(unsigned short y = 0; y < 16; y++)
		{
			if( (horizontal[x] & pow(2,y) )!= 0)//check for wall
			{
				cout << hWall;
			}
			else cout << empty;
			cout << node;
		}
		
		cout << endl;
	}

}

//remove the verticle wall at vert, horz
void removeVWall(unsigned short vert, unsigned short horz)
{
	unsigned short mod;
	mod = pow(2, horz);
	verticle[vert] = (verticle[vert] & (~mod));
}

//removes the horizontal wall at vert, horz
void removeHWall(unsigned short vert, unsigned short horz)
{
	unsigned short mod;
	mod = pow(2, horz);
	horizontal[vert] = (horizontal[vert] & (~mod));
}
//sets the verticle wall at vert, horz 
void addVWall(unsigned short vert, unsigned short horz)
{
	unsigned short mod;
	mod = pow(2, horz);
	verticle[vert] = (verticle[vert] | mod);
}

//sets the horizontal wall at vert, horz
void addHWall(unsigned short vert, unsigned short horz)
{
	unsigned short mod;
	mod = pow(2, horz);
	horizontal[vert] = (horizontal[vert] | mod);
}
//checks if there is a verticle wall at vert, horz
bool getVWall(unsigned short vert, unsigned short horz)
{
	unsigned short mod;
	mod = pow(2, horz);
	return (verticle[vert] & mod);
}

//checks if there is a horizontal wall at vert, horz
bool getHWall(unsigned short vert, unsigned short horz)
{
	unsigned short mod;
	mod = pow(2, horz);
	return (horizontal[vert] & mod);
}


//Retuns b^e
 unsigned short pow( unsigned short b, unsigned short e)
{
	unsigned short result = 1;
	while( e != 0)
	{
		result = result * b;
		e--;
	}	
	return result;
}


};


#endif //MAZE_HPP
