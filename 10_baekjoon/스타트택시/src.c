#pragma warning(disable: 4996)
#pragma warning(disable: 6031)

#include <stdio.h>
#include <assert.h>

#define MAX_MAP_SIZE (20+1)
#define MAX_CUSTOM_CNT (MAX_MAP_SIZE*MAX_MAP_SIZE)
#define EMPTY  0
#define BLOCK  1
#define CUSTOM 2
#define NOT_VISIT 0
#define VISITED 1
#define DIR_CNT 4
#define DEBUG 0

typedef struct _Position
{
    int r;
    int c;
}Position;

typedef struct _Queue
{
    Position posi;
    int distance;
}Queue;

typedef struct _CustomInfo
{
    int id;
    Position posi;
    int distanceFromTaxi;
}CustomInfo;
int dr[DIR_CNT] = {0,  0, 1, -1};
int dc[DIR_CNT] = {1, -1, 0,  0};
int gMap[MAX_MAP_SIZE][MAX_MAP_SIZE];
int gVisited[MAX_MAP_SIZE][MAX_MAP_SIZE];
int gMapSize;
int gCustomCnt;
int gEnergy;
Position gTaxiPosi;
Position gCustomEndPosi[MAX_CUSTOM_CNT];
Queue gQueue[MAX_MAP_SIZE * MAX_MAP_SIZE];
int gHead;
int gTail;
int gCnt;
/*
택시 위치에서 최단거리가 가장 짧은 승객을 고른다.
(1.행번호작은순, 2.열번호작은순)
최단거리와 연료량을 비교한다. 연료가 작을 경우, 이동실패.
(연료량-최단거리 >  0; 이동가능)
이동거리만큼 연료를 소모한다. 승객을 태운다.
승객의 목적지까지 최단거리로 이동한다.
최단거리와 연료량을 비교한다. 연료가 작을 경우, 이동실패.
(연료량-최단거리 >= 0; 이동가능)
이동거리만큼 연료를 소모한다.
이동거리의 2배만큼 연료가 충전된다.
 */
void InitVisited()
{
    for (int r = 1; r <= gMapSize; r++)
    {
        for (int c = 1; c <= gMapSize; c++)
        {
            gVisited[r][c] = 0;
        }
    }
}
void InitQueue()
{
    gHead = gTail = gCnt = 0;
}
void Init()
{
    InitQueue();
    scanf("%d%d%d", &gMapSize, &gCustomCnt, &gEnergy);
    for (int r = 1; r <= gMapSize; r++)
    {
        for (int c = 1; c <= gMapSize; c++)
        {
            scanf("%d", &gMap[r][c]);
            gVisited[r][c] = 0;
        }
    }
    scanf("%d%d", &gTaxiPosi.r, &gTaxiPosi.c);
    for (int i = 1; i <= gCustomCnt; i++)
    {
        int startRow, startCol;
        scanf("%d%d", &startRow, &startCol);
        gMap[startRow][startCol] = i * -1;
        scanf("%d%d", &gCustomEndPosi[i].r, &gCustomEndPosi[i].c);
    }
}
void PrintCustomEndPosi()
{
    for (int i = 1; i <= gCustomCnt; i++)
    {
        printf("customEndPosi id %d: (%d,%d)\n", i, gCustomEndPosi[i].r, gCustomEndPosi[i].c);
    }
}
void PrintTaxiPosi()
{
    printf("TaxiPosi: (%d,%d)\n", gTaxiPosi.r, gTaxiPosi.c);
}
void PrintMap()
{
    printf("PrintMap()\n");
    for (int r = 1; r <= gMapSize; r++)
    {
        for (int c = 1; c <= gMapSize; c++)
        {
            printf("%2d ", gMap[r][c]);
        }
        puts("");
    }
}
void EnQueue(Position *pPosi, int dir)
{
    gVisited[pPosi->r][pPosi->c] = VISITED;
    gQueue[gHead].posi = *pPosi;
    gQueue[gHead].distance = dir + 1;
    //printf(">EnQueue: (%d, %d), %d\n", gQueue[gHead].posi.r, gQueue[gHead].posi.c, gQueue[gHead].distance);
    gHead++;
    gCnt++;
}
bool IsEmpty()
{
    return (gCnt == 0);
}
Queue* DeQueue()
{
    assert(gCnt > 0);
    gCnt--;
    //printf("<DeQueue: (%d, %d), %d\n", gQueue[gTail].posi.r, gQueue[gTail].posi.c, gQueue[gTail].distance);
    return &gQueue[gTail++];
}
bool IsInArea(int r, int c)
{
    return (r > 0) && (r <= gMapSize) && (c > 0) && (c <= gMapSize);
}
bool IsCustomer(int r, int c)
{
    return (gMap[r][c] < 0);
}

