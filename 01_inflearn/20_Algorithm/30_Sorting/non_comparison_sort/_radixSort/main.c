//https://m.blog.naver.com/PostView.nhn?blogId=dntkrl79&logNo=220730180796&proxyReferer=https%3A%2F%2Fwww.google.com%2F

#include <stdio.h>

#define MAX 50

void print_array(int* A, int n)
{
	for(int i = 0; i < n; i++)
	{
		printf("%d ", A[i]);
	}
	puts("");
}

/*
radix sort(stable sort)

10진수를 기준으로 10개의 버킷이 필요하다; 범위는 0 ~ 9
카드를 일의 자리수별로 버킷에 모두 넣습니다. 
그런 다음 0번 버킷부터 순서대로 다시 꺼냅니다.

꺼낸 카드를 꺼냈던 순서대로 십의 자리수별로 버킷에 모두 넣습니다. 
다시 0 번 버킷부터 순서대로 꺼냅니다. 

이 작업을 가장 큰 수의 자리수만큼 반복하면 어느새 정렬이 완료되게 됩니다.

[*] 그런데 이 방식으로 코딩하려면 메모리 공간이 [자료수 * 10개]가 더 필요합니다. [*]
이 메모리 공간을 줄이기 위해서, 
자료를 직접 버킷에 넣지 않고, 버킷의 몇 개의 자료가 들어가는지 누적수를 구합니다.

n: 자료수
k: k진법수
d: 자릿수

n번: 자료를 모두 탐색하면서 카운팅을 한다
k번: 카운팅 한것을 탐색하면서 배치를 시킨다
d번: 자릿수만큼 n+k 번을 수행해야한다
*/
void radixSort(int* A, int n)
{
	int i = 0;
	int B[MAX] = {0, };
	int m = 0; //max
	int exp = 1;

	//looking for the max of data_array
	for(int i = 0; i < n; i++)
	{
		if(m < A[i]) m = A[i];
	}

	while( m/exp > 0 )	//가장 큰 수의 자릿수만큼 반복문을 돌려고,
	{
		int bucket[10] = {0, };

		//counting
		/*
		 A[i] / exp % 10 ???
		 
		 if, exp == 1,
		 524 / 1 % 10 = 4
		 435 / 1 % 10 = 5
		 ...

		 if, exp == 10,
		 524 / 10 % 10 = 52 % 10 = 2
		 435 / 10 % 10 = 43 % 10 = 3
		 ... 
		 */

		//버킷에 몇 개의 자료가 들어가는지 구한다
		//따라서 데이터의 앞에서 하든 뒤에서 하든 상관없다
		for(i = 0; i < n; i++)
		//for(i = n-1; i >= 0; i--)
		{
			bucket[A[i] / exp % 10]++;
		}

		//위에서 구한 것을 토대로, 버킷에 자료의 누적수로 덮어쓴다
		for(i = 1; i < 10; i++)
		{
			bucket[i] = bucket[i] + bucket[i-1];
		}

		/*
		(190224)
		Q. 정렬하고자 하는 데이터의 "맨 뒤에서부터" 정렬을 시작하는 이유는?
		핵심은 stable sort를 유지하기 위해서다.
		stable sort란 입력에 동일한 값이 있을때 입력에 먼저 나오는 값이 출력에서도 먼저 나온다.

		B[--bucket[A[i] / exp % 10]] = A[i];
        --로 역순으로 B라는 배열에 자료를 집어넣기 때문에,
		버킷에 들어있는 자료를 뒤에서부터 써줘야
		같은 버킷 안의 값은 기존의 순서를 유지한다. 
		*/
		
		for(i = n-1; i >= 0; i--)	// O 정렬하고자 하는 데이터의 "맨 뒤에서부터" 정렬을 시작한다
		//for(i = 0; i < n; i++)	// X
		{
			/*
			(190224)
			Q. --bucket[A[i] / exp % 10]에서 --가 앞에 붙은 이유는?
			>배열의 인덱스가 0부터 시작하니까 0부터 값이 저장되도록 하기 위함이다
			*/
			B[--bucket[A[i] / exp % 10]] = A[i];
		}

		//copy B matrix -> A matrix
		for(i = 0; i < n; i++)
		{
			A[i] = B[i];
			printf("%d ", A[i]);
		}
		puts("");
		exp = exp * 10;
	}
	printf("\nPASS:   ");
	print_array(A, n);
}

void main()
{
	int arr[] = {524, 435, 690, 422, 654};
	int n = sizeof(arr)/sizeof(int);

	printf("\nINPUT:  ");
	print_array(arr, n);

	radixSort(arr, n);

	printf("\nSORTED: ");
	print_array(arr, n);
	puts("");
}