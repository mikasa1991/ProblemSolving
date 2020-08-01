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
f0 = 0
f1 = 1
fn = f
*/

//0 1 1 2 3 5 8 13 21 34 55

#include <stdio.h>

int func(int n)
{
	if(n < 2)	//base case
	{
		printf("func(%d): return %d\n", n, n);
		return n;
	}
	else		//recursive case
	{
		printf("func(%d): func(%d) + func(%d)\n", n, n-1, n-2);
		return func(n-1) + func(n-2);
	}
}

void main()
{
	printf("val: %d\n", func(10)); //55
}


