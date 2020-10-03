//https://www.algospot.com/judge/problem/read/JUMPGAME
#pragma warning(disable: 4996)
#pragma warning(disable: 6031)

#include <stdio.h>
#include <assert.h>
#include <string.h>

const int MAX_SIZE = (100 + 1);
int gMap[MAX_SIZE][MAX_SIZE];
int gCache[MAX_SIZE][MAX_SIZE];
int n;

#define FINAL_POINT (n-1)

bool funcRecursive(int r, int c)
{
    //printf("funcRecursive(%d, %d)\n", r, c);
    if ((FINAL_POINT == r) && (FINAL_POINT == c)) return true;
    if (r > FINAL_POINT || c > FINAL_POINT) return false;

    int& ret = gCache[r][c];
    if (-1 != ret)
    {
        /* do nothing */
    }
    else
    {
        int jumpSize = gMap[r][c];
        ret = funcRecursive(r + jumpSize, c) || funcRecursive(r, c + jumpSize);
    }
    return ret;
}

int main()
{
    freopen("input.txt", "r", stdin);
    int c;
    scanf("%d%d", &c, &n);
    for (int i = 0; i < c; i++)
    {
        //input
        //int map[MAX_SIZE][MAX_SIZE];
        for (int r = 0; r < n; r++)
        {
            for (int c = 0; c < n; c++)
            {
                scanf("%d", &gMap[r][c]);
                gCache[r][c] = -1;
                //printf("%d ", gMap[r][c]);   //debug
            }
            //printf("\n");   //debug
        }
        if (true == funcRecursive(0, 0)) printf("YES\n");
        else                             printf("NO\n");
    }
    return 0;
}