bool GetCustomInfo(Position* pTaxiPosi, CustomInfo* closeCustom)
{
    //현재 택시위치에 승객이 있다면
    if (0 > gMap[pTaxiPosi->r][pTaxiPosi->c])
    {
        closeCustom->distanceFromTaxi = 0;
        closeCustom->posi = *pTaxiPosi;
        closeCustom->id = gMap[closeCustom->posi.r][closeCustom->posi.c] * -1;
        return true;
    }

    InitQueue();
    InitVisited();
    closeCustom->posi.r = MAX_MAP_SIZE;
    closeCustom->posi.c = MAX_MAP_SIZE;

    EnQueue(pTaxiPosi, -1);
    while (false == IsEmpty())
    {
        Queue* tmp = DeQueue();
        Position posi = tmp->posi;
        for (int dir = 0; dir < DIR_CNT; dir++)
        {
            Position nextPosi;
            nextPosi.r = posi.r + dr[dir];
            nextPosi.c = posi.c + dc[dir];
            if (IsInArea(nextPosi.r, nextPosi.c) && BLOCK != gMap[nextPosi.r][nextPosi.c] && NOT_VISIT == gVisited[nextPosi.r][nextPosi.c])
            {
                EnQueue(&nextPosi, tmp->distance);
                if (IsCustomer(nextPosi.r, nextPosi.c))
                {
                    closeCustom->distanceFromTaxi = tmp->distance + 1;
                    if (closeCustom->posi.r > nextPosi.r) //행번호 작은순
                    {
                        closeCustom->posi = nextPosi;
                    }
                    else if (closeCustom->posi.r == nextPosi.r)
                    {
                        if (closeCustom->posi.c > nextPosi.c) //열번호 작은순
                        {
                            closeCustom->posi = nextPosi;
                        }
                        else if (closeCustom->posi.c == nextPosi.c)
                        {
                            assert(0);
                        }
                        else
                        {
                            /* do nothing */
                        }
                    }
                    else
                    {
                        /* do nothing */
                    }
                }
            }
        }
        if ((closeCustom->posi.r != MAX_MAP_SIZE) && (closeCustom->posi.c != MAX_MAP_SIZE))
        {
            closeCustom->id = gMap[closeCustom->posi.r][closeCustom->posi.c] * -1;
            //printf("customPosi %d: (%d,%d), %d\n", closeCustom->id, closeCustom->posi.r, closeCustom->posi.c, closeCustom->distanceFromTaxi);
            return true;
        }
    }
    return false;
}

/*
택시 위치에서 최단거리가 가장 짧은 승객을 고른다.
(1.행번호작은순, 2.열번호작은순)
최단거리와 연료량을 비교한다. 연료가 작을 경우, 이동실패.
(연료량-최단거리 >  0; 이동가능)
이동거리만큼 연료를 소모한다. 승객을 태운다.
승객의 목적지까지 최단거리로 이동한다.
최단거리와 연료량을 비교한다. 연료가 작을 경우, 이동실패.
(연료량-최단거리 >= 0; 이동가능)
이동거리만큼 연료를 소모한다.
이동거리의 2배만큼 연료가 충전된다.
 */
