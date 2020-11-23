//https://www.acmicpc.net/problem/5926
#pragma warning(disable: 4996)
#pragma warning(disable: 6031)

#include <stdio.h>
#include <assert.h>
#include <string.h>

const int MAX_NUM_COW = 50000+10;

typedef struct _CowInfo
{
    int x;
    int breedId;
}CowInfo;

CowInfo gstCows[MAX_NUM_COW];
CowInfo gstTemp[MAX_NUM_COW];
int gIdTable[MAX_NUM_COW];

typedef struct _Node
{
    _Node* prev;
    _Node* next;
    int originId;
    int newId;
}Node;
typedef struct _ArrayAllocNodes
{
    Node notUsedNode[MAX_NUM_COW];
    int idx;
    Node* allocNode(int id)
    {
        Node* newNode = &notUsedNode[idx++];
        newNode->originId = id;
        return newNode;
    }
    int id;
}ArrayAllocNodes;

ArrayAllocNodes gstNodes;

typedef struct _List
{
    Node head;
    Node tail;
    _List()
    {
        head.next = &tail;
        tail.prev = &head;
        head.prev = NULL;
        tail.next = NULL;
    }
    int findSameId(int id)
    {
        for (Node* temp = head.next; temp != &tail; temp = temp->next)
        {
            if (id == temp->originId)
            {
                return temp->newId;
            }
        }
        return -1;
    }
    void insert(int id)
    {
        Node* newNode = gstNodes.allocNode(id);
        newNode->newId = gstNodes.id++;
        newNode->prev = &head;
        newNode->next = head.next;
        head.next->prev = newNode;
        head.next = newNode;
    }
}List;

List gstHashTb[MAX_NUM_COW];
void mergeSort(CowInfo* pCows, int s, int e)
{
    if (s >= e) return;

    int m = (s + e) / 2;
    mergeSort(pCows, s, m);
    mergeSort(pCows, m + 1, e);

    int i = s;
    int j = m + 1;
    int k = s;

    while ((i <= m) && (j <= e))
    {
        if (pCows[i].x < pCows[j].x)
        {
            gstTemp[k++] = pCows[i++];
        }
        else
        {
            gstTemp[k++] = pCows[j++];
        }
    }
    while (i <= m) gstTemp[k++] = pCows[i++];
    while (j <= e) gstTemp[k++] = pCows[j++];

    for (int i = s; i <= e; i++)
    {
        pCows[i] = gstTemp[i];
    }
}
int hash(int id)
{
    return (id % MAX_NUM_COW);
}
int getNewId(int id)
{
    int hId = hash(id);
    int findId = gstHashTb[hId].findSameId(id);
    if (-1 == findId)
    {
        gstHashTb[hId].insert(id);
        return gstHashTb[hId].head.next->newId;
    }
    else
    {
        return findId;
    }
}
int main()
{
    freopen("input.txt", "r", stdin);
    int n;
    scanf("%d", &n);
    int uniqueIdCnt = 0;
    for (int i = 0; i < n; i++)
    {
        scanf("%d%d", &gstCows[i].x, &gstCows[i].breedId);
        gstCows[i].breedId = getNewId(gstCows[i].breedId);
        //printf("%d %d\n", gstCows[i].x, gstCows[i].breedId);
        gIdTable[gstCows[i].breedId]++;
        if (1 == gIdTable[gstCows[i].breedId]) uniqueIdCnt++;
    }
    memset(gIdTable, 0, sizeof(gIdTable));
    mergeSort(gstCows, 0, n - 1);

    int s = 0;
    int e = 0;
    int cnt = 0;
    int minSum = 2147483647;

    //2 pointer
    while (e <= n)
    {
        assert(s <= e);
        if (cnt >= uniqueIdCnt)
        {
            int sum = gstCows[e - 1].x - gstCows[s].x;
            if (minSum > sum)
            {
                minSum = sum;
                //printf("s.x=%d, e.x=%d\n", gstCows[s].x, gstCows[e-1].x);
            }
            gIdTable[gstCows[s].breedId]--;
            if (0 == gIdTable[gstCows[s].breedId])
            {
                cnt--;
            }
            s++;
        }
        else
        {
            gIdTable[gstCows[e].breedId]++;
            if (1 == gIdTable[gstCows[e].breedId])
            {
                cnt++;
            }
            e++;
        }
    }
    printf("%d", minSum);
    return 0;
}