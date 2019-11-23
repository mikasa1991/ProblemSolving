/*
문제 설명
태균이는 영화 블루레이 수집가이다. 그는 블루레이를 쌓아서 보관한다. 보고 싶은 영화가 있으면, 영화의 위치를 찾은 다음 쌓아놓은 것이 무너지지 않게 조심스럽게 빼서 본다. 영화를 다 본 후에는 가장 위에 놓는다.
태균이는 블루레이가 매우 많기 때문에, 위치를 찾는데 시간이 너무 오래 걸린다 .각 블루레이의 위치는 찾으려는 블루레이의 위에 있는 개수만 알면 쉽게 구할 수 있다. 각 영화는 블루레이 표지에 붙어있는 숫자로 쉽게 구별 할 수 있다
각 영화의 위치를 기록하는 프로그램을 작성하자. 태균이가 영화를 한 편 볼 때마다 그 블루레이의 위에 몇 개의 블루레이가 있었는지를 구해야 한다.
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
첫 번째 줄에 테스트 케이스 개수 T가 입력된다. (1≤T≤100)
두 번째 줄부터 각 테스트 케이스에 대한 정보가 두 줄씩 T개가 입력된다
각 테스트 케이스의 첫 번째 줄에는 태균이가 갖고 있는 영화 블루레이의 개수 N과 보려고 하는 영화의 개수 M이 공백으로 구분되어 입력된다. (1≤N,M≤100,000)
두 번째 줄에는 보려고 하는 영화의 번호가 순서대로 주어진다.
영화의 번호는 1부터 N까지 이며, 최초로 영화가 쌓여있는 순서는 1부터 증가하는 순서이다. 가장 위에 있는 영화의 번호는 1이다.
출력 설명
각 테스트 케이스의 결과를 M개의 정수로 공백으로 구분하여 출력한다. i번째 출력하는 수는 i번째로 영화를 볼 때 그 영화 위에 쌓여있던 블루레이의 개수이다. 태균이는 영화를 볼 때 마다 본 블루레이는 가장 위에 올려 놓는다.
*/

//영화 블루레이 수집(segment tree)
#include <stdio.h>
#define DEBUG 1
#define MAXN ((int)1e5 + 10)
#define MAXM ((int)1e5 + 10)
#define MAXT (1 << 19)//M+N보다 크거나 같은 2의 제곱수의 2배 공간 필요(2^18이 25만정도이므로 2^19 필요)

int N;//블루레이 개수
int M;//볼 영화 개수
int NN;//총개수
int pos[MAXN];//각 블루레이가 실제 놓인곳
int tree[MAXT];//본 영화를 놓을 공간이 필요함, 즉, M개의공간도 같이 확보해야 함

void InitTree(int n, int s, int e) 
{
    tree[n] = 0;
    if (s == e) return;
    int L = n * 2, R = L + 1, m = (s + e) / 2;
    InitTree(L, s, m); 
    InitTree(R, m + 1, e);
}

int query(int n, int s, int e, int qs, int qe) 
{
    if ((qe < s) || (e < qs)) return 0;
    if ((qs <= s) && (e <= qe)) return tree[n];
    int L = n * 2, R = L + 1, m = (s + e) / 2;
    return query(L, s, m, qs, qe) + query(R, m + 1, e, qs, qe);
}

void update(int n, int s, int e, int idx, int val) 
{
    if (s == e) {//leaf node
        tree[n] += val; return;
    }
    int L = n * 2, R = L + 1, m = (s + e) / 2;
    if (idx > m) update(R, m + 1, e, idx, val);
    else update(L, s, m, idx, val);
    tree[n] = tree[L] + tree[R];
}

void solve() 
{
    int v, vp = M;
    for (register int i = 1; i <= M; i++) 
    {
        scanf("%d", &v);
        printf("%d ", query(1, 1, NN, 1, pos[v] - 1));
        update(1, 1, NN, pos[v], -1);//본 영화 그 자리에서 제거
        pos[v] = vp--;//본 영화가 놓일 자리 계산
        update(1, 1, NN, pos[v], 1);//새로운 자리에 추가
    }
    printf("\n");
}

void InputData() 
{
    scanf("%d %d", &N, &M); NN = M + N;
    InitTree(1, 1, NN);//tree 초기화
    for (register int i = 1; i <= N; i++) {
        pos[i] = M + i; 
        update(1, 1, NN, pos[i], 1);//볼영화 개수만큼 비워놓고 저장
    }
}

int main(void) 
{
#ifdef DEBUG
    freopen("input.txt", "r", stdin);
#endif
    int T;
    scanf("%d", &T);
    for (int t = 1; t <= T; t++) {
        InputData();
        solve();
    }
    return 0;
}
/**************************************************************
    Problem: 2939
    User: AXQ7106
    Language: C
    Result: Accepted
    Time:254 ms
    Memory:3596 kb
****************************************************************/