/***********************************************************/
// [2-3] Tree
/***********************************************************/

/***********************************************************/
// [2-3-1] Heap 
/***********************************************************/

#if 01

/***********************************************************/
// [2-3-1.1] Heap 자료
/***********************************************************/

#if 01

#include <stdio.h>

#define NUM_DATA	(8)
#define MAX_DATA	(NUM_DATA)
#define MAX_HEAP	(MAX_DATA+1)
#define LAST_NODE	(MAX_DATA)

int heap[MAX_HEAP];
int lastnode = 0;

int exam[NUM_DATA+1] = {0,4,8,2,7,1,3,6,5}; // 0번 index 공간 무시

#define PRINT_TREE {int j;printf("( ");	for(j = 1;j <= LAST_NODE; j++){printf("%3d ",heap[j]);}printf(")\n");}

// 이제부터 설계되는 모든 함수는 이 부분에 선언을 추가한다
int Heap_Push_Minheap(int *heap, int size, int *lastnode, int d);
int Heap_Pop_Minheap(int *heap, int *lastnode, int *d);
int Heap_Push_Maxheap(int *heap, int size, int *lastnode, int d);
int Heap_Pop_Maxheap(int *heap, int *lastnode, int *d);
void Heap_Sort(int *data,int cnt,int order);
#endif

/***********************************************************/
// [2-3-1.2] Heap Push (Min Heap)
/***********************************************************/

/*
완전 이진 트리
인덱스를 1부터 시작하면,
어떤 자식이든 2로 나누면 부모를 찾는다.
*/

