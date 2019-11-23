/*
https://www.acmicpc.net/problem/2805
*/

#include <stdio.h>
#define DEBUG 1
#define MAXN ((int)1e6 + 10)

int N;			//나무 수
int M;			//원하는 나무 수량
int H[MAXN];	//나무 높이

int getMax_InputData() 
{
	int maxh = 0;
	scanf("%d %d", &N, &M);
	for (int i = 0; i < N; i++) 
	{
		scanf("%d", &H[i]);
		if (maxh < H[i]) maxh = H[i];
	}
	return maxh;
}

int check(int m) 
{
	int sum = M;
	for (int i = 0; i < N; i++) 
	{
		if (H[i] <= m) continue;	//기준 높이보다 낮으므로 잘리지 않음
		sum -= H[i] - m;			//기준높이 이상 값만 얻음
		if (sum <= 0) return 1;		//m이면 원하는 나무 수량 얻을 수 있음
	}
	return 0;//불가능
}

int solve(int e) //upper bound
{//가능한 높이 중 제일 높은 높이를 찾기
	int s = 0, sol = -1, m;
	while (s <= e) 
	{
		m = (s + e) / 2;
		if (check(m))	//m(톱의 높이)으로 원하는 나무수량을 얻는 경우,
		{ 
			sol = m; 
			s = m + 1; 
		}
		else e = m - 1;
	}
	return sol;
}

int main() {
#ifdef DEBUG
	freopen("input.txt", "r", stdin);
#endif
	int e = getMax_InputData();
	int ans = solve(e);
	printf("%d\n", ans);
	return 0;
}