/*
문제 설명
소들은 농부 존의 농장을 탈출하는 대담한 계획을 세웠다. 그들은 작은 고무 보트를 구했고 한 밤중에 농장 경계에 흐르는 강을 보트를 타고 건너려는 계획이다. 그 계획은 완벽해 보였다. 작은 고무 보트가 소들의 무게를 견디지 못한다는 사실을 알기 전까지는…
 
N마리의 소(1≤N≤20)들의 무게는 각각 W_1, …, W_N이다. 보트가 침몰하지 않을 만큼 가벼운 소들을 선별해야 한다. 불행하게도, 소들은 산수를 못하기로 유명하다. 10진법을 사용하는 소들은 소들의 무게를 더하다가 자리올림이 발생하는 경우 그 소는 보트를 사용하기에는 너무 무거운 소라고 판단한다. 자리올림이 발생하지 않고 더할 수 있는 무게가 보트를 사용할 수 있는 가벼운 무게이다.
 
당신이 할 일은 소들을 도와서 보트를 탈 수 있는 소들의 최대 수를 구하는 것이다. 즉, 소들의 무게들을 모두 더했을 때 자리올림이 발생하지 않게 하는 소들의 최대 수를 구하는 것이다.

* C 제출은 다음 Template을 복사하여 코드를 작성하시오.
 
#include <stdio.h>
 
int main(void)
{
      // 여기서부터 작성
 
      return 0;
}
* C++ 제출은 다음 Template을 복사하여 코드를 작성하시오.
 
#include <iostream>
using namespace std;
 
int main(void)
{
      // 여기서부터 작성
 
      return 0;
}
* JAVA 제출은 다음 Template을 복사하여 코드를 작성하시오.
 
import java.util.Scanner;
 
public class Main {
 
      public static void main(String[] args) {
 
            // 여기서부터 작성
 
      }
}
입력 설명
첫 줄에 소들의 수 N(1≤N≤20)이 주어진다.
두 번째 줄부터 N 줄에 걸쳐 각 소의 무게(W_i)가 입력된다. (정수, 1≤W_i≤100,000,000)
출력 설명
무게를 모두 더했을 때 어떤 자리에서도 자리올림이 발생하지 않는 소들의 최대 수를 출력하라.
입력 예시
5
522
6
84
7311
19
출력 예시
3
*/

//농장 탈출(조합 문제임)
#include <stdio.h>
#define DEBUG 1
int N;				//소마리수
int W[20 + 10];		//소무게
int sol;			//최대로 태운 마리수

void InputData() {
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {//소 인덱스
        scanf("%d", &W[i]);
    }
}

int check(int a, int b) 
{
    while (a && b) {
        if (a % 10 + b % 10 >= 10) return 0;	//자리 올림 발생
        a /= 10; b /= 10;
    }
    return 1;									//올림 발생 안함, 성공
}
 
void DFS(int s, int n, int sum) {//인덱스, 태운 마리수, 태운 무게합 //조합
    if (sol < n) sol = n;					//이전 답보다 좋으면 갱신
    if (sol >= n + N - s) return;			//가지치기 남은 소를 모두 태워도 이전 답보다 안좋음
    for (int i = s; i < N; i++) 
    {//소 인덱스
        if (!check(sum, W[i])) continue;	//i번째 소는 태울수없음
        DFS(i + 1, n + 1, sum + W[i]);
    }
}
 
int solve() {
    sol = 0;
    DFS(0, 0, 0);							//인덱스, 태운 마리수, 태운 무게합
    return sol;
}
 
int main(void) 
{
#ifdef DEBUG
	freopen("input.txt", "r", stdin);
#endif
    InputData();
    int ans = solve();
    printf("%d\n", ans);
    return 0;
}

/**************************************************************
    Problem: 1910
    User: AXQ7106
    Language: C
    Result: Accepted
    Time:2 ms
    Memory:1156 kb
****************************************************************/