//https://www.acmicpc.net/problem/1766
#pragma warning(disable: 4996)
#pragma warning(disable: 6031)

#include <stdio.h>
#include <assert.h>

#define METHOD 2
const int MAX_VERTEX_CNT = (32000 + 10);
const int MAX_EDGE_CNT = ((int)1e5 + 10);
typedef struct _Node
{
    int val;
    _Node* prev;
    _Node* next;
}Node;
typedef struct _AllocatedNode
{
    Node array[MAX_EDGE_CNT];
    int index;
}AllocatedNode;

AllocatedNode gAllocNode;
typedef struct _List
{
    int inDegree;
    Node head;
    Node tail;
    void init()
    {
        inDegree = 0;
        head.next = &tail;
        tail.prev = &head;
    }
    Node* allocNode(int val)
    {
        Node* newNode = &gAllocNode.array[gAllocNode.index++];
        newNode->prev = NULL;
        newNode->next = NULL;
        newNode->val = val;
        return newNode;
    }
    void pushBack(int val)
    {
        Node* newNode = allocNode(val);
        newNode->next = &tail;
        newNode->prev = tail.prev;
        tail.prev->next = newNode;
        tail.prev = newNode;
    }
    void printList()
    {
        for (Node* temp = head.next; temp != &tail; temp = temp->next)
        {
            printf("%d ", temp->val);
        }
        printf("\n");
    }
}List;

void swap(int* a, int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}
#define PARENT_ID(idx)      ((idx - 1) / 2)
#define LEFT_CHILD_ID(idx)  (2*idx + 1)
#define RIGHT_CHILD_ID(idx) (2*idx + 2)
#define ROOT_ID             0
typedef struct _MinHeap
{
    int top;
    int arr[MAX_VERTEX_CNT];
    void init()
    {
        top = 0;
    }
    int heapSize()
    {
        return top;
    }
    bool isEmpty()
    {
        return (top == 0);
    }
    bool isFull()
    {
        return (top == MAX_VERTEX_CNT);
    }
    void push(int val)
    {
        assert(false == isFull());
        arr[top] = val;
        top++;
        int idx = top - 1;

        //LOOP
        //Exit Condition: idx가 ROOT_ID다. 또는 부모가 더 작다.
        //Do : 부모와 자식 바꾸기.
        while ((idx > ROOT_ID) && (arr[idx] < arr[PARENT_ID(idx)]))
        {
            swap(&arr[idx], &arr[PARENT_ID(idx)]);
            idx = PARENT_ID(idx);
        }
    }
    void pop()
    {
        assert(false == isEmpty());
        arr[ROOT_ID] = arr[top - 1];
        top--;

        //LOOP
        //Exit Condition: idx가 leaf다. 또는 두 자식보다 작다.
        //DO: 가장 작은 자식과 바꾼다.
        int idx = ROOT_ID;
        while (1)
        {
            int leftChildIdx = LEFT_CHILD_ID(idx);
            int rightChildIdx = RIGHT_CHILD_ID(idx);
            if (idx >= heapSize()) break;

            int nextIdx = idx;
            if (arr[nextIdx] > arr[leftChildIdx])
            {
                nextIdx = leftChildIdx;
            }
            if ((rightChildIdx < heapSize()) && arr[nextIdx] > arr[rightChildIdx])
            {
                nextIdx = rightChildIdx;
            }
            if (idx == nextIdx) break;
            swap(&arr[idx], &arr[nextIdx]);
            idx = nextIdx;
        }
    }
    int getRoot()
    {
        return arr[ROOT_ID];
    }
}MinHeap;

int main()
{
    freopen("input.txt", "r", stdin);
    int N;
    int M;
    scanf("%d%d", &N, &M);

    List stList[MAX_VERTEX_CNT];
    for (int i = 1; i <= N; i++)
    {
        stList[i].init();
    }
    for (int i = 1; i <= M; i++)
    {
        int a, b;
        scanf("%d%d", &a, &b);
        stList[a].pushBack(b);
        stList[b].inDegree++;
    }

#if (1 == METHOD)
    //solve
    //indegree가 0인 Vertex를 출력한다.
    //해당 Vertex가 가르키는 Vertex의 indegree를 --한다.
    //위의 과정을 Vertex의 개수만큼 반복한다.
    for (int i = 1; i <= N; i++)
    {
        // O(V + E)
        for (int i = 1; i <= N; i++)
        {
            if (0 == stList[i].inDegree)
            {
                printf("%d ", i);
                stList[i].inDegree--;
                for (Node* temp = stList[i].head.next; temp != &stList[i].tail; temp = temp->next)
                {
                    stList[temp->val].inDegree--;
                }
                break;
            }
        }
    }
#elif (2 == METHOD) //위상정렬을 우선순위큐를 이용해서 하면 된다.
    //indegree가 0인 Vertex를 minHeap에 넣는다.
    //pop한 Vertex가 가르키는 Vertex의 indegree를 --한다. 이 중에 indegree가 0인 Vertex를 minHeap에 넣는다.
    //위의 과정을 Vertex의 개수만큼 반복한다.
    MinHeap stMinHeap;
    stMinHeap.init();
    for (int i = 1; i <= N; i++)
    {
        if (0 == stList[i].inDegree) stMinHeap.push(i);
    }

    // O(V + E)
    while (false == stMinHeap.isEmpty())
    {
        int vertexId = stMinHeap.getRoot();
        printf("%d ", vertexId);
        stMinHeap.pop();
        for (Node* temp = stList[vertexId].head.next; temp != &stList[vertexId].tail; temp = temp->next)
        {
            stList[temp->val].inDegree--;
            if (0 == stList[temp->val].inDegree) stMinHeap.push(temp->val);
        }
    }
#else
#error "not defined METHOD"
#endif
    return 0;
}