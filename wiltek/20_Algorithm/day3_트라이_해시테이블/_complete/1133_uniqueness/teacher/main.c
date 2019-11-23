/*
http://jungol.co.kr/xpert/viewp.php?bo_table=sm_bank&id=1133&alcate=&mtitle=%EB%AC%B8%EC%A0%9C%EC%9D%80%ED%96%89&al=003&altitle=&alname=&altag=&page=1#none
*/

/*
N개의 문자열이 주어졌을 때, 동일한 문자열이 존재하는지 판단하는 프로그램을 작성하라.

문자열이란 사이에 공백이 없는 연속된 알파벳 소문자열을 뜻한다.
문자열의 길이는 최소 1글자, 최대 20글자이다.
입력되는 문자열의 개수는 2개 이상 10,000개 이하이다.

//입력 
입력의 첫 번째 줄에는 입력될 문자열의 개수 N이 입력된다.
그 다음 줄에는 N개의 문자열이 공백을 사이에 두고 입력된다. 전제조건을 어긋나는 입력이 들어오는 경우는 없다.

//출력
입력에서 동일한 문자열이 존재하지 않을 경우는 "unique"를 출력한다.(큰 따옴표 제외) 
동일한 문자열이 발생한 경우에는 한 줄에 해당 문자열과, 문자열이 몇 번째로 입력되었는지를 출력해야 하는데, 
이 경우 우선 앞에 동일한 문자열이 발견된 문자열을 출력한 다음 공백을 출력한 다음, 공백을 사이에 두고 몇 번째로 입력이 되었는지를 출력한다. 
동일한 문자열이 존재하는 문자열이 여럿 발견 되었을 경우, 매 줄마다 입력된 순서대로 앞에 나온 형식에 맞춰서 출력을 한다. 자세한 사항은 입력예시를 참고한다.

//입력
10
alice bob libe lie libe libe alice bob alice alice

//출력
alice 1 7 9 10
bob 2 8
libe 3 5 6
*/

#if 0
//UNIQUENESS O(N^2) hash func를 이용한 비교
#pragma warning (disable : 4996)
#include <stdio.h>
#define MAXN ((int)1e4 + 4)
#define STRN (20 + 4)
typedef unsigned int U32;
int N;//문자열 개수
char str[MAXN][STRN];
int used[MAXN];//동일 문자열이 있었는지 표시
U32 hashkey[MAXN];//hash 값 저장용
U32 hashfunc(char *s) {
    U32 hashk = 5381; char ch;
    while (ch = *s++) hashk = (hashk << 5) + hashk + ch;
    return hashk;
}
void InputData() {
    scanf("%d", &N);
    for (int i = 1; i <= N; i++) {
        scanf("%s", str[i]);
        hashkey[i] = hashfunc(str[i]);
    }
}
inline int strlength(char *s) {//문자열 길이 파악
    register int i;
    for (i = 0; s[i]; i++);
    return i;
}
inline int strcompare(char *a, char *b) {//문자열 비교(앞 문자열이 크면 양수, 뒤 문자열이 크면 음수
    for (register int i = 0; a[i] || b[i]; i++) {
        if (a[i] == b[i]) continue;//동일 문자면 skip
        return a[i] - b[i];//다르면 차를 리턴
    }
    return 0;//두 문자열이 동일
}
inline int strcpy(char *dst, char *src) {//dst에 src를 복사
    while (*dst++ = *src++);//대입연산자가 판단문에 있어서 경고 발생함
}
void solve() {
    int uniq = 1, first;
    for (int i = 1; i < N; i++) {//선택 문자열 인덱스
        if (used[i]) continue;//다른 문자열과 동일 문자열 이었으므로 skip
        first = 1;
        for (int j = i + 1; j <= N; j++) {
            if (hashkey[i] != hashkey[j]) continue;//hash 값이 다르면 무조건 다른 문자열
            if (strcompare(str[i], str[j])) continue;//collision 체크용
            uniq = 0;//동일 문자열 발견
            used[j] = 1;//i문자열과 동일 문자열임을 표시
            if (first) {//처음 동일 문자열 발견
                first = 0;
                printf("%s %d %d", str[i], i, j);
            }
            else {
                printf(" %d", j);
            }
        }
        if (!first) printf("\n");
    }
    if (uniq) printf("unique\n");//동일 문자열이 없었음
}
int main() {
    InputData();
    solve();
    return 0;
}
/**************************************************************
    Problem: 2293
    User: AXQ7106
    Language: C
    Result: Accepted
    Time:58 ms
    Memory:1468 kb
****************************************************************/
#endif

#if 01
//UNIQUENESS O(N) hash table을 이용
#include <stdio.h>

#define MAXN ((int)1e4 + 4)
#define STRN (20 + 4)
typedef unsigned int U32;
int N;								//문자열 개수
char str[MAXN][STRN];

int strcompare(char *a, char *b)	//문자열 비교(앞 문자열이 크면 양수, 뒤 문자열이 크면 음수 
{
    for (register int i = 0; a[i] || b[i]; i++) 
    {
        if (a[i] == b[i]) continue;	//동일 문자면 skip
        return a[i] - b[i];			//다르면 차를 리턴
    }
    return 0;						//두 문자열이 동일
}
U32 hashfunc(char *s) 
{
    U32 hashk = 5381; 
    char ch;
    while (ch = *s++) hashk = (hashk << 5) + hashk + ch;
    return hashk % MAXN;			//배열요소개수 이내의 값
}

