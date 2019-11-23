/*
문제 설명
배열이 주어지고 특정 구간의 합을 구하는 일은 prefix sum 테이블을 만들어 손쉽게 할 수 있다. 하지만 중간에 배열의 값이 바뀌게 되면 prefix sum 배열을 새롭게 바꿔야 하기 때문에 자주 값이 바뀌는 상황이라면 비효율적인 방법이 된다.
 
배열이 주어지고 구간의 합을 구해야 하는 여러 개의 상황이 주어진다. 그리고 구간의 합을 한번 구한 뒤에는 반드시 배열상 하나의 값이 증가되는 상황이다.
 
 이런 문제를 해결할 때는 Segment Tree나 Fenwick Tree와 같은 Tree를 사용하면 빠른 시간 안에 변화에 대한 갱신과 구간의 합을 얻어낼 수 있다. Segment Tree나 Fenwick Tree를 이용해서 문제들 해결해보자.
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
첫째 줄에는 데이터의 수 N(1<=N<=50000), 그리고 구해야 할 구간에 대한 정보의 수 Q(2<=Q<=200000) 개가 주어진다.
둘째 줄에는 배열의 데이터 Di가 N개 주어진다. (1<= Di <=100)
셋째 줄부터 Q줄에 구간에 대한 정보가 주어진다.
각 구간에 대한 정보는 Rs, Re, I, C 총 4개의 값이 주어진다.
Rs, Re는 합을 구해야 할 구간의 시작지점과 끝 지점이다. (1<= Rs ,Re <=N)
I, C는 구간의 합을 구한 후 변경해야 할 데이터에 대한 정보이다.
I는 변경할 데이터의 위치번호(1<= I <=N), C는 데이터의 증가될 값이다. (1<= Ci <=10)
출력 설명
각 줄에 구간의 합에 대한 결과를 출력한다.
*/

//구간의 합 구하기(segment tree)
#include <stdio.h>

#define DEBUG 1
#define MAXN ((int)5e4 + 10)
#define MAXT (1 << 17)//N보다 크거나 같은 2의 제곱수의 2배 공간 필요(2^16이 65,536이므로 2^17 필요)
int N;//원소의개수
int Q;//구간의개수
int A[MAXN];//요소 값
int tree[MAXT];
 
int I, C;
int MAXV(int a, int b) {
    return (a > b) ? a : b;
}
void InitTree(int n, int s, int e) {
    if (s == e) {//leaf node
        tree[n] = A[s]; return;
    }
    int L = n * 2, R = L + 1, m = (s + e) / 2;
    InitTree(L, s, m); InitTree(R, m + 1, e);
    tree[n] = tree[L] + tree[R];
}
 
void update_tree(int n, int s, int e, int i, int c) {
    if (s == e && s == i) {
        tree[n] += c;
        return;
    }
    int L = n * 2, R = L + 1, m = (s + e) / 2;
    
    if (i <= m) update_tree(L, s, m, i, c);
    else 		update_tree(R, m + 1, e, i, c);
    
    tree[n] = tree[L] + tree[R];
}
int query(int n, int s, int e, int qs, int qe) {
    if ((qe < s) || (e < qs)) return 0;				//범위 벗어남, 의미 없는 값을 리턴(결과에 영향을 안주는값)
    if ((qs <= s) && (e <= qe)) return tree[n];		//관리 범위가 쿼리 범위 이내이므로 현재값 리턴
    int L = n * 2, R = L + 1, m = (s + e) / 2;
    return query(L, s, m, qs, qe) + query(R, m + 1, e, qs, qe);
    //#define으로 MAXV를 만들면 위와 같은 식으로 하면 안됨 단순변환되므로 중복호출됨
}
void InputData() {
    scanf("%d %d", &N, &Q);
    for (int i = 1; i <= N; i++) {
        scanf("%d", &A[i]);
    }
}
void solve() {
    int s, e;
    InitTree(1, 1, N);//segment tree 만들기
    for (int i = 1; i <= Q; i++) {
        scanf("%d %d %d %d", &s, &e, &I, &C);
        printf("%d\n", query(1, 1, N, s, e));
        update_tree(1, 1, N, I, C);
    }
}
int main(void) 
{
#ifdef DEBUG
	freopen("input.txt", "r", stdin);
#endif
    InputData();
    solve();
    return 0;
}
/**************************************************************
    Problem: 2934
    User: AXQ7106
    Language: C
    Result: Accepted
    Time:217 ms
    Memory:1864 kb
****************************************************************/