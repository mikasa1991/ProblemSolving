//http://jungol.co.kr/bbs/board.php?bo_table=pbank&wr_id=358&sca=99
#pragma warning(disable: 4996)
#pragma warning(disable: 6031)

#include <stdio.h>
#include <assert.h>
#include <malloc.h>

#define MAX_MAP_SIZE (100+1)
#define ZERGLING     (1)
#define VISITED      (1)
#define DEBUG        (0)

#if (1 == DEBUG)
#define PRINT printf
#else
#define PRINT
#endif

int ROW;
int COL;
int gMap[MAX_MAP_SIZE][MAX_MAP_SIZE];
int gVisit[MAX_MAP_SIZE][MAX_MAP_SIZE];
const int dr[4] = { 0,  0, 1, -1 };
const int dc[4] = { 1, -1, 0,  0 };
void init()
{
    ROW = 0;
    COL = 0;

    for (int r = 0; r < MAX_MAP_SIZE; r++)
    {
        for (int c = 0; c < MAX_MAP_SIZE; c++)
        {
            gMap[r][c] = 0;
            gVisit[r][c] = 0;
        }
    }
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

    // map 범위를 벗어난 경우, continue;
    // 저글링이 아닌 경우, continue;
    // 이미 방문한 경우, continue;
    bool isAbletoVisit()
    {
        return (r >= 1) && (r <= ROW) && (c >= 1) && (c <= COL) && (ZERGLING == gMap[r][c]) && (VISITED != gVisit[r][c]);
    }
};

class Node
{
public:
    Position posi;
    int time;
    Node* prev;
    Node* next;
public:
    Node()
    {
        time = 2;
        prev = NULL;
        next = NULL;
    }
};

class Queue
{
public:
    Node head;
    Node tail;
    int remainNodeCnt;
public:
    Queue()
    {
        remainNodeCnt = 0;
        head.next = &tail;
        tail.prev = &head;
    }

    //tail앞에 넣는다.
    void push(Node* pNode)
    {
        Node* newNode = (Node*)malloc(sizeof(Node));
        assert(NULL != newNode);
        newNode->posi = pNode->posi;
        newNode->time = pNode->time + 1;
        newNode->next = &tail;
        newNode->prev = tail.prev;
        tail.prev->next = newNode;
        tail.prev = newNode;
        remainNodeCnt++;
        PRINT(">push(): (%d,%d), time=%d\n", newNode->posi.r, newNode->posi.c, newNode->time);
    }

    //head뒤를 pop한다.
    Node pop()
    {
        assert(false == isEmpty());
        Node* nodeTemp = head.next;
        nodeTemp->next->prev = nodeTemp->prev;
        nodeTemp->prev->next = nodeTemp->next;
        remainNodeCnt--;
        Node retNode = *nodeTemp;
        free(nodeTemp);
        PRINT("<<pop(): (%d,%d), time=%d\n", retNode.posi.r, retNode.posi.c, retNode.time);
        return retNode;
    }

    bool isEmpty()
    {
        return (0 == remainNodeCnt);
    }
};
int main()
{
    freopen("input.txt", "r", stdin);
    init();
    scanf("%d%d", &COL, &ROW);
    PRINT("ROW=%d, COL=%d\n", ROW, COL);

    char string[MAX_MAP_SIZE][MAX_MAP_SIZE] = { 0, };
    for (int r = 0; r < ROW; r++)
    {
        scanf("%s", string[r]);
    }

    int zerglingCnt = 0;
    for (int r = 0; r < ROW; r++)
    {
        for (int c = 0; c < COL; c++)
        {
            gMap[r + 1][c + 1] = string[r][c] - '0';
            if (ZERGLING == gMap[r + 1][c + 1])
            {
                zerglingCnt++;
            }
            PRINT("%d ", gMap[r + 1][c + 1]);
        }
        PRINT("\n");
    }
    Position posiStart;
    scanf("%d%d", &posiStart.c, &posiStart.r);
    PRINT("Posi: (%d, %d)\n", posiStart.r, posiStart.c);
    Node nodeStart;
    nodeStart.posi = posiStart;

    //how to solve it?
    Queue que;
    que.push(&nodeStart);
    gVisit[posiStart.r][posiStart.c] = VISITED;

    int retTime = 0;
    while (false == que.isEmpty())
    {
        Node nodePop = que.pop();
        zerglingCnt--;
        retTime = nodePop.time;
        Position posiCur = nodePop.posi;

        for (int i = 0; i < 4; i++)
        {
            Position posiNext;
            posiNext.r = posiCur.r + dr[i];
            posiNext.c = posiCur.c + dc[i];

            // map 범위를 벗어난 경우, continue;
            // 저글링이 아닌 경우, continue;
            // 이미 방문한 경우, continue;

            if (posiNext.isAbletoVisit())
            {
                Node nodeNext = nodePop;
                nodeNext.posi = posiNext;
                que.push(&nodeNext);
                gVisit[posiNext.r][posiNext.c] = VISITED;
            }
        }
    }
    printf("%d\n%d", retTime, zerglingCnt);
    return 0;
}