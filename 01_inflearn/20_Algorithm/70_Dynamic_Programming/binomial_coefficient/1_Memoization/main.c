#include <stdio.h>

#define MAX 10
/*
Q.이항계수문제를 왜 관계식으로 접근해서 풀어야하나요?
A.이항계수 공식을 이용해서 계산을 하면 값의 범위가 커서
변수 범위를 초과하는 경우가 발생한다.
따라서, 관계식을 이용해서 재귀방식으로 풀던가 해야겠지.
*/

/*
탑다운방식, 중복되는 계산이 많다.
비효율적이다.
*/
int binomial(int n, int k)
{
	printf("n: %d, k: %d\n", n, k);
	if(n == k || k == 0)
		return 1;
	else
		return binomial(n-1, k) + binomial(n-1, k-1);
}

/*
방법1. 메모이제이션
*/

int binom[MAX+1][MAX+1];

int init_cache()
{
	for(int i = 0; i < MAX + 1; i++)
	{
		for(int j = 0; j < MAX + 1; j++)
		{
			binom[i][j] = -1;
		}
	}
}

int binomial2(int n, int k)
{
	printf("n: %d, k: %d\n", n, k);
	if(n == k || k == 0)
		return 1;
	else if(binom[n][k] > -1)
		return binom[n][k];
	else
	{
		binom[n][k] = binomial2(n-1, k) + binomial2(n-1, k-1);
		return binom[n][k];
	}
}

int main()
{
	init_cache();
	printf("%d\n", binomial2(8, 3));
	return 0;
}