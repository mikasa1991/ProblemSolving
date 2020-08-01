#include <stdio.h>

void print_array(int* data, int n)
{
	for(int i = 0; i < n; i++)
	{
		printf("%d ", data[i]);
	}
	puts("");
}

void merge(int* data, int s, int q, int e)
{
	int i = s;
	int j = q + 1;
	int k = s;
	int tmp[e+1];	//e + 1 means the size of array
	printf("left side: %d ~ %d, right side: %d ~ %d\n", i, q, j, e);
	/*
	  i is the first index of partition left side
	  j is the first index of partition right side
	  q is the last index of partition left side
	  e is the last index of partition right side
	  k is for being fill with tmp array
	 */

	while(i <= q && j <= e)
	{
		if(data[i] <= data[j]) 
			tmp[k++] = data[i++];
		else //data[i] > data[j]
			tmp[k++] = data[j++];
	}

	//두 개의 와일 문 중에 하나만 실행된다.
	//왜냐하면 left side 또는 right side 중의 한 파트에 값이 남아있기 때문임
	while(i <= q) tmp[k++] = data[i++];
	while(j <= e) tmp[k++] = data[j++];
	
	for(int i = s; i <= e; i++)
	{
		data[i] = tmp[i];
	}
	print_array(data, e+1);
}

/*
시간복잡도는 mergeSort.png를 참고하세요

f(s, e): 인덱스 s에서 e까지 정렬한다

f(s, e) =
+ f(s  , q)
+ f(q+1, e)
+ merge(sorting)

cf. base case가 따로 없기 때문에, 
*/
void mergeSort(int* data, int s, int e)
{
	int q = 0;

	if(s < e)				//if s == e, it is same with only one. so you don't have to divide. 
	{
		q = (s + e) / 2;	//q is the last index of partition left side

		//recursive case
		mergeSort(data, s, q);		//divide
		mergeSort(data, q+1, e);	//divide

		//base case
		merge(data, s, q, e);		//conquer, merge
	}
	//base case
}

void main()
{
	int data[5] = {5, 4, 3, 2, 1};
	int size = sizeof(data)/sizeof(int);
	print_array(data, size);
	mergeSort(data, 0, size - 1);
	print_array(data, size);
}