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
//x is coef, n is expo
x^0 = 1
x^n = n * x^(n-1)
*/

#include <stdio.h>

int func(int coef, int expo)
{
	if(expo == 0)	//base case
	{
		printf("func(0): return 1\n");
		return 1;
	}
	else		//recursive case
	{
		printf("func(coef, %d): %d * func(coef, %d)\n", expo, expo, expo-1);
		return coef * func(coef, expo-1);
	}
}

void main()
{
	printf("val: %d\n", func(2, 10)); //2^10 = 1024
}


