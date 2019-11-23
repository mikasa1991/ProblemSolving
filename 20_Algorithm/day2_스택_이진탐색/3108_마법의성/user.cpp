/**************************************************************
    Problem: 3108
    User: dong_hee.lee
    Language: C++
    Result: Success
    Time:241 ms
    Memory:17376 kb
****************************************************************/
 
//정올 마법의성
extern int getNumber(int, int);
#define LEFT (1)
#define RIGHT (2)
#define MAXN ((int)1e6)
static int L[MAXN];//왼쪽카드 쿼리한 결과
static int R[MAXN];//오른쪽카드 쿼리한 결과
static int Lend, Rend;//각 카드더미 마지막 요소번호
static int anscnt;//없어진카드 찾은개수(찾은 답을 순서대로 담기위해)
static int *ans;//답 저장공간

int bsup(int select, int *arr) {
    int s = 0, e = MAXN - 1, m, sol = 0;
    while (s <= e) {
        m = (s + e) / 2;
        if (!arr[m]) arr[m] = getNumber(select, m);
        if (arr[m]) { sol = m; s = m + 1; }
        else e = m - 1;
    }
    return sol;
}

void DFS(int rs, int re) {
    int le = re + anscnt;
    if (!L[le]) L[le] = getNumber(LEFT, le);
    if (!R[re]) R[re] = getNumber(RIGHT, re);
    if (L[le] == R[re]) return;//rs~re까지 없어진 카드 없음
    if(rs==re){//분할불가, le번째 요소가 없어진 카드임
        for (int i = le; i <= Lend; i++) {
            if (!L[i]) L[i] = getNumber(LEFT, i);
            if (L[i] == R[re]) break;//더이상 없어진 카드 없음(rs~re사이에)
            ans[anscnt++] = L[i];
        }
    }
    else {
        int m = (rs + re) / 2;
        DFS(rs, m); DFS(m + 1, re);
    }
}

int card_find(int user_ans[])
{
    //초기화
    anscnt = 0; ans = user_ans;
    for (int i = 0; i < MAXN; i++) {
        L[i] = R[i] = 0;
    }
    Lend = bsup(LEFT, L);
    Rend = bsup(RIGHT, R);
    //분할정복을 이용한 없어진 카드 찾기
    DFS(0, Rend);
    //나머지 없어진 카드 담기
    for (int i = Rend + anscnt + 1; i <= Lend; i++) {
        if (!L[i]) L[i] = getNumber(LEFT, i);
        ans[anscnt++] = L[i];
    }
    return anscnt;//없어진 카드 개수 리턴
}