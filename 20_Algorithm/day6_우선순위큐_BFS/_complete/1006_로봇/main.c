/*
http://jungol.co.kr/xpert/viewp.php?bo_table=sm_bank&id=1006&alcate=&mtitle=%EB%AC%B8%EC%A0%9C%EC%9D%80%ED%96%89&al=003&altitle=&alname=&altag=&page=1
*/
#include <stdio.h>
#define DEBUG 1
#define MAXN (100 + 4)
int H, W;                       //세로, 가로 크기
int map[MAXN][MAXN];            //지도 정보
int sh, sw, sd;                 //시작 세로, 가로, 방향
int eh, ew, ed;                 //도착 세로, 가로, 방향

                                //방향 1:동, 2:서, 3:남, 4:북
int visit[MAXN][MAXN][5];       //경험표시(방향이 있으므로 3차원 배열을 이용) 방향도 고려해야함
typedef struct 
{
    int h, w, d, t;             //세로, 가로, 방향, 명령횟수
}QUE;

QUE que[MAXN * MAXN * 4];       //경험개수만큼 확보해야함
int wp, rp;

void push(int h, int w, int d, int t) 
{
    if (visit[h][w][d] != 0) return; //이미 경험한 경우임
    visit[h][w][d] = 1;
#ifdef DEBUG
    printf(" >push:(%d, %d, %d, %d)\n", h, w, d, t);
#endif
    que[wp].h = h; 
    que[wp].w = w; 
    que[wp].d = d; 
    que[wp].t = t; 
    wp++;
}

QUE front() { return que[rp]; }
void pop() 
{
#ifdef DEBUG
    printf("<pop:(%d, %d, %d, %d)\n", que[rp].h, que[rp].w, que[rp].d, que[rp].t);
#endif 
    rp++; 
}
int empty() { return wp == rp; }

void InputData() 
{
    scanf("%d %d", &H, &W);

    //테스트 케이스 여러개면 map배열 초기화 필요) [0][0]~[H+1][W+1]까지 모두 0으로 초기화
    //혹은 1로 초기화(0으로 초기화 했으면 지도 내용은 반전시키면됨)
    for ( int i = 0; i <= H + 1; i++) 
    {
        for ( int j = 0; j <= W + 1; j++) 
        {
            map[i][j] = 1;//map[i][j] = 0;
        }
    }
    for (int i = 1; i <= H; i++)
    {
        for (int j = 1; j <= W; j++) 
        {
            scanf("%d", &map[i][j]);
            //map[i][j] ^= 1;//0으로 초기화 했으면 지도 내용은 반전시킴
        }
    }
    scanf("%d %d %d", &sh, &sw, &sd);
    scanf("%d %d %d", &eh, &ew, &ed);
}

int BFS() 
{
    int dh[] = { 0, 0,  0, 1, -1 };     //방향 1:동, 2:서, 3:남, 4:북
    int dw[] = { 0, 1, -1, 0,  0 };
    QUE cur = { 0, 0, 0, 0 };
    
    //1.초기화
    //테스트 케이스 여러개면 visit배열 초기화 필요[1][1][1]~[H][W][4]까지 모두 0으로 초기화
    wp = rp = 0;//큐 초기화
    
    //2.시작위치 큐에 저장
    push(sh, sw, sd, 0);
    while (!empty())    //3.반복문 
    {
        cur = front(); 
        pop();
        if ((cur.h == eh) && (cur.w == ew) && (cur.d == ed)) return cur.t;//도착 성공
        
        //1.진행 방향으로 1~3칸 전진
        for (int i = 1; i <= 3; i++) {
            int nh = cur.h + dh[cur.d] * i; 
            int nw = cur.w + dw[cur.d] * i;
            
            if (map[nh][nw] == 1) break;//레일이 없거나 범위 벗어났으므로 정지
            push(nh, nw, cur.d, cur.t + 1);
        }
        
        //2.방향 전환(남북일 경우 => 동서, 동서일 경우 => 남북)
        if (cur.d >= 3) {                           //남북일 경우
            push(cur.h, cur.w, 1, cur.t + 1);//동
            push(cur.h, cur.w, 2, cur.t + 1);//서
        }
        else {                                      //동서일 경우
            push(cur.h, cur.w, 3, cur.t + 1);//남
            push(cur.h, cur.w, 4, cur.t + 1);//북
        }
    }

    //4.중복방문하지 않고 목적지가 있는 경우 실패
    return -1;                                      //이 문제는 이런 경우 없지만 디버깅을 위해 추가
}
int main() 
{
#ifdef DEBUG
    freopen("input.txt", "r", stdin);
#endif
    InputData();
    int ans = BFS();
    printf("%d\n", ans);
    return 0;
}
/**************************************************************
    Problem: 1815
    User: AXQ7106
    Language: C
    Result: Accepted
    Time:3 ms
    Memory:2088 kb
****************************************************************/