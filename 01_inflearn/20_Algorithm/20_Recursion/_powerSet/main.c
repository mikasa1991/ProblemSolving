//임의의 집합 data의 모든 부분집합을 출력하라.

/*
f(str): str번째 원소부터 모든 부분집합 수

//base case
마지막번째 원소까지 도달한 경우,
print

//recursive case
f(str) =
case1. str번째 원소 포함
+f(str+1)

case2. str번째 원소 불포함
+f(str+1)
*/

#include <stdio.h>

int data[] = {1, 2, 3, 4};
int flag[] = {0, 0, 0, 0};

void print_flag()
{
    printf("flag: ");
	for(int i = 0; i < 4; i++)
	{
		printf("%d ", flag[i]);
	}
	puts("");
}

void powerset(int n, int depth)
{
	printf("n: %d, depth: %d\n", n, depth);	    //for debugging
	print_flag();								//for debugging

	//base case
    if(n == depth)
    {
        printf("{ ");
        for(int i = 0;i < n;i++)
        {
            if(flag[i] == 1) printf("%d ", data[i]); //if include, print
        }
        printf("}\n");
        return;
    }

    //recursive case
    flag[depth] = 1;		//include
    powerset(n, depth + 1);
    flag[depth] = 0;		//exclude
    powerset(n, depth + 1);
}

int main()
{
	int n = sizeof(data)/sizeof(int);
    powerset(n, 0);
    return 0;    
}