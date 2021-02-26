// http://jungol.co.kr/xpert/contestproblem.php?bo_table=prelearning&cid=1475&pid=1&al=005004&stx=1
// No. A : 스택 (stack)
#pragma warning(disable: 4996)
#pragma warning(disable: 6031)

#include <stdio.h>
#include <malloc.h>
#include <assert.h>

class Stack
{
public:
    int arr[100 + 1];
    int top;
public:
    Stack()
    {
        for (int i = 0; i < 100 + 1; i++)
        {
            arr[i] = 0;
        }
        top = 0;
    }
    void push(int num)
    {
        arr[top++] = num;
    }
    int getDataCnt()
    {
        assert(top >= 0);
        return top;
    }
    int pop()
    {
        assert(top > 0);
        int num = arr[--top];
        return num;
    }
};

int main()
{
    freopen("input.txt", "r", stdin);
    int n;
    scanf("%d", &n);

    Stack stack;
    for (int i = 0; i < n; i++)
    {
        char str[2];
        scanf("%s", str);
        switch (str[0])
        {
        case 'i':
        {
            int b;
            scanf("%d", &b);
            stack.push(b);
        }
            break;
        case 'o':
        {
            if (0 == stack.getDataCnt())
            {
                printf("empty\n");
            }
            else
            {
                int num = stack.pop();
                printf("%d\n", num);
            }
        }
            break;
        case 'c':
            printf("%d\n", stack.getDataCnt());
            break;
        default:
            break;
        }
    }
    return 0;
}