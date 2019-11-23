/*
http://jungol.co.kr/xpert/viewp.php?bo_table=sm_bank&id=1124&alcate=&mtitle=%EB%AC%B8%EC%A0%9C%EC%9D%80%ED%96%89&al=003&altitle=&alname=&altag=&page=1
*/

#include <stdio.h>

#define DEBUG 1

#define MAX (100 + 10)
int paper[MAX][MAX];					//흰색도화지

void FillPaper(int sr, int sc, int er, int ec) 
{
    for (int r = sr; r < er; r++)		//sr ~ (er - 1) 
    {
        for (int c = sc; c < ec; c++)	//sc ~ (ec - 1)
        {
            paper[r][c] = 1;			//fill
        }
    }
}

void print_paper()
{
    for(int r = 0; r < 101; r++)
    {
        for(int c = 0; c < 101; c++)
        {
            printf("%d ", paper[r][c]);
        }
        puts("");
    }
}

void InputData() {
    int n, sc, sr;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) 
    {
        scanf("%d %d", &sc, &sr);
        FillPaper(sr, sc, sr + 10, sc + 10);
    }
}

int check(int sr, int sc, int er, int ec) 
{
    for (int r = sr; r <= er; r++) 
    {
        for (int c = sc; c <= ec; c++) 
        {
            if (paper[r][c] == 0) return 0;//직사각형 그려지지 않음
        }
    }
    return 1;//직사각형 그려짐
}

int solveN6() 
{
    int maxarea = 100; 
    int area = 0;
    for (int sr = 0; sr < 100; sr++)						//시작 세로 위치 
    {
        for (int sc = 0; sc < 100; sc++)					//시작 가로 위치 
        {
            if (paper[sr][sc] == 0) continue;				//시작점에 색종이 없으면 해볼필요 없음
            for (int er = sr + 1; er < 100; er++)			//끝 세로 위치 
            {
                for (int ec = sc + 1; ec < 100; ec++)		//끝 가로 위치 
                {
                    if (paper[er][ec] == 0) break;			//어차피 er&ec를 늘려도 사각형 그려지지 않음, 정지
                    area = (er - sr + 1) * (ec - sc + 1);	//시작~끝까지 구할수있는 넓이
                    if (maxarea >= area) continue;
                    if (check(sr, sc, er, ec) == 0) break;	//어차피 er&ec를 늘려도 사각형 그려지지 않음, 정지
                    maxarea = area;							//갱신
                }
            }
        }
    }
    return maxarea;
}

int solveN3() 
{//시간복잡도 O(N^3)
    int maxarea = 100;

    //각 세로줄 높이 구하기
    for (int c = 0; c < 100; c++) 
    {
        for (int r = 1; r < 100; r++) 
        {
            if (paper[r][c] != 0) paper[r][c] += paper[r - 1][c];
        }
    }

    //시작위치에서 최대 높이 구해보기
    for (int sr = 1; sr < 100; sr++) 
    {
        for (int sc = 0; sc < 100; sc++) 
        {
            if (paper[sr][sc] == 0) continue;
            int h = paper[sr][sc];
            for (int k = sc; k < 100; k++) 
            {
                if (h > paper[sr][k]) h = paper[sr][k];//(sc, sr) ~ (k, sr)중에 제일 낮은 높이 선택
                if (h == 0) break;
                int area = h * (k - sc + 1);
                if (maxarea < area) maxarea = area;
            }
        }
    }
    return maxarea;
}

int main() {
#ifdef DEBUG
	freopen("input.txt", "r", stdin);
#endif
    InputData();
    //print_paper();
    //int ans = solveN6();
    int ans = solveN3();
    printf("%d\n", ans);
    return 0;
}