//문자열 별로 id 부여용(collision 회피해서)
int NewId;
typedef struct st 
{
    int id; 
    char *s;
    struct st *next;
}HASHK;
HASHK head[MAXN];
int hkptr;
HASHK hknode[MAXN];

HASHK *myalloc(int id, char *s, HASHK *next) 
{
    HASHK *p = &hknode[hkptr++];
    p->id = id; p->s = s; p->next = next;
    return p;
}

int Inserthk(HASHK *p, char *s) 
{
    if ((!p->next) || (strcompare(p->next->s, s) > 0)) 
    {
        p->next = myalloc(++NewId, s, p->next); 
        return NewId;//새로운 문자열
    }
    if (strcompare(p->next->s, s) == 0) return p->next->id;//기존 문자열과 같음
    return Inserthk(p->next, s);
}

int getid(char *s) 
{
    int idx = hashfunc(s);
    return Inserthk(&head[idx], s);
}

//같은 문자열 관리용
typedef struct ht 
{
    int idx; 
    struct ht *next;
}HTBL;

HTBL htbl[MAXN];
int samecnt[MAXN];//같은 문자열 개수
int htptr;
HTBL htnode[MAXN];

HTBL *htblalloc(int idx, HTBL *next) 
{
    HTBL *p = &htnode[htptr++];
    p->idx = idx; p->next = next;
    return p;
}

void Inserthtbl(int id, int idx) 
{
    htbl[id].next = htblalloc(idx, htbl[id].next);
    samecnt[id]++;
}

void PRT(HTBL * p) 
{
    if (!p->next) 
    {
        printf("%s %d", str[p->idx], p->idx); 
        return;
    }
    PRT(p->next);
    printf(" %d", p->idx);
}

void Init() 
{
    NewId = 0; 
    hkptr = 0; 
    htptr = 0;
    for (register int i = 0; i < MAXN; i++) 
    {
        head[i].next = NULL; 
        htbl[i].next = NULL; 
        samecnt[i] = 0;
    }
}

void InputData() 
{
    scanf("%d", &N);
    for (int i = 1; i <= N; i++) 
    {
        scanf("%s", str[i]);
        int id = getid(str[i]);
        Inserthtbl(id, i);
    }
}

void solve() 
{
    if (NewId == N) 
    {
        printf("unique\n");//동일 문자열이 없었음
        return;
    }
    for (register int i = 1; i <= NewId; i++) 
    {
        if (samecnt[i] < 2) continue;//같은 문자가 1개임
        PRT(htbl[i].next); 
        printf("\n");
    }
}

int main() 
{
#if 1
	freopen("input.txt", "r", stdin);
#endif
    Init();
    InputData();
    solve();
    return 0;
}
/**************************************************************
    Problem: 2293
    User: AXQ7106
    Language: C
    Result: Accepted
    Time:8 ms
    Memory:2244 kb
****************************************************************/
#endif

#if 0
//UNIQUENESS O(N^2) 문자열비교활용
#pragma warning (disable : 4996)
#include <stdio.h>
#define MAXN ((int)1e4 + 4)
#define STRN (20 + 4)
int N;//문자열 개수
char str[MAXN][STRN];
int used[MAXN];//동일 문자열이 있었는지 표시
void InputData() {
    scanf("%d", &N);
    for (int i = 1; i <= N; i++) {
        scanf("%s", str[i]);
    }
}
inline int strlength(char *s) {//문자열 길이 파악
    register int i;
    for (i = 0; s[i]; i++);
    return i;
}
inline int strcompare(char *a, char *b){//문자열 비교(앞 문자열이 크면 양수, 뒤 문자열이 크면 음수
    for (register int i = 0; a[i] || b[i]; i++) {
        if (a[i] == b[i]) continue;//동일 문자면 skip
        return a[i] - b[i];//다르면 차를 리턴
    }
    return 0;//두 문자열이 동일
}
inline int strcpy(char *dst, char *src){//dst에 src를 복사
    while (*dst++ = *src++);//대입연산자가 판단문에 있어서 경고 발생함
}
void solve() {
    int uniq = 1, first;
    for (int i = 1; i < N; i++) {//선택 문자열 인덱스
        if (used[i]) continue;//다른 문자열과 동일 문자열 이었으므로 skip
        first = 1;
        for (int j = i + 1; j <= N; j++) {
            if (strcompare(str[i], str[j])) continue;//다른 문자열 skip
            uniq = 0;//동일 문자열 발견
            used[j] = 1;//i문자열과 동일 문자열임을 표시
            if(first){//처음 동일 문자열 발견
                first = 0;
                printf("%s %d %d", str[i], i, j);
            }
            else {
                printf(" %d", j);
            }
        }
        if (!first) printf("\n");
    }
    if (uniq) printf("unique\n");//동일 문자열이 없었음
}
int main() {
    InputData();
    solve();
    return 0;
}
/**************************************************************
    Problem: 2293
    User: AXQ7106
    Language: C++
    Result: Accepted
    Time:101 ms
    Memory:1432 kb
****************************************************************/
#endif