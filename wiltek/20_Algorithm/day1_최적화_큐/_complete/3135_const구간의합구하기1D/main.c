/*
http://jungol.co.kr/xpert/viewp.php?bo_table=sm_bank&id=3135&alcate=&mtitle=%EB%AC%B8%EC%A0%9C%EC%9D%80%ED%96%89&al=003&altitle=&alname=&altag=&page=1
*/

/*
1차원 배열에 N개의 수들이 입력되어 있다.
이 배열의 임의의 구간에 있는 수들의 합을 
물어보는 M개의 쿼리에 답하는 프로그램을 작성하시오.
쿼리에 답하는 중간에 배열의 어떤 원소도 값이 변경되지 않는다.

첫 행에 원소의 수 N이 입력된다. ( 1 <= N <= 1,000,000)
다음 행에 N개의 수 Ai가 공백을 구분하여 입력된다. ( -1,000,000 <= Ai <= 1,000,000)
다음 행에 쿼리의 수 M이 입력된다. ( 1 <= M <= 1,000,000)
이어서 M개의 행에 쿼리의 정보 si, ei가 공백으로 구분되어 입력된다. ( 1<= si <= ei<= N)
*/

#include <stdio.h>

#define DEBUG 1

#ifdef DEBUG
#define MAX_N (10+1)

#else
#define MAX_N ((int)(1e6)+10)
#endif

typedef long long ll;

ll A[MAX_N];
int N;

void input_data()
{
	scanf("%d\n", &N);
	for(int i = 1; i <= N; i++)
	{
		scanf("%lld", &A[i]);
		A[i] = A[i] + A[i-1];
	}
}

//si ~ ei 구간합 반환하기
ll query(int si, int ei)
{
	return A[ei] - A[si-1]; 
}

void solve()
{
	int q_n;
	int si, ei;
	ll ans;

	scanf("%d", &q_n);
	for(int i = 0; i < q_n; i++)
	{
		scanf("%d %d", &si, &ei);
		ans = query(si, ei);
		printf("%lld\n", ans);
	}
}

void main()
{
#ifdef DEBUG
	freopen("input.txt", "r", stdin);
#endif
	input_data();
	solve();
}