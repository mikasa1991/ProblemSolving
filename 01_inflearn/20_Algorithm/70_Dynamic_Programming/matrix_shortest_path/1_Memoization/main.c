/*
정수들이 저장된 nbyn행렬의 좌상단에서 우하단까지 이동한다.
단 오른쪽이나 아래쪽 방향으로만 이동할 수 있다.

방문한 칸에 있는 정수들의 합이 최소화되도록 하라

여기서는 동적계획법으로 풀어보자

[Action] (190428)
다익스트라 알고리즘으로 풀어보기
*/

/*
0: 제출용
1: 테스트용
*/
#define MODE 1

#define MAX 10
#define MIN(a, b) ((a < b) ? a : b)

#include <stdio.h>
#include <time.h>

int L[MAX+1][MAX+1];	//cache
int m[MAX+1][MAX+1];
int mat_func_call_cnt = 0;

/*
f(i, j): (1,1)에서 (i,j)까지 이르는 최소합
m_ij: (i, j)의 경로 값

//recursive case
f(i, j)
= MIN(f(i-1, j), f(i, j-1)) + m_ij

//base case
case1. i == 1, j == 1
 f(i, j) = m_ij
case2. i == 1,
 f(i, j) = f(i, j-1) + m_ij
case3. j == 1,
 f(i, j) = f(i-1, j) + m_ij
*/

/*
방법1. 탑다운, 재귀함수
재귀함수를 이용해 탑다운방식으로 
문제풀이를 접근하는 경우, 많은계산이 중복된다.
어떻게 효율적으로 바꿀 수 없을까?
*/
int mat(int i, int j)
{
	mat_func_call_cnt++;
	if(i == 1 && j == 1)	//base case
		return m[i][j];

	else if(i == 1)
		return mat(1, j-1) + m[i][j];
	
	else if(j == 1)
		return mat(i-1, 1) + m[i][j];
	
	else
		return MIN(mat(i-1,j), mat(i,j-1)) + m[i][j];
}

/*
메모이제이션으로 효율적으로 바꿀 수 있다.
*/
int mat2(int i, int j)
{
	mat_func_call_cnt++;
	
	if(L[i][j] > -1)
		return L[i][j];

	if(i == 1 && j == 1)	//base case
		L[i][j] = m[i][j];

	else if(i == 1)
		L[i][j] = mat2(1, j-1) + m[i][j];
	
	else if(j == 1)
		L[i][j] = mat2(i-1, 1) + m[i][j];
	
	else
		L[i][j] = MIN(mat2(i-1,j), mat2(i,j-1)) + m[i][j];
	
	return L[i][j];
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

#if MODE
	freopen("input.txt", "r", stdin);
	setbuf(stdout, NULL);

	float gap = 0;
	time_t startTime = 0;
	time_t endTime = 0;
	startTime = clock();	//측정시작 시각
#endif

	int n = 0;
	scanf("%d", &n);
	init_cache(n);
	input_matrix(n);
	output_matrix(n);
	//printf("목적지까지의 정수들의 최소합: %d\n", mat(4, 4));
	printf("목적지까지의 정수들의 최소합: %d\n", mat2(4, 4));
	//printf("mat함수 콜 된 횟수: %d\n", mat_func_call_cnt);

#if MODE
	endTime = clock();		//측정완료 시각
	gap = (float)(endTime - startTime)/(CLOCKS_PER_SEC);
	printf("%fsec\n", gap);
#endif

	return 0;
}