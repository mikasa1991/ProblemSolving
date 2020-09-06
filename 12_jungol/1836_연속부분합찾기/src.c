//http://jungol.co.kr/bbs/board.php?bo_table=pbank&wr_id=1109&sca=20
#pragma warning(disable: 4996)
#pragma warning(disable: 6031)

#include <stdio.h>
#include <assert.h>
#include <limits.h>

const int MAX_NUM = (int)1e5 + 1;
int A[MAX_NUM];

#define GETMAX(a, b) ((a > b) ? a : b)

int main()
{
    freopen("input.txt", "r", stdin);

    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &A[i]);
    }

    int sum = 0;
    int max = INT_MIN;

    // N
    // 동적계획법
    // 분할정복법과 유사하다.
    // 분할정복법과 차이점이 발생하는 부분은, 문제를 나누는 방식이다.
    // 어떤 나눠진 문제는 두 개 이상의 문제를 푸는데 사용될 수 있기 때문이다.
    // 이렇게 계산결과를 재활용함으로써 속도의 향상을 꾀할 수 있다.

    for (int i = 0; i < n; i++)
    {
        sum = GETMAX(0, sum) + A[i]; //"pre_sum + A[i]" or "A[i]"
        max = GETMAX(max, sum);
    }
    printf("%d", max);
    return 0;
}