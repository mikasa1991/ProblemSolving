/*
정수들이 저장된 nbyn행렬의 좌상단에서 우하단까지 이동한다.
단 오른쪽이나 아래쪽 방향으로만 이동할 수 있다.

방문한 칸에 있는 정수들의 합이 최소화되도록 하라

여기서는 동적계획법으로 풀어보자

[Action] (190428)
1.다익스트라 알고리즘으로 풀어보기
2.경로를 시각화해서 구현해보기 
*/

#define MAX 10
#define MIN(a, b) ((a < b) ? a : b)

#include <stdio.h>

int L[MAX+1][MAX+1];	//cache
int m[MAX+1][MAX+1];
//int mat_func_call_cnt = 0;

/*
방법2.바텀업 방식, 순환식

[Action]
4개의 조건문을 더 간단하게 할 방법을 생각해보기
*/
int mat(int i, int j, int n)
{
	for(int i = 1; i <= n; i++)
	{
		for(int j = 1; j <= n; j++)
		{
			if(i == 1 && j == 1)
				L[i][j] = m[1][1];
			else if(i == 1)
				L[i][j] = m[1][j] + L[i][j-1];
			else if(j == 1)
				L[i][j] = m[i][j] + L[i-1][j];
			else
				L[i][j] = m[i][j] + MIN(L[i-1][j], L[i][j-1]);
		}
	}
	return L[n][n];
}

void input_matrix(int n)
{
	for(int i = 1; i <= n; i++)
	{
		for(int j = 1; j <= n; j++)
		{
			scanf("%d", &m[i][j]);
		}
	}
}

void output_matrix(int n)
{
	for(int i = 1; i <= n; i++)
	{
		for(int j = 1; j <= n; j++)
		{
			printf("%d ", m[i][j]);
		}
		puts("");
	}
}

void init_cache(int n)
{
	for(int i = 1; i <= n; i++)
	{
		for(int j = 1; j <= n; j++)
		{
			L[i][j] = -1;
		}
	}
}

int main()
{

#if 1
	freopen("input.txt", "r", stdin);
	setbuf(stdout, NULL);
#endif

	int n = 0;
	scanf("%d", &n);
	//init_cache(n);
	input_matrix(n);
	output_matrix(n);
	printf("목적지까지의 정수들의 최소합: %d\n", mat(4, 4, 4));
	//printf("mat함수 콜 된 횟수: %d\n", mat_func_call_cnt);
	return 0;
}