/*
n개로 이루어진 정수 집합에서 원하는 수 k 이하의 값 중에 가장 큰 자료의 인덱스를 출력하시오.
단, 입력되는 집합은 오름차순으로 정렬되어 있으며, 같은 수가 여러 개 존재할 수 있다.
인덱스는 1부터 시작한다.

입력
첫째 줄에 한 정수 n, 둘째 줄에 n개의 정수가 공백으로 구분되어 입력된다. 
셋째 줄에는 찾고자 하는 값 k가 입력된다.
(단, 2 <= n <= 1,000,000, 각 원소의 크기는 100,000,000을 넘지 않는다.)

출력
찾고자 하는 원소의 위치를 출력한다. 만약 모든 원소가 k보다 작으면 n+1을 출력한다.

5
1 3 5 5 7
5

4
*/

/*
k 이하의 값 중에 가장 큰 자료라는 것은, 결국 k값을 가지는 자료인데, 그렇다면 이진탐색이랑 다를 게 없잖아?

근데, k값이 2개 이상인 경우에는, 이진탐색처럼 풀 수가 없다.
이 때, 오름차순 정렬 기준으로, 가장 오른쪽에 있는 k값이 upper bound가 된다.
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
	int sol = n+1;
	//int sol = -1;
	
	//A[m] == find, s = m + 1
	//A[m] >  find, e = m - 1
	//A[m] <  find, s = m + 1
	while(s <= e)
	{
		m = (s+e) / 2;
		if(A[m] <= find)
		{
			sol = m;
			s = m + 1;
		}
		else e = m - 1;
	}
	return sol;
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