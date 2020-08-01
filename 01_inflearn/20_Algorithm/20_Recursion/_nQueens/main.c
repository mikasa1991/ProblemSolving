/*
cols[i] = j는 i번 말이 (i행, j열)에 놓였음을 의미한다.
*/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define N 4
int cnt = 0;
int col[N+1] = {0, };	//i wanna use the range of index from 1 to N

/*
return-type queens( arguments )
{
	if non-promising
		report failure and return;
	else if success
		report answer and return;
	else
		visit children recursively;
}
*/
bool promising(int level)
{
	//하기의 반복문은 level이 2부터 의미가 있는거지
	for(int i = 1; i < level; i++)	//1 ~ level - 1
	{
		if(col[i] == col[level])						//same row 
			return false;

		else if(level-i == abs(col[level] - col[i]))	//same diagonal 
			return false;
	}

	return true;
}

bool queens(int level)
{
	if(!promising(level))	//base case
		return false;
	
	else if(level == N)		//base case
	{
		cnt++;

		//for debugging
		for(int i = 1; i <= N; i++)
		{
			printf("%d ", col[i]);
		}
		puts("");
		
		return true;
	}

	else					//recursive case
	{
		for(int i = 1; i <= N; i++)
		{
			col[level+1] = i;
			
			/*
			//최초의 queens배열을 만족하는 케이스를 확인하고 바로 프로그램을 종료시키고 싶은 경우에
			if(queens(level+1))
			{
				return true;
			}
			*/

			//모든 가능한 queens배열을 확인하고 싶은 경우에
			(void)queens(level+1);
		}
		return false;
	}
}

void main()
{
	(void)queens(0);
	printf("count: %d\n", cnt);
}