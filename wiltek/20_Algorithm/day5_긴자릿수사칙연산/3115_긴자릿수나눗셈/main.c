//긴 자릿수 나눗셈
#pragma warning (disable : 4996)
#include <stdio.h>
#define MAXN (200 + 4)
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
int strlength(char *a) {
    register int i;
    for (i = 0; a[i]; i++);
    return i;
}
int InputData() {
    scanf("%s", N);
    scanf("%s", M);
    return !strcompare(N, "0") || !strcompare(M, "0");
}
int conv(int *dst, char *src) {
    register int i;
    for (i = 0; src[i]; i++) dst[i] = src[i] - '0';
    return i;
}
int dividesub(int *a, int *b, int len) {
    //뺄셈 가능한지 체크
    for (int i = 0; i < len; i++) {
        if (a[i] > b[i]) break;//뺄셈 가능
        if (a[i] < b[i]) return 0;//뺄셈 불가능
    }
    //뺄셈 진행
    for (int i = len - 1; i >= 0; i--) {//0번째까지 진행해야 함
        a[i] -= b[i];
        if(a[i]< 0){//빌림처리
            a[i - 1] -= 1; a[i] += 10;
        }
    }
    return 1;
}
void divide(char *a, char *b) {//a/b
    int A[MAXN], B[MAXN], sol[MAXN] = { 0 };
    int alen = conv(A, a), blen = conv(B, b);
    int slen = alen - blen + 1;//최대 자리수 긴자릿수-짧은자릿수+1, 최소 자리수 긴자릿수-짧은자릿수
    //뺄셈으로 나눗셈 처리
    for (int i = 0; i < slen; i++) {
        while (dividesub(&A[i], B, blen)) sol[i]++;//뺄셈 진행했으면 몫 증가
        A[i + 1] += A[i] * 10; A[i] = 0;//남은 값 뒷자리로 보내기(이렇게 해야 뺄셈 가능판단 및 계산이 심플함)
    }
    //인쇄
    for (int i = sol[0] == 0; i < slen; i++) {
        printf("%d", sol[i]);
    }
    printf("\n");
}
void solve() {
    int nlen = strlength(N), mlen = strlength(M);
    if ((nlen > mlen) || ((nlen == mlen) && (strcompare(N, M) >= 0))) {
        divide(N, M);
    }
    else {
        divide(M, N);
    }
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
    Problem: 2786
    User: AXQ7106
    Language: C
    Result: Accepted
    Time:2 ms
    Memory:1156 kb
****************************************************************/