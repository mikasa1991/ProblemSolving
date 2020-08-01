#include <stdio.h>
#define MAX 10

//recursion
/*
재귀함수를 이용해 탑다운방식으로 
문제풀이를 접근하는 경우, 많은계산이 중복된다.
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
방법2. 바텀업 방식으로 접근하자.
*/

int f[MAX+1];

int fib2(int n)
{
	f[1] = f[2] = 1;
	for(int i = 3; i <= n; i++)
	{
		f[i] = f[i-1] + f[i-2];
	}
	return f[n];
}

int main()
{
	printf("%d\n", fib2(10));
	return 0;
}