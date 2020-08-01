//https://www.youtube.com/watch?v=7BDzle2n47c


/*
0: 제출용
1: 테스트용
*/
#define MODE 1

#include <stdio.h>
#include <time.h>

void print_array(int* data, int n);

void swap(int* d1, int* d2)
{
	int temp = 0;
	temp = *d1;
	*d1 = *d2;
	*d2 = temp;
}

//s가 e보다 커지는 게...
int partition(int* data, int start, int end)
{
	int s = start;
	int e = end;
	int p = (s+e) / 2;	//p means pivot

	//printf("before partition: s: %d, e: %d, p: %d\n", s, e, p);
	while(s < e)
	{
		while(data[s] < data[p]) s++;
		while(data[p] < data[e]) e--;

		/*
		if(s < e) 로 조건문을 쓰는 경우에 왜 segmentation fault(core dumped)가 발생하는가?
		위처럼 조건문을 수정하면, s, e가 같은 경우에 base case에 도달하지 못하기 때문이다.
		*/
		if(s <= e)
		{
			swap((data + s), (data + e));
			s++;
			e--;
		}
	}
	//print_array(data, e + 1);
	//printf("after partition: s: %d, e: %d, p: %d\n", s, e, p);
	return s;
}

/*
f(s, e): 인덱스 s에서 e까지 정렬한다

f(s, e) =
+ sorting
+ f(s  , q)
+ f(q+1, e)

cf. base case가 따로 없기 때문에, 
*/
void quickSort(int* data, int s, int e)
{
	if(s < e)
	{
		//puts("quickSort call");
		int part2 = partition(data, s, e);
	
		//recursive case
		if(s < part2 - 1) quickSort(data, s, part2 - 1);
		if(part2 < e) 	  quickSort(data, part2, e);
	}

	//base case
}

void print_array(int* data, int n)
{
	for(int i = 0; i < n; i++)
	{
		printf("%d ", data[i]);
	}
	puts("");
}

int main()
{
#if MODE
	float gap = 0;
	time_t startTime = 0;
	time_t endTime = 0;
	startTime = clock();	//측정시작 시각
#endif

	int data[5] = {5, 4, 3, 2, 1};
	int size = sizeof(data)/sizeof(int);
	print_array(data, size);
	quickSort(data, 0, size - 1);
	print_array(data, size);

#if MODE
	endTime = clock();		//측정완료 시각
	gap = (float)(endTime - startTime)/(CLOCKS_PER_SEC);
	printf("%fsec\n", gap);
#endif

	return 0;
}