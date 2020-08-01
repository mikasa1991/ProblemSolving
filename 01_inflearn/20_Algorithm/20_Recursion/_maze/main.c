/*
현재 위치에서 이미 가본 곳을 다시 지나지 않고 출구까지 가는 경로가 있으려면
1) 현재 위치가 출구이거나 혹은
2) 이웃한 셀들 중 하나에서 이미 가본 곳을 다시 지나지 않고 출구까지 가는 경로가
있거나
*/

#include <stdio.h>
#include <stdbool.h>

#define PATHWAY 0
#define WALL    1
/*
PATH_COLOR: visited이며, 아직 출구로 가는 경로가 될 가능성이 있는 cell
BLOCKED_COLOR: visited이며, 출구까지의 경로상에 있지 않음이 밝혀진 cell
*/
#define BLOCKED 2 	//after visited, figure out blocked
#define PATH    3	//visited

int n = 4;
int maze[][4] = {
	{0, 0, 0, 0},
	{0, 1, 1, 0},
	{0, 0, 0, 1},
	{0, 1, 0, 0}
};

void printMaze()
{
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < n; j++)
		{
			printf("%d ", maze[i][j]);
		}
		puts("");
	}
}
/*
f(x, y) WALL      ... return 
f(x, y) end point ... return
f(x, y) 		  ... f(x-1, y) || f(x, y+1) || f(x+1, y) || f(x, y-1)
*/
bool findMazePath(int x, int y)
{
	//printf("(%d, %d)\n", x, y);
	if( x < 0 || y < 0 || x >= n || y >= n || maze[x][y] != PATHWAY)	//base case_fail
	{
		//printf("(%d, %d) <- range error\n", x, y);
		return false;
	}
	else if(x == n-1 && y == n-1) //base case_success
	{
		//printf("(%d, %d) <- end point\n", x, y);
		maze[x][y] = PATH;
		return true;
	}
	else						  //recursive case
	{
		//printf("(%d, %d) <- check PATH\n", x, y);
		maze[x][y] = PATH;		//3

		// north || east || south || west
		if(findMazePath(x-1, y) || findMazePath(x, y+1) || findMazePath(x+1, y) || findMazePath(x, y-1))
		{
			//printf("(%d, %d) <- Can do PATH\n", x, y);
			return true;
		}
		//printf("(%d, %d) <- BLOCK\n", x, y);
		maze[x][y] = BLOCKED;	//2
		return false;
	}
}

void main()
{
	printMaze();
	puts("");
	findMazePath(0, 0);
	printMaze();
}