bool GetCustomEndInfo(Position* pTaxiPosi, CustomInfo* closeCustomEnd, int id)
{
    //현재 택시위치에 승객이 있다면
    if (0 > gMap[pTaxiPosi->r][pTaxiPosi->c])
    {
        closeCustomEnd->distanceFromTaxi = 0;
        closeCustomEnd->posi = *pTaxiPosi;
        return true;
    }

    InitQueue();
    InitVisited();
    EnQueue(pTaxiPosi, -1);
    while (false == IsEmpty())
    {
        Queue* tmp = DeQueue();
        Position posi = tmp->posi;
        for (int dir = 0; dir < DIR_CNT; dir++)
        {
            Position nextPosi;
            nextPosi.r = posi.r + dr[dir];
            nextPosi.c = posi.c + dc[dir];
            if (IsInArea(nextPosi.r, nextPosi.c) && BLOCK != gMap[nextPosi.r][nextPosi.c] && NOT_VISIT == gVisited[nextPosi.r][nextPosi.c])
            {
                EnQueue(&nextPosi, tmp->distance);
                if ((nextPosi.r == gCustomEndPosi[id].r) && (nextPosi.c == gCustomEndPosi[id].c))
                {
                    closeCustomEnd->distanceFromTaxi = tmp->distance + 1;
                    closeCustomEnd->posi = nextPosi;
                    //printf("customEndPosi: (%d,%d), %d\n", closeCustomEnd->posi.r, closeCustomEnd->posi.c, closeCustomEnd->distanceFromTaxi);
                    return true;
                }
            }
        }
    }
    return false;
}
int main()
{
    freopen("input.txt", "r", stdin);
    Init();
#if (1 == DEBUG)
    PrintMap();
    PrintTaxiPosi();
    PrintCustomEndPosi();
    printf("gEnergy: %d\n", gEnergy);
#endif
    int result = 0;
    for (int i = 0; i < gCustomCnt; i++)
    {
#if (1 == DEBUG)
        printf("\n%d:\n", i);
#endif
        CustomInfo closeCustom;
        if (false == GetCustomInfo(&gTaxiPosi, &closeCustom))
        {
            result = -1;
            break;
        }
        gEnergy = gEnergy - closeCustom.distanceFromTaxi;
        if (gEnergy <= 0)
        {
            result = -1;
            break;
        }
        gTaxiPosi = closeCustom.posi;                     //승객 탑승 위치 도달
        gMap[closeCustom.posi.r][closeCustom.posi.c] = 0; //승객 태움
#if (1 == DEBUG)
        PrintTaxiPosi();
        PrintMap();
        printf("moveCnt: %d\n", closeCustom.distanceFromTaxi);
        printf("gEnergy: %d\n", gEnergy);
        puts("");
#endif
        CustomInfo closeCustomEnd;
        if (false == GetCustomEndInfo(&gTaxiPosi, &closeCustomEnd, closeCustom.id))
        {
            result = -1;
            break;
        }
        gEnergy = gEnergy - closeCustomEnd.distanceFromTaxi;
        if (gEnergy < 0)
        {
            result = -1;
            break;
        }
        gTaxiPosi = closeCustomEnd.posi;                  //승객 목적지 도달
        gEnergy = gEnergy + (2 * closeCustomEnd.distanceFromTaxi);
#if (1 == DEBUG)
        PrintTaxiPosi();
        PrintMap();
        printf("moveCnt: %d\n", closeCustomEnd.distanceFromTaxi);
        printf("gEnergy: %d\n", gEnergy);
        puts("");
#endif
    }
    if (-1 != result) printf("%d", gEnergy);
    else printf("%d", -1);
    return 0;
}