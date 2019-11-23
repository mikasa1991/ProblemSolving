/*
https://www.acmicpc.net/problem/10755
*/

//컴퓨터실(Basic)
#include <stdio.h>
#define MAXN ((int)1e5 + 10)
#define MAXM ((int)3e5 + 10)
#define MAXQ ((int)1e5 + 10)
int M;                      //컴퓨터수
int N;                      //이미자리잡은학생수
int Q;                      //친구수
int A[MAXM];                //이미자리잡은학생뿐만아니라 최대M대 컴퓨터에 앉은 모든 학생들이 앉은 컴퓨터 번호 저장용(인덱스 들어온 순서, 내용 컴퓨터 번호)
int B[MAXQ];                //친구가 들어간 순서

typedef struct 
{
    int cnt;    //그룹내컴퓨터수
    int s;      //시작좌석번호
}HEAP;

HEAP heap[MAXM];
int lastn;

/*
a가 우선하는 경우, 1 반환
b가 우선하는 경우, 0 반환
*/
int comp(int a, int b) 
{//그룹내 컴퓨터수가 많은게 우선, 차순위는 시작좌석번호가 작은게 우선
    if (heap[a].cnt == heap[b].cnt) return heap[a].s < heap[b].s;
    return heap[a].cnt > heap[b].cnt;
}

void swap(HEAP *a, HEAP *b)
{
    HEAP temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

void push(int cnt, int s) 
{
    printf(" >push: (%d, %d)\n", cnt, s);
    heap[++lastn].cnt = cnt;
    heap[lastn].s = s;
    int C = lastn; 
    int P = C / 2;
    while ((P > 0) && (comp(P, C) == 0))    //P가 존재하고, C가 P보다 우선하는 경우
    {
        swap(&heap[P], &heap[C]);
        C = P; 
        P = C / 2;
    }
}

HEAP pop() 
{
    HEAP ret = heap[1]; 
    heap[1] = heap[lastn--];
    int P = 1, L = 2, R = 3, C;
    while (L <= lastn) 
    {
        if (R > lastn) C = L;
        else C = comp(L, R) ? L : R;
        if (comp(P, C) > 0) break;

        swap(&heap[P], &heap[C]);
        
        P = C; 
        L = P * 2; 
        R = L + 1;
    }
    return ret;
}

/*
int M;               //컴퓨터수
int N;               //이미자리잡은학생수
int Q;               //친구수
int A[MAXM];         //이미자리잡은학생뿐만아니라 최대M대 컴퓨터에 앉은 모든 학생들이 앉은 컴퓨터 번호 저장용(인덱스 들어온 순서, 내용 컴퓨터 번호)
int B[MAXQ];         //친구가 들어간 순서

*/
void InputData() {
    int s = 1; 
    int i;
    scanf("%d %d %d", &M, &N, &Q);
    for (i = 1; i <= N; i++) 
    {//순서번호 1번부터 임으로
        scanf("%d", &A[i]);
        if (A[i] - s > 0) push(A[i] - s, s);    //그룹내 컴퓨터수가 1이상이어야 우선순위 큐에 저장
        s = A[i] + 1;                           //이전 학생이 앉은 다음자리가 다음그룹 시작 좌석번호임
    }
    if (M - s + 1 > 0) push(M - s + 1, s);
    for (i = 1; i <= Q; i++) 
    {
        scanf("%d", &B[i]);
    }
}

void OutputData() {
    for (int i = 1; i <= Q; i++) 
    {
        printf("%d\n", A[B[i]]);            //A배열에 들어간 순서에 따른 컴퓨터 번호 저장되어있음, B배열에 친구가 들어간 순서가 있음
    }
}

void solve() {
    //N명은 이미 들어가 앉아있으므로 
    //N+1부터 친구들중 가장 마지막에 들어간 친구까지만 구하면됨(M대의 자리를 모두 구할필요없음)
    for (int i = N + 1; i <= B[Q]; i++) 
    {
        HEAP t = pop();                         //그룹내 컴퓨터 수가 제일 큰 그룹꺼내기(같은 경우 좌석 번호가 제일 작은 그룹)
        int e = t.s + t.cnt - 1;                //현재 그룹의 마지막 좌석번호 구하기
        A[i] = (t.s + e) / 2;                   //그룹내 중앙에 i번째 들어온 학생이 앉음
        if (A[i] - t.s) push(A[i] - t.s, t.s);  //i번째 학생이 앉은 왼쪽에 그룹 발생한 경우
        if (e - A[i]) push(e - A[i], A[i] + 1); //i번째 학생이 앉은 오른쪽에 그룹 발생한 경우(오른쪽 시작좌석번호는 A[i]+1임을 주의)
    }
}

int main() 
{
#if 1
    freopen("input.txt", "r", stdin);
#endif
    InputData();
    solve();
    OutputData();
    return 0;
}
/**************************************************************
    Problem: 2937
    User: AXQ7106
    Language: C
    Result: Accepted
    Time:74 ms
    Memory:5064 kb
****************************************************************/