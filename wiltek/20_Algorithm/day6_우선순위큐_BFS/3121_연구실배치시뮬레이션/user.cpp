/**************************************************************
    Problem: 3121
    User: dong_hee.lee
    Language: C++
    Result: Success
    Time:375 ms
    Memory:1324 kb
****************************************************************/
 
 
//(정올 실전문제:3121) 연구실 배치 시뮬레이션 
///=============== user.cpp ===============
#define MAXN (50 + 2)
#define MAXLAB (1000 + 1)
int map[MAXN][MAXN];
typedef struct {
    int h, w, d;//세로, 가로, 방향(0:동, 1:남, 2:서, 3:북)
}DATA;
DATA data[MAXLAB];//각 실험실 출발&도착 정보
int uniq;//visit배열에 표시할 유니크한 값(visit배열 초기화 불필요)
int visit[MAXN][MAXN][4];//[세로][가로][방향], 경험표시
typedef struct {
    int h, w, d, t;//세로, 가로, 방향, 시간
}QUE;
QUE que[MAXN * MAXN * 4];
int dh[] = { 0, 1,  0, -1 };//동남서북
int dw[] = { 1, 0, -1,  0 };
int wp, rp; 
int target;//도착 실험실 번호
int push(int h, int w, int d, int t) {
    int nd = (d + 1) % 4;//진행방향 오른쪽 방향
    int nh = h + dh[nd], nw = w + dw[nd];//진행방향 오른쪽 좌표
    if ((map[nh][nw] != 1) && (map[nh - dh[d]][nw - dw[d]] != 1)) return 0;//이 곳은 올수없음
    if ((map[h][w] == 1) || (visit[h][w][d] == uniq)) return 0;
    if (map[h][w] == 2) {//교차로
        for (register int i = 0; i < 4; i++) {
            if (visit[h][w][i] == uniq) continue;
            visit[h][w][i] = uniq;
            que[wp].h = h; que[wp].w = w; que[wp].d = i; que[wp].t = t; wp++;
        }
    }
    else {
        if ((h == data[target].h) && (w == data[target].w) && (d == data[target].d))
            return t;//도착 성공
        visit[h][w][d] = uniq;
        que[wp].h = h; que[wp].w = w; que[wp].d = d; que[wp].t = t; wp++;
    }
    return 0;
}
QUE pop() { return que[rp++]; }
bool empty() { return wp == rp; }
int maxn;//지도 크기
void initUser(int tableSize) {
    maxn = tableSize; register int i, j;
    for (i = 0; i <= tableSize + 1; i++) {
        for (j = 0; j <= tableSize + 1; j++) {
            map[i][j] = 0;
        }
    }
}
void makeLabRoom(int id, int r, int c, int h, int w, int vr, int vc) {
    register int i, j;
    for (i = 0; i < h; i++) {
        for (j = 0; j < w; j++) {
            map[r + i][c + j] = 1;
        }
    }
    int sr = r - 1, sc = c - 1, er = r + h, ec = c + w;
    map[sr][sc] = map[sr][ec] = map[er][sc] = map[er][ec] = 2;//회전가능한 모서리
    if (r == vr) {//윗면에 승차장 있음, 동쪽방향
        data[id].h = sr; data[id].w = vc; data[id].d = 0;
    }
    else if (vc == ec - 1) {//동쪽면에 승차장 있음, 남쪽방향
        data[id].h = vr; data[id].w = ec; data[id].d = 1;
    }
    else if (vr == er - 1) {//아랫면에 승차장 있음, 서쪽방향
        data[id].h = er; data[id].w = vc; data[id].d = 2;
    }
    else {//서쪽면에 승차장 있음, 북쪽방향
        data[id].h = vr; data[id].w = sc; data[id].d = 3;
    }
}
int getShortestPath(int s, int e) {
    wp = rp = 0; uniq++; target = e;//초기화
    if (push(data[s].h, data[s].w, data[s].d, 2) > 0) return 2;//시작위치 큐에 저장
    while (!empty()) {//반복문
        QUE tmp = pop();
        int ret = push(tmp.h + dh[tmp.d], tmp.w + dw[tmp.d], tmp.d, tmp.t + 1);
        if (ret > 0) return ret;//도착 성공
    }
    return -1;//실패(이 문제에서는 이런 경우 없음)
}