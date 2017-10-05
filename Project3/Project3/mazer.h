#ifndef _mazer_h
#define _mazer_h

#include <string.h>
#include "maze.h"
#include "dbg.h"

//---- Global Variables -----------------------------------------------------//
int xpos;
int ypos;
int facing;

//---- Function Prototypes
/*
  Initialize the beginning position and facing of your virtual robot
*/
int  InitRunner();

/*
  Change the robot's facing counterclockwise
*/
int  TurnLeft();

/*
  Change the robot's facing clockwise
*/
int  TurnRight();

/*
  Return true if there is a wall ('*') one space in the direction of facing.
  Otherwise return false.  You can use functions from the maze library, so
  figure out the XY coordinate you are interested in, then use XYToIndex to
  get the array index and then check the character at that index to see if
  it is a wall.  While you're checking for walls, also look for the
  'breadcrumb' character that indicates a position has been visited from every
  direction, which means there is nothing left to try.
*/ 
int  IsWall();

/*
  Change the robot's position appropriately due to facing. Don't forget to
  leave a 'breadcrumb' in the old position (see the project requirements).
*/
int  MoveForward();

/*
  Checks to see if the robot's position matches the destination coordinates
  and returns true if it does.  Otherwise, return false.
*/
int  AtDestination();

#endif