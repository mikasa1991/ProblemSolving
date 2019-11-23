/*
문제 설명
광규네 집에는 총 N개의 스위치가 있고 1번부터 N번까지 번호가 붙어있다. 광규는 취미가 이 스위치들을 켜고 끄는 것이다. 광규는 2가지 방법으로 스위치를 갖고 논다.
1.    A번부터 B번 사이의 스위치 상태를 반전시킨다.
2.    C번부터 D번 사이의 스위치 중 켜져 있는 스위치의 개수를 세는 것이다.
광규가 위와 같은 조작을 하였을 때의 결과를 알아보자
* C 제출은다음 Template을복사하여코드를작성하시오.
 
#include <stdio.h>
 
int main(void)
{
      // 여기서부터작성
 
      return 0;
}
* C++ 제출은다음 Template을복사하여코드를작성하시오.
 
#include <iostream>
using namespace std;
 
int main(void)
{
      // 여기서부터작성
 
      return 0;
}
* JAVA 제출은다음 Template을복사하여코드를작성하시오.
 
import java.util.Scanner;
 
public class Main {
 
      public static void main(String[] args) {
 
            // 여기서부터작성
 
      }
}
입력 설명
첫 번째 줄에는 스위치의 개수 N과 처리할 일의 개수 M이 공백으로 구분되어 입력된다 (2≤N≤100,000) (1≤M≤100,000)
두 번째 줄부터 M줄에 걸쳐 처리할 일의 정보가 3개의 정수 형태로 입력된다. 3개의 정수 O, S, T는 공백으로 구분되어 있다. O의 값이 0이면 S부터 T까지 스위치 상태를 반전시킨다. 1이면 S부터 T까지 스위치 중 켜져 있는 스위치의 개수를 묻는 것이다.
초기에는 모든 스위치가 꺼져 있다.
출력 설명
입력 중 켜져 있는 스위치의 개수를 묻는 명령에 대한 답을 한 줄에 하나씩 출력한다.
*/

#include <stdio.h>

#define DEBUG 1
#define MAXT (1 << 18)//N보다 크거나 같은 2의 제곱수의 2배 공간 필요(2^17이 12만정도이므로 2^18 필요)
int N;//원소의개수
int M;//처리할 일의 개수
int tree[MAXT];//스위치
int lazy[MAXT];//lazy propagation 용
void InitTree(int n, int s, int e) {//모두 꺼진 상태므로 모든 노드 0으로 초기화
    lazy[n] = tree[n] = 0;
    if (s == e) {//leaf node
        return;
    }
    int L = n * 2, R = L + 1, m = (s + e) / 2;
    InitTree(L, s, m); InitTree(R, m + 1, e);
}
void lazypropagation(int n, int s, int e) {
    if (!(lazy[n] & 1)) return;//짝수면 할 필요없음(원래대로됨)
    int L = n * 2, R = L + 1;
    tree[n] = e - s + 1 - tree[n];
    if (s != e) {//자식노드 있으면 전파
        lazy[L] += lazy[n]; 
        lazy[R] += lazy[n];
    }
    lazy[n] = 0;
}
void update(int n, int s, int e, int qs, int qe) {
    lazypropagation(n, s, e);
    if ((qe < s) || (e < qs)) return;
    int L = n * 2, R = L + 1, m = (s + e) / 2;
    if ((qs <= s) && (e <= qe)) {
        tree[n] = e - s + 1 - tree[n];
        if (s != e) 
        {//자식노드 있으면 표시
            lazy[L] += 1; lazy[R] += 1;
        }
        return;
    }
    update(L, s, m, qs, qe); 
    update(R, m + 1, e, qs, qe);
    tree[n] = tree[L] + tree[R];
}

int query(int n, int s, int e, int qs, int qe) {
    lazypropagation(n, s, e);
    if ((qe < s) || (e < qs)) return 0;//범위 벗어남, 의미 없는 값을 리턴(결과에 영향을 안주는값)
    if ((qs <= s) && (e <= qe)) return tree[n];//관리 범위가 쿼리 범위 이내이므로 현재값 리턴
    int L = n * 2, R = L + 1, m = (s + e) / 2;
    return query(L, s, m, qs, qe) + query(R, m + 1, e, qs, qe);
}

int main()
{
#ifdef DEBUG
    freopen("input.txt", "r", stdin);
#endif
    int c, s, e;
    scanf("%d %d", &N, &M);
    InitTree(1, 1, N);//테스트 케이스 여러개일 경우필요(한개일 경우 필요없음)
    for (register int i = 1; i <= M; i++) {
        scanf("%d %d %d", &c, &s, &e);
        if (c == 0) update(1, 1, N, s, e);
        else printf("%d\n", query(1, 1, N, s, e));
    }
    return 0;
}
/**************************************************************
    Problem: 2942
    User: AXQ7106
    Language: C
    Result: Accepted
    Time:101 ms
    Memory:3204 kb
****************************************************************/