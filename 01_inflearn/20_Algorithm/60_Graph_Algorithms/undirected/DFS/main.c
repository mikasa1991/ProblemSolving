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
#define NOT_VISITED  0
#define MAX 	     1000

int stack[MAX];
int map[1001][1001];
int visited[1001];	//0: not visited, 1: visited

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
//재귀함수
임의의 정점을 방문한다
그 정점과 연결된 정점이 있을 경우, 연결된 정점을 매개변수로 해서 함수를 콜한다.
그 정점과 연결된 정점이 없을 경우, 함수를 종료한다.
*/
void DFS(int v, int n)
{
	printf("%d ", v);
	visited[v] = 1;
	for(int i = 1; i <= n; i++)
	{
		if(map[v][i] == LINK && visited[i] == NOT_VISITED) DFS(i, n);
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
	
	for(int i = 0; i < cnt_edge; i++)
	{
		scanf("%d %d", &x, &y);
		map[x][y] = map[y][x] = LINK;	//undirected linking
	}

	DFS(start_vertex, cnt_vertex);
	//print_map(cnt_vertex);

	return 0;
}