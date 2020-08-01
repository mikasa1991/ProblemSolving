#include "pos.h"

static int offset[4][2] 
= { {-1, 0}, 	//North //offset[0][0], offset[0][1]
	{0,  1}, 	//East	//offset[1][0], offset[1][1]
	{1,  0}, 	//South	//offset[2][0], offset[2][1]
	{0, -1} };	//West	//offset[3][0], offset[3][1]

int n = 0;	//maze n by n
int maze[MAX][MAX] = {0, };

/*
 *Go to One Step
 *dir == 0, Northward 
 *dir == 1, Eastward
 *dir == 2, Southward
 *dir == 3, Westward
 */
position move_to(position pos, int dir)
{
	position next;
	next.x = pos.x + offset[dir][0];
	next.y = pos.y + offset[dir][1];
	return next;
}

bool movable(position pos, int dir)
{
	position next = move_to(pos, dir);

	//if cur location is WALL or VISITED or NOT_AREA or BACKTRACKED
	if(is_wall(next) || is_visited(next) || is_not_area(next) || is_backtracked(next))
	{
		return false;
	}
	return true;
}

bool is_wall(position pos)
{
	if(maze[pos.x][pos.y] == WALL)
	{ 
		return true;
	}
	return false;
}

bool is_visited(position pos)
{
	if(maze[pos.x][pos.y] == VISITED)
	{
		return true;
	}
	return false;
}

bool is_not_area(position pos)
{
	if( pos.x < 0 || pos.x >= n || pos.y < 0 || pos.y >= n)
	{
		return true;
	}
	return false;
}

bool is_backtracked(position pos)
{
	if(maze[pos.x][pos.y] == BACKTRACKED)
	{
		return true;
	}
	return false;
}