//https://www.algospot.com/judge/problem/read/BOARDCOVER

#pragma warning(disable: 4996)
#pragma warning(disable: 6031)

#include <stdio.h>
#include <assert.h>

typedef struct _Posi
{
    int r;
    int c;
}Posi;

const int BLOCK_CNT = 4;
const int BLOCK_SIZE = 3;
const int MAP_SIZE = 20;
const char BARRIER = '#';
const char CLEAR = '.';
const char SET = 'v';
const Posi DELTA[BLOCK_CNT][BLOCK_SIZE]
= {
    {{0, 0}, {0, 1}, { 1,  1}},
    {{0, 0}, {1, 0}, { 1,  1}},
    {{0, 0}, {0, 1}, { 1,  0}},
    {{0, 0}, {1, 0}, { 1, -1}},
 };

char gMap[MAP_SIZE][MAP_SIZE];
int gCnt;
int gMaxRow;
int gMaxCol;

void printMap(void)
{
    for (int r = 0; r < gMaxRow; r++)
    {
        for (int c = 0; c < gMaxCol; c++)
        {
            printf("%c", gMap[r][c]);
        }
        printf("\n");
    }
}

Posi FindPosi(Posi* pPosi)
{
    Posi retPosi = *pPosi;
    retPosi.r = retPosi.c = -1;
    for (int r = 0; r < gMaxRow; r++)
    {
        for (int c = 0; c < gMaxCol; c++)
        {
            if (CLEAR == gMap[r][c])
            {
                retPosi.r = r;
                retPosi.c = c;
                return retPosi;
            }
        }
    }
    return retPosi;
}

Posi GetNextPosi(Posi* pPosi, int dr, int dc)
{
    Posi nextPosi;
    nextPosi.r = pPosi->r + dr;
    nextPosi.c = pPosi->c + dc;
    return nextPosi;
}

bool IsInArea(Posi* pPosi)
{
    return (pPosi->r >= 0) && (pPosi->r < gMaxRow)
        && (pPosi->c >= 0) && (pPosi->c < gMaxCol);
}

bool IsAbleToSetBlock(int blockType, Posi* pPosi)
{
    for (int i = 0; i < BLOCK_SIZE; i++)
    {
        Posi nextPosi = GetNextPosi(pPosi, DELTA[blockType][i].r, DELTA[blockType][i].c);
        if (CLEAR != gMap[nextPosi.r][nextPosi.c] || !IsInArea(&nextPosi))
        {
            return false;
        }
    }
    return true;
}

void SetBlock(int blockType, Posi* pPosi)
{
    //printf("SetBlock: blockType=%d, startPosi=(%d,%d)\n", blockType, pPosi->r, pPosi->c);
    for (int i = 0; i < BLOCK_SIZE; i++)
    {
        Posi nextPosi = GetNextPosi(pPosi, DELTA[blockType][i].r, DELTA[blockType][i].c);
        assert(CLEAR == gMap[nextPosi.r][nextPosi.c]);
        gMap[nextPosi.r][nextPosi.c] = SET;
    }
    //printMap();
}

void ClearBlock(int blockType, Posi* pPosi)
{
    //printf("ClearBlock: blockType=%d, startPosi=(%d,%d)\n", blockType, pPosi->r, pPosi->c);
    for (int i = 0; i < BLOCK_SIZE; i++)
    {
        Posi nextPosi = GetNextPosi(pPosi, DELTA[blockType][i].r, DELTA[blockType][i].c);
        assert(SET == gMap[nextPosi.r][nextPosi.c]);
        gMap[nextPosi.r][nextPosi.c] = CLEAR;
    }
    //printMap();
}

void FuncRecursive(Posi* pPosi)
{
    //printf("pPosi=(%d,%d)\n", pPosi->r, pPosi->c);
    Posi startPosi = FindPosi(pPosi);
    //printf("startPosi=(%d,%d)\n", startPosi.r, startPosi.c);

    if ((-1 == startPosi.r) && (-1 == startPosi.c)) //EMPTY NOT EXIST
    {
        gCnt++;
        return;
    }

    for (int i = 0; i < BLOCK_CNT; i++)
    {
        if (IsAbleToSetBlock(i, &startPosi))
        {
            SetBlock(i, &startPosi);
            FuncRecursive(&startPosi);
            ClearBlock(i, &startPosi);
        }
    }
}

int main(void)
{
    freopen("input.txt", "r", stdin);
    int tcCnt;
    scanf("%d", &tcCnt);

    for (int tc = 0; tc < tcCnt; tc++)
    {
        //init
        //printf("tc=%d\n", tc);
        gCnt = 0;
        int emptyCnt = 0;
        scanf("%d%d", &gMaxRow, &gMaxCol);
        for (int r = 0; r < gMaxRow; r++)
        {
            scanf("%s", gMap[r]);
            for (int c = 0; c < gMaxCol; c++)
            {
                if (CLEAR == gMap[r][c])
                {
                    emptyCnt++;
                }
            }
        }
        //printf("emptyCnt=%d\n", emptyCnt);
        //printMap();

        //solve
        if (0 == emptyCnt % 3)
        {
            Posi nPosi;
            nPosi.r = nPosi.c = 0;
            FuncRecursive(&nPosi);
        }
        printf("%d\n", gCnt);
    }
    return 0;
}