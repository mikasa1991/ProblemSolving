/*
*Mathematical induction is a mathematical proof technique. 

It is essentially used to prove that a property P(n) holds for every natural number n, 
i.e. for n = 0, 1, 2, 3, and so on.
The method of induction requires two cases to be proved. 
The first case, called the base case (or, sometimes, the basis), proves that the property holds for the number 0. 
The second case, called the induction step, proves that, if the property holds for one natural number n, 
then it holds for the next natural number n + 1. 
*/

/*
//Greatest Common Divisor
m≥n인 두 양의 정수 m과 n에 대해서 
m이 n의 배수이면 gcd(m, n)=n이고,
그렇지 않으면 gcd(m, n)= gcd(n, m%n)이다.

아래 내용이 이해가 안가는 경우에는, 알고리즘 도감 어플리케이션 참고하기
유클리드 호제법 편

func: gcd(p, q)

f(p, 0) = p
f(p, n) = f(n, p%n)

*/

#include <stdio.h>

int gcd(int p, int q)
{
	if(q == 0)	//base case
	{
		printf("gcd(%d, 0): return %d\n", p, p);
		return p;
	}
	else		//recursive case
	{
		printf("gcd(%d, %d)\n", q, p%q);
		return gcd(q, p%q);
	}
}

void main()
{
	printf("val: %d\n", gcd(10, 7));
}


