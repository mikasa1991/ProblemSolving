#include <stdio.h>

#define CAPACITY 11
#define MAX(a, b) ((a > b) ? a : b)

typedef struct _item item;
typedef struct _item
{
	int value;
	int weight;
}item;

void input_item(item* it, int n)
{
	for(int i = 1; i < n+1; i++)
	{
		scanf("%d %d", &(it[i].value), &(it[i].weight));
		printf("%d: %d %d\n", i, it[i].value, it[i].weight);
	}
}

/*
f(i, w): 배낭용량이 w일 때, 아이템 1 ~ i로 얻을 수 있는 최대 이득

f(i, w)
case1. i == 0, 0
case2. wi > w, f(i-1, w)
case3. w<= wi, MAX(f(i-1, w), f(i-1, w-wi) + vi)
*/
int f(int i, int w, item* it)
{
	printf("called: f(%d, %d)\n", i, w);
	if(i == 0) 
		return 0;
	
	else if(it[i].weight > w) 
		return f(i-1, w, it);
	
	else 
		return MAX(f(i-1, w, it), it[i].value + f(i-1, w - it[i].weight, it));	
}

int main()
{
	freopen("input.txt", "r", stdin);
	setbuf(stdout, NULL);

	int w = CAPACITY;		//배낭용량
	int n = 0;
	scanf("%d", &n);	//item 개수

	item it[n];
	input_item(it, n);

	printf("%d\n", f(n, w, it));
	return 0;
}