/*
http://jungol.co.kr/xpert/viewp.php?bo_table=sm_bank&id=2788&alcate=&mtitle=%EB%AC%B8%EC%A0%9C%EC%9D%80%ED%96%89&al=003&altitle=&alname=&altag=&page=1
*/

#include <stdio.h>
#define DEBUG 1

#define MAXN ((int)1e3 + 10)
int N;          //연잎수
int A[MAXN];    //연잎좌표
int tmp[MAXN];  //merge sort용

void mergesort(int s, int e)                        //오름차순 정렬
{
    if (s >= e) return;                             //분할 불가능, 종료
    int i = s, m = (s + e) / 2, j = m + 1, k = s;
    mergesort(s, m); 
    mergesort(m + 1, e);
    while ((i <= m) && (j <= e)) 
    {
        if (A[i] <= A[j]) 
            tmp[k++] = A[i++];
        else 
            tmp[k++] = A[j++];
    }
    while (i <= m) tmp[k++] = A[i++];
    while (j <= e) tmp[k++] = A[j++];
    for (int i = s; i <= e; i++) A[i] = tmp[i];
}

int bslow(int s, int e, int d)  //d보다 크거나 같은 요소 중 제일 작은 인덱스
{
    int sol = -1, m;
    while (s <= e)
    {
        m = (s + e) / 2;
        if (A[m] >= d) 
        {
            sol = m; 
            e = m - 1; 
        }
        else s = m + 1;
    }
    return sol;
}

int bsup(int s, int e, int d)   //d보다 작거나 같은 요소 중 제일 큰 인덱스
{
    int sol = -1, m;
    while (s <= e) 
    {
        m = (s + e) / 2;
        if (A[m] <= d) 
        { 
            sol = m; 
            s = m + 1; 
        }
        else e = m - 1;
    }
    return sol;
}

int solveN2logN()
{
    int cnt = 0;
    mergesort(0, N - 1);                                        //오름차순 정렬
    for (int a = 0; a < N - 2; a++) 
    {
        for (int b = a + 1; b < N - 1; b++) 
        {
            int first = A[b] - A[a];                            //첫번째 뛴거리
            
            /*
            파라미터를 b+1, N-1로 하면 안되는 이유는?
            
            파라미터를 b+1, N-1로 하고,
            예를 들어, 다음과 같은 상황을 가정하자.
            
            1 4 5 6 11
            a: 4, b: 5
            1배이상의 하한은 6
            2배이하의 상한은 없다

            그러면 여기서 cnt가 하나 증가해야하는데,
            cnt += up - low + 1; 이와 같은 로직으로 계산이 불가능하다.

            따라서, 파라미터를 0, N-1로 해야한다.
            그렇게하면, 하한이 존재한다는 가정 하에 하한이 안 나올 수가 없다.
            1배이상의 하한은 6
            2배이하의 상한은 6
            */
            //int low = bslow(b+1, N - 1, A[b] + first);        //1배 이상중에 제일 작은 인덱스
            int low = bslow(0, N - 1, A[b] + first);            //1배 이상중에 제일 작은 인덱스
            if (low < 0) break;   
            
            //int up = bsup(b+1, N - 1, A[b] + first * 2);      //2배 이하중에 제일 큰 인덱스
            int up = bsup(0, N - 1, A[b] + first * 2);          //2배 이하중에 제일 큰 인덱스
            //if (up < 0) break;
            cnt += up - low + 1; 
        }
    }
    return cnt;
}

int solveN3() 
{
    int cnt = 0;
    mergesort(0, N - 1);                        //오름차순 정렬
    for (int a = 0; a < N - 2; a++)             //첫번째 연잎 인덱스
    {
        for (int b = a + 1; b < N - 1; b++)     //두번째 연잎 인덱스
        {
            int first = A[b] - A[a];            //첫번째 뛴거리
            
            for (int c = b + 1; c < N; c++)     //세번째 연잎 인덱스
            {
                int second = A[c] - A[b];       //두번째 뛴거리
                if (second < first) continue;   //뛴 거리가 부족하면 다음 연잎 체크 필요
                if (second > first * 2) break;  //이미 2배보다 멀리 뛰었으므로 뒤 연잎은 해볼필요 없음
                cnt++;                          //도약 횟수 증가
            }
        }
    }
    return cnt;
}

void InputData() {
    scanf("%d", &N);
    for (int i = 0; i < N; i++) 
    {
        scanf("%d", &A[i]);
    }
}

int main() 
{
#ifdef DEBUG
    freopen("input.txt", "r", stdin);
#endif
    InputData();
    //int ans = solveN3();
    int ans = solveN2logN();
    printf("%d\n", ans);
    return 0;
}