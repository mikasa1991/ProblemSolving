//https://www.youtube.com/watch?v=UFn0Zr21sZw&feature=youtu.be
//http://www.jungol.co.kr/bbs/board.php?bo_table=pbank&wr_id=2465
#pragma warning(disable: 4996)
#pragma warning(disable: 6031)

#include <stdio.h>
#include <assert.h>

const int MAX_NUM = (int)1e5 + 1;
int N;
int A[MAX_NUM];
int B[MAX_NUM]; //temp
long long Ans;

void MergeSort(int s, int e)
{
    if (s >= e) return;
    
    //divide
    int m = (s + e) / 2;
    MergeSort(s, m);
    MergeSort(m+1, e);
    
    //merge
    int i = s;
    int j = m + 1;
    int k = s;
    
    while (i <= m && j <= e)
    {
        if (A[i] <= A[j])
        {
            B[k++] = A[i++];
        }
        else
        {
            B[k++] = A[j++];
            Ans = Ans + (long long)m + 1 - i;
        }
    }
    while (i <= m) B[k++] = A[i++];
    while (j <= e) B[k++] = A[j++];
    
    for (int i = s; i <= e; i++)
    {
        A[i] = B[i];
    }
}

int main()
{
    freopen("input.txt", "r", stdin);
    
    int tc;
    scanf("%d", &tc);
    while (tc--)
    {
        //init
        Ans = 0;
        scanf("%d", &N);
        for (int i = 0; i < N; i++)
        {
            scanf("%d", &A[i]);
        }

        //solve
        MergeSort(0, N-1);
        printf("%lld\n", Ans);
    }
    return 0;
}