#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

typedef enum { false, true } bool;

const char vWall[] = "|";
const char hWall[] = "---";
const char node[] = "+";
const char goal[] = " # ";
const char empty[] = "   ";
const char N[] = " ^ ";
const char S[] = " V ";
const char W[] = " < ";
const char E[] = " > ";
const char TOP[] = "+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+";

typedef struct
{
    unsigned short verticle[16];
    unsigned short horizontal[16];
} Maze;

typedef struct
{
    unsigned short x;
    unsigned short y;
} coord; 

void setCoord(coord c, unsigned short a, unsigned short b)
{
    c.x = a;
    c.y = b;
}
/*
coord adjacent(Maze inMaze, coord thisC)
{
    vector<coord> adj;
    if( x != 0)
        if(!inMaze.getHWall(thisC.x-1, thisC.y))
            adj.push_back( coord(thisC.x-1, thisC.y) );
    if( x != 15 )
        if(!inMaze.getHWall(thisC.x, thisC.y) )
            adj.push_back( coord(thisC.x+1, thisC.y) );
    if( y != 0 )
        if(!inMaze.getVWall(thisC.x, thisC.y-1))
            adj.push_back( coord(thisC.x, thisC.y-1) );
    if( y != 15 )
        if(!inMaze.getVWall(thisC.x, thisC.y))
            adj.push_back( coord(thisC.x, thisC.y+1) );
    return adj;
}*/


typedef struct
{
    unsigned char direction;//Which direction the mouse is facing
    unsigned short vert;//Verticle position in maze, 0-15
    unsigned short horz;//Horizontal position, 0-15
    Maze inMaze;
    unsigned short distance[16][16];//floodfill distance 
} mouse;

void new_mouse(mouse m)
{
    m.direction = 'E';//Initial direction in maze is east
    m.vert = 0;//Starting at position 0,0
    m.horz = 0;
    MazeFull(m.inMaze);//Initiallizing a fullmaze for dfs algorithm
    for(int i = 0; i < 16; i++)
    {
        for(int j = 0; j < 15; j++)
        {
            m.distance[i][j] = -1;
        }
    }
}
void new_ffmouse(mouse m,int x)
{

    m.direction = 'E';//Initial direction in maze is east
    m.vert = 0;//Starting at position 0,0
    m.horz = 0;
    //Initiallizing an empty maze for floodfill algorithm
    for( int i = 0; i < 8; i++)
    {
        for( int j = 0; j < 8; j++ )
        {
            m.distance[i][j] = abs( i-7 ) + abs( j-7 );
        //  cout << "i= " << i << " j= " << j << " : " << distance[i][j] << endl;
            m.distance[15-i][j] = m.distance[i][j];
        //  cout << "i= " << 15-i << " j= " << j << " : " << distance[15-i][j] << endl;
            m.distance[15-i][15-j] = m.distance[i][j];
        //  cout << "i= " << 15-i << " j= " << 15-j << " : " << distance[15-i][15-j] << endl;
            m.distance[i][15-j] = m.distance[i][j];
        //  cout << "i= " << i << " j= " << 15-j << " : " << distance[i][15-j] << endl;
        }
    }

}

void print(mouse m)
{
    printf("Verticle: %u Horizontal: %u", m.vert,  m.horz);
    printf(" Direction: %c\n", m.direction);
    for( int i=0; i<16; i=i+1)
    {
        for( int j=0; j<16; j=j+1)
        {
            printf("%u ", m.distance[j][i]);
        }
        printf("\n");
    }
}
bool notDone(mouse m)
{
    if( m.vert == 7 && m.horz == 7 )
        return false;
    else if ( m.vert == 7 && m.horz == 8 )
        return false;
    else if ( m.vert == 8 && m.horz == 7 )
        return false;
    else if ( m.vert == 8 && m.horz == 8 )
        return false;
    else
        return true;
}
/*  Function that updates the mouses position in the maze
    Accepts no parameters, increments the vert and horz positions
    based on the mouses current direction
*/
void moveForward(mouse m)
{
    if(m.direction == 'N' && m.vert != 0)
    {
        m.vert = m.vert - 1;
    }
    else if(m.direction == 'E' && m.horz != 15)
    {
        m.horz = m.horz + 1;
    }
    else if(m.direction == 'S' && m.vert != 15)
    {
        m.vert = m.vert + 1;
    }
    else if(m.direction == 'W' && m.horz != 0)
    {
        m.horz = m.horz - 1;
    }

}
void turn(mouse m, unsigned short x)
{
    if( x == 0 )
    {
        if( m.direction == 'N' )
            m.direction = 'W';
        else if( m.direction == 'E' )
            m.direction = 'N';
        else if (m.direction == 'S' )
            m.direction = 'E';
        else if( m.direction == 'W' )
            m.direction = 'S';
    }
    else if( x == 1 )
    {
        if( m.direction == 'N' )
            m.direction = 'E';
        else if( m.direction == 'E' )
            m.direction = 'S';
        else if (m.direction == 'S' )
            m.direction = 'W';
        else if( m.direction == 'W' )
            m.direction = 'N';
    }
    else if( x == 2 )
    {
        if( m.direction == 'N' )
            m.direction = 'S';
        else if( m.direction == 'E' )
            m.direction = 'W';
        else if (m.direction == 'S' )
            m.direction = 'N';
        else if( m.direction == 'W' )
            m.direction = 'E';
    }
}

