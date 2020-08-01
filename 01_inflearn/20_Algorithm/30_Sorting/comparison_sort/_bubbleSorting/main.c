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
비교횟수 n-1번; 1번째부터 n번째까지 정렬을 해서 그 중 최댓값을 n번째로 보낸다.
비교횟수 n-2번; 1번째부터 n-1번째까지 정렬을 해서 그 중 최댓값을 n-1번째로 보낸다.
...
비교횟수   1번; 1부터 2번째까지 정렬을 해서 그 중 최댓값을 2번째로 보낸다.

시간복잡도는 n-1 + n-2 + ... + 1
*/
void bubbleSorting(int* data, int cnt)
{
	for (int loop = 0; loop < cnt - 1; loop++)
	{
		printf("loop: %d\n", loop);
		for (int i = 0; i < cnt - 1 - loop; i++)
		{
			printf("i: %d\n", i);
			if (data[i] > data[i + 1])
			{
				swap((data+i), (data+i+1));
			}
		}
		print_array(data, cnt);	//print in processing
	}
}

void main()
{
	int data[5] = {5, 4, 3, 2, 1};
	int size = sizeof(data)/sizeof(int);
	print_array(data, size);
	bubbleSorting(data, size);
	print_array(data, size);
}