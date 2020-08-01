/*
*Mathematical induction is a mathematical proof technique. 

It is essentially used to prove that a property P(n) holds for every natural number n, 
i.e. for n = 0, 1, 2, 3, and so on.
The method of induction requires two cases to be proved. 
The first case, called the base case (or, sometimes, the basis), proves that the property holds for the number 0. 
The second case, called the induction step, proves that, if the property holds for one natural number n, 
then it holds for the next natural number n + 1. 
*/

//Q)solve the problem that is sum from 1 to n
/*
정리: func(int n)은 음이 아닌 정수 n에 대해서 0에서 n까지의 합을 올바로 계산한다.
증명:
1. n=0인 경우: n=0인 경우 0을 반환한다. 올바르다.
2. 임의의 양의 정수 k에 대해서 n<k인 경우 0에서 n까지의 합을 올바르게 계산하여 반환한다
고 가정하자.
3. n=k인 경우: func은 먼저 func(k-1) 호출하는데 2번의 가정에 의해서 0에서 k-1까지의 합이
올바로 계산되어 반환된다. 메서드 func은 그 값에 n을 더해서 반환하므로 결국 0에서 k까지
의 합을 올바로 계산하여 반환한다.
*/
#include <stdio.h>

int func(int n)
{
	if(n == 0)	//base case
	{
		printf("func(0): return 0\n");
		return 0;
	}
	else		//recursive case
	{
		printf("func(%d): %d + func(%d)\n", n, n, n-1);
		return n + func(n-1);
	}
}

void main()
{
	printf("sum: %d\n", func(4));
}
