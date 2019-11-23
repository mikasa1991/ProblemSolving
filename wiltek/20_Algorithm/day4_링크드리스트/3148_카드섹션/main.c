
#if 01
/**************************************************************
    Problem: 3148
    User: dong_hee.lee
    Language: C
    Result: Success
    Time:36 ms
    Memory:18244 kb
****************************************************************/
 
//(정올 실전문제:3148)카드섹션
#pragma warning (disable : 4996)
#include <stdio.h>
#define MAXM ((int)1e4 + 1)
#define MAXN ((int)1e3)
typedef struct node {
    int id;
    struct node *prev, *next;
}NODE;
NODE head, tail;//dummy node (섹션 순서 저장용)
int ptr;
NODE dnode[MAXM];
NODE *myalloc(int id, NODE *cur) {//cur앞에 추가
    NODE *p = &dnode[ptr++];
    p->id = id; p->next = cur; p->prev = cur->prev; p->prev->next = p;
    return p;
}
typedef struct section {
    int r, c, h, w; char color[40 * 40 + 4];
    NODE *p;//작업 순서에 저장된 주소
}SECT;
SECT sect[MAXM];
void strcopy(char *dst, char *src) {
    while (*dst++ = *src++);
}
void Init() {
    ptr = 0;
    head.next = &tail; tail.prev = &head;
}
void addsection(int id, int r, int c, int h, int w, char *str) {
    sect[id].r = r; sect[id].c = c; sect[id].h = h; sect[id].w = w;
    strcopy(sect[id].color, str);
    sect[id].p = tail.prev = myalloc(id, &tail);//마지막 순서에 추가
}
void delsecion(int id) {
    NODE *p = sect[id].p;//지울 노드 주소
    p->prev->next = p->next; p->next->prev = p->prev;//지울 노드 앞뒤노드가 서로 가르키게 변경
    sect[id].p = NULL;
}
void movesection(int id) {
    NODE *p = sect[id].p;//자리 이동할 노드 주소
    //이전 위치의  앞뒤노드가 서로 가르키게 변경(그 자리에서 빠지기)
    p->prev->next = p->next; p->next->prev = p->prev;
    //마지막 작업으로 추가(tail.prev에 추가)
    p->prev = tail.prev; p->next = &tail; 
    p->prev->next = p->next->prev = p;
}
char prt[MAXN][MAXN];
void PRT(int sr, int sc, int er, int ec) {
    //초기화
    for (register int r = sr; r < er; r++) {
        for (register int c = sc; c < ec; c++) {
            prt[r][c] = '0';
        }
    }
    //갱신
    for (NODE *p = head.next; p != &tail; p = p->next) {
        int id = p->id;
        if ((sect[id].r >= er) || (sect[id].r + sect[id].h <= sr)) continue;//출력 영역과 관련없는 섹션
        if ((sect[id].c >= ec) || (sect[id].c + sect[id].w <= sc)) continue;//출력 영역과 관련없는 섹션
        int k = 0;
        for (register int r = sect[id].r; r < sect[id].r + sect[id].h; r++) {
            for (register int c = sect[id].c; c < sect[id].c + sect[id].w; c++) {
                prt[r][c] = sect[id].color[k++];
            }
        }
    }
    //인쇄
    for (register int r = sr; r < er; r++) {
        for (register int c = sc; c < ec; c++) {
            printf("%c", prt[r][c]);
        }
    }
    printf("\n");
}
void solve() {
    int N, M;
    int cmd; int id, r, c, h, w; char str[40 * 40 + 4];
    scanf("%d %d", &N, &M);
    Init();
    for (register int i = 1; i <= M; i++) {//작업 정보
        scanf("%d", &cmd);
        switch (cmd) {
        case 1://섹션 추가
            scanf("%d %d %d %d %d %s", &id, &r, &c, &h, &w, str);
            addsection(id, r, c, h, w, str);
            break;
        case 2://섹션 제거
            scanf("%d", &id);
            delsecion(id);
            break;
        case 3://섹션 순서 마지막 순서로 변경
            scanf("%d", &id);
            movesection(id);
            break;
        case 4://섹션 이동 및 마지막 순서로 변경
            scanf("%d %d %d", &id, &r, &c);
            sect[id].r = r; sect[id].c = c;
            movesection(id);
            break;
        default://출력
            scanf("%d %d", &r, &c);
            PRT(r, c, r + 4, c + 4);
        }
    }
}
int main() {
    int T;
#if 1
    freopen("input.txt", "r", stdin);
#endif
    scanf("%d", &T);
    for (int t = 1; t <= T; t++) {
        solve();
    }
    return 0;
}
#endif

