/**************************************************************
    Problem: 3140
    User: dong_hee.lee
    Language: C
    Result: Success
    Time:13 ms
    Memory:1100 kb
****************************************************************/
 
 
//(정올 실전문제:3140) 계산기2
#pragma warning (disable : 4996)
#include <stdio.h>
#define MAXN (300 + 4)
typedef struct {
    int sign;
    char child[MAXN];
    char parent[MAXN];
}DATA;
int strcompare(const char *a, const char *b) {
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
void strcopy(char *dst, const char *src) {
    while (*dst++ = *src++);
}
int conv1(int *dst, char *src) {
    register int i;
    for (i = 0; src[i]; i++) dst[i] = src[i] - '0';
    return i;
}
void conv2(int *dst, char *src, int dlen, int slen) {//문자를 숫자로 변환
    for (register int i = slen - 1, j = dlen - 1; i >= 0; i--, j--) {
        dst[j] = src[i] - '0';
    }
}
void multi(char *a, char *b) {//a *= b
    if (!strcompare(a, "0") || !strcompare(b, "0")) {//예외사항처리
        strcopy(a, "0"); return;
    }
    int A[MAXN], B[MAXN], sol[MAXN] = { 0 };
    int alen = conv1(A, a), blen = conv1(B, b);
    int slen = alen + blen, i, j;
    //N^2 곱하기
    for (i = 0; i < alen; i++) {
        for (j = 0; j < blen; j++) {
            sol[i + j + 1] += A[i] * B[j];
        }
    }
    //올림처리
    for (i = slen - 1; i > 0; i--) {
        if (sol[i] >= 10) {//올림처리
            sol[i - 1] += sol[i] / 10; sol[i] %= 10;
        }
    }
    //저장
    for (i = sol[0] == 0, j = 0; i < slen; i++, j++) {
        a[j] = sol[i] + '0';
    }
    a[j] = 0;
}
void add(char *a, char *b) {//a += b
    int A[MAXN] = { 0 }, B[MAXN] = { 0 }, sum[MAXN] = { 0 };
    int alen = strlength(a), blen = strlength(b);
    int slen = ((alen > blen) ? alen : blen) + 1, i, j;
    conv2(A, a, slen, alen); conv2(B, b, slen, blen);
    //덧셈 계산(뒷자리수부터)
    for (i = slen - 1; i > 0; i--) {
        sum[i] += A[i] + B[i];
        if (sum[i] >= 10) {//올림발생
            sum[i - 1] += 1; sum[i] -= 10;
        }
    }
    //저장
    for (i = sum[0] == 0, j = 0; i < slen; i++, j++) {
        a[j] = sum[i] + '0';
    }
    a[j] = 0;
}
void sub(char *a, char *b, char *c) {//c = a-b;
    int A[MAXN] = { 0 }, B[MAXN] = { 0 }, sum[MAXN] = { 0 };
    int alen = strlength(a), blen = strlength(b);
    int slen = ((alen > blen) ? alen : blen), i, j;
    conv2(A, a, slen, alen); conv2(B, b, slen, blen);
    //차 계산(뒷자리수부터)
    for (register int i = slen - 1; i >= 0; i--) {
        sum[i] += A[i] - B[i];
        if (sum[i] < 0) {//빌림발생
            sum[i - 1] -= 1; sum[i] += 10;
        }
    }
    //저장
    for (i = 0; (i < slen - 1) && (sum[i] == 0); i++);//앞자리부터 0이 아닌 자리 찾기
    for (j = 0; i < slen; i++, j++) {
        c[j] = sum[i] + '0';
    }
    c[j] = 0;
}
int compare(char *a, char *b) {
    int alen = strlength(a), blen = strlength(b);
    if (alen == blen) return strcompare(a, b) >= 0;
    return alen > blen;
}
void calculate(DATA *a, DATA *b) {
    multi(a->child, b->parent);
    multi(b->child, a->parent);
    multi(a->parent, b->parent);
    if(a->sign == b->sign){//같은 부호일경우 덧셈 진행(부호 변경 없음)
        add(a->child, b->child);
    }
    else {//부호가 다르므로 뺄셈 진행
        if (compare(a->child, b->child)) {
            sub(a->child, b->child, a->child);
        }
        else {
            sub(b->child, a->child, a->child);
            a->sign = b->sign;//b가 크므로 b의 부호로 변경되어야 함
        }
    }
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
        if (a[i] < 0) {//빌림처리
            a[i - 1] -= 1; a[i] += 10;
        }
    }
    return 1;
}
void divide(char *a, char *b, char *c) {//c = a/b
    if(!compare(a, b)){//b가 크므로 나눗셈 불가
        strcopy(c, "0"); return;//몫은 0임
    }
    int A[MAXN], B[MAXN], sol[MAXN] = { 0 };
    int alen = conv1(A, a), blen = conv1(B, b), i, j;
    int slen = alen - blen + 1;//최대 자리수 긴자릿수-짧은자릿수+1, 최소 자리수 긴자릿수-짧은자릿수
    //뺄셈으로 나눗셈 처리
    for (i = 0; i < slen; i++) {
        while (dividesub(&A[i], B, blen)) sol[i]++;//뺄셈 진행했으면 몫 증가
        A[i + 1] += A[i] * 10; A[i] = 0;//남은 값 뒷자리로 보내기(이렇게 해야 뺄셈 가능판단 및 계산이 심플함)
    }
    //저장
    for (i = sol[0] == 0, j = 0; i < slen; i++, j++) {
        c[j] = sol[i] + '0';
    }
    c[j] = 0;
}
void divideprt(DATA *res){//res->child/res->parent를 소수점 이하 30자리까지 출력
    char c[MAXN];
    divide(res->child, res->parent, c);//몫 계산
    if (res->sign < 0) printf("-");//결과가 음수일경우 부호 출력
    printf("%s.", c);//몫 출력
    for (int i = 0; i < 30; i++) {//소수점 이하 30자리 출력
        multi(c, res->parent);//몫에 나눈값 곱하기
        sub(res->child, c, res->child);//분자-몫*분모=나머지구하기
        multi(res->child, "10");//나머지 * 10
        divide(res->child, res->parent, c);//몫 구하기
        printf("%s", c);//출력(한자리만 구해짐)
    }
    printf("\n");
}
void solve() {
    char str[MAXN], num[MAXN];
    DATA result = { 1, "0", "1" }, tmp = { 1, "1", "1" };
    int updown = 1, i, j;
    scanf("%s", str);
    for (i = j = 0; str[i]; i++) {
        if (('0' <= str[i]) && (str[i] <= '9')) {//숫자면 num배열에 순서대로 저장
            num[j++] = str[i];
        }
        else{//연산자임
            num[j] = 0;//마지막에 널문자 추가(문자열 만들기)
            j = 0;
            if (updown) multi(tmp.child, num);//tmp.child *= num
            else multi(tmp.parent, num);//tmp.parent *= num
            if (str[i] == '/') {
                updown = 0; continue;//계속 tmp에 곱해나감(연산자 우선순위를 위해)
            }
            updown = 1;
            if (str[i] == '*') continue;//계속 tmp에 곱해나감(연산자 우선순위를 위해)
            calculate(&result, &tmp);//그외 연산자인 경우 result에 tmp를 분수식 계산하기
            strcopy(tmp.child, "1"); strcopy(tmp.parent, "1"); tmp.sign = 1;
            if (str[i] == '-') tmp.sign = -1;
        }
    }
    divideprt(&result);
}
int main() {
    freopen("input.txt", "r", stdin);
    int T;
    scanf("%d", &T);
    for (int t = 1; t <= T; t++) {
        solve();
    }
    return 0;
}