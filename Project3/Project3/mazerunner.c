#include "maze.h"
#include <string.h>

void usage();

/*
  This program uses the maze library to build a maze.
*/
int main(int argc, char* argv[])
{
  if (argc < 3) { usage(); return 1; }
  int width = (int)strtol(argv[1], (char**)NULL, 10);
  int height = (int)strtol(argv[2], (char**)NULL, 10);
  if (width < 9 || width > 79 || (width%2)!= 1) { usage(); return 1; }
  if (height < 9 || height > 25 || (height%2) != 1) { usage(); return 1; }

  // all the params check out, so do the maze
  setX(width);
  setY(height);
  InitMaze();
  srand( time(0) );
  Visit(1,1);
  PrintMaze();

  InitRunner();

  while(!AtDestination())
  {
    TurnRight();
    if(IsWall())
    {
      TurnLeft();
      if(IsWall())
      {
        TurnLeft();
        if(IsWall())
        {
          TurnLeft();
        }
      }
    }
    MoveForward();
  }
  PrintMaze();
  return 1;
}

/*
  This function displays the usage message if the parameters are missing
  or incorrect.
*/
void usage()
{
  printf("Usage: mazerunner x y \n");
  printf("       x must be an odd integer between 9 and 79 inclusive\n");
  printf("       y must be an odd integer between 9 and 25 inclusive\n\n");
}
