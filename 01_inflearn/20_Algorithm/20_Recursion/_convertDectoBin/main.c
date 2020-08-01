/*
f(0) = 0
f(1) = 1
f(n) = f(n/2)
     = print(n%2)
*/

// 음이 아닌 정수 n을 이진수로 변환하여 인쇄한다.
#include <stdio.h>

void func(int n)
{
	if(n<2)
	{
		printf("%d", n);
	}
	else
	{
		func(n/2);
		printf("%d", n%2);
	}
}

void main()
{
	func(10); //0b1010
	puts("");
}
