//http://www.cs.miami.edu/home/burt/learning/Csc517.091/workbook/countingsort.html

#include <stdio.h>

#define MAX 100

int g_len_A = 0;

void print_index(int k)
{
    for(int i = 0; i <= k; i++)
    {
        printf("%2d ", i);
    }
    puts("");
}

void print_array(int* data, int n)
{
    for(int i = 0; i < n; i++)
    {
        printf("%2d ", data[i]);
    }
    puts("");
}

/*
counting sort(stable sort)

최댓값 M을 기준으로 M개의 버킷이 필요하다

n: 자료수
k: 최댓값 크기

n번: 자료를 모두 탐색하면서 카운팅을 한다
k번: 카운팅한 것을 탐색하면서 배치를 시킨다 
*/
void countingSort(int* A, int* B, int k)
{
    int C[MAX];

    //initializing the C_array; interval [0, k]
    for(int i = 0; i<= k; i++)
    {
        C[i] = 0;
    }

    //버킷에 몇 개의 자료가 들어가는지 구한다
    for(int i = 0; i< g_len_A; i++)
    {
        C[A[i]]++;
    }

    //위에서 구한 것을 토대로, 버킷에 자료의 누적수로 덮어쓴다
    for(int i = 1; i <= k; i++)
    {
        C[i] = C[i] + C[i-1];
    }

    //for debugging
    printf("i_array ");
    print_index(k);
    printf("C_array ");
    print_array(C, k+1);

    for(int i = g_len_A - 1; i >= 0; i--)
    {
        //sorting
        B[--C[A[i]]] = A[i];

        //for debugging
        printf("A_array ");
        print_array(A, g_len_A);
        printf("i_array ");
        print_index(k);
        printf("C_array ");
        print_array(C, k+1);
        printf("B_array ");
        print_array(B, k+1);
    }
}

void main()
{
    int A[] = { 15, 10, 9, 10, 7};
    int B[MAX] = {0, };
    int m = 0;

    g_len_A = sizeof(A)/sizeof(int);

    //looking for the max of A_array
    for(int i = 0; i < g_len_A; i++)
    {
        if(m < A[i]) m = A[i];
    }

    printf("A_array ");
    print_array(A, g_len_A);
    countingSort(A, B, m);
}