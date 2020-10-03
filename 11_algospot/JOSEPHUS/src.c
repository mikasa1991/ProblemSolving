//https://www.algospot.com/judge/problem/read/JOSEPHUS
#pragma warning(disable: 4996)
#pragma warning(disable: 6031)

#include <stdio.h>
#include <assert.h>

const int SURVIVOR_CNT = 2;
const int MAX_NODE_CNT = (1000 + 1);

typedef struct _Node
{
    int num;
    _Node* prev;
    _Node* next;
}Node;

typedef struct _List
{
    Node stNodeNotUsed[MAX_NODE_CNT];
    int idx;
    Node stHead;
    Node stTail;
    int nodeCnt;
    void initialize()
    {
        idx = 0;
        nodeCnt = 0;
        stHead.prev = NULL;
        stHead.next = &stTail;
        stTail.prev = &stHead;
        stTail.next = NULL;
    }
    Node* allocNode(int num)
    {
        assert(idx < MAX_NODE_CNT);
        Node* pNewNode;
        pNewNode = &stNodeNotUsed[idx++];
        pNewNode->num = num;
        pNewNode->prev = NULL;
        pNewNode->next = NULL;
        return pNewNode;
    }
    void insertNode(Node* pNode, int num)
    {
        Node* pNewNode = allocNode(num);
        pNewNode->prev = pNode->prev;
        pNewNode->next = pNode;
        pNode->prev->next = pNewNode;
        pNode->prev = pNewNode;
        nodeCnt++;
    }
    void printNode()
    {
        for (Node* t = stHead.next; t != &stTail; t = t->next)
        {
            printf("%d ", t->num);
        }
        printf("\n");
    }
    void deleteNode(Node* pNode)
    {
        assert(nodeCnt > 0);
        pNode->prev->next = pNode->next;
        pNode->next->prev = pNode->prev;
        nodeCnt--;
    }
}List;

int main()
{
    freopen("input.txt", "r", stdin);
    int C;
    scanf("%d", &C);

    for (int i = 0; i < C; i++)
    {
        int N, K;
        scanf("%d%d", &N, &K);

        List stList;
        stList.initialize();

        for (int i = 1; i <= N; i++)
        {
            stList.insertNode(&stList.stTail, i);
        }

        //Loop: 생존자가 2명일 때, 탈출한다.
        //Do  : K번 이동한다. 죽인다.
        Node* pNode = stList.stHead.next;
        while (1)
        {
            stList.deleteNode(pNode);
            if (SURVIVOR_CNT == stList.nodeCnt) break;
            for (int i = 0; i < K; i++)
            {
                if (pNode->next == &stList.stTail)
                    pNode = stList.stHead.next;
                else
                    pNode = pNode->next;
            }
        }
        //생존자 2명을 출력한다.
        stList.printNode();
    }
    return 0;
}