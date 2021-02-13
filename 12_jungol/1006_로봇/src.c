//http://jungol.co.kr/bbs/board.php?bo_table=pbank&wr_id=285&sca=30
#pragma warning(disable: 4996)
#pragma warning(disable: 6031)

#include <stdio.h>
#include <assert.h>
#include <malloc.h>

#define DEBUG 0
#if (1 == DEBUG)
#define PRINT printf
#else // (0 == DEBUG)
#define PRINT
#endif

#define MAX_MAP_SIZE  (100 + 1)
#define DIRECTION_NUM (4+1)
#define STEP_CNT      (3)
#define TURN_CNT      (2)

int gMap[MAX_MAP_SIZE][MAX_MAP_SIZE];
int gVisitedMap[DIRECTION_NUM][MAX_MAP_SIZE][MAX_MAP_SIZE];
int ROW;
int COL;
// 동쪽이 1, 서쪽이 2, 남쪽이 3, 북쪽이 4
typedef enum _Direction
{
    DEFAULT = 0,
    EAST = 1,
    WEST = 2,
    SOUTH = 3,
    NORTH = 4,
    DIRECTION_COUNT = NORTH + 1
}Direction;

class Position
{
public:
    int r;
    int c;
    Direction d;
public:
    Position()
    {
        r = 0;
        c = 0;
        d = DEFAULT;
    }

    Position getNextPosition(int step)
    {
        //EAST //WEST //SOUTH //NORTH
        int dr[DIRECTION_NUM] = { 0,      0,     0,      1,    -1 };
        int dc[DIRECTION_NUM] = { 0,      1,    -1,      0,     0 };
        Position retPosi;

        retPosi.d = d;
        retPosi.r = r + (dr[d] * step);
        retPosi.c = c + (dc[d] * step);

        return retPosi;
    }

    Position getNextDirection(int step)
    {
        Direction dd[DIRECTION_NUM][TURN_CNT] =
        {
            {DEFAULT, DEFAULT},
            {SOUTH  , NORTH},  //EAST
            {SOUTH  , NORTH},  //WEST
            {EAST   , WEST },  //SOUTH
            {EAST   , WEST }   //NORTH
        };

        Position retPosi;
        retPosi.d = dd[d][step];
        retPosi.r = r;
        retPosi.c = c;

        return retPosi;
    }

    bool isEqualtoPosition(const Position* pPosi)
    {
        return (pPosi->r == r) && (pPosi->c == c) && (pPosi->d == d);
    }
};

class Node
{
public:
    Position posi;
    int commandCnt;
    Node* prev;
    Node* next;
public:
    Node()
    {
        commandCnt = -1;
        prev = NULL;
        next = NULL;
    }
};

//FIFO
class Queue
{
public:
    Node head;
    Node tail;
    int remainCnt;
public:
    Queue()
    {
        head.next = &tail;
        tail.prev = &head;
        remainCnt = 0;
    }
    void push(Node* pNode)
    {
        Node* newNode = (Node*)malloc(sizeof(Node));
        assert(newNode != NULL);

        newNode->posi.r = pNode->posi.r;
        newNode->posi.c = pNode->posi.c;
        newNode->posi.d = pNode->posi.d;
        newNode->commandCnt = pNode->commandCnt + 1;
        PRINT("> push(): (%d,%d), d=%d, commandCnt=%d\n", newNode->posi.r, newNode->posi.c, newNode->posi.d, newNode->commandCnt);

        newNode->next = &tail;
        newNode->prev = tail.prev;
        tail.prev->next = newNode;
        tail.prev = newNode;

        remainCnt++;
    }
    Node pop()
    {
        assert(false == isEmpty());
        Node* temp = head.next;
        temp->next->prev = temp->prev;
        temp->prev->next = temp->next;

        Node retNode = *temp;
        free(temp);
        remainCnt--;

        PRINT("<< pop(): (%d,%d), d=%d, commandCnt=%d\n", retNode.posi.r, retNode.posi.c, retNode.posi.d, retNode.commandCnt);
        return retNode;
    }
    bool isEmpty()
    {
        return (0 == remainCnt);
    }
};

void init()
{
    ROW = 0;
    COL = 0;
    for (int r = 0; r < MAX_MAP_SIZE; r++)
    {
        for (int c = 0; c < MAX_MAP_SIZE; c++)
        {
            gMap[r][c] = 0;
        }
    }

    for (int d = 0; d < DIRECTION_NUM; d++)
    {
        for (int r = 0; r < MAX_MAP_SIZE; r++)
        {
            for (int c = 0; c < MAX_MAP_SIZE; c++)
            {
                gVisitedMap[d][r][c] = 0;
            }
        }
    }
}

int main()
{
    freopen("input.txt", "r", stdin);

    //input
    init();
    scanf("%d%d", &ROW, &COL);

    //int map[MAX_MAP_SIZE][MAX_MAP_SIZE];
    PRINT("---map---\n");
    for (int r = 1; r <= ROW; r++)
    {
        for (int c = 1; c <= COL; c++)
        {
            scanf("%d", &gMap[r][c]);
            PRINT("%d ", gMap[r][c]);
        }
        PRINT("\n");
    }

    Position posiStart;
    Position posiEnd;
    scanf("%d%d%d", &posiStart.r, &posiStart.c, &posiStart.d);
    scanf("%d%d%d", &posiEnd.r, &posiEnd.c, &posiEnd.d);
    PRINT("Start: (%d,%d) %d\n", posiStart.r, posiStart.c, posiStart.d);
    PRINT("End  : (%d,%d) %d\n", posiEnd.r, posiEnd.c, posiEnd.d);

    //how to solve
    //int gVisitedMap[DIRECTION_NUM][MAX_MAP_SIZE][MAX_MAP_SIZE] = { 0, };
    Node nodeStart;
    nodeStart.posi = posiStart;

    Queue que;
    que.push(&nodeStart);
    gVisitedMap[nodeStart.posi.d][nodeStart.posi.r][nodeStart.posi.c] = 1;

    int commandCnt = 0;
    while (false == que.isEmpty())
    {
        Node nodeCur = que.pop();
        Position posiCur = nodeCur.posi;
        if (posiCur.isEqualtoPosition(&posiEnd))
        {
            commandCnt = nodeCur.commandCnt;
            break;
        }
        else
        {
            for (int i = 1; i <= STEP_CNT; i++)
            {
                Position posiNext = posiCur.getNextPosition(i);
                Node nodeNext = nodeCur;
                nodeNext.posi = posiNext;

                //Map을 벗어난 경우, break
                //도로가 막혀있을 경우, break
                //기존에 방문한 경우, continue
                if ((posiNext.r < 1) || (posiNext.r > ROW) || (posiNext.c < 1) || (posiNext.c > COL) || 1 == gMap[posiNext.r][posiNext.c]) break;
                if (0 == gVisitedMap[posiNext.d][posiNext.r][posiNext.c])
                {
                    que.push(&nodeNext);
                    gVisitedMap[posiNext.d][posiNext.r][posiNext.c] = 1;
                }
            }

            for (int i = 0; i < TURN_CNT; i++)
            {
                Position posiNext = posiCur.getNextDirection(i);
                Node nodeNext = nodeCur;
                nodeNext.posi = posiNext;
                if (0 == gVisitedMap[posiNext.d][posiNext.r][posiNext.c])
                {
                    que.push(&nodeNext);
                    gVisitedMap[posiNext.d][posiNext.r][posiNext.c] = 1;
                }
            }
        }
    }
    printf("%d", commandCnt);
    return 0;
}