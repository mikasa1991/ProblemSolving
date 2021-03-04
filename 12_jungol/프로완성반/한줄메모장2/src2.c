///*** user.cpp ***
#ifndef NULL
#define NULL 0
#endif

#define INSERT_MODE (1)
#define DELETE_MODE (-1)

int bn;
int mode;
int undoCnt;

struct Node
{
    int len;
    char str[32 + 1];
    Node* prev;
    Node* next;

    // _prev와 _next 사이에 node를 할당한다.
    void alloc(int _len, char* _str, Node* _prev, Node* _next)
    {
        len = _len;
        prev = _prev;
        next = _next;
        for (int i = 0; i < len; i++)
        {
            str[i] = _str[i];
        }
        prev->next = this;
        next->prev = this;
    }

    // 현재 노드를 떼서, _prev와 _next 사이로 이동시킨다.
    void move(Node* _prev, Node* _next)
    {
        prev->next = next;
        next->prev = prev;
        prev = _prev;
        next = _next;
        prev->next = this;
        next->prev = this;
    }

    // 현재 노드 뒤에 할당한다.
    void devide(int _len, Node buf[])
    {
        len -= _len;
        buf[bn++].alloc(_len, str + len, this, next);
        str[len] = 0;
    }
};

Node buf[101000];
Node* head;
Node* tail;
Node* cur;
Node* delHead;
Node* delTail;

void initUser()
{
    head = buf;
    tail = buf + 1;
    cur = tail;
    delHead = buf + 2;
    delTail = buf + 3;
    head->next = tail;
    tail->prev = head;

    bn = 4;
    mode = 0;
    undoCnt = 0;
}

void Insert(int len, char str[])
{
    if (INSERT_MODE != mode)
    {
        mode = INSERT_MODE;
        undoCnt = 0;
    }
    undoCnt++;
    buf[bn++].alloc(len, str, cur->prev, cur);
}

void Backspace(int count)
{
    if (mode != DELETE_MODE)
    {
        mode = DELETE_MODE;
        delHead->next = delTail;
        delTail->prev = delHead;
    }

    while (count && cur->prev != head)
    {
        if (cur->prev->len > count)
        {
            cur->prev->devide(count, buf);
        }
        count -= cur->prev->len;
        cur->prev->move(delHead, delHead->next);
    }
}

void Delete(int count)
{
    if (mode != DELETE_MODE)
    {
        mode = DELETE_MODE;
        delHead->next = delTail;
        delTail->prev = delHead;
    }
    while (count && cur != tail)
    {
        if (cur->len > count)
        {
            cur->devide(cur->len - count, buf);
        }
        count -= cur->len;
        cur = cur->next;
        cur->prev->move(delTail->prev, delTail);
    }
}

void moveForward(int moveCnt)
{
    mode = 0;
    while (moveCnt && cur->prev != head)
    {
        if (cur->prev->len > moveCnt)
        {
            cur->prev->devide(moveCnt, buf);
        }
        moveCnt -= cur->prev->len;
        cur = cur->prev;
    }
}

void moveBackward(int moveCnt)
{
    mode = 0;
    while (moveCnt && cur != tail)
    {
        if (cur->len > moveCnt)
        {
            cur->devide(cur->len - moveCnt, buf);
        }
        moveCnt -= cur->len;
        cur = cur->next;
    }
}

void Undo()
{
    if (INSERT_MODE == mode)
    {
        mode = DELETE_MODE;
        delHead->next = delTail;
        delTail->next = delHead;
        while (undoCnt--)
        {
            cur->prev->move(delHead, delHead->next);
        }
    }
    else if (DELETE_MODE == mode)
    {
        mode = INSERT_MODE;
        undoCnt = 0;
        while (delHead->next != delTail)
        {
            delHead->next->move(cur->prev, cur);
            undoCnt++;
        }
    }
}

void getString(int stPos, int len, char str[])
{
    mode = 0;
    Node* p = head->next;
    while (stPos && p != tail)
    {
        if (p->len > stPos)
        {
            p->devide(p->len - stPos, buf);
        }
        stPos -= p->len;
        p = p->next;
    }

    int i, k = 0;
    while (k < len && p != tail)
    {
        for (i = 0; i < p->len && k < len; i++, k++)
        {
            str[k] = p->str[i];
        }
        p = p->next;
    }
    str[k] = 0;
}