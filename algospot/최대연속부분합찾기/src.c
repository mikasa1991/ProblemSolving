//https://www.algospot.com/judge/problem/read/MAXSUM

#include <stdio.h>
#pragma warning(disable: 4996)
#pragma warning(disable: 6031)
//#define DEBUG
#define MAX_CNT ((int)1e5 + 1)
#define MIN_VAL (-100)

#ifdef DEBUG
#define D_Printf printf
#else
#define D_Printf
#endif  //(DEBUG)

void Input(int* naNum, int nCnt);
int Solve(int* naNum, int nCnt);
int GetMax(int a, int b);
int GetMaxBothSide(int* naNum, int nMiddle, int nFirst, int nLast);
int Solve2(int* naNum, int nFirst, int nLast);
int Solve3(int* naNum, int nCnt);

#include <stdio.h>
#include <assert.h>

int main()
{
#ifdef DEBUG
    freopen("input.txt", "r", stdin);
#endif
    int naNum[MAX_CNT];
    int nTC;
    scanf("%d", &nTC);
    D_Printf("nTCCnt = %d\n", nTC);

    for (int i = 0; i < nTC; i++)
    {
        int nCnt;
        scanf("%d", &nCnt);
        Input(naNum, nCnt);
        //printf("%d", Solve(naNum, nCnt));       //N^2
        //printf("%d", Solve2(naNum, 0, nCnt-1)); //N*logN
        printf("%d", Solve3(naNum, nCnt));        //N*logN
        D_Printf("\n");
    }
    return 0;
}

void Input(int* naNum, int nCnt)
{
    for (int i = 0; i < nCnt; i++)
    {
        scanf("%d", &naNum[i]);
        D_Printf("%d ", naNum[i]);
    }
    puts("");
}

// N^2
// 무식하게 풀기
int Solve(int* naNum, int nCnt)
{
    int nMax = MIN_VAL;
    for (int i = 0; i < nCnt; i++)
    {
        int nSum = 0;
        for (int j = i; j < nCnt; j++)
        {
            nSum = nSum + naNum[j];
            if (nMax < nSum)
            {
                nMax = nSum;
            }
            D_Printf("nSum = %d; from %d to %d\n", nSum, i, j);
        }
    }
    D_Printf("nMax = %d\n", nMax);
    return nMax;
}

// N * logN
// 분할정복법
// 둘 이상의 부분문제로 나눈 뒤 각 문제에 대한 답을 재귀호출을 이용해 계산한다.
// 각 부분문제의 답으로부터 전체 문제의 답을 계산한다.

/*
분할정복법을 이용하자
// 나는 분할정복법을 아예 떠올리지 못했다. 왜냐하면 분할정복법을 제대로 이해하지 못하고 있었다.

절반으로 나누자; 왼쪽 배열과 오른쪽 배열
최대연속부분합은 왼쪽 배열에 존재하거나 오른쪽 배열에 존재하거나 두 배열에 걸쳐있거나이다.
이 3가지 case의 최대값이 최대연속부분합이 된다.

Q) 최대연속부분합이 두 배열에 걸쳐있는 경우의 최대연속부분합은 어떻게 구해야할까?
A) 중간지점에서 왼쪽 방향으로 최대연속부분합 + 중간지점에서 오른쪽 방향으로 최대연속부분합
*/

int GetMax(int a, int b)
{
    if (a > b)
    {
        return a;
    }
    return b;
}

//최대연속부분합이 두 배열에 걸쳐있는 경우
int GetMaxBothSide(int* naNum, int nMiddle, int nFirst, int nLast)
{
    int nMaxLeft  = MIN_VAL;
    int nMaxRight = MIN_VAL;
    int nSum = 0;
    for (int i = (nMiddle+1); i <= nLast; i++)
    {
        nSum = nSum + naNum[i];
        if (nMaxRight < nSum)
        {
            nMaxRight = nSum;
        }
    }

    nSum = 0;
    for (int i = nMiddle; i >= nFirst; i--)
    {
        nSum = nSum + naNum[i];
        if (nMaxLeft < nSum)
        {
            nMaxLeft = nSum;
        }
    }
    return nMaxLeft + nMaxRight;
}

int Solve2(int* naNum, int nFirst, int nLast)
{
    assert(nFirst >= 0 && nLast >= 0 && nLast >= nFirst);
    D_Printf("Solve2(): nFirst=%d, nLast=%d\n", nFirst, nLast);
    if (nFirst == nLast) //더 이상 분할할 수 없을 때(base)
    {
        return naNum[nFirst];
    }
    int nMiddle = (nFirst + nLast) / 2;
    int MaxSumLeftSide = Solve2(naNum, nFirst, nMiddle);
    int MaxSumRightSide = Solve2(naNum, nMiddle + 1, nLast);
    return GetMax(GetMaxBothSide(naNum, nMiddle, nFirst, nLast), GetMax(MaxSumLeftSide, MaxSumRightSide));
}

// N
// 동적계획법
/*
// 분할정복법과 유사하다.
// 분할정복법과 차이점이 발생하는 부분은, 문제를 나누는 방식이다.
// 어떤 나눠진 문제는 두 개 이상의 문제를 푸는데 사용될 수 있기 때문이다.
// 이렇게 계산결과를 재활용함으로써 속도의 향상을 꾀할 수 있다.
*/

/*
동적계획법을 이용하자
// 나는 동적계획법을 아예 떠올리지 못했다. 왜냐하면 동적계획법을 제대로 이해하지 못하고 있었다.
*/
int Solve3(int* naNum, int nCnt)
{
    int nMax = MIN_VAL;
    int nSum = 0;

    //naNum[i]를 오른쪽 끝으로 갖는 최대연속부분합을 nMax[i]라 하자.
    //그렇다면 nMax[i]는 항상 2가지 경우의 답을 갖는다.
    //case1. naNum[i]
    //case2. nMax[i-1] + naNum[i]

    //이를 점화식으로 표현하면 다음과 같다.
    //nMax[i] = GetFindMax(0, nMax[i-1]) + naNum[i]
    for (int i = 0; i < nCnt; i++)
    {
        nSum = GetMax(0, nSum) + naNum[i];
        nMax = GetMax(nSum, nMax);
    }
    return nMax;
}