void swap(int *a, int *b)
{
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

#if 01
/*
int Heap_Push_Minheap(int *heap, int size, int *lastnode, int d)
{
	int n, p, temp;
	if(*lastnode == size) return 0;
	heap[++(*lastnode)] = d;
	n = *lastnode; 
	p = n / 2;

	while(p > 0)
	{
		if(heap[n] < heap[p])
		{
			temp = heap[n];
			heap[n] = heap[p];
			heap[p] = temp;
			n = p; 
			p = n / 2;
		}
		else break;
	}

	return 1;
}
*/

int Heap_Push_Minheap(int *heap, int size, int *lastnode, int d)
{
	int n_idx, p_idx;
	if(*lastnode == size) return 0;		//fail
	heap[++(*lastnode)] = d;			//끝에 노드를 추가(완전이진트리)

	n_idx = *lastnode;					//현재 노드의 인덱스
	p_idx = n_idx / 2;						//그 노드 부모의 인덱스

	while(p_idx > 0)					//부모노드가 존재하면,
	{
		if(heap[n_idx] < heap[p_idx])	//부모노드보다 작다면,
		{
			swap(&heap[n_idx], &heap[p_idx]);
			n_idx = p_idx;
			p_idx = n_idx / 2;
		}
		else break;
	}
	return 1;	//success
}
#endif

#if 0

int main(void)
{
	printf("Heap Push Test (Minheap)\n");

	for(int i = 1; i <= NUM_DATA; i++)
	{
		printf("[%d] Heap_Push_Minheap(%d) => %d",
			i, exam[i], Heap_Push_Minheap(heap, MAX_DATA, &lastnode, exam[i]));
		
		PRINT_TREE;
	}
	printf("[9] Heap_Push_Minheap(9) => %d\n", Heap_Push_Minheap(heap, MAX_DATA, &lastnode, 9));
	return 0;
}
#endif

/***********************************************************/
// [2-3-1.3] Heap Pop (Min Heap)
/***********************************************************/

#if 01
int Heap_Pop_Minheap(int *heap, int *lastnode, int *d)
{
	int n,c,lc,rc,temp;
	if(*lastnode == 0) return 0;

	*d = heap[1];
	heap[1] = heap[(*lastnode)--];	//last에 위치한 노드를 root로 옮긴다

	n  = 1; 
	lc = 2; 
	rc = 3;

	while(lc <= *lastnode)
	{
		if(*lastnode == lc) c = lc;	//오른쪽 자식이 없을 때,
		else c = (heap[lc] < heap[rc]) ? (lc) : (rc);

		if(heap[c] < heap[n])
		{
			swap(&heap[c], &heap[n]);
			n = c; 
			lc = n * 2; 
			rc = lc + 1;
		}
		else break;
	}
	return 1;
}
#endif

#if 0

int main(void)
{
	int i, ret;
	printf("Heap Pop Test (Minheap)\n");

	for(i = 1; i <= NUM_DATA; i++)
	{
		printf("[%d] Heap_Push_Minheap(%d) => %d",
			i, exam[i], Heap_Push_Minheap(heap,MAX_DATA,&lastnode,exam[i]));
		PRINT_TREE;
	}

	for(i =1; i <= NUM_DATA; i++)
	{
		printf("[%d] Heap_Pop_Minheap() => %d - ", i, Heap_Pop_Minheap(heap, &lastnode, &ret));
		printf("%d\n",ret);
	}
	printf("[9] Heap_Pop_Minheap() => %d\n", Heap_Pop_Minheap(heap, &lastnode, &ret));
	return 0;
}
#endif

/***********************************************************/

// [2-3-1.4] Heap Push (Max Heap)

/***********************************************************/

#if 01
int Heap_Push_Maxheap(int *heap, int size, int *lastnode, int d)
{
	int n,p,temp;

	if(*lastnode == size) return 0;
	heap[++(*lastnode)] = d;
	n = *lastnode; 
	p = n/2;

	while(p>0)
	{
		if(heap[n] > heap[p])
		{
			temp = heap[n];
			heap[n] = heap[p];
			heap[p] = temp;
			n = p; 
			p = n / 2;
		}
		else break;
	}
	return 1;
}
#endif

#if 0

int main(void)
{
	int i;
	printf("Heap Push Test (Maxheap)\n");

	for(i=1;i<=NUM_DATA;i++)
	{
		printf("[%d] Heap_Push_Maxheap(%d) => %d",
			i,exam[i],Heap_Push_Maxheap(heap,MAX_DATA,&lastnode,exam[i]));
		PRINT_TREE;
	}
	printf("[9] Heap_Push_Maxheap(9) => %d\n",Heap_Push_Maxheap(heap,MAX_DATA,&lastnode,9));
	return 0;
}

#endif

/***********************************************************/
// [2-3-1.5] Heap Pop (Max Heap)
/***********************************************************/

#if 01

int Heap_Pop_Maxheap(int *heap, int *lastnode, int *d)
{
	int n,c,lc,rc,temp;

	if(*lastnode == 0) return 0;

	*d = heap[1];
	heap[1] = heap[(*lastnode)--];

	n = 1; lc = 2; rc = 3;

	while(lc<=*lastnode)
	{
		if(*lastnode == lc) c = lc;
		else c = (heap[lc]>heap[rc])?(lc):(rc);

		if(heap[c]>heap[n])
		{
			temp = heap[c];
			heap[c] = heap[n];
			heap[n] = temp;
			n = c; lc = n*2; rc = lc+1;
		}
		else break;
	}
	return 1;
}
#endif

#if 01

int main(void)

{
	int i,ret;
	printf("Heap Pop Test (Maxheap)\n");

	for(i=1;i<=NUM_DATA;i++)
	{
		printf("[%d] Heap_Push_Maxheap(%d) => %d",
			i,exam[i],Heap_Push_Maxheap(heap,MAX_DATA,&lastnode,exam[i]));
		PRINT_TREE;
	}

	for(i=1;i<=NUM_DATA;i++)
	{
		printf("[%d] Heap_Pop_Maxheap() => %d - ",i,Heap_Pop_Maxheap(heap,&lastnode,&ret));
		printf("%d\n",ret);
	}
	printf("[9] Heap_Pop_Maxheap() => %d\n",Heap_Pop_Maxheap(heap,&lastnode,&ret));
	return 0;
}
#endif