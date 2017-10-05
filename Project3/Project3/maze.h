#ifndef _maze_h
#define _maze_h

#include <stdio.h>
#include <stdlib.h>

//---- Directional Constants ------------------------------------------------//
#define NORTH 0
#define EAST  1
#define SOUTH 2
#define WEST  3

//---- Boolean Constants ----------------------------------------------------//
#define true  1
#define false 0

//---- Global Variables -----------------------------------------------------//
int gwidth;
int gheight;
char *grid;

//---- Function Prototypes
void InitMaze();
void ResetMaze();
int  XYToIndex(int, int);
int  IsInBounds(int, int);
void Visit(int, int);
void PrintMaze();
void setX(int);
int  getX();
void setY(int);
int  getY();
char getCharAtIndex(int);
void setCharAtIndex(int, char);

#endif
