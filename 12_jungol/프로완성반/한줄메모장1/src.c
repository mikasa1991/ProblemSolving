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
 
    Node* alloc(char ch)
    {
        this->ch = ch;
        this->prev = NULL;
        this->next = NULL;
        return this;
    }
    void pop()
    {
        prev->next = next;
        next->prev = prev;
    }
};
Node buf[101000];
Node head;
Node tail;
Node* cur;
 
int bn;
int mode;
int undoCnt;
 
void undoDel()
{
    //undoCnt만큼 삭제하자. 커서 앞을.
    while (undoCnt-- && cur->prev != &head)
    {
        cur->prev->pop();
    }
}
 
void initUser()
{
    head.next = &tail;
    tail.prev = &head;
    cur = &tail;
 
    bn = 0;
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
        Node* pNode = buf[bn++].alloc(str[i]);
        pNode->prev = cur->prev;
        pNode->next = cur;
        pNode->prev->next = pNode;
        pNode->next->prev = pNode;
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
 
    //delete는 cursor를 기준으로 뒤로 len만큼 삭제하는 것인데,
    //undoDel은 cursor를 기준으로 앞으로 len만큼 삭제하고 있다.
    //따라서, undoDel을 사용하려면, 여기서 cursor를 뒤로 보내줘야한다.
    while (len-- && cur != &tail)
    {
        cur = cur->next;
        undoCnt++;
    }
}
 
void moveForward(int moveCnt)
{
    if (mode == DELETE_MODE) undoDel();
    mode = 0;
 
    while (moveCnt-- && cur->prev != &head)
    {
        cur = cur->prev;
    }
}
 
void moveBackward(int moveCnt)
{
    if (mode == DELETE_MODE) undoDel();
    mode = 0;
 
    while (moveCnt-- && cur != &tail)
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
 
    // stPos에 해당하는 pNode를 찾는다.
    Node* pNode;
    for (pNode = head.next; (pNode != &tail) && stPos; pNode = pNode->next)
    {
        stPos--;
    }
 
    // stPos부터 len만큼의 문자를 str에 넣는다.
    for (int i = 0; (i < len) && (pNode != &tail); i++, pNode = pNode->next)
    {
        str[i] = pNode->ch;
    }
}