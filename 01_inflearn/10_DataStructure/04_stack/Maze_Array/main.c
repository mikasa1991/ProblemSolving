#include "stackADT.h"
#include "pos.h"

int read_maze(FILE* fp);
void print_maze();

void main()
{
	FILE* fp = fopen(FileName, "r");
	if(fp == NULL)	//if file not exist
	{
		puts("Open failed.");
		return;
	}
	
	if(read_maze(fp) != (n*n))
	{
		puts("read_maze failed.");
		return;
	}
	print_maze();	//for debug

	stack* s = create_stack_instance();

	//current position initialized: start point (0, 0)
	//position cur;
	//cur.x = 0;
	//cur.y = 0;
	//cur.dir = 0;
	
	position cur = {0, };	//현재 위치를 저장하는데 쓰려고

	int init_dir = 0;		//push할 때, 현재 dir을 저장해서, pop할 때, 불필요한 탐색 방향을 가지 않을려고

	/*
	//스택은 큐와 다르게, 언제 반복문을 탈출해야할지 자료구조적으로 트리거가 없다.
	//미로를 통과하기까지 몇 개의 정점을 지나는지도 모른다.
	//그래서 무한루프로 설정을 하고 트리거는 피니셔 정점에 도달했을 때로 할려고 한다.

	무한루프
 	 임의의 정점을 방문한다.
 	 그 정점이 finish 지점인 경우, 반복문을 탈출한다.
 	 이동 가능한 정점이 있다면, 푸쉬하고 그 정점을 가지고 무한루프 도입으로 돌아간다.
  	 이동 가능한 정점이 없다면, 팝을 한 후에 top이 가르키는 정점을 가지고 무한루프 도입으로 돌아간다.
	*/
	while(1)
	{
		maze[cur.x][cur.y] = VISITED;	//CHECKED

		//Check if you get to final position 
		if(cur.x == n-1 && cur.y == n-1) //if you get to end point,
		{
			puts("found the path.");
			break;
		}

		//if you did't get to final position
		//step3. Check you can move out from another postion
		bool forwarded = false;						//flag; you found you can go another direction?
		for (int dir = init_dir; dir < 4; dir++)	//0(North) 1(East) 2(South) 3(West)
		{
			if(movable(cur, dir))	//if you can move out from the current position,
			{
				/*
				 *push your current position
				 *move out to next
				 */
				cur.dir = dir;
				push(s, cur);												//push the point_now
				printf("push: (%d, %d), dir: %d\n", cur.x, cur.y, cur.dir);	//for debug
				cur =  move_to(cur, dir);									//move to the point_new through direction
				forwarded = true;
				init_dir = 0;
				break;
			}
		}

		//if you can't move out from current position, you should come back to prev position. 
		if(forwarded == false)
		{
			maze[cur.x][cur.y] = BACKTRACKED;
			if(is_empty(s))
			{
				puts("No path exists.");
				break;
			}

			item temp = pop(s);
			printf("_pop: (%d, %d), dir: %d\n", temp.x, temp.y, temp.dir);	//for debug
			int d = temp.dir;
			
			/*
			 백트래킹을 하고나서,
			 기존에 진행했던 방향을 가지 않기 위해서는,
		 	 방법1. 방문지점을 체크할 변수를 할당한다.
			 또는,
			 방법2. 위 소스에서 구현한 것처럼, 2차원 배열의 좌표뿐만 아니라,
      	 	 진행방향까지 저장하는 변수를 할당한다.
			 
			 * what does it mean the para "(d+2) % 4"?
			 *if d is 0(North), para val will be 2(South)
			 *if d is 1(East), para val will be 3(West)
			 *if d is 2(South), para val will be 0(North)
			 *if d is 3(West), para val will be 1(East)
			 */
			cur = move_to(cur, (d+2)%4);	//cf. Maze_pic07
			
			init_dir = d+1;
			printf("cur.dir : %d\n", cur.dir);
			printf("init_dir: %d\n", init_dir);
		}
	}
	print_maze();
}

int read_maze(FILE* fp)
{
	int ch = 0;
	int x = 0;
	int y = 0;
	int cnt_char = 0;
	
	//while((ch = fgetc(FileName)) != '\n' && ch != EOF)
	while((ch = fgetc(fp)) != EOF)
	{
		if(ch == '\n')
		{
			x++;
			y = 0;
			continue;
		}

		if(y < MAX)
		{
			maze[x][y] = ch - '0';
			y++;
			cnt_char++;
		}
	}
	n = x + 1;
	return cnt_char;
}

void print_maze()	//array n by n
{	
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < n; j++)
		{
			printf("%d ", maze[i][j]);
		}
		puts(" ");
	}
}
