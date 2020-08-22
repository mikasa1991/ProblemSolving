//https://www.algospot.com/judge/problem/read/PICNIC

#pragma warning(disable: 4996)
#pragma warning(disable: 6031)

#include <stdio.h>
#include <assert.h>
#include <string.h>

#define MAX_STUDENT (10)

int gnStudentCnt;
bool gnDone[MAX_STUDENT];
bool gnRelationMap[MAX_STUDENT][MAX_STUDENT];
int gCnt;

void FuncRecursive(int nId)
{
    //if (nId >= gnStudentCnt) return;
    //printf("FuncRecursive(): %d\n", nId);

    //base case
    if (gnStudentCnt - 1 == nId)
    {
        //If they're not all paired,
        for (int i = 0; i < gnStudentCnt; i++)
        {
            if (0 == gnDone[i])
            {
                return;
            }
        }

        //If they're all paired,
        gCnt++;
        return;
        //printf("FuncRecursive(): gCnt=%d\n", gCnt);
    }

    //recursive case
    if (1 == gnDone[nId])
    {
        FuncRecursive(nId + 1);
    }
    else
    {
        for (int i = nId + 1; i < gnStudentCnt; i++)
        {
            if ((1 == gnRelationMap[nId][i]) && (0 == gnDone[i]))
            {
                //printf("gnRelation: %d, %d\n", nId, i);
                gnDone[nId] = gnDone[i] = 1;
                FuncRecursive(nId + 1);
                gnDone[nId] = gnDone[i] = 0;
            }
        }
    }
}

int main()
{
    freopen("input.txt", "r", stdin);

    int nTCCnt;
    scanf("%d", &nTCCnt);
    for (int t = 0; t < nTCCnt; t++)
    {
        //1. init global variables
        gCnt = 0;
        memset(gnDone, 0, sizeof(gnDone));
        memset(gnRelationMap, 0, sizeof(gnRelationMap));

        //2. input relationTable
        int nRelationCnt;
        scanf("%d%d", &gnStudentCnt, &nRelationCnt);
        //printf("nTc=%d, gnStudentCnt=%d, nRelationCnt=%d\n", t+1, gnStudentCnt, nRelationCnt);

        for (int i = 0; i < nRelationCnt; i++)
        {
            int t1, t2;
            scanf("%d%d", &t1, &t2);
            gnRelationMap[t1][t2] = gnRelationMap[t2][t1] = 1;
        }

        //3. solve
        FuncRecursive(0);
        printf("%d\n", gCnt);
    }
    return 0;
}