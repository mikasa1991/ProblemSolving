/*
//출처: 6장. 그래프 알고리즘 13페이지
//너비우선순회, 최단거리, 최단거리루트 출력하기

//input
첫째 줄에 정점의 개수 N(1 ≤ N ≤ 1,000), 간선의 개수 M(1 ≤ M ≤ 10,000), 탐색을 시작할 정점의 번호 V가 주어진다. 
다음 M개의 줄에는 간선이 연결하는 두 정점의 번호가 주어진다. 어떤 두 정점 사이에 여러 개의 간선이 있을 수 있다. 
입력으로 주어지는 간선은 양방향이다.

Q.> 정점의 개수는 왜 필요할까?

//output
첫째 줄에 DFS를 수행한 결과를, 그 다음 줄에는 BFS를 수행한 결과를 출력한다. 
V부터 방문된 점을 순서대로 출력하면 된다.
*/

#include <stdio.h>
#include <memory.h>

#define LINK 		 1
#define NOT_VISITED -1
#define MAX 	     1000

int queue[MAX];
int map[1001][1001];
int d[1001]; 		//시작점에서 i정점까지의 거리; 방문하지 않은 정점은 -1로 초기화한다.
int v_prev[1001];	//i정점의 이전 정점
int size_queue = 0;
int front = 0;
int rear = -1;

int is_empty()
{
	if(size_queue == 0) return 1;
	else 				return 0;
}

void enqueue(int val)
{
	rear = (rear + 1) % MAX;
	queue[rear] = val;
	size_queue++;
}

int dequeue()
{
	if(is_empty()) return -1;
	
	int val = queue[front];
	front = (front + 1) % MAX;
	size_queue--;

	return val;
}

void print_map(int n)
{
	for(int i = 1; i <= n; i++)
	{
		for(int j = 1; j <= n; j++)
		{
			printf("%d ", map[i][j]);
		}
		puts("");
	}
	puts("");
}

/*
주의해야하는 것은 끝 정점에서 시작 정점으로 타고 가야한다.
그래야 바로바로 탐색시간 낭비없이 진행이 가능하다.

//base case
s, v가 같으면, s(== v) 출력하고 종결

//recursive case
s, v가 다르면, s, v_prev에 대해서 함수 call하기
함수 call 돌아와서 v 출력하고 종결
*/

void print_root_shortest_distance(int s, int v)
{
	if(s == v) printf("%d ", s);
	else if(v_prev[v] == -1)
	{
		puts("no path from s to v exists");
	}
	else
	{
		print_root_shortest_distance(s, v_prev[v]);
		printf("%d ", v);
	}
}

int main()
{
	freopen("input.txt", "r", stdin);
	setbuf(stdout, NULL);

	//init
	int cnt_vertex = 0;
	int cnt_edge = 0;
	int start_vertex = 0;

	int x, y = 0;
	int v = 0;

	scanf("%d %d %d", &cnt_vertex, &cnt_edge, &start_vertex);
	
	for(int i = 1; i <= cnt_vertex; i++)
	{
		d[i] = NOT_VISITED;
	}

	for(int i = 0; i < cnt_edge; i++)
	{
		scanf("%d %d", &x, &y);
		map[x][y] = map[y][x] = LINK;	//undirected linking
	}

	//print_map(cnt_vertex);

	d[start_vertex] = 0;
	v_prev[start_vertex] = -1;	//nothing

	enqueue(start_vertex);

	/*
	시작정점을 방문한다. d[start_vertex] = 0
	시작정점을 enqueue한다.

	큐가 비어있지 않다면 루프를 도는데,
 	 dequeue한다.
 	 dequeue한 값과 연결되어있고, 방문하지않은 정점들을 방문한다.
 	 dequeue한 값과 연결되어있고, 방문하지않은 정점들을 enqueue한다.
	*/
	while(!is_empty())
	{
		v = dequeue();
		printf("%d(L%d)(v_prev:%d)\n", v, d[v], v_prev[v]);		//너비우선순회, 최단거리
		for(int i = 1; i <= cnt_vertex; i++)
		{
			if(map[v][i] == LINK && d[i] == NOT_VISITED)
			{
				d[i] = d[v] + 1;
				v_prev[i] = v;
				enqueue(i);
			}
		}
	}
	print_root_shortest_distance(start_vertex, v);
	puts("");
	return 0;
}