#include <stdio.h>
#define MAX 10

//recursion
/*
많은계산이 중복된다.
어떻게 효율적으로 바꿀 수 없을까?
*/
int fib(int n)
{
	printf("%d\n", n);
	if(n == 1 || n == 2) 
		return 1;
	else
		return fib(n-2) + fib(n-1);
}

/*
메모이제이션을 사용하자.
즉, 중간계산결과를 캐싱함으로써 중복계산을 피하자.
*/

int f[MAX+1];

void init_cache()
{
	for(int i = 0; i < MAX + 1; i++)
	{
		f[i] = -1;
	}
}

int fib2(int n)
{
	//printf("%d\n", n);
	if(n == 1 || n == 2)
		return 1;
	else if(f[n] > -1)	//이미 계산된 값이라면,
		return f[n];
	else
	{
		f[n] = fib2(n-2) + fib2(n-1);
		return f[n];
	}
}

int main()
{
	init_cache();
	//printf("%d\n", fib(10));
	printf("%d\n", fib2(10));
	return 0;
}