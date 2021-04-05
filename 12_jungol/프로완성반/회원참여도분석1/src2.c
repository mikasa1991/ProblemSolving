//
#pragma warning(disable: 4996)
#pragma warning(disable: 6031)

const int LM = (int)1e5;
int N;
int M;
int total;
int memberCnt;
int freq[LM + 5];
int active[LM + 5];

inline bool minBool(int aid, int bid)
{
    if (freq[aid] != freq[bid])
        return freq[aid] < freq[bid];
    else
        return aid < bid;
}

inline bool maxBool(int aid, int bid)
{
    if (freq[aid] != freq[bid])
        return freq[aid] > freq[bid];
    else
        return aid > bid;
}

void swap(int& a, int& b)
{
    int t = a;
    a = b;
    b = t;
}

struct PriorityQueue
{
    int heap[LM + 10];
    int hn;
    bool (*comp)(int, int);
    void init(int cmd)
    {
        hn = 0;
        comp = cmd ? maxBool : minBool;
    }
    int size()
    {
        return hn;
    }
    bool empty()
    {
        return hn == 0;
    }
    int top()
    {
        while (hn && 0 == active[heap[1]])
            pop();

        if (0 == hn)
            return LM;

        return heap[1];
    }
    void push(int id)
    {
        heap[++hn] = id;
        for (int c = hn; c > 1 && comp(heap[c], heap[c / 2]); c /= 2)
        {
            swap(heap[c], heap[c / 2]);
        }
    }
    void pop()
    {
        swap(heap[1], heap[hn--]);
        int p = 1;
        int c = 2;
        for (; c <= hn; p = c, c *= 2)
        {
            if (c < hn && comp(heap[c + 1], heap[c]))
                c++;
            if (!comp(heap[c], heap[p]))
                break;
            swap(heap[c], heap[p]);
        }
    }
}minH, maxH;

#include <stdio.h>
#include <assert.h>

int main()
{
    freopen("input.txt", "r", stdin);
    minH.init(0);
    maxH.init(1);
    scanf("%d%d", &N, &M);
    int i, cmd, id, fq;

    for (i = 0; i < M; ++i)
    {
        scanf("%d", &cmd);
        switch (cmd)
        {
        case 0:
            scanf("%d%d", &id, &fq);
            memberCnt++;
            active[id] = 1;
            freq[id] = fq;
            total += fq;
            minH.push(id);
            maxH.push(id);
            break;
        case 1:
            id = minH.top();
            if (0 == active[id])
                continue;
            memberCnt--;
            active[id] = 0;
            total -= freq[id];
            printf("%d\n", id);
            break;
        case 2:
            id = maxH.top();
            if (0 == active[id])
                continue;
            memberCnt--;
            active[id] = 0;
            total -= freq[id];
            printf("%d\n", id);
            break;
        case 3:
            int ret = 0;
            if (memberCnt > 2)
            {
                id = maxH.top();
                int tid = minH.top();
                ret = total - freq[id] - freq[tid];
            }
            printf("%d\n", ret);
        }
    }
    return 0;
}