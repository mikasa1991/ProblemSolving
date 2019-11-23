/**************************************************************
    Problem: 3220
    User: dong_hee.lee
    Language: C
    Result: Success
    Time:25 ms
    Memory:1236 kb
****************************************************************/
 
 
//(정올 실전문제 : 3220) 퍼즐조각 맞추기2
#pragma warning (disable : 4996)
#include <stdio.h>
#define MAXN (50 * 50 + 5)
enum {RIGHT, DOWN, LEFT, UP};
int N, M, T, NN;//한변의 퍼즐개수, 퍼즐 한변의길이, 추가된퍼즐개수, 퍼즐총개수(N*N+T) 
int puzzle[MAXN][4];//각 퍼즐 4변의 모양값([0]:우, [1]:하, [2]:좌, [3]:상 순서임)
int rpuzzle[MAXN][4];//각 퍼즐에 4변에 결합될 모양값
int used[MAXN];//각 퍼즐 사용여부
int board[50][50];//퍼즐판
int c2d[128];//현재 모양에서 문자를 숫자로 변환시 사용
int rc2d[128];//결합될 모양에서 문자를 숫자로 변환시 사용
int R, C;//출력해야하는 퍼즐조각 행열
int same[MAXN];//각 퍼즐이 다른 퍼즐과 결합되는 개수파악
int calcode(char *s) {//3가지이므로 3진법으로 만들기 [0],[M-1]번째는 무조건평면이므로 제외해도 됨
    register int code = 0, i;
    for (i = 1; i < M - 1; i++) code = code * 3 + c2d[s[i]];
    return code;
}
int rcalcode(char *s) {
    register int code = 0, i;
    for (i = 1; i < M - 1; i++) code = code * 3 + rc2d[s[i]];
    return code;
}
void InputData() {
    char str[20]; int rev = 1;
    scanf("%d %d %d", &N, &M, &T);
    for (int i = 1; i < M - 1; i++) rev *= 3;
    rev -= 1;
    NN = N * N + T;//퍼즐 총 개수
    for (register int i = 0; i < NN; i++) {//퍼즐 인덱스
        for (register int j = 0; j < 4; j++) {//4면([0]:우, [1]:하, [2]:좌, [3]:상 순서임)
            scanf("%s", str);
            puzzle[i][j] = calcode(str);
            //rpuzzle[i][j] = rcalcode(str);
            rpuzzle[i][j] = rev - puzzle[i][j];
        }
    }
    scanf("%d %d", &R, &C);
}
void samecnt() {//시간복잡도 O(N^2)
    register int i, j;
    for (i = 0; i < NN; i++) {
        for (j = 0; j < NN; j++) {
            if (i == j) continue;
            if (puzzle[i][UP] == rpuzzle[j][DOWN]) same[i]++;//내 위쪽면과 결합되는 퍼즐개수(상대퍼즐은 아래측임)
            if (puzzle[i][LEFT] == rpuzzle[j][RIGHT]) same[i]++;//내 좌측면과 결합되는 퍼즐개수(상대퍼즐은 우측임)
        }
    }
}
int DFS(int r, int c) {
    if (c >= N) { r++; c = 0; }//가로가 넘어가면 세로 증가, 가로는 0
    if (r >= N) return 1;//세로가 넘어가면 완성(성공)
    for (register int i = 0; i < NN; i++) {//퍼즐 인덱스
        if (used[i]) continue;//이미 사용중
        if (r && (puzzle[i][UP] != rpuzzle[board[r - 1][c]][DOWN])) continue;
        if (c && (puzzle[i][LEFT] != rpuzzle[board[r][c - 1]][RIGHT])) continue;
        used[i] = 1; board[r][c] = i;//사용으로 표시 및 퍼즐판에 저장
        if (DFS(r, c + 1)) return 1;//성공이면 종료
        used[i] = 0;//표시 제거
    }
    return 0;//실패
}
void OutputData() {
    printf("%d\n", board[R][C]);//퍼즐판에 원하는 위치의 퍼즐 번호 출력
    for (register int i = 0; i < NN; i++) {//사용안된 조각 번호 출력
        if (used[i]) continue;//사용했음
        printf("%d ", i);
    }
    printf("\n");
}
void solve() {
    samecnt();//결합되는 퍼즐 개수 파악
    for (register int i = 0;; i++) {//결합되는 개수가 적은 퍼즐을 좌상단으로 놓고 완성해가기
        for (register int j = 0; j < NN; j++) {
            if (same[j] != i) continue;//같은 개수일 경우에만 시도
            used[j] = 1; board[0][0] = j;//좌상단 퍼즐이 j번째로 놓고 시도
            if (DFS(0, 1)) return;//성공하면 종료
            used[j] = 0;//표시 제거
        }
    }
}
void init() {
    c2d['M'] = 0;  c2d['0'] = 1;  c2d['F'] = 2;
    rc2d['M'] = 2; rc2d['0'] = 1; rc2d['F'] = 0;
}
int main() {
    freopen("input.txt", "r", stdin);
    init();
    InputData();
    solve();
    OutputData();
    return 0;
}