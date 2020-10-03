//https://www.algospot.com/judge/problem/read/BRACKETS2
#pragma warning(disable: 4996)
#pragma warning(disable: 6031)

#include <stdio.h>
#include <assert.h>
#include <string.h>
const int MAX_STRLEN = (10000 + 10);

typedef struct _Stack
{
    int top;
    char arr[MAX_STRLEN];
    void init()
    {
        top = -1;
    }
    bool isEmpty()
    {
        return (top == -1);
    }
    bool isFull()
    {
        return (top == MAX_STRLEN - 1);
    }
    char peek()
    {
        assert(false == isEmpty());
        return arr[top];
    }
    void push(char cVal)
    {
        assert(false == isFull());
        top++;
        arr[top] = cVal;
    }
    void pop()
    {
        assert(false == isEmpty());
        top--;
    }
}Stack;

bool isOpenBracket(char cha)
{
    return (('(' == cha) || ('{' == cha) || ('[' == cha));
}

bool isCoupledBrackets(char cha, Stack* pstStack)
{
    bool bRet = false;

    switch (cha)
    {
    case ')':
        if ('(' == pstStack->peek()) bRet = true;
        break;
    case '}':
        if ('{' == pstStack->peek()) bRet = true;
        break;
    case ']':
        if ('[' == pstStack->peek()) bRet = true;
        break;
    default:
        assert(0);
    }
    return bRet;
}

bool IsSolved(char* str)
{
    Stack stStack;
    stStack.init();
    for (int j = 0; j < strlen(str); j++)
    {
        if (isOpenBracket(str[j])) stStack.push(str[j]);
        else //IsCloseBracket
        {
            if (stStack.isEmpty()) return false;

            if (isCoupledBrackets(str[j], &stStack)) stStack.pop();
            else break;
        }
    }
    return stStack.isEmpty();
}

int main()
{
    freopen("input.txt", "r", stdin);
    int C;
    scanf("%d", &C);
    char str[MAX_STRLEN];
    for (int i = 0; i < C; i++)
    {
        scanf("%s", str);
        //printf("%s\n", str);
        //printf("%d\n", strlen(str));
        if (true == IsSolved(str)) printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}