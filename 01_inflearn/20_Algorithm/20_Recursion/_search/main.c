/*
data[0]에서 data[n-1] 사이에서 target을 검색한다.
존재하면 배열 인덱스, 존재하지 않으면 -1을 반환한다.

f(n) if it be found, return n
     otherwise, f(n-1)
f(0) return
*/

#include <stdio.h>

#if 0
int func(int* data, int n, int target)
{
	if(n == 0)
	{
		return -1; //error
	}
	else
	{
		if(target == data[n-1])
		{
			return n-1;
		}
		else
		{
			return func(data, n-1, target);
		}
	}
}
#endif

//순차탐색
int func2(int* data, int begin, int end, int target)
{
	if(begin > end)
	{
		return -1;					//base case_fail
	}
	else
	{
		if(target == data[begin])	//base case_success
			return begin;
		else						//recursive case 
			return func2(data, begin+1, end, target);
	}
}

void main()
{
	int data[] = {1,2,3,4,5,6};
	int data_size = sizeof(data)/sizeof(int);

	//int index = func(data, data_size, 4);
	int index = func2(data, 0, data_size-1, 4);

	printf("data[%d]: %d\n", index, data[index]);
}