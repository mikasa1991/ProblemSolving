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
#define DEBUG 	 1
#define MAXN 	 (100 + 4)
#define DIR_N    4
#define MAX_HEAP (MAXN * MAXN * 10)

int N;						//지도크기
char map[MAXN][MAXN];		//지도정보

#define INF ((int)1e9)		//올수없는 큰 값
int visit[MAXN][MAXN];		//경험표시에 가중치를 저장(이전보다 좋을경우만 확산)
typedef struct {
    int r, c, t;			//세로, 가로, 가중치
}HEAP;
int lastn;
HEAP heap[MAX_HEAP];		//minimum heap (보통 노드 개수 만큼 필요하나 중복방문하므로 약간 여유롭게 잡는다)
 
void swap(HEAP *a, HEAP *b)
{
    HEAP temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

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

void push(int r, int c, int t) 
{
    //if (visit[r][c] <= t) return;//이전보다 좋지 않으므로 확산안함
    //visit[r][c] = t;
#ifdef DEBUG
	printf(" >push:(%d, %d, %d)\n", r, c, t);
#endif
    heap[++lastn].r = r; 
    heap[lastn].c = c; 
    heap[lastn].t = t;
    int C = lastn, P = C / 2;
     
    while (P && (heap[P].t > heap[C].t)) 
    {
        swap(&heap[P], &heap[C]); 
        C = P; 
        P = C / 2;
    }
}
 
HEAP pop() 
{
    HEAP ret = heap[1];
#ifdef DEBUG
	printf("<pop:(%d, %d, %d)\n", ret.r, ret.c, ret.t);
#endif 
    heap[1] = heap[lastn--];
    int P = 1, L = 2, R = 3, C;
    while (L <= lastn) 
    {
        if (R > lastn) C = L;
        else C = (heap[L].t <= heap[R].t) ? L : R;
        if (heap[P].t <= heap[C].t) break;
        swap(&heap[P], &heap[C]);
        P = C; 
        L = P * 2; 
        R = L + 1;
    }
    return ret;
}

int is_empty() { return lastn == 0; }
 
void init()
{
	for (int r = 1; r <= N; r++) 
    {
        for (int c = 1; c <= N; c++) 
        {
            visit[r][c] = INF;	//올수없는 큰 값으로 초기화(좋을때만 확산하기 위해)
        }
    }
    lastn = 0;	//큐 초기화
}

int BFS() 
{
    int dr[] = { -1, 1, 0, 0 };
    int dc[] = { 0, 0, -1, 1 };

    //1.초기화
    init();

    //2.시작위치 큐에 저장
    push(1, 1, 0);
    visit[1][1] = 0;

    //3.반복문(꺼낸게 갖고 있는 값 중에 제일 좋은 값이므로 도착하면 성공으로 판단해도 됨)
    while (!is_empty()) 
    {
        HEAP cur = pop();
        if ((cur.r == N) && (cur.c == N)) return cur.t;		//도착 성공
        //if (visit[cur.r][cur.c] < cur.t) continue;			//가지치기 이미 더 좋은 경우가 진행되었음, skip
        
        for (int i = 0; i < DIR_N; i++) 
        {
            int nr = cur.r + dr[i]; 
            int nc = cur.c + dc[i];
            int nt = cur.t + (map[nr][nc] - '0');
 
            if (map[nr][nc] == 0) continue;					//범위 벗어남
            if (visit[nr][nc] <= nt) continue;				//이전보다 좋지 않으므로 확산안함
            push(nr, nc, nt);
            visit[nr][nc] = nt;
        #ifdef DEBUG
            print_visit();
        #endif
        }
    }
    //4.실패
    return -1;
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