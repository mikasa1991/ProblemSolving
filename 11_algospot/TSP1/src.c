//https://www.algospot.com/judge/problem/read/TSP1
#pragma warning(disable: 4996)
#pragma warning(disable: 6031)

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <assert.h>

typedef unsigned int UINT;
const UINT MAX_MAP_SIZE = 8;
const bool VISITED = true;
const bool NOT_VISITED = false;

double gMap[MAX_MAP_SIZE][MAX_MAP_SIZE];
bool gVisited[MAX_MAP_SIZE];
UINT gMapSize;
double gSum;
double gMinSum;

bool ExistToVisit()
{
    for (int i = 0; i < gMapSize; i++)
    {
        if (NOT_VISITED == gVisited[i])
        {
            return true;
        }
    }
    return false;
}

void FuncRecursive(UINT cityId)
{
    //printf("FuncRecursive(): StartCityId=%d\n", cityId);
    gVisited[cityId] = true;

    if (false == ExistToVisit())
    {
        //printf("FuncRecursive(): gSum=%f\n", gSum);
        if (gMinSum > gSum)
        {
            gMinSum = gSum;
        }
    }

    else
    {
        for (UINT i = 0; i < gMapSize; i++)
        {
            if (NOT_VISITED == gVisited[i])
            {
                gSum = gSum + gMap[cityId][i];
                //printf("+ %d to %d=%lf\n", cityId, i, gMap[cityId][i]);
                FuncRecursive(i);
                gSum = gSum - gMap[cityId][i];
                //printf("- %d to %d=%lf\n", cityId, i, gMap[cityId][i]);
                //printf("FuncRecursive(): Clear cityId=%d\n", i);
            }
        }
    }

    gVisited[cityId] = false;
}

int main()
{
    freopen("input.txt", "r", stdin);

    UINT tcCnt;
    scanf("%d", &tcCnt);
    for (UINT tc = 0; tc < tcCnt; tc++)
    {
        //input
        gSum = 0;
        memset(gVisited, 0, sizeof(gVisited));
        scanf("%d", &gMapSize);
        for (UINT r = 0; r < gMapSize; r++)
        {
            for (UINT c = 0; c < gMapSize; c++)
            {
                scanf("%lf", &gMap[r][c]);
                gMinSum = gMinSum + gMap[r][c];
            }
        }

        //solve
        for (UINT i = 0; i < gMapSize; i++)
        {
            FuncRecursive(i/*Start City*/);
        }
        printf("%lf\n", gMinSum);
    }
    return 0;
}