//
#pragma warning(disable: 4996)
#pragma warning(disable: 6031)

#include <stdio.h>
#include <assert.h>

#define MAX_MEMBER ((int)1e5+10)
#define EXIST      (1)
#define NOT_EXIST  (0)

struct member
{
    int freq;
    int bExist;

    void init()
    {
        freq = 0;
        bExist = 0;
    }

    void setter(int freq, int bExist)
    {
        this->freq = freq;
        this->bExist = bExist;
    }
};
int gSum;
int gCnt;
member gMemberTb[MAX_MEMBER];
struct heap
{
#define PARENT(a) ((a - 1) / 2)
    int heap[MAX_MEMBER];
    int heapSize = 0;

    void init(void)
    {
        heapSize = 0;
    }

    int compare(int aId, int bId, int para)
    {
#define MIN_HEAP (0)
#define MAX_HEAP (1)
        int bRet = 0;
        if (gMemberTb[aId].freq < gMemberTb[bId].freq)
        {
            bRet = 1;
        }
        else if (gMemberTb[aId].freq > gMemberTb[bId].freq)
        {
            /* do nothing */
        }
        else
        {
            if (aId < bId)
            {
                bRet = 1;
            }
            else // (aId > bId)
            {
                /* do nothing */
            }
        }

        if (MAX_HEAP == para)
        {
            if (1 == bRet)
                bRet = 0;
            else
                bRet = 1;
        }
        return bRet;
    }

    int push(int value, int para)
    {
        if (heapSize + 1 > MAX_MEMBER)
        {
            printf("queue is full!");
            return 0;
        }

        heap[heapSize] = value;

        int current = heapSize;
        while (current > 0 && compare(heap[current], heap[PARENT(current)], para))
        {
            int temp = heap[PARENT(current)];
            heap[PARENT(current)] = heap[current];
            heap[current] = temp;
            current = PARENT(current);
        }

        heapSize = heapSize + 1;

        return 1;
    }

    int pop(int* value, int para)
    {
#define LEFT_CHILD(a)  (a * 2 + 1)
#define RIGHT_CHILD(a) (a * 2 + 2)
        if (heapSize <= 0)
        {
            return 0;
        }

        *value = heap[0];
        heapSize = heapSize - 1;

        heap[0] = heap[heapSize];

        int current = 0;
        while (LEFT_CHILD(current) < heapSize)
        {
            int child;
            if (RIGHT_CHILD(current) == heapSize)
            {
                child = LEFT_CHILD(current);
            }
            else
            {
                child = compare(heap[LEFT_CHILD(current)], heap[RIGHT_CHILD(current)], para) ? LEFT_CHILD(current) : RIGHT_CHILD(current);
            }

            if (compare(heap[current], heap[child], para))
            {
                break;
            }

            int temp = heap[current];
            heap[current] = heap[child];
            heap[child] = temp;

            current = child;
        }
        return 1;
    }

    void goToTop(int para)
    {
        while (NOT_EXIST == gMemberTb[heap[0]].bExist && heapSize > 0)
        {
            int temp;
            if (MAX_HEAP == para)
                pop(&temp, MAX_HEAP);
            else
                pop(&temp, MIN_HEAP);
        }
    }
};

heap gMaxHeap;
heap gMinHeap;

void init()
{
    for (int i = 0; i < MAX_MEMBER; i++)
    {
        gMemberTb[i].init();
    }
    gMaxHeap.init();
    gMinHeap.init();
    gSum = 0;
    gCnt = 0;
}

void addMember(int id, int freq)
{
    gMemberTb[id].setter(freq, EXIST);
    gMaxHeap.push(id, MAX_HEAP);
    gMinHeap.push(id, MIN_HEAP);
    gSum += freq;
    gCnt++;
}

void removeMemberLow()
{
    gMinHeap.goToTop(MIN_HEAP);
    int id;
    if (gMinHeap.pop(&id, MIN_HEAP))
    {
        gMemberTb[id].bExist = NOT_EXIST;
        gSum -= gMemberTb[id].freq;
        gCnt--;
        printf("%d\n", id);
    }
    else
    {
        /* do nothing */
    }
}

void removeMemberHigh()
{
    gMaxHeap.goToTop(MAX_HEAP);
    int id;
    if (gMaxHeap.pop(&id, MAX_HEAP))
    {
        gMemberTb[id].bExist = NOT_EXIST;
        gSum -= gMemberTb[id].freq;
        gCnt--;
        printf("%d\n", id);
    }
    else
    {
        /* do nothing */
    }
}

int getSum()
{
    if (gCnt > 2)
    {
        //각 heap에 heapData는 gCnt상으로 존재한다.
        gMaxHeap.goToTop(MAX_HEAP);
        gMinHeap.goToTop(MIN_HEAP);
        int maxFreq = gMemberTb[gMaxHeap.heap[0]].freq;
        int minFreq = gMemberTb[gMinHeap.heap[0]].freq;
        return gSum - maxFreq - minFreq;
    }
    else
    {
        return 0;
    }
}

int main()
{
    freopen("input.txt", "r", stdin);
    int N, M;
    scanf("%d%d", &N, &M);
    init();
    for (int i = 0; i < M; i++)
    {
        int mode;
        scanf("%d", &mode);

        switch (mode)
        {
        case 0:
            int id, freq;
            scanf("%d%d", &id, &freq);
            addMember(id, freq);
            break;
        case 1:
            removeMemberLow();
            break;
        case 2:
            removeMemberHigh();
            break;
        case 3:
            printf("%d\n", getSum());
            break;
        default:
            break;
        }
    }

    return 0;
}