CC= g++
CXXFLAGS= -g -Wall -std=c++11

default: main

main: main.o
	g++ -o main main.o

main.o: Maze.hpp RandomMaze.hpp mouse.cpp

clean: 
	$(RM) main
