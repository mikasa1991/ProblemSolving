#include "pos.h"
#include "queueADT.h"

int read_maze(FILE* fp);
void print_maze();

void main()
{
	FILE* fp = fopen(FileName, "r");
	if(fp == NULL)
	{
		puts("file Open Failed.");
		return;
	}

	if(read_maze(fp) != n*n)
	{
		puts("read_maze failed.");
		return;
	}
	print_maze();

	queue* q = create_queue_instance();
	position cur;
	cur.x = 0;
	cur.y = 0;

	/*
	 *1. Set start point (0, 0)
	 *2. enqueue a start point in queue
	 */
	enqueue(q, cur);
	maze[0][0] = -1;
	printf("enqueue: (%d, %d), %d\n", cur.x, cur.y, maze[cur.x][cur.y]);	//for debug
	bool found = false;

	/*
	시작정점을 방문한다. maze[0][0] = -1
	시작정점을 enqueue한다.

	큐가 비어있지 않다면 루프를 도는데,
 	 dequeue한다.
 	 dequeue한 값과 연결되어있고, 이동가능한 정점들을 방문한다.
  	 단, 이동가능한 정점이 finish지점인 경우, 반복문을 탈출한다?
 	 dequeue한 값과 연결되어있고, 이동가능한 정점들을 enqueue한다.
	*/
	while(is_empty(q) == false)
	{
		position cur = dequeue(q);
		printf("dequeue: (%d, %d), %d\n", cur.x, cur.y, maze[cur.x][cur.y]);	//for debug
		for(int dir = 0; dir < 4; dir++)
		{
			if(movable(cur, dir))
			{
				position pos = move_to(cur, dir);				//move out from the current location
				maze[pos.x][pos.y] = maze[cur.x][cur.y] - 1;	//write VISITED
				
				//이는 마지막 정점을 enqueue를 하지 않고자.				
				if(pos.x == n-1 && pos.y == n-1)				//if you get to end point
				{
					found = true;
					break;
				}
				enqueue(q, pos);
				printf("enqueue: (%d, %d), %d\n", pos.x, pos.y, maze[pos.x][pos.y]);	//for debug
			}
		}
	}

	if(found == true) puts("Found the path.");
	else 			  puts("No path exists.");

	print_maze();
	return;
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