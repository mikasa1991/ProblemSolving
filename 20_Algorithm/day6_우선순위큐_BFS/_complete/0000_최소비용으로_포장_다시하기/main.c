/*
문제출처를 찾지 못했음.

//문제 설명
사탕 공장에서는 요구에 따라 다양한 개수의 사탕을 담고 있는 포장을 하고 있다. 
어느 날 갑자기 대형 이벤트가 생겨서 공장에 있는 모든 사탕들을 풀어서 하나로 포장 해야 한다.
 
A, B, C 3개의 사탕 포장이 있을 때 이 포장들을 한번에 하나로 합칠 수는 없고, 한번에 2개씩만 합칠 수 있다. 
예를 들면 A와 B를 먼저 합친 후 C를 다시 합치거나 A와 C를 먼저 합치고 B를 합치기, 혹은 B와 C를 먼저 합치고 A를 합칠 수 있다.
 
사탕 포장을 풀었다가 다시 합치는 순서는 매우 중요한데, 그 이유는 그 순서에 따라 전체 비용이 달라지기 때문이다.
 
사탕 포장 A와 B에 각각 a개와 b개의 사탕이 들어있다고 할 때 이 둘을 합치는 비용은 a + b라고 한다. 
그러므로 A와 B를 먼저 합치고 C를 합치는 경우 그 전체 비용은 a + b + a + b + c이며, 
B와 C를 먼저 합치고 A를 합치는 비용은 b + c + b + c + a 이므로 그 둘은 서로 같지 않을 수 있다.
 
예를 들어, 각각 2, 2, 5개가 포장되어 있다면 A(2)와 B(2)를 합치는 비용은 4. 합쳐진 것(4)과 C(5)를 합치는 비용은 9로 총 13이 최소비용이다.
현재 공장에 포장되어 있는 포장 개수 N과 각각 포장에 들어있는 사탕의 개수 ni가 주어질 때, 이들을 하나로 합치는데 들어가는 비용의 최소(C)를 구하라.


//입력 설명
첫 번째 줄에는 포장 개수 N(1<=N<=5000)이 주어진다.
두 번째 줄에는 포장에 들어있는 사탕의 개수 ni(1<=ni<=100)가 주어진다.

//출력 설명
최소 비용을 출력한다.

//입력 예시
3
2 2 5

//출력 예시
13
*/

//최소 비용으로 포장 다시 하기
#include <stdio.h>
#define TEST 3
#define MAXN ((int)5e3 + 10)
int N;//포장 개수

void swap(int *a, int *b)
{
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

#if TEST == 1
//(n * nlogn)
//정렬을 이용한 방법

int A[MAXN];        //포장에 들어있는 사탕개수
int tmp[MAXN];      //mergesort용
void InputData() 
{
    scanf("%d", &N);
    for (int i = 0; i < N; i++) 
    {
        scanf("%d", &A[i]);
    }
}

void mergesort(int s, int e) 
{
    if (s >= e) return;
    int i = s, k = s;
    int m = (s + e) / 2;
    int j = m + 1;
    
    mergesort(s, m); 
    mergesort(m + 1, e);
    
    while ((i <= m) && (j <= e)) 
    {
        if (A[i] <= A[j]) tmp[k++] = A[i++];
        else tmp[k++] = A[j++];
    }
    while (i <= m) tmp[k++] = A[i++];
    while (j <= e) tmp[k++] = A[j++];
    for (i = s; i <= e; i++) A[i] = tmp[i];
}

int solve() {
    int sum = 0;
    for (int i = 0; i < N - 1; i++) //n
    {
        mergesort(i, N - 1);        //n*logn
        A[i + 1] += A[i];           //제일 작은 두개 결합
        sum += A[i + 1];
    }
    return sum;
}

#elif TEST == 2
//최소요소 두개만 찾기(2 n^2)
int A[MAXN];                        //포장에 들어있는 사탕개수

void InputData() 
{
    scanf("%d", &N);
    for (int i = 0; i < N; i++) 
    {
        scanf("%d", &A[i]);
    }
}

/*
i는 s, s + 1이 가능하다
j는 i+1 ~ e가 가능하다
A[i]와 A[i+1] ~ A[e]의 값을 비교를 계속하면서,
A[i]값보다 작은 값이 나오면, swap해준다.
따라서, 반복문이 완료되면, A[i]에는 가장 작은 수가 저장되어있다.
*/
void sort(int s, int e) //2n
{//제일 작은 두개만 찾아서 정렬
    for (int i = s; i < s + 2; i++)         //2번
    {
        for (int j = i + 1; j <= e; j++)    //n번
        {
            if (A[i] <= A[j]) continue;
            swap(&A[i], &A[j]);
        }
    }
}

int solve() 
{
    int sum = 0;
    for (int i = 0; i < N - 1; i++)     //n번
    {
        sort(i, N - 1);
        A[i + 1] += A[i];               //제일 작은 두 개 결합
        sum += A[i + 1];
    }
    return sum;
}

#else
//우선순위큐 이용 O(nlogn)
int lastn;
int heap[MAXN];//minimum heap

void push(int d) 
{
    heap[++lastn] = d;
    int C = lastn;
    int P = C / 2;
    while ((P > 0) && (heap[P] > heap[C])) 
    {
        swap(&heap[P], &heap[C]); 
        C = P; 
        P = C / 2;
    }
}

int pop() 
{
    int ret = heap[1]; 
    heap[1] = heap[lastn--];
    int P = 1, L = 2, R = 3, C;
    while (L <= lastn) 
    {
        if (R > lastn) C = L;
        else C = (heap[L] <= heap[R]) ? L : R;
        if (heap[P] <= heap[C]) break;
        swap(&heap[P], &heap[C]); 
        P = C; 
        L = P * 2; 
        R = L + 1;
    }
    return ret;
}

void InputData() 
{
    int d;
    lastn = 0;
    scanf("%d", &N);
    for (int i = 0; i < N; i++) 
    {
        scanf("%d", &d); 
        push(d);
    }
}

int solve() 
{
    int sum = 0;
    for (int i = 0; i < N - 1; i++) 
    {
        int tmp = pop() + pop();    //제일 작은 포장 두개 꺼내서 결합
        sum += tmp;                 //비용에 누적합
        push(tmp);                  //결합한 포장 다시 저장
    }
    return sum;
}
#endif

int main() 
{
#if 1
    freopen("input.txt", "r", stdin);
#endif
    InputData();
    int ans = solve();
    printf("%d\n", ans);
    return 0;
}
/**************************************************************
    Problem: 1834
    User: AXQ7106
    Language: C
    Result: Accepted
    Time:5 ms
    Memory:1176 kb
****************************************************************/