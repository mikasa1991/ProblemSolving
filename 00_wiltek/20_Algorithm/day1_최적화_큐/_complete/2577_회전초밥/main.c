/*
http://jungol.co.kr/xpert/viewp.php?bo_table=&bo_table&id=2577&sca=50
*/

/*
O(NK)로 접근하면 제한 실행시간내에 못 들어온다.
여기서는 대안으로 sliding window 알고리즘을 사용한다.
*/

#include <stdio.h> 

#define DEBUG 1

#ifdef DEBUG
#define MAXN  8
#define MAXDK 30

#else
#define MAXN ((int)3e6 + 10) 
#define MAXDK ((int)3e3 + 10) 
#endif

int N;                  //접시수 
int D;                  //가짓수 
int K;                  //연속먹는 접시수 
int C;                  //쿠폰번호 
int A[MAXN + MAXDK];    //초밥번호; MAXDK를 더하는 이유는 모듈러 연산은 피하고자 
int ckcnt[MAXDK];     //초밥종류 파악용(테스트 케이스 여러개면 반드시 초기화 필요) 

void InputData() 
{
    scanf("%d %d %d %d", &N, &D, &K, &C);
    for (int i = 0; i < N; i++) 
    {
        scanf("%d", &A[i]);
    }
}

int solve() 
{
    int maxv = 0; 
    int var = 1;                          //먹을 수 있는 초밥 가짓 수
    
    ckcnt[C] = 1;                         //쿠폰 초밥 미리 먹고 시작 
    
    //0 ~ (K - 1)
    for (int i = 0; i < K; i++) 
    {
        if (ckcnt[A[i]]++ == 0) var++;    //0에서 증가되는 경우는 처음먹는 초밥이므로 종류 증가 
        A[N + i] = A[i];                  //뒤에 K개만큼 복사 
    }
    
    maxv = var;
    
    //K ~ (N + K -2)
    for (int i = K; i < N + K - 1; i++)     //sliding window기법 활용 
    { 
        if (--ckcnt[A[i - K]] == 0) var--;  //이번 체크에서 제외되는 초밥 제거 후 0이면 종류 감소 
        if (ckcnt[A[i]]++ == 0) var++;      //0에서 증가되는 경우는 처음먹는 초밥이므로 종류 증가 
        if (maxv < var) maxv = var;
    }
    return maxv;
}

int main() 
{
#ifdef DEBUG
    freopen("input.txt", "r", stdin);
#endif
    InputData();
    int ans = solve();
    printf("%d\n", ans);
    return 0;
}