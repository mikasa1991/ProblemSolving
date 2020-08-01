#ifndef POS_H
#define POS_H

#include <stdbool.h>
#define MAX 		10
#define PATH 		0	//can move
#define WALL 		1	//can't move
#define VISITED 	2
#define BACKTRACKED 3	//after visiting, come back
#define FileName    "maze.txt"

extern int n;				//maze n by n
extern int maze[MAX][MAX];

typedef struct _position
{
	int x;		//the x point of location
	int y;		//the y point of location
	int dir;	//the dir you gonna move out
}position;

position move_to(position pos, int dir);
bool movable(position pos, int dir);
bool is_wall(position pos);
bool is_visited(position pos);
bool is_not_area(position pos);
bool is_backtracked(position pos);
#endif //POS_H