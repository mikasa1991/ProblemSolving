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
비교횟수 n-1: n개 중에서 최솟값을 찾아서 1번째에 위치
비교횟수 n-2: n-1개 중에서 최솟값을 찾아서 2번째에 위치
...
비교횟수 1  :2개 중에서 최솟값을 찾아서 n-1번째에 위치

시간복잡도는 n-1 + ... + 1
*/

void selectSorting(int* data, int cnt)
{
	int min_index = 0;

	for(int loop = 0; loop < cnt - 1; loop++)
	{
		min_index = loop;

		//for(int i = loop + 1; i < cnt - 1; i++)
		for(int i = loop + 1; i < cnt; i++)
		{
			if(data[min_index] > data[i])
			{
				min_index = i;
			}		
		}
		swap((data+loop), (data+min_index));
		print_array(data, cnt);	//print in processing 
	}
}

void main()
{
	int data[5] = {5, 4, 3, 2, 1};
	int size = sizeof(data)/sizeof(int);
	print_array(data, size);
	selectSorting(data, size);
	print_array(data, size);
}