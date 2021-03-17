/// === user.cpp ===
#pragma warning(disable: 4996)
#pragma warning(disable: 6031)

#ifndef NULL
#define NULL 0
#endif

int mystrlen(const char* s)
{ 
    int i = 0;
    while (s[i])
    {
        i++;
    }
    return i;
}

int mystrcmp(const char* s, const char* t) {
    while (*s && *s == *t) ++s, ++t;
    return *s - *t;
}

/// s가 t의 접두문자열이면 1을 그렇지 않다면 0을 반환
int prefix(const char* s, const char* t) {
    while (*s && *s == *t) ++s, ++t;
    return *s == 0;
}

/// 문자열 dest에 문자열 src를 복사
void mystrcpy(char* dest, const char* src) {
    while ((*dest++ = *src++));
}

int mystrncmp(char* str1, char* str2, int n)
{
    int i = 0;
    // 한쪽 문자열이 끝날 때까지 또는 n 보다 작을 때 비교 수행
    while (i < n && (str1[i] != '\0' || str2[i] != '\0')) {
        // 문자 같으면 계속 비교
        if (str1[i] == str2[i]) {
            i++;
            continue;
        }
        else if (str1[i] > str2[i]) return 1; // 앞의 문자가 더 크면 1 리턴
        else if (str1[i] < str2[i]) return -1; // 뒤의 문자가 더 크면 -1 리턴

        i++;
    }

    // 어느 한쪽 문자열이 끝나거나 n 갯수만큼 비교한 후
    if (n == i)return 0; //i == n이라면 찾는 갯수 안의 문자는 모두 같음, 0 리턴 
    else if (str1[i] == '\0' && str2[i] == '\0')return 0; //문자열 끝났으면 0 리턴
    else if (str1[i] > str2[i])return 1; //둘 중 하나라도 문자열 남아 있으면 비교
    else return -1;
}

struct data
{
#define STR_LEN (12+1)
    char name[STR_LEN];
    data* parent;
    data* child;
    data* prev;
    data* next;

    data* myAlloc(char _name[], data* _parent, data* _next)
    {
        mystrcpy(name, _name);
        parent = _parent;
        next = _next;
        child = prev = 0;

        if (next) next->prev = this;
        return this;
    }

    void pop()
    {
        if (prev)
            prev->next = next;
        else
            parent->child = next;

        if (next)
            next->prev = prev;
    }
} buf[40000], *root, *cur;

int bn;
int count(data* p, char* name);

void init_user()
{
    bn = 0;
    char tmp[STR_LEN] = "root";
    root = cur = buf[bn++].myAlloc(tmp, buf, 0);
}

void Add_child(char name[])
{
    for (data* p = cur->child; p != 0; p = p->next)
    {
        if (0 == mystrcmp(name, p->name))
            return;
    }
    cur->child = buf[bn++].myAlloc(name, cur, cur->child);
}

/// name[]이 "ALL"인 경우에는 현재 멤버의 모든 자식을 그 후손들과 함께 제거하고 그 수를 반환한다.
/// 그렇지 않은 경우 name[]으로 시작하는 모든 자식을 찾아 그 후손들과 함께 제거하고 그 수를 반환한다.
int Delete(char name[])
{
    if (0 == mystrcmp(name, "ALL"))
        name[0] = 0;

    int cnt = 0;
    int len = mystrlen(name);
    char tmp[STR_LEN] = "";

    for (data* p = cur->child; p != 0; p = p->next)
    {
        if (0 == mystrncmp(p->name, name, len))
        {
            cnt += count(p->child, tmp) + 1;
            p->pop();
        }
    }
    return cnt;
}

/// name[]이 "root"인 경우에는 최상위(root)로 이동한다.
/// name[]이 "parent"인 경우에는 부모 노드로 이동한다.
/// name[]이 "first"인 경우에는 사전순으로 가장 빠른 이름을 가진 자식 노드로 이동한다.
/// 그렇지 않은 경우 name[]으로 시작하는 사전순으로 가장 빠른 이름을 가진 자식 노드로 이동한다.
void Move(char name[])
{
    if (0 == mystrcmp(name, "first"))
        name[0] = 0;
    
    if (0 == mystrcmp(name, "root"))
        cur = root;
    else if (0 == mystrcmp(name, "parent"))
        cur = cur->parent;
    else
    {
        data* q = 0;
        int len = mystrlen(name);
        for (data* p = cur->child; p != 0; p = p->next)
        {
            if (0 != mystrncmp(p->name, name, len))
                continue;
            if (0 == q || mystrcmp(p->name, q->name) < 0) q = p;
        }
        if (q) cur = q;
    }
}

int count(data* p, char* name)
{
    if (0 == p)
        return 0;

    int len = mystrlen(name);
    int cnt = count(p->next, name) + count(p->child, name);

    if (0 == mystrncmp(name, p->name, len)) cnt++;
    return cnt;
}

/// name[]이 "ALL"인 경우에는 현재 멤버의 자식을 포함한 모든 후손들의 수를 반환한다.
/// 그렇지 않은 경우 현재멤버의 자식을 포함한 모든 후손들 중에 name[]으로 시작하는 후손들의 수를 반환한다.
int Count(char name[])
{
    if (0 == mystrcmp(name, "ALL"))
        name[0] = 0;

    return count(cur->child, name);
}