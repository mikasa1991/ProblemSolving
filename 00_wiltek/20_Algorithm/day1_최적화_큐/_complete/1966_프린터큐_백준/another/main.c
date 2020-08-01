/*
https://www.acmicpc.net/problem/1966
프린터큐
*/
#include <stdio.h> 
#define MAXN (100 + 10) 

int N;//문서수 
int M;//문서번호 

typedef struct {
	int prio;	//우선순위
	int num; 	//문서번호
}DATA;

DATA que[MAXN * MAXN];//linear queue 

int wp, rp;

void push(int prio, int num) 
{
	que[wp].prio = prio; 
	que[wp].num = num; 
	wp++;
}

DATA front() 
{ 
	return que[rp]; 
}

void pop() 
{ 
	rp++; 
}

int empty() 
{ 
	return wp == rp; 
}

int priocnt[10];//각 우선순위별개수 파악용 

void Init() {
	wp = rp = 0;//큐 초기화 
	for (int i = 1; i <= 9; i++) 
		priocnt[i] = 0;//0으로 초기화 
}

void InputData() {
	int prio;
	scanf("%d %d", &N, &M);
	for (int i = 0; i < N; i++) 
	{
		scanf("%d", &prio);
		priocnt[prio]++;//우선 순위별 개수 파악 
		push(prio, i);//큐에 저장 
	}
}

int solve() {
	int seq = 0;
	for (int i = 9; i >= 1; i--) 
	{//높은 우선순위부터 출력 
		while (priocnt[i]) 
		{
			DATA cur = front(); 
			pop();
			if (cur.prio == i) 
			{//같은 우선순위는 출력 
				seq++; 
				priocnt[i]--;
				if (cur.num == M) return seq;//궁금한 문서면 종료 
			}
			else {//같은 우선순위 아니면 다시 push 
				push(cur.prio, cur.num);
			}
		}
	}
	return -1;//여기오면 코딩 오류(디버깅용) 
}

int main() {
	int T;
#if 1
	freopen("input.txt", "r", stdin);
#endif	
	scanf("%d", &T);

	for (int i = 1; i <= T; i++) 
	{
		Init();
		InputData();
		int ans = solve();
		printf("%d\n", ans);
	}
	return 0;
}