//https://www.acmicpc.net/problem/14502
#pragma warning(disable: 4996)
#pragma warning(disable: 6031)

#include <stdio.h>
#include <malloc.h>
#include <assert.h>

//#define DEBUG 1
#ifdef DEBUG
#define PRINT printf
#else
#define PRINT
#endif

#define MAX_MAP_SIZE (8+1)
#define EMPTY        0
#define WALL         1
#define VIRUS        2
#define VISIT        1
#define MAX(a,b) ((a > b) ? a : b)
#define WALL_CNT     3
int ROW;
int COL;
int gInputMap[MAX_MAP_SIZE][MAX_MAP_SIZE];
int gMap[MAX_MAP_SIZE][MAX_MAP_SIZE];

void init()
{
    ROW = 0;
    COL = 0;
}

class Position
{
public:
    int r;
    int c;
public:
    Position()
    {
        r = 0;
        c = 0;
    }

    bool isEmptySpace(int i)
    {
        r = i / COL;
        c = i % COL;

        if (EMPTY == gMap[r][c])
            return true;
        else
            return false;
    }

    bool isAbletoGo()
    {
        return (EMPTY == gMap[r][c] && r >= 0 && r < ROW && c >= 0 && c < COL);
    }
};

void printMap()
{
    printf("printMap():\n");
    for (int r = 0; r < ROW; r++)
    {
        for (int c = 0; c < COL; c++)
        {
            printf("%d ", gMap[r][c]);
        }
        printf("\n");
    }
}

int getEmptyCnt()
{
    int cnt = 0;
    for (int r = 0; r < ROW; r++)
    {
        for (int c = 0; c < COL; c++)
        {
            if (EMPTY == gMap[r][c])
            {
                cnt++;
            }
        }
    }
    return cnt;
}

const int dr[4] = { 0,  0, 1, -1};
const int dc[4] = { 1, -1, 0,  0};
void DFS(int r, int c)
{
    gMap[r][c] = VIRUS;
    for (int i = 0; i < 4; i++)
    {
        Position posiNext;
        posiNext.r = r + dr[i];
        posiNext.c = c + dc[i];

        if (posiNext.isAbletoGo())
        {
            DFS(posiNext.r, posiNext.c);
        }
    }
}

void moveVirus()
{
    for (int r = 0; r < ROW; r++)
    {
        for (int c = 0; c < COL; c++)
        {
            if (VIRUS == gMap[r][c])
            {
                DFS(r, c);
            }
        }
    }
}

void inputMapLoad()
{
    for (int r = 0; r < ROW; r++)
    {
        for (int c = 0; c < COL; c++)
        {
            gMap[r][c] = gInputMap[r][c];
        }
    }
}
int main()
{
    freopen("input.txt", "r", stdin);
    init();

    scanf("%d%d", &ROW, &COL);
    int i = 0;
    for (int r = 0; r < ROW; r++)
    {
        for (int c = 0; c < COL; c++)
        {
            scanf("%d", &gInputMap[r][c]);
            PRINT("%d ", gInputMap[r][c]);
        }
        PRINT("\n");
    }

    int loop = 0;
    int maxEmptyCnt = 0;
    Position arrPosi[WALL_CNT];
    inputMapLoad();
    for (int i = 0; i < ROW * COL; i++)
    {
        if (false == arrPosi[0].isEmptySpace(i)) continue;
        for (int j = i + 1; j < ROW * COL; j++)
        {
            if (false == arrPosi[1].isEmptySpace(j)) continue;
            for (int k = j + 1; k < ROW * COL; k++)
            {
                if (false == arrPosi[2].isEmptySpace(k)) continue;
                //PRINT("\n(%d,%d), (%d,%d), (%d,%d)\n", arrPosi[0].r, arrPosi[0].c, arrPosi[1].r, arrPosi[1].c, arrPosi[2].r, arrPosi[2].c);

                loop++;
                // 벽 3개를 선택한다.
                for (int m = 0; m < WALL_CNT; m++)
                {
                    gMap[arrPosi[m].r][arrPosi[m].c] = WALL;
                }
                //printMap();

                //바이러스를 퍼뜨린다.
                moveVirus();
                //printMap();

                //생존지역을 확인한다.
                int emptyCnt = 0;
                emptyCnt = getEmptyCnt();

                //MAX 생존지역을 확인한다.
                maxEmptyCnt = MAX(emptyCnt, maxEmptyCnt);

                inputMapLoad();
            }
        }
    }
    PRINT("loop=%d\n", loop);
    printf("%d", maxEmptyCnt);
    return 0;
}