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
    bool bChecked;
}Node;
Node gstNotUsedNode[STR_CNT];
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
int hash(char* str)
{
    int sum = 0;
    for (char* ch = str; *ch != NULL; ch++)
    {
        sum = sum + *ch;
    }
    return (sum % STR_CNT);
}
List gstHashTb[STR_CNT];
int main()
{
    freopen("input.txt", "r", stdin);
    int N;
    scanf("%d", &N);
    //printf("N=%d, insert hashTb\n", N);
    for (int i = 0; i < N; i++)
    {
        scanf("%s", STR[i]);
        int hid = hash(STR[i]);
        //printf("%s, hid=%d\n", STR[i], hid);
        gstHashTb[hid].insert(STR[i], i+1);
    }

    bool bUnique = true;
    for (int i = 0; i < N; i++)
    {
        //printf("input: %d %s\n", i + 1, STR[i]);
        int hid = hash(STR[i]);
        int firstIndex = 0;
        for (Node* stTemp = gstHashTb[hid].head.next; stTemp != &gstHashTb[hid].tail; stTemp = stTemp->next)
        {
            //문자열이 일치한다면? 해당노드에 check 표시를 한다.
                //이미 checked된 문자열이라면? 해당 List를 더 이상 순회하지 않는다.
                //else:
                    //처음으로 일치한다면? firstIndex에 index값을 쓴다. firstIndex > 0
                    //두번째로 일치한다면?
                    //그 이상으로 일치한다면?
            //else: 다음 node로 넘어간다.
            //List 순회에 끝에 도달했으며, 해당 문자열이 동일 문자열이 있었다면? 출력문 한칸 뛴다.
            if (0 == strcmp(STR[i], stTemp->str))
            {
                if (true == stTemp->bChecked) break;
                if (0 == firstIndex)
                {
                    firstIndex = stTemp->id;
                }
                else if (firstIndex > 0)
                {
                    printf("%s %d %d", stTemp->str, firstIndex, stTemp->id);
                    firstIndex = -1;
                    bUnique = false;
                }
                else
                {
                    printf(" %d", stTemp->id);
                }
                stTemp->bChecked = true;
            }
            if (stTemp->next == &gstHashTb[hid].tail && firstIndex < 0) printf("\n");
        }
    }
    if (true == bUnique)
    {
        printf("unique");
    }
    return 0;
}