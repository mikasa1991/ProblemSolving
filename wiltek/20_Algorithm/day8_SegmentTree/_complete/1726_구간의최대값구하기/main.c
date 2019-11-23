/*
http://jungol.co.kr/xpert/viewp.php?bo_table=sm_bank&id=1726&alcate=&mtitle=%EB%AC%B8%EC%A0%9C%EC%9D%80%ED%96%89&al=003&altitle=&alname=&altag=&page=1
*/

//구간의 최대값 구하기(segment tree)
#include <stdio.h>

#define DEBUG 1
#define MAXN ((int)5e4 + 10)
#define MAXT (1 << 17)//N보다 크거나 같은 2의 제곱수의 2배 공간 필요(2^16이 65,536이므로 2^17 필요)
int N;//원소의개수
int Q;//구간의개수
int A[MAXN];//요소 값
int tree[MAXT];
int MAXV(int a, int b) {
    return (a > b) ? a : b;
}

void InitTree(int n, int s, int e) 
{
    if (s == e) {//leaf node
        tree[n] = A[s]; 
        return;
    }
    int L = n * 2, R = L + 1, m = (s + e) / 2;
    InitTree(L, s, m); 
    InitTree(R, m + 1, e);
    tree[n] = MAXV(tree[L], tree[R]);
}

int query(int n, int s, int e, int qs, int qe) 
{
    if ((qe < s) || (e < qs))   return 0;	    //범위 벗어남, 의미 없는 값을 리턴(결과에 영향을 안주는값)
    if ((qs <= s) && (e <= qe)) return tree[n];	//관리 범위가 쿼리 범위 이내이므로 현재값 리턴
    
    int L = n * 2; 
    int R = L + 1; 
    int m = (s + e) / 2;
    
    return MAXV(query(L, s, m, qs, qe), query(R, m + 1, e, qs, qe));
    //#define으로 MAXV를 만들면 위와 같은 식으로 하면 안됨 단순변환되므로 중복호출됨
}

void InputData() 
{
    scanf("%d %d", &N, &Q);
    for (int i = 1; i <= N; i++) 
    {
        scanf("%d", &A[i]);
    }
}

void solve() 
{
    int s, e;
    InitTree(1, 1, N);				//segment tree 만들기
    for (int i = 1; i <= Q; i++) 
    {
        scanf("%d %d", &s, &e);
        printf("%d\n", query(1, 1, N, s, e));
    }
}

int main(void) 
{
#ifdef DEBUG
	freopen("input.txt", "r", stdin);
#endif
    InputData();
    solve();
    return 0;
}
/**************************************************************
    Problem: 2932
    User: AXQ7106
    Language: C
    Result: Accepted
    Time:144 ms
    Memory:1864 kb
****************************************************************/