//Gets the direction to the mouses left
unsigned char left(mouse m)
{

        if( m.direction == 'N' )
            return'W';
        else if( m.direction == 'E' )
            return 'N';
        else if (m.direction == 'S' )
            return 'E';
        else //if( direction == 'W' )
            return 'S';


}
unsigned char right(mouse m)
{

        if( m.direction == 'N' )
            return'E';
        else if( m.direction == 'E' )
            return 'S';
        else if (m.direction == 'S' )
            return 'W';
        else //if( direction == 'W' )
            return 'N';


}
void updateWallsAdd(mouse m, unsigned short front, unsigned short right, unsigned short left)
{

    if( m.direction == 'N' )
    {
     if( front && m.vert != 0 )
        addHWall( m.inMaze, m.vert - 1, m.horz );
     if( left && m.horz != 0 )
        addVWall( m.inMaze, m.vert , m.horz - 1 );
     if( right )
        addVWall( m.inMaze, m.vert, m.horz );
    }
    else if( m.direction == 'E' )
    {
     if( front )
        addVWall( m.inMaze, m.vert, m.horz );
     if( left && m.vert != 0 )
        addHWall( m.inMaze, m.vert - 1 , m.horz );
     if( right )
        addHWall( m.inMaze, m.vert, m.horz );

    }
    else if (m.direction == 'S' )
    {
     if( front )
        addHWall( m.inMaze, m.vert, m.horz );
     if( left )
        addVWall( m.inMaze, m.vert, m.horz );
     if( right && m.horz != 0 )
        addVWall( m.inmaze, m.vert, m.horz - 1);

    }
    else if( m.direction == 'W' )
    {
     if( front && m.horz != 0 )
        addVWall( m.inMaze, m.vert, m.horz - 1 );
     if( left )
        addHWall( m.inMaze, m.vert, m.horz );
     if( right && m.vert != 0 )
        addHWall( m.inMaze, m.vert - 1, m.horz );

    }

}

/*	TO BE CONVERTED*************************************8
void updateWallsRemove(mouse m, unsigned short front, unsigned short right, unsigned short left)
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
*/
void  new_Maze(Maze z)
{
    for(int i = 0; i < 16; i++)
    {
        z.verticle[i] = 32768;
        z.horizontal[i] = 0;
    }
    z.horizontal[15] = 65535;

}
void MazeFull(Maze z)
{
    for(int i = 0; i < 16; i++)
    {
        z.verticle[i] = 65535;
        z.horizontal[i] = 65535;
    }

}

