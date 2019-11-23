/*
http://jungol.co.kr/xpert/viewp.php?bo_table=sm_bank&id=1169&alcate=&mtitle=%EB%AC%B8%EC%A0%9C%EC%9D%80%ED%96%89&al=003&altitle=&alname=&altag=&page=1
*/
#include <stdio.h>
#define DEBUG 1

int N, M;
int num[10];
int used[10];

void DFS1(int n) {//중복순열
    if (n >= N) {//종료 조건
        for (int i = 0; i < N; i++) printf("%d ", num[i]);
        printf("\n");
        return;
    }
    for (int i = 1; i <= 6; i++) {
        num[n] = i;
        DFS1(n + 1);
    }
}

void DFS2(int n, int s) {//중복조합
    if (n >= N) {//종료 조건
        for (int i = 0; i < N; i++) printf("%d ", num[i]);
        printf("\n");
        return;
    }
    for (int i = s; i <= 6; i++) {
        num[n] = i;
        DFS2(n + 1, i);
    }
}

void DFS3(int n) {//순열
    if (n >= N) {//종료 조건
        for (int i = 0; i < N; i++) printf("%d ", num[i]);
        printf("\n");
        return;
    }
    for (int i = 1; i <= 6; i++) {
        if (used[i]) continue;
        used[i] = 1;//사용으로 표시
        num[n] = i;
        DFS3(n + 1);
        used[i] = 0;//표시 제거
    }
}

int main(void)
{
#ifdef DEBUG
	freopen("input.txt", "r", stdin);
#endif
    scanf("%d %d", &N, &M);
    if (M == 1) DFS1(0);
    else if (M == 2) DFS2(0, 1);
    else DFS3(0);
    return 0;
}
/**************************************************************
    Problem: 1956
    User: AXQ7106
    Language: C
    Result: Accepted
    Time:2 ms
    Memory:1156 kb
****************************************************************/