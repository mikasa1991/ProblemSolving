/*
https://www.acmicpc.net/problem/1966
프린터큐
*/
#include <stdio.h> 
#define MAXN 	  100
#define PRIOR_N   9

int N;								//문서수 
int M;								//문서번호 

typedef struct _DATA{
	int prio;						//우선순위
	int num; 						//문서번호
}DATA;

DATA que[MAXN]; 
int front = 0;
int rear = -1;
int queue_size = 0;

int priocnt[PRIOR_N+1];				//각 우선순위별개수 파악용

void enqueue(int prio, int num)
{
	rear = (rear + 1) % MAXN;
	que[rear].prio = prio;
	que[rear].num = num;
	queue_size++;
}

DATA dequeue()
{
	DATA temp = que[front];
	front = (front + 1) % MAXN;
	queue_size--;
	return temp;
}

void Init() 
{
	front = 0;
	rear = -1;
	for (int i = 1; i <= PRIOR_N; i++)
	{
		priocnt[i] = 0;								//0으로 초기화 
	} 
}

void InputData() {
	int prio;
	scanf("%d %d", &N, &M);
	for (int i = 0; i < N; i++) 
	{
		scanf("%d", &prio);
		priocnt[prio]++;							//우선 순위별 개수 파악 
		enqueue(prio, i);							//큐에 저장 
	}
}

/*
dequeue한다
 같은 우선순위라면,
  seq++
  내가 알고자하는 번호라면, seq를 반환하고 종료한다.
 다른 우선순위라면, enqueue한다
*/
int solve() 
{
	int seq = 0;
	for (int i = PRIOR_N; i >= 1; i--) 
	{												//높은 우선순위부터 출력 
		while (priocnt[i]) 
		{
			DATA cur = dequeue(); 

			if (cur.prio == i)						//같은 우선순위라면, 
			{										 
				seq++; 
				priocnt[i]--;
				if (cur.num == M) return seq;		 
			}
			else 									//같은 우선순위가 아니다; 여기서는 i라는 우선순위보다 작다는거다
			{										
				enqueue(cur.prio, cur.num);
			}
		}
	}
	return -1;										//여기오면 코딩 오류(디버깅용) 
}

int main() {
	int T;
#if 0
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