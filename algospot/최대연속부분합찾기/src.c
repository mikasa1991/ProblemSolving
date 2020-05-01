//https://www.algospot.com/judge/problem/read/MAXSUM
#pragma warning(disable: 4996)
#pragma warning(disable: 6031)
#define DEBUG
#define MAX_ARRAY_SIZE ((int)1e5 + 1)

#ifdef DEBUG
#define dprintf printf
#else
#endif
#include <stdio.h>
#include <assert.h>

int GetMaxsum(int* pArray, int nArraySize);
int GetMaxsum2(int* pArray, int lo, int hi);

int main()
{
#ifdef DEBUG
    freopen("input.txt", "r", stdin);
#endif
    int nTcSize;
    int nArraySize;
    int naNum[MAX_ARRAY_SIZE];
    scanf("%d", &nTcSize);
    for (int nTestIdx = 0; nTestIdx < nTcSize; nTestIdx++)
    {
        //input
        scanf("%d", &nArraySize);
        for (int nArrayIdx = 0; nArrayIdx < nArraySize; nArrayIdx++)
        {
            scanf("%d", &naNum[nArrayIdx]);
        }
        printf("%d\n", GetMaxsum2(naNum, 0, nArraySize-1));
    }
    return 0;
}

//(N^2)
int GetMaxsum(int* pArray, int nArraySize)
{
    int nSum;
    int nMax = pArray[0];
    for (int i = 0; i < nArraySize; i++)
    {
        nSum = pArray[i];
        for (int j = i + 1; j < nArraySize; j++)
        {
            nSum = nSum + pArray[j];
            if (nSum > nMax)
            {
                nMax = nSum;
            }
        }
    }
    return nMax;
}

int max(int a, int b)
{
    if (a > b)
    {
        return a;
    }
    return b;
}

/*
분할정복기법을 이용하자
절반으로 나누자; 왼쪽 배열과 오른쪽 배열
다음의 2가지 경우가 존재한다.

1. 최대연속부분합이 왼쪽과 오른쪽 배열에 걸쳐 있다.
 -> 중간지점에서 왼쪽 방향으로 최대연속부분합 + 중간지점에서 오른쪽 방향으로 최대연속부분합
2. 최대연속부분합이 왼쪽 또는 오른쪽에 있다.
 -> 왼쪽배열의 최대연속부분합 vs 오른쪽배열의 최대연속부분합 중에 큰 값을 찾는다
*/
//(N logN)
int GetMaxsum2(int* pArray, int lo, int hi)
{
    if (lo == hi) return pArray[lo];
    int mid = (lo + hi) / 2;
    int left = -100;
    int right = -100;
    int sum = 0;

    for (int i = mid; i >= lo; i--)
    {
        sum = sum + pArray[i];
        left = max(left, sum);
    } 

    sum = 0;

    for (int j = mid + 1; j <= hi; j++)
    {
        sum = sum + pArray[j];
        right = max(right, sum);
    }
    int single = max(GetMaxsum2(pArray, lo, mid), GetMaxsum2(pArray, mid+1, hi));

    return max(left+right, single);
}