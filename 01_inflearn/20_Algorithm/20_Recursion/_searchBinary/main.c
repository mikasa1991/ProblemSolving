/*
 *오름차순이나 내림차순으로 정렬된 경우에 이진탐색이 의미가 있다.
 */

#include <stdio.h>

int func2(int* data, int target, int begin, int end)
{
	if(begin > end)	//base case_fail
	{
		return -1;
	}
	else
	{
		int middle = (begin+end) / 2;
		if(data[middle] == target)
		{
			return middle;
		}
		else if(data[middle] > target)
		{
			return func2(data, target, begin, middle - 1);
		}
		else if(data[middle] < target)
		{
			return func2(data, target, middle + 1, end);
		}
	}
}

void main()
{
	int data[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
	int data_size = sizeof(data)/sizeof(int);

	int index = func2(data, 4, 0, data_size - 1);
	printf("data[%d]: %d\n", index, data[index]);
}