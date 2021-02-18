// https://www.acmicpc.net/problem/14500
#pragma warning(disable: 4996)
#pragma warning(disable: 6031)

#include <stdio.h>
#include <malloc.h>
#include <assert.h>

//#define DEBUG
#ifdef DEBUG
#define PRINT printf
#else
#define PRINT
#endif

#define MAP_MAX_SIZE (500+1)
#define MAX(a,b) ((a > b)? a : b)
#define DIR_CNT 4

int gMap[MAP_MAX_SIZE][MAP_MAX_SIZE];
int gVisit[MAP_MAX_SIZE][MAP_MAX_SIZE];
int ROW;
int COL;
int gMaxSum;
const int dr[DIR_CNT] = {  0, 0, 1, -1};
const int dc[DIR_CNT] = { -1, 1, 0,  0};

const int TETROMINO_dr[4][3]
= {
    { 0, 0, 1},
    {-1, 0, 1},
    {-1, 0, 0},
    { 1, 1, 2}
};
const int TETROMINO_dc[4][3]
= {
    {1, 2, 1},
    {1, 1, 1},
    {1, 1, 2},
    {0, 1, 0}
};
void printVisit();

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

    bool isNotVisited()
    {
        return (0 == gVisit[r][c]);
    }

    bool isInArea()
    {
        return (r >= 0) && (r < ROW) && (c >= 0) && (c < COL);
    }
};

void DFS(int r, int c, int depth, int sum)
{
    gVisit[r][c] = 1;

    Position posiCur;
    posiCur.r = r;
    posiCur.c = c;

    if (depth < 4)
    {
        for (int i = 0; i < DIR_CNT; i++)
        {
            Position posiNext;
            posiNext.r = r + dr[i];
            posiNext.c = c + dc[i];

            if (posiNext.isInArea() && posiNext.isNotVisited())
            {
                DFS(posiNext.r, posiNext.c, depth + 1, sum + gMap[posiNext.r][posiNext.c]);
            }
        }
    }
    else
    {
        //printVisit();
        gMaxSum = MAX(sum, gMaxSum);
    }

    gVisit[r][c] = 0;
}

void init()
{
    for (int r = 0; r < ROW; r++)
    {
        for (int c = 0; c < COL; c++)
        {
            gVisit[r][c] = 0;
        }
    }
}

void printVisit()
{
    printf("printVisit():\n");
    for (int r = 0; r < ROW; r++)
    {
        for (int c = 0; c < COL; c++)
        {
            printf("%d ", gVisit[r][c]);
        }
        printf("\n");
    }
}

void func(int r, int c)
{
    for (int i = 0; i < 4; i++)
    {
        //init();
        int flg = 1;
        int sum = gMap[r][c];
        //gVisit[r][c] = 1;
        for (int j = 0; j < 3; j++)
        {
            Position posiNext;
            posiNext.r = r + TETROMINO_dr[i][j];
            posiNext.c = c + TETROMINO_dc[i][j];

            if (posiNext.isInArea())
            {
                sum = sum + gMap[posiNext.r][posiNext.c];
                //gVisit[posiNext.r][posiNext.c] = 1;
            }
            else
            {
                flg = 0;
                break;
            }
        }
        if (1 == flg) //도형 배치가 가능했다면,
        {
            //printVisit();
            gMaxSum = MAX(sum, gMaxSum);
        }
    }
}

int main()
{
    freopen("input.txt", "r", stdin);

    //input
    gMaxSum = 0;
    scanf("%d%d", &ROW, &COL);
    for (int r = 0; r < ROW; r++)
    {
        for (int c = 0; c < COL; c++)
        {
            scanf("%d", &gMap[r][c]);
            PRINT("%d ", gMap[r][c]);
        }
        PRINT("\n");
    }

    init();
    //how to solve it?
    for (int r = 0; r < ROW; r++)
    {
        for (int c = 0; c < COL; c++)
        {
            PRINT("(%d,%d)\n", r, c);
            DFS(r, c, 1, gMap[r][c]);
            func(r, c);
        }
    }

    printf("%d", gMaxSum);
    return 0;
}