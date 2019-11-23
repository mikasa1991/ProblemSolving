//긴 자릿수 덧셈 뺄셈
#include <stdio.h>
#define MAXN (200 + 4)
char N[MAXN];
char M[MAXN];

int strcompare(char *a, char *b) 
{
    int i;
    for (i = 0; (a[i] > 0) || (b[i] > 0) ; i++)  //a, b 둘다 NULL에 도달하는 경우, 반복문 탈출. 
    {
        if (a[i] == b[i]) continue;
        return a[i] - b[i];
    }
    return 0;//두 문자열이 동일한 문자열
}
 
int strlength(char *a) 
{
    int i;
    for (i = 0; a[i] > 0; i++);
    return i;
}
 
int InputData() {
    scanf("%s", N);
    scanf("%s", M);
    return !strcompare(N, "0") && !strcompare(M, "0");
}
 
void conv(int *dst, char *src, int dlen, int slen) 
{//문자를 숫자로 변환
    for (int i = slen - 1, j = dlen - 1; i >= 0; i--, j--) 
    {
        dst[j] = src[i] - '0';
    }
}
 
void calculate(char *a, char *b, int alen, int blen) 
{
    int A[MAXN] = { 0 }, B[MAXN] = { 0 };
    int sum[MAXN] = { 0 }, sub[MAXN] = { 0 };
    int sol = alen + 1;     //최대 긴 자릿수보다 1자리 더 길어질수있음
    conv(A, a, sol, alen);  //문자를 숫자로 변환
    conv(B, b, sol, blen);  //문자를 숫자로 변환
    //덧셈 계산(뒷자리수부터)
    for (register int i = sol - 1; i > 0; i--) {
        sum[i] += A[i] + B[i];
        if (sum[i] >= 10) 
        {//올림발생
            sum[i - 1] += 1; 
            sum[i] -= 10;
        }
    }
    //인쇄
    //sum[0]이 0이면 i = 1부터, 0이 아니면 i = 0부터
    for (register int i = (sum[0] == 0); i < sol; i++)
        printf("%d", sum[i]);
    printf("\n");
 
    //차 계산(뒷자리수부터)
    for (register int i = sol - 1; i > 0; i--) {
        sub[i] += A[i] - B[i];
        if (sub[i] < 0) 
        {//빌림발생
            sub[i - 1] -= 1; 
            sub[i] += 10;
        }
    }
    //인쇄
    register int i;
    for (i = 0; (i < sol - 1) && (sub[i] == 0); i++);//앞자리부터 0이 아닌 자리 찾기
    for (; i < sol; i++) {
        printf("%d", sub[i]);
    }
    printf("\n");
}
 
void solve() {
    int nlen = strlength(N);
    int mlen = strlength(M);
    if ((nlen > mlen) || ((nlen == mlen) && (strcompare(N, M) >= 0))) 
        calculate(N, M, nlen, mlen);//N이 크므로 N-M
    else
        calculate(M, N, mlen, nlen);//M이 크므로 M-N
}
 
int main() 
{
#if 1
    freopen("input.txt", "r", stdin);
#endif

    for (;;) 
    {
        if (InputData()) break;
        solve();
    }
    return 0;
}
/**************************************************************
    Problem: 1744
    User: AXQ7106
    Language: C
    Result: Accepted
    Time:3 ms
    Memory:1156 kb
****************************************************************/