#include "maze.h"

/*
  InitMaze allocates the memory for the maze array based on gwidth and
  gheight, set elsewhere.
*/
void InitMaze()
{
  grid = malloc((size_t)(gwidth * gheight));
  ResetMaze();
}

/*
  ResetMaze fills the grid with blocks ('#' characters).
*/
void ResetMaze()
{
  int i;
  for (i=0; i<gwidth*gheight; ++i)
  {
    *(grid + i) = '#';
  }
}

/*
  XYToIndex converts the two-dimensional index pair (x, y) into a
  single-dimensional index.  The result it y * gwidth + x.
*/
int XYToIndex( int x, int y )
{
  return y * gwidth + x;
}

/*
  IsInBounds returns "true" if x and y are both in-bounds.
*/
int IsInBounds( int x, int y )
{
  if (x < 0 || x >= gwidth) return false;
  if (y < 0 || y >= gheight) return false;
  return true;
}

/*
  setX sets the gwidth of the maze array
*/
void setX(int x)
{
  gwidth = x;
}

/*
  setY sets the gheight of the maze array
*/
void setY(int y)
{
  gheight = y;
}

/*
  getX gets the gwidth of the maze array
*/
int getX()
{
  return gwidth;
}

/*
  getY gets the gheight of the maze array
*/
int getY()
{
  return gheight;
}

/*
  getCharAtIndex returns the character in grid at the passed index
*/
char getCharAtIndex(int index)
{
  return grid[index];
}

/*
  setCharAtIndex sets the character in grid at the passed index to the
  passed character.
*/
void setCharAtIndex(int index, char c)
{
  grid[index] = c;
}

/*
  PrintMaze displays the grid to the screen.
*/
void PrintMaze()
{
  int y, x;
  for (y=0; y < gheight; ++y)
  {
    for (x=0; x < gwidth; ++x)
    {
      printf("%c", *(grid + XYToIndex(x,y)));
    }
    printf("\n");
  }
}

/*
  Visit starts at a given index and recursively visits every direction in a
  randomized order. Recursion ends at a particular location when all the
  directions have been visited.
*/
void Visit( int x, int y)
{
  int i;

  // Set the current location to be an empty space (remove the block).
  grid[XYToIndex(x, y)] = ' ';

  // Create a local array containing the four directions
  int dirs[4];
  dirs[0] = NORTH;
  dirs[1] = EAST;
  dirs[2] = SOUTH;
  dirs[3] = WEST;

  // Shuffle the dirs array
  for (i=0; i < 4; ++i)
  {
    int r = rand() & 3;
    int temp = dirs[r];
    dirs[r] = dirs[i];
    dirs[i] = temp;
  }

  // Loop through the suffled array and attempt to visit every direction
  for (i=0; i < 4; ++i)
  {
    // dx and dy will be offsets from the current location set based on
    // the current direction in the dirs array
    int dx = 0, dy = 0;
    switch (dirs[i])
    {
      case NORTH: dy = -1; break;
      case SOUTH: dy = 1; break;
      case EAST:  dx = 1; break;
      case WEST:  dx = -1; break;
    }

    // get the (x, y) coordinates for the grid cell 2 spots away in the
    // given direction
    int x2 = x + (dx << 1);
    int y2 = y + (dy << 1);

    // See if the location at (x2, y2) is in bounds
    if (IsInBounds(x2, y2))
    {
      // See if the location has been visited
      if (*(grid + XYToIndex(x2, y2)) == '#')
      {
	// not visited, so remove the intervening wall and then visit it
	*(grid + XYToIndex(x2-dx, y2-dy)) = ' ';
	Visit(x2, y2);
      }
    }
  }
}
