///*** user.cpp ***
#ifndef NULL
#define NULL 0
#endif

#define DELETE_MODE (-1)
#define INSERT_MODE (1)
struct Node
{
    char ch;
    Node* prev;
    Node* next;

    void alloc(char ch, Node* prev, Node* next)
    {
        this->ch = ch;
        this->prev = prev;
        this->next = next;
        this->prev->next = this;
        this->next->prev = this;
    }
    void pop()
    {
        prev->next = next;
        next->prev = prev;
    }
};
Node buf[101000];
Node* head;
Node* tail;
Node* cur;

int bn;
int mode;
int undoCnt;

void undoDel()
{
    //undoCnt만큼 삭제하자. 커서 앞을.
    while (undoCnt-- && cur->prev != head)
    {
        cur->prev->pop();
    }
}

void initUser()
{
    head = buf;
    cur = buf + 1;
    tail = cur;

    head->next = tail;
    tail->prev = head;
    bn = 2;
    undoCnt = 0;
    mode = 0;
}

void Insert(int len, char str[])
{
    if (mode == DELETE_MODE) undoDel();
    if (mode != INSERT_MODE)
    {
        mode = INSERT_MODE;
        undoCnt = 0;
    }
    undoCnt += len;
    for (int i = 0; i < len; i++)
    {
        buf[bn++].alloc(str[i], cur->prev, cur);
    }
}

void Backspace(int len)
{
    if (mode != DELETE_MODE)
    {
        mode = DELETE_MODE;
        undoCnt = 0;
    }
    undoCnt += len;
}

void Delete(int len)
{
    if (mode != DELETE_MODE)
    {
        mode = DELETE_MODE;
        undoCnt = 0;
    }
    while (len-- && cur != tail)
    {
        cur = cur->next;
        undoCnt++;
    }
}

void moveForward(int moveCnt)
{
    if (mode == DELETE_MODE) undoDel();
    mode = 0;
    while (moveCnt-- && cur->prev != head)
    {
        cur = cur->prev;
    }
}

void moveBackward(int moveCnt)
{
    if (mode == DELETE_MODE) undoDel();
    mode = 0;
    while (moveCnt-- && cur != tail)
    {
        cur = cur->next;
    }
}

void Undo()
{
    mode = -mode;
}

void getString(int stPos, int len, char str[])
{
    if (mode == DELETE_MODE) undoDel();
    mode = 0;
    Node* pNode;
    for (pNode = head->next; pNode != tail && stPos; pNode = pNode->next)
    {
        stPos--;
    }
    int i;
    for (i = 0; i < len && pNode != tail; i++, pNode = pNode->next)
    {
        str[i] = pNode->ch;
    }
}