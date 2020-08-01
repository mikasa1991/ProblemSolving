#include <stdio.h>

#define parent(x) (x-1) / 2

int heap_size = 0;

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

/*
값을 트리의 맨 끝에 삽입한 후, 기존의 데이터들과 비교해서 맥스 힙형태로 만든다
*/
void max_heap_insert(int* data, int key)
{
	heap_size++;
	data[heap_size-1] = key;
	
	int i = heap_size-1;
	while(i > 0 && data[parent(i)] < data[i])	//if (not root) && (max heap property)
	{
		swap(data + parent(i), data + i);
		i = parent(i);
	}
}

/*
기존의 데이터들, 비교해서 맥스 힙형태로 만든다
*/
void heapify_max(int* data, int n)
{
	for(int i = 1; i < n; i++)			//root exclude; the index of 0 is root
	{
		int child = i;
		while(child > 0)				//looping until getting to root
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

/*
 루트(data[0])를 반환하기 위해서, 따로 저장하고, 루트 위치에 힙에 맨 끝에 위치하는 값으로 쓴다
 힙 사이즈를 하나 줄인다
 heapify_max 함수를 통해서 힙으로 만든다
 루트를 반환한다
*/
int heap_extract_max(int* data)
{
	if(heap_size < 1)
	{
		puts("heap underflow!");
		return -1;
	}
	int max = data[0];
	swap(data + 0, data + heap_size - 1);
	heap_size--;
	heapify_max(data, heap_size);

	return max;
}

void main()
{
	int data[10] = {0, };

	//insert
	max_heap_insert(data, 15);
	printf_array(data, heap_size);	//15
	max_heap_insert(data, 4);
	printf_array(data, heap_size);  //15 4
	max_heap_insert(data, 8);
	printf_array(data, heap_size);  //15 4 8
	max_heap_insert(data, 11);
	printf_array(data, heap_size);  //15 11 8 4

	//extract
	printf("max %d\n", heap_extract_max(data));
	printf_array(data, heap_size);  //11 8 4
	printf("max %d\n", heap_extract_max(data));
	printf_array(data, heap_size);  //8 4
	printf("max %d\n", heap_extract_max(data));
	printf_array(data, heap_size);  //4
	printf("max %d\n", heap_extract_max(data));
	printf_array(data, heap_size);  //nothing
	printf("max %d\n", heap_extract_max(data));
	printf_array(data, heap_size);  //nothing
}