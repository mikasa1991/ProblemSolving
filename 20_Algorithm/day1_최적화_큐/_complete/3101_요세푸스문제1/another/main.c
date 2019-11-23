#include <stdio.h> 
#define MAXN (1 << 14) 
#define MOD (MAXN - 1) 

int N, K;
int que[MAXN];//circular queue 
int wp, rp;

void push(int d) 
{
    que[wp] = d;
    wp = (wp + 1) & MOD;    //(wp + 1) % MAXN 와 같은 효과 2의 제곱수에 한해서 동일한 동작함 
}
int front() 
{ 
    return que[rp]; 
}

void pop() 
{ 
    rp = (rp + 1) & MOD; 
}

int empty() 
{ 
    return wp == rp; 
}

void InputData() 
{
    scanf("%d %d", &N, &K);
}

void solve() 
{
    wp = rp = 0;//큐 초기화 

    for (int i = 1; i <= N; i++) 
        push(i);
    
    for (int i = 1; i < N; i++) 
    {//N-1개 순서찾기 
        for (int j = 1; j < K; j++) 
        {//K-1개는 다시 push 
            push(front()); 
            pop();
        }
        printf("%d ", front()); 
        pop();//K번째는 출력 
    }
    printf("%d\n", front()); 
    pop();//마지막 남은 한개 출력 
}

int main() {
#if 1
    freopen("input.txt", "r", stdin);
#endif
    InputData();
    solve();
    return 0;
}