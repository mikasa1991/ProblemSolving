//http://jungol.co.kr/xpert/contestproblem.php?bo_table=prelearning&cid=1475&pid=4&al=005004&stx=4
//주문형 농산물재배
//======== user.cpp ========
#ifndef NULL
#define NULL 0
#endif

extern int add_lot();
extern void assign(int lot_num, int s, int size, int member_id);
extern void back(int lot_num, int s, int size);
extern void grow(int lot_num, int s, int size, int crop);
const int MAXLOT = 100000;

struct data
{
    int lot, st, size;
    data* next;
    data* myAlloc(int _lot, int _st, int _size, data* _next)
    {
        lot = _lot;
        st = _st;
        size = _size;
        next = _next;
        return this;
    }
};
data buf[50000];
data* mem[10010];
int bcnt;
int memSize[10010];
void move(int s, int e);
void push(int id, int lot, int st, int size)
{
    mem[id] = buf[bcnt++].myAlloc(lot, st, size, mem[id]);
}

void init_member()
{
    bcnt = 0;
    for (int i = 0; i <= 10000; i++)
    {
        mem[i] = 0;
        memSize[i] = 0;
    }
}

void assign_member(int id, int size)
{
    memSize[0] = memSize[0] - size;
    memSize[id] = size;

    if (memSize[0] < 0)
    {
        int lot = add_lot();
        push(0, lot, 0, MAXLOT);
        memSize[0] = memSize[0] + MAXLOT;
    }

    while (size > 0)
    {
        if (mem[0]->size > size)
        {
            push(0, mem[0]->lot, mem[0]->st, size);
            mem[0]->next->st = mem[0]->next->st + size;
            mem[0]->next->size = mem[0]->next->size - size;
        }
        size = size - mem[0]->size;
        assign(mem[0]->lot, mem[0]->st, mem[0]->size, id);
        move(0, id);
    }
}

void back_member(int id)
{
    memSize[0] = memSize[0] + memSize[id];
    memSize[id] = 0;
    while (mem[id])
    {
        back(mem[id]->lot, mem[id]->st, mem[id]->size);
        move(id, 0);
    }
}

void grow_member(int id, int crop)
{
    for (data* p = mem[id]; p; p = p->next)
    {
        grow(p->lot, p->st, p->size, crop);
    }
}

void move(int s, int e)
{
    data* tmp = mem[s];
    mem[s] = mem[s]->next;
    tmp->next = mem[e];
    mem[e] = tmp;
}