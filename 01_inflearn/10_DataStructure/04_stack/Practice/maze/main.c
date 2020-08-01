/*
data structure; linked list

(190214)
[Quesion]
Q1.백트래킹 하는 지점에 대해서는 다시 갈 수 있도록 해야하는가?
>다시 돌아갈 필요가 없음

Q2.is_go_next함수의 경우, 백트래킹 했을 때 기존에 체크했던 방향은 체크하지 않도록 하려면?
>Maze_Array 폴더의 소스코드 참고해주세요.

[Action]
A1.최단거리를 구하는 것으로 할려면 코드를 어떻게 변경해야하는가?
>when push, result upcounting. when pop, result downcounting.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 	10	//map size ;MAX * MAX size
#define CHECKED 2
#define BARRIER 1	//can not move out to here
#define ROAD	0	//can move out to here

typedef struct _data item;
typedef struct _data
{
	int x_pos;
	int y_pos;	
}data;

typedef struct _node node;
typedef struct _node
{
	data* item;
	node* next;
}node;

//function declare
node* create_node(int x, int y);
data* create_data(int x, int y);
void push(int x, int y);
int pop(data* t_data);
void traverse();
bool is_empty();
void print_map();
void remove_node(node* t_node);
int is_go_next(int x, int y);
int read_map();

//variable declare
node* top = NULL;
int map[MAX][MAX] = {0, };
int row_size = 0;
int col_size = 0;
int result = 0;				//최단거리
//
int main()
{
#if 0
	data t_data = {0, };
	print_map();
	push(0, 0);
	push(1, 0);
	push(2, 0);
	traverse();
	
	(void)pop(&t_data);
	printf("pop (%d, %d)\n", t_data.x_pos, t_data.y_pos);
	traverse();

	(void)pop(&t_data);
	printf("pop (%d, %d)\n", t_data.x_pos, t_data.y_pos);
	traverse();
#endif

	//bool flg_finish = false;
	data t_data = {0, };
	int x, y = 0;				//map index

	freopen("input.txt", "r", stdin);
	setbuf(stdout, NULL);

	//read txt file error
	if(read_map() == -1)
	{
		puts("read_map error");
		return -1;
	}

	print_map();
	push(0, 0);	//start
	while(1)
	{
		//can not process checked
		if(top == NULL)
		{
			puts("can not process");
			break;
		}

		//now position checked
		x = top->item->x_pos;
		y = top->item->y_pos;
		//map[x][y] = CHECKED;
		if(map[x][y] == ROAD)
			map[x][y] = result * -1;	//CHECKED

		printf("position: (%d, %d)\n", x, y);

		//finish point checked
		if(x == row_size-1 && y == col_size-1)
		{
			puts("finish");
			break;
		}

		switch(is_go_next(x, y))
		{
			case 1:	//up
				push(x-1, y);
				break;
			case 2:	//right
				push(x, y+1);
				break;
			case 3:	//down
				push(x+1, y);
				break;
			case 4:	//left
				push(x, y-1);
				break;
			case 5:	//can not anywhere, so come back to pre_root
				(void)pop(&t_data);
				break;
			default:
				break;
		}
	}
	print_map();
	return 0;
}

/*
txt file format
 - map row size
 - map col size
 - map val
*/
int read_map()
{
	scanf("%d %d", &row_size, &col_size);
	if((row_size > MAX) || (col_size > MAX))
	{
		puts("row_size or col_size is bigger than MAX");
		return -1;
	}

	int cnt = 0;

	for(int i = 0; i < row_size; i++)
	{
		for(int j = 0; j < col_size; j++)
		{
			scanf("%d", map[i] + j);
			cnt++;
		}
	}
	return cnt;
}

int is_go_next(int x, int y)
{
	//up
	if(map[x-1][y] == ROAD && (x-1 >= 0) && (y >= 0) && (x-1 < row_size) && (y < col_size)) 	 return 1;
	//right
	else if(map[x][y+1] == ROAD && (x >= 0) && (y+1 >= 0) && (x < row_size) && (y+1 < col_size)) return 2;
	//down
	else if(map[x+1][y] == ROAD && (x+1 >= 0) && (y >= 0) && (x+1 < row_size) && (y < col_size)) return 3;
	//left
	else if(map[x][y-1] == ROAD && (x >= 0) && (y-1 >= 0) && (x < row_size) && (y-1 < col_size)) return 4;
	//can not go anywhere
	else return 5;
}

void print_map()
{
	printf("map size: (%d,%d)\n", row_size, col_size);
	for(int i = 0; i < row_size; i++)
	{
		for(int j = 0; j < col_size; j++)
		{
			printf("%d ", map[i][j]);
		}
		puts("");
	}
}

node* create_node(int x, int y)
{
	node* new_node = (node*)malloc(sizeof(node));
	new_node->item = create_data(x, y);
	new_node->next = NULL;
	return new_node;
}

data* create_data(int x, int y)
{
	data* new_data = (data*)malloc(sizeof(data));
	new_data->x_pos = x;
	new_data->y_pos = y;
	return new_data;
}

//insert_unique_node, and insert_node_first(head_after)
void push(int x, int y)
{
	node* new_node = create_node(x, y);
	new_node->next = top;
	top = new_node;
	result++;
}

void remove_node(node* t_node)
{
	free(t_node->item);
	free(t_node);
}

//delete_unique_node, and delete_node_first(head_after)
//음수값은 입력받지 않는다고 가정
int pop(data* t_data)
{
	if(is_empty())
	{
		puts("stack is empty");
		return -1; //error
	}

	t_data->x_pos = top->item->x_pos;
	t_data->y_pos = top->item->y_pos;

	//int val = top->item;
	node* t_node = top;
	top = top->next;
	remove_node(t_node);
	result--;
	return 1;
}

void traverse()
{
	node* t_node = top;

	while(t_node != NULL)
	{
		printf("(%d, %d)\n", t_node->item->x_pos, t_node->item->y_pos);
		t_node = t_node->next;
	}
}

bool is_empty()
{
	return top == NULL;
}