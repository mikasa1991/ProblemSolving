//http://www.jungol.co.kr/bbs/board.php?bo_table=pbank&wr_id=2465
#pragma warning(disable: 4996)
#pragma warning(disable: 6031)

#include <stdio.h>
#include <assert.h>

#define MAX (100000)

int gNumber[MAX];

void swap(int* a, int* b)
{
    int temp = *b;
    *b = *a;
    *a = temp;
}
void printMap(int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d ", gNumber[i]);
    }
    puts("");
}
int main()
{
    freopen("input.txt", "r", stdin);

    int tcCnt;
    scanf("%d", &tcCnt);

    for (int tc = 0; tc < tcCnt; tc++)
    {
        int n;
        scanf("%d", &n);
        for (int i = 0; i < n; i++)
        {
            scanf("%d", &gNumber[i]);
        }

        //solve
        int cnt = 0;
        for (int i = 1; i < n; i++)
        {
            for (int j = i; j > 0; j--)
            {
                if (gNumber[j-1] <= gNumber[j])
                    break;

                swap(&gNumber[j-1], &gNumber[j]);
                cnt++;
                //printMap(n);
            }
        }
        printf("%d\n", cnt);
    }
    return 0;
}