#if 0
/**************************************************************
    Problem: 3148
    User: dong_hee.lee
    Language: C
    Result: Success
    Time:100 ms
    Memory:282568 kb
****************************************************************/
 
//(정올 실전문제:3148)카드섹션
#pragma warning (disable : 4996)
#include <stdio.h>
#define MAXM ((int)1e4 + 1)
#define MAXN ((int)1e3)
typedef struct {
    int r, c, h, w;
    char col[40 * 40 + 4];
}DATA;
DATA sect[MAXM];
typedef struct node {
    char color;//색
    int id;//섹션아이디
    struct node *next;
}NODE;
NODE A[MAXN][MAXN];//좌석 dummy(next부터 내용 저장됨)
int ptr;
NODE dnode[MAXM * 40 * 40];
NODE *myalloc(int id, char color, NODE *next) {
    NODE *p = &dnode[ptr++];
    p->color = color; p->id = id; p->next = next;// *p = {color, id, next}; cpp에서 가능
    return p;
}
void Init(int n) {
    ptr = 0;
    for (register int i = 0; i < n; i++) {
        for (register int j = 0; j < n; j++) {
            A[i][j].next = NULL;
        }
    }
}
void PRT(int sr, int sc, int er, int ec) {
    for (register int i = sr; i < er; i++) {
        for (register int j = sc; j < ec; j++) {
            if (A[i][j].next) printf("%c", A[i][j].next->color);
            else printf("0");
        }
    }
    printf("\n");
}
void strcopy(char *dst, char *src) {
    while (*dst++ = *src++);
}
void addsection(int id, int r, int c, int h, int w, char *s) {
    int seq = 0;
    for (register int i = r; i < r + h; i++) {
        for (register int j = c; j < c + w; j++) {
            A[i][j].next = myalloc(id, s[seq++], A[i][j].next);
        }
    }
}
void searchdel(NODE *p, int id) {
/*  if (p->next->id == id) {//재귀함수로 구현
        p->next = p->next->next; return;
    }
    searchdel(p->next, id);*/
    while (p->next->id != id) p = p->next;//p->next=p->next->next;이렇게 구현하면 링크가 손상됨
    p->next = p->next->next;
}
void delsection(int id) {
    int r = sect[id].r, c = sect[id].c, h = sect[id].h, w = sect[id].w;
    for (register int i = r; i < r + h; i++) {
        for (register int j = c; j < c + w; j++) {
            searchdel(&A[i][j], id);
        }
    }
}
void solve() {
    int N, M;
    int cmd; int id, r, c, h, w; char str[40 * 40 + 4];
    scanf("%d %d", &N, &M);
    Init(N);
    for (register int i = 1; i <= M; i++) {//작업 정보
        scanf("%d", &cmd);
        switch (cmd) {
        case 1://섹션 추가
            scanf("%d %d %d %d %d %s", &id, &r, &c, &h, &w, str);
            sect[id].r = r; sect[id].c = c; sect[id].h = h; sect[id].w = w; 
            strcopy(sect[id].col, str);
            addsection(id, r, c, h, w, str);
            break;
        case 2://섹션 제거
            scanf("%d", &id);
            delsection(id);
            break;
        case 3://섹션 순서 마지막 순서로 변경
            scanf("%d", &id);
            delsection(id); 
            addsection(id, sect[id].r, sect[id].c, sect[id].h, sect[id].w, sect[id].col);
            break;
        case 4://섹션 이동 및 마지막 순서로 변경
            scanf("%d %d %d", &id, &r, &c);
            delsection(id);
            sect[id].r = r; sect[id].c = c;
            addsection(id, sect[id].r, sect[id].c, sect[id].h, sect[id].w, sect[id].col);
            break;
        default://출력
            scanf("%d %d", &r, &c);
            PRT(r, c, r + 4, c + 4);
        }
    }
}
int main() {
    int T;
    scanf("%d", &T);
    for (int t = 1; t <= T; t++) {
        solve();
    }
    return 0;
}
#endif