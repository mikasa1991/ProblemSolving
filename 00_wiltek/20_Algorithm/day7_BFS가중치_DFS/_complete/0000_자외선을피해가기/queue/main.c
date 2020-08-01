/*
영희는 자외선이 피부에 좋지 않기 때문에 이동 시 자외선에 노출되는 것을 
최소한으로 하고 싶어서 가는 길의 자외선 양을 모두 조사하였다.
값이 제 각각이어서 어떤 경로로 가야 좋을지 난감한 영희를 도와주자.
N*N 모양의 장소의 모든 길의 자외선 양이 주어지고 영희는 상하좌우 한 칸씩만 이동이 가능하다.
시작점(1,1)에서 도착점(N,N)까지 이동 시 자외선 합의 최소값을 찾아라.
예를 들어 3*3 장소의 자외선 양이 아래와 같다면 오른쪽처럼 이동하면 8만큼만 노출된다.
 
//입력 설명
첫 줄에 N(2≤N≤100)이 들어온다.
그 다음 줄부터 N개의 줄에 각각 N개씩 M(0≤M≤9)이 공백 없이 들어온다.

//출력 설명
출발점에서 도착점까지 자외선 합의 최소값을 출력한다. 

//입력 예시
3
041
253
620

//출력 예시
8
*/

#include <stdio.h>
#define DEBUG 1
#define MAXN (100 + 4)
#define MAXQ (MAXN * MAXN * 50)	///중복방문하므로 경험개수 * 10배 이상 필요(심한경우 10배로 부족)
#define DIR_N 4

int N;						//지도크기
char map[MAXN][MAXN];		//지도정보

#define INF ((int)1e9)		//올수없는 큰 값
int visit[MAXN][MAXN];		//경험표시에 가중치를 저장(이전보다 좋을경우만 확산)
typedef struct 
{
    //int r, c;//세로, 가로, 가중치는 저장불필요(visit배열에 저장하기때문에 중복됨)
    int r, c, t;
}QUE;

QUE que[MAXN * MAXN * 50];
int front = 0;
int rear = -1;
int q_size = 0;

void push(int r, int c, int t) 
{
    rear = (rear + 1) % MAXQ;
#ifdef DEBUG
    printf(" >push: (%d, %d, %d)\n", r, c, t);
#endif    
    que[rear].r = r; 
    que[rear].c = c;
    que[rear].t = t;
    q_size++; 
}

QUE pop() 
{ 
	QUE temp = que[front];
#ifdef DEBUG
    printf("<pop : (%d, %d, %d)\n", temp.r, temp.c, temp.t);
#endif  
	front = (front + 1) % MAXQ;
	q_size--;
	return temp; 
}

int is_empty() { return (q_size == 0); }

void print_visit()
{
	for (int r = 1; r <= N; r++) 
    {
        for (int c = 1; c <= N; c++) 
        {
            printf("%10d ", visit[r][c]);
        }
        puts("");
    }	
}

void init()
{
	front = 0;
	rear = -1;
	q_size = 0;

	for(int r = 1; r <= N; r++)
	{
		for(int c = 1; c <= N; c++)
		{
			visit[r][c] = INF;	//올수없는 큰 값으로 초기화(좋을때만 확산하기 위해)
		}
	}
}

/*
//시작위치는 접근가능이 명백하고, 가중치 갱신도 처음이라서, 체크할 필요없음.
시작위치 큐에 푸시
가중치 배열에 해당 위치에 가중치를 갱신

큐가 빌때까지 반복문
 top = 팝 하기
 
 top에서 접근가능한 위치이고, 가중치가 갱신되는 경우에 한해서,
 그 위치를 푸시하고, 가중치 배열에 해당 위치에 가중치를 갱신.

큐가 비면, 가중치 배열의 도착점이 자외선의 최솟값이 된다.
*/
int BFS() {
    
    int dr[] = { -1, 1, 0, 0 };
    int dc[] = { 0, 0, -1, 1 };
    
    //1.초기화
    init();

    //2.시작위치 큐에 저장
    push(1, 1, 0);
    visit[1][1] = 0;

    //3.반복문(큐가 빌때까지 확산해야 함, 중복방문하므로 가중치가 동일한 경우처럼 도착했다고 종료하면 안됨)
    while (!is_empty()) 
    {
        QUE cur = pop();
        if (visit[cur.r][cur.c] < cur.t) continue;
        for (int i = 0; i < DIR_N; i++) 
        {
            int nr = cur.r + dr[i];
            int nc = cur.c + dc[i];
            int nt = visit[cur.r][cur.c] + (map[nr][nc] - '0');

            if (map[nr][nc] == 0) continue;						//N*N 범위를 벗어나는 경우
            if (nt >= visit[nr][nc]) continue;					//이전보다 좋지 않으므로 확산안함
            push(nr, nc, nt);
            visit[nr][nc] = nt;
        #ifdef DEBUG
            print_visit();
        #endif
        }
    }
    //4.도착점의 visit값 리턴(초기값 그대로면 도착 실패임)
    return visit[N][N];
}

void InputData() 
{
    int r, c;
    scanf("%d", &N);
    //초기화: 0은 이동불가능한 영역으로 하고자.
    for (r = 0; r <= N + 1; r++) 
    {
        for (c = 0; c <= N + 1; c++) 
        {
            map[r][c] = 0;
        }
    }

    //지도정보입력
    for (r = 1; r <= N; r++) 
    {
        scanf("%s", &map[r][1]);
    }
}

void print_map()
{
	for (int r = 1; r <= N; r++) 
    {
        for (int c = 1; c <= N; c++) 
        {
            printf("%d ", map[r][c] - '0');
        }
        puts("");
    }	
}

int main() 
{
#ifdef DEBUG
	freopen("input.txt", "r", stdin);
#endif
    InputData();
#ifdef DEBUG
    print_map();
#endif
    int ans = BFS();
    printf("%d\n", ans);
    return 0;
}