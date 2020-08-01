
/*
 이해 안가면 알고리즘 어플 참고하자

 heap is ...
 1. complete binary tree
 2. heap property
  2-1. max heap property
   parents >= son
  2-2. min heap property
   parents <= son

>how to do heap sort 
데이터를 입력받는대로 1, 2조건을 만족해서 heap을 만든다.
피라미드 정점에 있는 값을 꺼내고, 나머지 부분을 가지고 1, 2조건을 만족하는 heap을 만든다.

이를 모든 값을 꺼낼 때까지 반복하면 우리가 원하는 정렬이 완성된다.

>힙은(because of complete binary tree) 1차원 배열로 표현가능: A[1..n]
*/

#include <stdio.h>

#define parent(x) (x-1) / 2

void swap(int* data1, int* data2);
void printf_array(int* data, int n);
void heapify_max(int* data, int n);

/*
1.heapify(data, size)
2.swap(root, last)
3.heapify(data, size-1)
...
*/
void main()
{
	int data[] = {15, 4, 8, 11, 6, 3, 1, 6, 5};
	int size = sizeof(data)/sizeof(int);
	heapify_max(data, size);
	printf_array(data, size);			//for debug

	for(int i = size - 1; i > 0; i--)	//from index_(size - 1) to index_1 
	{
		swap(data + i, data + 0);		//맨 마지막 원소와 가장 큰 숫자(root)를 스왑
		heapify_max(data, i);			//맨 마지막 원소(가장 큰 원소)를 제외하고 다시 힙을 만든다.
		printf("%d: ", i);
		printf_array(data, size);		//for debug
	}
}

/*
 - 데이터를 하나씩 입력하면서, 힙을 만들어간다.

 * root를 제외한 모든 원소에 대해서 부모와 값을 비교해서 자리 바꾸는 것
 */
void heapify_max(int* data, int n)
{
	for(int i = 1; i < n; i++)			//root(배열의 인덱스가 0인 값)값은 제외하는게 맞으니까 i = 1부터 시작한다
	{
		int child = i;
		while(child > 0)				//looping until getting to root(index 0)
		{
			int root = parent(child);
			if(data[root] < data[child])
			{
				swap(data + root, data + child);
			}
			child = root;
		}
	}
}

void swap(int* data1, int* data2)
{
	int temp = *data1;
	*data1 = *data2;
	*data2 = temp;
}

void printf_array(int* data, int n)
{
	for(int i = 0; i < n; i++)
	{
		printf("%d ", data[i]);
	}
	puts("");
}