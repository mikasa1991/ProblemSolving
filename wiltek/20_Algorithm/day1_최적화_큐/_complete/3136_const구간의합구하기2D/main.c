/*
http://jungol.co.kr/xpert/viewp.php?bo_table=sm_bank&id=3136&alcate=&mtitle=%EB%AC%B8%EC%A0%9C%EC%9D%80%ED%96%89&al=003&altitle=&alname=&altag=&page=1
*/

/*
N * N크기의 2차원 배열에 수들이 입력되어 있다.

이 배열의 임의의 구간에 있는 수들의 합을 
물어보는 M개의 쿼리에 답하는 프로그램을 작성하시오.
쿼리에 답하는 중간에 배열의 어떤 원소도 값이 변경되지 않는다.​ 

첫 행에 행과 열의 크기 N이 입력된다. ( 1 <= N <= 1,000)
다음 N개의 행에 걸쳐 N개의 수 Ai가 공백을 구분하여 입력된다. ( -1,000,000 <= Ai <= 1,000,000)
다음 행에 쿼리의 수 M이 입력된다. ( 1 <= M <= 1,000,000)
이어서 M개의 행에 쿼리의 정보 sri, sci, eri, eci가 공백으로 구분되어 입력된다. ( 1<= sri <= eri<= N, 1<= sci <= eci<= N)
각 쿼리에 대한 결과를 행으로 구분하여 출력한다.
*/

#include <stdio.h>

#define DEBUG 1

#ifdef DEBUG
#define MAX_N (10+1)

#else
#define MAX_N ((int)(1e3)+10)
#endif

typedef long long ll;

ll A[MAX_N][MAX_N];
int N;

void input_data()
{
	scanf("%d\n", &N);
	for(int r = 1; r <= N; r++)
	{
		for(int c = 1; c <= N; c++)
		{
			scanf("%lld", &A[r][c]);
			A[r][c] = A[r][c] + A[r-1][c] + A[r][c-1] - A[r-1][c-1];
		}
	}
}

//si ~ ei 구간합 반환하기
ll query(int sr, int sc, int er, int ec)
{
	return A[er][ec] - A[er][sc-1] - A[sr-1][ec] + A[sr-1][sc-1]; 
}

void solve()
{
	int q_n;
	int sr, sc, er, ec;
	ll ans;

	scanf("%d", &q_n);
	for(int i = 0; i < q_n; i++)
	{
		scanf("%d %d %d %d", &sr, &sc, &er, &ec);
		ans = query(sr, sc, er, ec);
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