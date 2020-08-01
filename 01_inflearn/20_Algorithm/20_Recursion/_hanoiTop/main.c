/*
 * 아래 관계식이 이해가 안가면, 알고리즘 도감 어플리케이션의 하노이탑 부분 참고하기
 * f(1) = 1
 * f(n) = f(n-1) + 1 + f(n-1)
 */

#include <stdio.h>

int func(int cnt)
{
	if(cnt == 1)	//base case
	{
		return 1;
	}
	else			//recursive case
	{
		return 1 + func(cnt-1) * 2;
	}
}

void main()
{
	printf("movement: %d\n", func(7));
}
