/*
http://jungol.co.kr/xpert/viewp.php?bo_table=&bo_table&id=3143&sca=30b0
*/

#include <stdio.h>
#define MAXN (1000)
#define STRN (10)
#define CHILD (26)

typedef struct trie 
{
    int cnt;//접두사로 시작하는 개수 파악용
    int leaf;//종단 노드(1) 아니면 (0)
    struct trie * child[CHILD];
}TRIE;

TRIE *root;
int nodeptr;
TRIE node[STRN * MAXN];

TRIE * myalloc() 
{//항상 맨뒤에 추가됨(종단노드)
    TRIE *p = &node[nodeptr++];
    p->cnt = 0; p->leaf = 1;
    for (int i = 0; i < CHILD; i++) p->child[i] = NULL;
    return p;
}

void init() 
{
    nodeptr = 0;
    root = myalloc();
}

int calidx(char ch) 
{
    return ch - 'A';
}

void insertnode(TRIE *p, char *str) 
{
    p->cnt++;//현재 접두사로 시작하는 개수 증가
    if (!*str) return;//문자열 끝났음
    int idx = calidx(*str);
    if (!p->child[idx]) {//해당 자식노드없으면 생성
        p->child[idx] = myalloc();
        p->leaf = 0;//자식노드를 생성했으므로 종단노드 아님
    }
    insertnode(p->child[idx], str + 1);
}

int query(TRIE *p, char *str) {
    if (!*str) return p->cnt;//현재 접두사로 시작하는 개수 리턴
    int idx = calidx(*str);
    if (!p->child[idx]) return 0;//현재 접두사로 시작하는 개수 없음
    return query(p->child[idx], str + 1);
}

void solve() {
    int N; char cmd; char str[STRN];
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf(" %c %s", &cmd, str);
        if (cmd == 'I') insertnode(root, str);
        else printf("%d ", query(root, str));
    }
    printf("\n");
}

int main() 
{
    int T;
#if 1
    freopen("input.txt", "r", stdin);
#endif
    scanf("%d", &T);
    for (int t = 1; t <= T; t++) 
    {
        init();
        solve();
    }
    return 0;
}