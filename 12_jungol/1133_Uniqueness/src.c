//http://www.jungol.co.kr/bbs/board.php?bo_table=pbank&wr_id=413&sca=99&sfl=wr_hit&stx=1133
#pragma warning(disable: 4996)
#pragma warning(disable: 6031)

#include <stdio.h>
#include <assert.h>
#include <string.h>

const int STR_CNT = 10000 + 10;
const int STR_LEN = 20 + 1;
char STR[STR_CNT][STR_LEN];

typedef struct _Node
{
    _Node* prev;
    _Node* next;
    char str[STR_LEN];
    int id;
}Node;
Node gstNotUsedNode[STR_CNT*2];
int gIdx;
typedef struct _List
{
    Node head;
    Node tail;
    _List()
    {
        head.prev = NULL;
        head.next = &tail;
        tail.prev = &head;
        tail.next = NULL;
    }
    void insert(char* str, int id)
    {
        Node* newNode = &gstNotUsedNode[gIdx++];
        strcpy(newNode->str, str);
        newNode->id = id;
        newNode->prev = tail.prev;
        newNode->next = &tail;
        tail.prev->next = newNode;
        tail.prev = newNode;
    }
}List;
List gstHashTb[STR_CNT];
List gstTb[STR_CNT];
int hash(char* str)
{
    int sum = 0;
    for (char* ch = str; *ch != NULL; ch++)
    {
        sum = sum + *ch;
    }
    return (sum % STR_CNT);
}
int gNewId;
int getNewId(char* str)
{
    int id = hash(str);
    for (Node* stTemp = gstHashTb[id].head.next; stTemp != &gstHashTb[id].tail; stTemp = stTemp->next)
    {
        if (0 == strcmp(stTemp->str, str))
            return stTemp->id;
    }

    gNewId++;
    gstHashTb[id].insert(str, gNewId);
    return gNewId;
}
int main()
{
    freopen("input.txt", "r", stdin);
    int N;
    scanf("%d", &N);
    for (int i = 1; i <= N; i++)
    {
        scanf("%s", STR[i]);
        int id = getNewId(STR[i]);
        gstTb[id].insert(STR[i], i);
        //printf("%s, id=%d\n", STR[i], id);
    }

    if (N <= gNewId) printf("unique");
    else
    {
        for (int i = 1; i <= gNewId; i++)
        {
            for (Node* stTemp = gstTb[i].head.next; stTemp != &gstTb[i].tail; stTemp = stTemp->next)
            {
                if (gstTb[i].head.next->next == &gstTb[i].tail) continue;
                if (stTemp == gstTb[i].head.next)
                {
                    printf("%s %d", stTemp->str, stTemp->id);
                }
                else
                {
                    printf(" %d", stTemp->id);
                    if (stTemp->next == &gstTb[i].tail) printf("\n");
                }
            }
        }
    }
    return 0;
}