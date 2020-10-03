//https://www.algospot.com/judge/problem/read/JOSEPHUS
#pragma warning(disable: 4996)
#pragma warning(disable: 6031)

#include <stdio.h>
#include <assert.h>

typedef struct _List
{
    int num;
    _List* prev;
    _List* next;
}List;

const int SURVIVOR_CNT = 2;
const int MAX_NODE_CNT = (1000 + 1);
List g_astNode[MAX_NODE_CNT];
int gIndex;

void initializeList(List* pHead, List* pTail)
{
    gIndex = 0;
    pHead->prev = NULL;
    pHead->next = pTail;
    pTail->prev = pHead;
    pTail->next = NULL;
}

List* makeAllocNode(int num)
{
    List* pNewNode;
    pNewNode = &g_astNode[gIndex++];
    pNewNode->num = num;
    pNewNode->prev = NULL;
    pNewNode->next = NULL;
    return pNewNode;
}

void insertNode(List* pNode, int num)
{
    List* pNewNode = makeAllocNode(num);
    pNewNode->prev = pNode->prev;
    pNewNode->next = pNode;
    pNode->prev->next = pNewNode;
    pNode->prev = pNewNode;
}

void printNode(List* pHead, List* pTail)
{
    for (List* t = pHead->next; t != pTail; t = t->next)
    {
        printf("%d ", t->num);
    }
    printf("\n");
}

void deleteNode(List* pNode)
{
    pNode->prev->next = pNode->next;
    pNode->next->prev = pNode->prev;
}

int main()
{
    freopen("input.txt", "r", stdin);
    int C;
    scanf("%d", &C);

    for (int i = 0; i < C; i++)
    {
        int N, K;
        scanf("%d%d", &N, &K);

        List Head;
        List Tail;
        initializeList(&Head, &Tail);

        //linkedlist 형태로 삽입한다.
        for (int i = 1; i <= N; i++)    //to delete 1, i just didn't insert that node.
        {
            insertNode(&Tail, i);
        }

        //1번 Node를 죽인다.
        List* pNode = Head.next;
        deleteNode(pNode);

        //Loop: 생존자가 2명이하일 때, 탈출한다.
        //Do  : K번 이동한다. 죽인다.
        for (int listCnt = N-1; listCnt > SURVIVOR_CNT; listCnt--)
        {
            for (int i = 0; i < K; i++)
            {
                if (pNode->next == &Tail)
                    pNode = Head.next;
                else
                    pNode = pNode->next;
            }
            deleteNode(pNode);
        }

        //생존자 2명을 출력한다.
        printNode(&Head, &Tail);
    }
    return 0;
}