void print(Maze z, unsigned short vert, unsigned short horz, unsigned char orientation)
{
	printf("%s\n", TOP);
    for(int x = 0; x < 16; x++)//For loop to iterate through the 16 rows of the maze
    {
        printf("%s", vWall); //cout << vWall;
        for(int y = 0; y < 16; y++)//For loop to iterate through the 16 horizontal blocks
        {
            if( (x == vert) && ( y == horz))//check for mouse
                {
					printf("%c", orientation ); 
                    /*if(orientation == 'N') printf("%s", cout << N;//print mouse with orientation
                    if(orientation == 'S') printf("%s", cout << S;
                    if(orientation == 'W') printf("%s", cout << W;
                    if(orientation == 'E') printf("%s", cout << E;
					*/
                }

            else if( ( (x == 7) || (x == 8) ) && ((y == 7) || (y == 8)) )//print the goal 
                printf("%s", goal);// cout << goal;

            else printf("%s", empty );// cout << empty;//print empty

            if( (verticle[x] & pow(2,y)) != 0)// check if there is a wall here
            {
                printf("%s", vWall); //cout << vWall;//if wall print line
            }
            else printf(" "); //cout << " ";//if no wall print blank
        }

        printf("%u\n", x);// cout << x << endl;  //switch to next line of horizontal walls
        printf("%s", node); // cout << node;
        for(unsigned short y = 0; y < 16; y++)
        {
            if( (horizontal[x] & pow(2,y) )!= 0)//check for wall
            {
                printf("%s", hWall); //cout << hWall;
            }
            else printf("%s", empty); //cout << empty;
            printf("%s", node); // cout << node;
        }
        //cout << vWall;
        printf("\n"); // cout << endl;
    }
}

void printFF(unsigned short vert, unsigned short horz, unsigned char orientation, unsigned short (&flood)[16][16])
{
    printf("%s\n", TOP);// cout << TOP << endl;

    for(int x = 0; x < 16; x++)//For loop to iterate through the 16 rows of the maze
    {
        printf("%s", vWall);// cout << vWall;
        for(int y = 0; y < 16; y++)//For loop to iterate through the 16 horizontal blocks
        {
            if( (x == vert) && ( y == horz))//check for mouse
                {
                    if(orientation == 'N') printf("%c", N);// cout << N;//print mouse orientation
                    if(orientation == 'S') printf("%c", S);// cout << S;
                    if(orientation == 'W') printf("%c", W);// cout << W;
                    if(orientation == 'E') printf("%c", E);// cout << E;
					
                }

            else if( ( (x == 7) || (x == 8) ) && ((y == 7) || (y == 8)) )//print the goal 
                printf("%s", goal);// cout << goal;

            else printf("%s03", flood[y][x]);// cout << setfill('0') << setw(3) << flood[y][x];//print flood value

            if( (verticle[x] & pow(2,y)) != 0)// check if there is a wall here
            {
               printf("%s", vWall); // cout << vWall;//if wall print line
            }
            else printf(" "); // cout << " ";//if no wall print blank
        }

        printf("%i", x);// cout << x << endl;  //switch to next line of horizontal walls
        printf("%s", node); // cout << node;
        for(unsigned short y = 0; y < 16; y++)
        {
            if( (horizontal[x] & pow(2,y) )!= 0)//check for wall
            {
                printf("%s", hWall); // cout << hWall;
            }
            else printf("%s", empty); // cout << empty;
            printf("%s", node); // cout << node;
        }

        printf("\n");// cout << endl;
    }

}

void removeVWall(Maze z, unsigned short vert, unsigned short horz)
{
    unsigned short mod;
    mod = pow(2, horz);
    z.verticle[vert] = (z.verticle[vert] & (~mod));
}

//removes the horizontal wall at vert, horz
void removeHWall(Maze z, unsigned short vert, unsigned short horz)
{
    unsigned short mod;
    mod = pow(2, horz);
    z.horizontal[vert] = (z.horizontal[vert] & (~mod));
}
//sets the verticle wall at vert, horz 
void addVWall(Maze z, unsigned short vert, unsigned short horz)
{
    unsigned short mod;
    mod = pow(2, horz);
    z.verticle[vert] = (z.verticle[vert] | mod);
}

//sets the horizontal wall at vert, horz
void addHWall(Maze z, unsigned short vert, unsigned short horz)
{
    unsigned short mod;
    mod = pow(2, horz);
    z.horizontal[vert] = (z.horizontal[vert] | mod);
}
//checks if there is a verticle wall at vert, horz
bool getVWall(Maze z, unsigned short vert, unsigned short horz)
{
    unsigned short mod;
    mod = pow(2, horz);
    return (z.verticle[vert] & mod);
}

//checks if there is a horizontal wall at vert, horz
bool getHWall(Maze z, unsigned short vert, unsigned short horz)
{
    unsigned short mod;
    mod = pow(2, horz);
    return (z.horizontal[vert] & mod);
}


/*Retuns b^e
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
*/


