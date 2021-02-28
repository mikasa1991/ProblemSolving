//======== user.cpp ========
//#include <assert.h>
#define AREAPOOL_ID 0
#ifndef NULL
#define NULL 0
#endif

#define MAX_NODE_POOL 50010
#define MAX_MEMBERID 10010
#define MAX_LOTSIZE 100000

extern int add_lot();
extern void assign(int lot_num, int s, int size, int member_id);
extern void back(int lot_num, int s, int size);
extern void grow(int lot_num, int s, int size, int crop);

struct Node
{
    int lotId;
    int st;
    int size;
    Node* prev;
    Node* next;

    void init()
    {
        lotId = 0;
        st = 0;
        size = 0;
        prev = NULL;
        next = NULL;
    }
    void setter(int st, int size)
    {
        this->st = st;
        this->size = size;
    }
    Node* alloc(int lotId, int st, int size)
    {
        this->lotId = lotId;
        this->st = st;
        this->size = size;
        return this;
    }
};
Node gNodePool[MAX_NODE_POOL];
int gUsedNodeCnt;
struct Stack
{
    Node head;
    Node tail;
    int nodeCnt;

    void init()
    {
        head.init();
        tail.init();
        nodeCnt = 0;
        head.next = &tail;
        tail.prev = &head;
    }
    void push(int lotId, int st, int size)
    {
        Node* newNode = gNodePool[gUsedNodeCnt++].alloc(lotId, st, size);
        newNode->next = head.next;
        newNode->prev = &head;
        head.next->prev = newNode;
        head.next = newNode;
        nodeCnt += size;
    }
    Node* pop()
    {
        Node* popNode = head.next;
        popNode->next->prev = popNode->prev;
        popNode->prev->next = popNode->next;
        nodeCnt -= popNode->size;
        return popNode;
    }
    bool isEmpty()
    {
        return (nodeCnt == 0);
    }
};

Stack gStack[MAX_MEMBERID];

void init_member()
{
    gUsedNodeCnt = 0;
    for (int i = 0; i < MAX_MEMBERID; i++)
    {
        gStack[i].init();
    }
    for (int i = 0; i < 10; i++)
    {
        gNodePool[i].init();
    }
}

void assign_member(int id, int size)
{
    if (gStack[AREAPOOL_ID].nodeCnt < size)
    {
        int lotId = add_lot();
        gStack[AREAPOOL_ID].push(lotId, 0, MAX_LOTSIZE);
    }

    //assert(gStack[AREAPOOL_ID].nodeCnt >= size);
    while (size > 0)
    {
        Node* topNode = gStack[AREAPOOL_ID].head.next;
        if (topNode->size > size)
        {
            gStack[AREAPOOL_ID].push(topNode->lotId, topNode->st, size);
            topNode = gStack[AREAPOOL_ID].head.next;
            topNode->next->setter(topNode->next->st + size, topNode->next->size - size);
            
            // 위에서 push할 때, nodeCnt를 size만큼 upCounting하기 때문에(이 때는 사실 push라기 보다는 기존 node를 split하는 개념이다),
            // 여기서 다시 downCounting을 했다.
            gStack[AREAPOOL_ID].nodeCnt -= size;
        }

        //assert(topNode->size <= size);
        Node* popNode = gStack[AREAPOOL_ID].pop();
        assign(popNode->lotId, popNode->st, popNode->size, id);
        gStack[id].push(popNode->lotId, popNode->st, popNode->size);
        size = size - popNode->size;
    }
}

void back_member(int id)
{
    while (false == gStack[id].isEmpty())
    {
        Node* popNode = gStack[id].pop();
        back(popNode->lotId, popNode->st, popNode->size);
        gStack[AREAPOOL_ID].push(popNode->lotId, popNode->st, popNode->size);
    }
}

void grow_member(int id, int crop)
{
    for (Node* temp = gStack[id].head.next; temp != &gStack[id].tail; temp = temp->next)
    {
        //assert(temp != NULL);
        grow(temp->lotId, temp->st, temp->size, crop);
    }
}