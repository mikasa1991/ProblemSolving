#include <stdio.h>

void swap(int* d1, int* d2)
{
	int temp = 0;
	temp = *d1;
	*d1 = *d2;
	*d2 = temp;
}

void print_array(int* data, int n)
{
	for(int i = 0; i < n; i++)
	{
		printf("%d ", data[i]);
	}
	puts("");
}

/*
1번째까지 정렬이 완료됐음
비교횟수 1  : 2번째항을 앞의 항과 정렬이 유지되도록 삽입
비교횟수 2  : 3번째항을 앞의 항들과 정렬이 유지되도록 삽입
...
비교횟수 n-1: n번째항을 앞의 항들과 정렬이 유지되도록 삽입

시간복잡도는 n-1 + n-2 + ... + 1
*/

void insertSorting(int* data, int cnt)
{
	for(int loop = 1; loop < cnt; loop++)
	{
		for(int i = loop; i > 0; i--)
		{
			if(data[i-1] > data[i])
			{
				swap(data + i - 1, data + i);
			}
			else break;
		}
		print_array(data, cnt);	//print in processing
	}
}

void main()
{
	int data[5] = {5, 4, 3, 2, 1};
	int size = sizeof(data)/sizeof(int);
	print_array(data, size);
	insertSorting(data, size);
	print_array(data, size);
}