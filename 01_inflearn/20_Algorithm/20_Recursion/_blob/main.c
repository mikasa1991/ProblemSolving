/*
현재 픽셀이 이 속한 blob의 크기를 카운트하려면
	//base case
	현재 픽셀이 image color가 아니라면
		0을 반환한다
	
	//recursive case
	현재 픽셀이 image color라면
		먼저 현재 픽셀을 카운트한다 (count=1).
		현재 픽셀이 중복 카운트되는 것을 방지하기 위해 다른 색으로 칠한다.
		현재 픽셀에 이웃한 모든 픽셀들에 대해서
			그 픽셀이 속한 blob의 크기를 카운트하여 카운터에 더해준다.
		카운터를 반환한다.
*/

#include <stdio.h>

#define BACHGROUND 		0
#define IMAGE	   		1
#define COUNTED_IMAGE	2

int cnt = 0;
int n = 4;
int pixel[][4] = {
	{0, 0, 0, 0},
	{0, 1, 1, 0},
	{0, 0, 0, 1},
	{0, 1, 0, 0}
};


/*
f(x,y): (x,y)에서 blob의 셀 수

f(x,y) =
+1
+f(x-1, y-1)
+f(x-1, y)
+f(x-1, y+1)
+f(x, y)
+f(x, y+1)
+f(x+1, y-1)
+f(x+1, y)
+f(x+1, y+1)

*/
int countCells(int x, int y)
{
	//base case
	if( x < 0 || x >= n || y < 0 || y >= n || pixel[x][y] != IMAGE)
	{
		return 0;
	}

	//recusive case
	else
	{
		pixel[x][y] = COUNTED_IMAGE;
		return 1
		+ countCells(x-1, y-1)
		+ countCells(x-1, y  )
		+ countCells(x-1, y+1)
		+ countCells(x  , y-1)
		+ countCells(x  , y  )
		+ countCells(x  , y+1)
		+ countCells(x+1, y-1)
		+ countCells(x+1, y  )
		+ countCells(x+1, y+1);
	}
}

void printPixel()
{
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < n; j++)
		{
			printf("%d ", pixel[i][j]);
		}
		puts("");
	}
}

void main()
{
	int x, y = 0;
	
	//입력은 특정 픽셀의 좌표이다
	x = 2;
	y = 3;
	printPixel();
	puts("");
	
	//출력은 특정 픽셀이 포함된 blob의 크기
	printf("the count of a blob include pixel (%d, %d): %d\n", x, y, countCells(x,y));
	printPixel();
}