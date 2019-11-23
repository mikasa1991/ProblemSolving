//긴 자릿수 곱셈
#pragma warning (disable : 4996)
#include <stdio.h>
#define MAXN (100 + 4)
char N[MAXN];
char M[MAXN];
int strcompare(char *a, char *b) {
    register int i;
    for (i = 0; a[i] || b[i]; i++) {
        if (a[i] == b[i]) continue;
        return a[i] - b[i];
    }
    return 0;//두 문자열이 동일한 문자열
}
int InputData() {
    scanf("%s", N);
    if (!strcompare(N, "0")) return 1;
    scanf("%s", M);
    return 0;
}
int conv(int *dst, char *src) {
    register int i;
    for (i = 0; src[i]; i++) dst[i] = src[i] - '0';
    return i;
}
void multi(char *a, char *b) {
    int A[MAXN], B[MAXN], sol[MAXN + MAXN] = { 0 };
    int alen = conv(A, a), blen = conv(B, b);
    int slen = alen + blen;//최대 a자리수+b자리수, 최소 a자리수+b자리수-1
    //N^2 곱하기
    for (int i = 0; i < alen; i++) {
        for (int j = 0; j < blen; j++) {
            sol[i + j + 1] += A[i] * B[j];
        }
    }
    //올림처리
    for (int i = slen - 1; i > 0; i--) {
        if (sol[i] >= 10) {//올림처리
            sol[i - 1] += sol[i] / 10; sol[i] %= 10;
        }
    }
    //인쇄
    for (int i = sol[0] == 0; i < slen; i++) {
        printf("%d", sol[i]);
    }
    printf("\n");
}
void solve() {
    if (!strcompare(M, "0")) {//예외사항
        printf("0\n"); return;
    }
    char *n = N, *m = M;
    int sign = 1;
    if (n[0] == '-') {//부호처리
        sign *= -1; n++;
    }
    if (m[0] == '-') {//부호처리
        sign *= -1; m++;
    }
    if (sign < 0) printf("-");
    multi(n, m);
}
int main() 
{
#if 1
    freopen("input.txt", "r", stdin);
#endif
    for (;;) {
        if (InputData()) break;
        solve();
    }
    return 0;
}
/**************************************************************
    Problem: 1743
    User: AXQ7106
    Language: C
    Result: Accepted
    Time:3 ms
    Memory:1156 kb
****************************************************************/