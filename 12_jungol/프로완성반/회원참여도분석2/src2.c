/// === sol.cpp ===
#ifndef NULL
#define NULL  0
#endif
 
struct Member{
    int id, frequency;
};

/// === submit area start ===
const int LM = (int)1e5;
int frr[LM + 5];
int active[LM + 5];
int fcnt, fsum, bcnt, bsum;

bool min(int aid, int bid)
{
    if (frr[aid] != frr[bid])
        return frr[aid] < frr[bid];
    else
        return aid < bid;
}

bool max(int aid, int bid)
{
    if (frr[aid] != frr[bid])
        return frr[aid] > frr[bid];
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
        comp = cmd ? max : min;
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
}minpq, front, back, maxpq;

void addMember(Member obj){
    int id = obj.id;
    active[id] = 1;
    frr[id] = obj.frequency;
    minpq.push(id);
    maxpq.push(id);
    front.top(); //max heap
    back.top();  //min heap

    if (fcnt + bcnt == 0 || min(id, front.top()))
    {
        front.push(id);
        fcnt++;
        fsum += obj.frequency;
    }
    else
    {
        back.push(id);
        bcnt++;
        bsum += obj.frequency;
    }

    while (fcnt > bcnt + 1)
    {
        id = front.top();
        front.pop();
        fcnt--;
        fsum -= frr[id];
        back.push(id);
        bcnt++;
        bsum += frr[id];
    }
    while (fcnt < bcnt)
    {
        id = back.top();
        back.pop();
        bcnt--;
        bsum -= frr[id];
        front.push(id);
        fcnt++;
        fsum += frr[id];
    }
}
 
int removeMembers(int mode){
    int sid = 0;
    int eid = 0;
    if (mode == 0)
    {
        sid = minpq.top();
        minpq.pop();
        active[sid] = 0;
        fcnt--;
        fsum -= frr[sid];
    }
    else if (mode == 1)
    {
        if (fcnt == bcnt)
        {
            eid = back.top();
            back.pop();
            active[eid] = 0;
            bcnt--;
            bsum -= frr[eid];
        }
        sid = front.top();
        front.pop();
        active[sid] = 0;
        fcnt--;
        fsum -= frr[sid];
    }
    else
    {
        eid = maxpq.top();
        maxpq.pop();
        active[eid] = 0;
        bcnt--;
        bsum -= frr[eid];
    }
    return sid + eid;
}
 
void getSum(int sum[]){
    sum[0] = fsum;
    sum[1] = bsum;
    if (fcnt > bcnt)
    {
        int id = front.top();
        sum[0] -= frr[id];
    }
}
 
void userInit(int memberCount, Member members[]){
    fcnt = 0;
    fsum = 0;
    bcnt = 0;
    bsum = 0;
    for (int i = 0; i < LM; ++i)
    {
        active[i] = 0;
    }

#define MIN_HEAP (0)
#define MAX_HEAP (1)
    minpq.init(MIN_HEAP);
    back.init(MIN_HEAP);
    
    front.init(MAX_HEAP);
    maxpq.init(MAX_HEAP);
    for (int i = 0; i < memberCount; ++i)
    {
        addMember(members[i]);
    }
}
 
/// === submit area end ===