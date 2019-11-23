/*
https://www.acmicpc.net/problem/6549
*/
#include <stdio.h>

#define DEBUG 1

#ifdef DEBUG
#define MAXN 7
#else
#define MAXN ((int)1e5 + 10)
#endif
typedef struct 
{
    int h, p;//높이, 위치
}STK;

STK stack[MAXN];//FA stack
int sp;

void push(int h, int p) { stack[++sp].h = h; stack[sp].p = p; }
void pop() { sp--; }
STK top() { return stack[sp]; }
int empty() { return sp == 0; }
int size() { return sp; }

int N;
int H[MAXN];

void init()
{
	sp = 0;
}

/*
로그와 히스토그램의 넓이를 확인하면서 이해하자.
*/
long long solve() 
{
    long long maxarea = 0;
    init();

    for (int i = 0; i < N; i++) 
    {
        int p = i;

        //스택이 비어있지 않고, top의 높이가 H[i]이상이라면, 반복문인데,
        while (!empty() && (top().h >= H[i])) 
        {
            long long area = (long long)top().h * (i - top().p);
        #ifdef DEBUG
            printf("area %lld = h %lld * w %d\n", area, (long long)top().h, (i - top().p));
        #endif
            if (maxarea < area) maxarea = area;
            p = top().p;
        #ifdef DEBUG
            printf("<pop_(%d, %d)\n", stack[sp].h, stack[sp].p); 
        #endif
            pop();
        }
    #ifdef DEBUG
        printf(">push_(%d, %d)\n", H[i], p);
    #endif
        push(H[i], p);
    }

    //puts("----------------------");
    while (!empty()) 
    {
        long long area = (long long)top().h * (N - top().p);
    #ifdef DEBUG
        printf("area %lld = h %lld * w %d\n", area, (long long)top().h, (N - top().p));
    #endif
        if (maxarea < area) maxarea = area;
    #ifdef DEBUG
        printf("<pop_(%d, %d)\n", stack[sp].h, stack[sp].p);
    #endif
        pop();
    }

    return maxarea;
}

int InputData() 
{
    scanf("%d", &N);
    if (N == 0) return 0;			//N이 0이면 종료
    for (int i = 0; i < N; i++) 
    {
        scanf("%d", &H[i]);
    }
    return 1;						//N이 0이 아니므로 정상 리턴
}

int main() 
{
#ifdef DEBUG
	freopen("input.txt", "r", stdin);
#endif
    while(1)
    {
        if (InputData() == 0) break;
        long long ans = solve();
        printf("%lld\n", ans);
    }
    return 0;
}