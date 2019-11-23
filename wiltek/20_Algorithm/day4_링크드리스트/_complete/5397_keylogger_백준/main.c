/*
https://www.acmicpc.net/problem/5397
*/

/*
첫째 줄에 테스트 케이스의 개수가 주어진다. 
각 테스트 케이스는 한줄로 이루어져 있고, 강산이가 입력한 순서대로 길이가 L인 문자열이 주어진다. 
(1 ≤ L의 길이 ≤ 1,000,000) 

강산이가 백스페이스를 입력했다면, '-'가 주어진다. 이때 커서의 바로 앞에 글자가 존재한다면, 그 글자를 지운다. 
화살표의 입력은 '<'와 '>'로 주어진다. 이때는 커서의 위치를 움직일 수 있다면, 왼쪽 또는 오른쪽으로 1만큼 움직인다. 
나머지 문자는 비밀번호의 일부이다. 물론, 나중에 백스페이스를 통해서 지울 수는 있다. 
만약 커서의 위치가 줄의 마지막이 아니라면, 그 문자를 입력하고, 커서는 오른쪽으로 한 칸 이동한다.

각 테스트 케이스에 대해서, 강산이의 비밀번호를 출력한다. 비밀번호의 길이는 항상 0보다 크다.
*/

#include <stdio.h>

#define DEBUG 1
#define MAXN ((int)1e6 + 10)

char str[MAXN];
typedef struct node 
{
    char ch;
    struct node *prev;
    struct node *next;
}NODE;
NODE head, tail;
NODE *cur;

int nptr;
NODE tnode[MAXN];

NODE *myalloc(char ch)
{
	NODE *new_node = &tnode[nptr++];
	new_node->ch = ch;
	new_node->next = NULL;
	new_node->prev = NULL;
	return new_node;
}

void insert_InFrontOf_cur(char ch) 
{//추가함수
    NODE* new_node = myalloc(ch);
    new_node->next = cur;
    new_node->prev = cur->prev;
    cur->prev->next = new_node;
    cur->prev = new_node;
}

void left() 
{//커서 왼쪽으로 이동
    if (cur->prev == &head) return;//맨 앞임, 무시
    //if (cur == &head) return;//head앞에 삽입하는건 말이 안되니까
    cur = cur->prev;
}

void right() 
{//커서 오른쪽으로 이동
    if (cur == &tail) return;//맨 뒤임, 무시
    cur = cur->next;
}

void del() 
{//커서 왼쪽문자 지우기
    if (cur->prev == &head) return;//맨 앞임, 무시
    NODE *p = cur->prev;
    p->prev->next = p->next; 
    p->next->prev = p->prev;
}

void PRT() 
{//남은 모든 문자 출력
    int i = 0;
    for (NODE *p = head.next; p != &tail; p = p->next) 
    {
        str[i++] = p->ch;
    }
    str[i] = 0;
    printf("%s\n", str);
}

void init()
{
	head.next = &tail; 
    tail.prev = &head; 
    cur = &tail; 
    nptr = 0;
}

void solve() 
{
    for (int i = 0; str[i]; i++) 
    {
        switch (str[i]) 
        {
        case '-':			//글자지우기
            del();
            break;

        case '<':			//커서 왼쪽이동
            left();
            break;

        case '>':			//커서 오른쪽이동
            right();
            break;

        default:			//글자추가
            insert_InFrontOf_cur(str[i]);
        }
    }
    PRT();
}

int main() 
{
#ifdef DEBUG
	freopen("input.txt", "r", stdin);
#endif
    int T;
    scanf("%d", &T);
    for (int tc = 1; tc <= T; tc++) 
    {
        scanf("%s", str);
        
        init();
        solve();
    }
    return 0;
}