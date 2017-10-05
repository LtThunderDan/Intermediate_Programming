#include <mazer.h>

/*
	InitRunner simply sets the x and y positions to 1 and the facing to
	North (defined in maze.h) to begin the path search
*/
int InitRunner()
{
	// Not much point in doing anything without a maze.  Otherwise we
	// initialize the runner.
	check(grid != NULL, "Init Warning: maze is not defined.");
	xpos = 1;
	ypos = 1;
	facing = NORTH;
	return true;

error:
	return false;
}

/*
	Change the robot's facing counterclockwise
*/
int TurnLeft()
{
	check(grid != NULL, "Init Warning: maze is not defined.");

	if(facing == NORTH)
	{
		facing = WEST;
	}
	else if(facing == SOUTH)
	{
		facing = EAST;
	}
	else if(facing == EAST)
	{
		facing = NORTH;
	}
	else if(facing == WEST)
	{
		facing = SOUTH;
	}

	return 1;

	error:
		return false;
}

/*
	Change the robot's facing clockwise
*/
int TurnRight()
{
	check(grid != NULL, "Init Warning: maze is not defined.");

	if(facing == NORTH)
	{
		facing = EAST;
	}
	else if(facing == SOUTH)
	{
		facing = WEST;
	}
	else if(facing == EAST)
	{
		facing = SOUTH;
	}
	else if(facing == WEST)
	{
		facing = NORTH;
	}

	return 1;

	error:
		return false;
}

/*
Return true if there is a wall ('*') one space in the direction of facing.
Otherwise return false.  You can use functions from the maze library, so
figure out the XY coordinate you are interested in, then use XYToIndex to
get the array index and then check the character at that index to see if
it is a wall.  While you're checking for walls, also look for the
'breadcrumb' character that indicates a position has been visited from every
direction, which means there is nothing left to try.
*/
int IsWall()
{
	int tempNORTH = XYToIndex(xpos, ypos - 1);
	int tempSOUTH = XYToIndex(xpos, ypos + 1);
	int tempWEST = XYToIndex(xpos - 1, ypos);
	int tempEAST = XYToIndex(xpos + 1, ypos);
	check(grid != NULL, "Init Warning: maze is not defined.");

	if(facing == NORTH)
	{
		if(getCharAtIndex(tempNORTH) == '#' || getCharAtIndex(tempNORTH) == 'O')
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else if(facing == SOUTH)
	{
		if(getCharAtIndex(tempSOUTH) == '#' || getCharAtIndex(tempSOUTH) == 'O')
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else if(facing == EAST)
	{
		if(getCharAtIndex(tempEAST) == '#' || getCharAtIndex(tempEAST) == 'O')
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else if(facing == WEST)
	{
		if(getCharAtIndex(tempWEST) == '#' || getCharAtIndex(tempWEST) == 'O')
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	return false;

	error:
		return true;
}

/*
Change the robot's position appropriately due to facing. Don't forget to
leave a 'breadcrumb' in the old position (see the project requirements).
*/
int MoveForward()
{
	int myPosition = XYToIndex(xpos, ypos);

	check(grid != NULL, "Init Warning: maze is not defined.");

	if(getCharAtIndex(myPosition) == ' ')
	{
		setCharAtIndex(myPosition, '.');
	}
	else if(getCharAtIndex(myPosition) == '.')
	{
		setCharAtIndex(myPosition, 'o');
	}
	else if(getCharAtIndex(myPosition) == 'o')
	{
		setCharAtIndex(myPosition, '0');
	}
	else if(getCharAtIndex(myPosition) == '0')
	{
		setCharAtIndex(myPosition, 'O');
	}


	if(facing == NORTH)
	{
		ypos = ypos - 1;
	}
	else if(facing == SOUTH)
	{
		ypos = ypos + 1;
	}
	else if(facing == EAST)
	{
		xpos = xpos + 1;
	}
	else if(facing == WEST)
	{
		xpos = xpos - 1;
	}

	return 1;

	error:
		return false;
}

/*
Checks to see if the robot's position matches the destination coordinates
and returns true if it does.  Otherwise, return false.
*/
int AtDestination()
{
	int myPosition = XYToIndex(xpos, ypos);

	check(grid != NULL, "Init Warning: maze is not defined.");

	if(xpos == (getX() - 2) && ypos == (getY() - 2))
	{
		setCharAtIndex(myPosition, 'X');
		return 1;
	}
	else
	{
		return 0;
	}

	error:
		return false;
}
