/*
n개로 이루어진 정수 집합에서 원하는 수의 위치를 찾으시오.
단, 입력되는 집합은 오름차순으로 정렬되어 있으며, 같은 수는 없다.

입력
첫 줄에 한 정수 n이 입력된다.
둘째 줄에 n개의 정수가 공백으로 구분되어 입력된다.
셋째 줄에는 찾고자 하는 수가 입력된다.
(단, 2 <= n <= 1,000,000 , 각 원소의 크기는 100,000,000을 넘지 않는다.)

출력
찾고자 하는 원소의 위치를 출력한다. 없으면 -1을 출력한다.

입력
8
1 2 3 5 7 9 11 15
11

출력
7

입력
3
2 5 7
3

출력
-1
*/
#include <stdio.h>
#define MAX_N ((int)1e6 + 10)
//#define MAX_N 10

int n;
int find;
int A[MAX_N];

void input_data()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
	{
		scanf("%d", &A[i]);
	}
	scanf("%d", &find);
}

int get_idx_solve()
{
	int s = 1;
	int e = n;
	int m = 0;

	while(s <= e)
	{
		m = (s+e) / 2;
		if(A[m] == find)     return m;
		else if(A[m] > find) e = m - 1;
		else 				 s = m + 1;
	}
	return -1;
}

void main()
{
#if 1
	freopen("input.txt", "r", stdin);
#endif
	int ans = 0;
	input_data();
	ans = get_idx_solve();
	printf("%d", ans);
}