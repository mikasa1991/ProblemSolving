/*
https://www.acmicpc.net/problem/5052
*/

#include <stdio.h>

#define DEBUG 1

#define CHILD (10)				//0 ~ 9
#define STRN  (12)				//전화번호길이최대 10자리 + NULL문자
#define MAXN  ((int)1e4)
typedef struct trie 
{
	int end;					//단어끝 표시
	int leaf;					//leaf node 표시
	struct trie *child[CHILD];
}TRIE;

const char *message[] = { "NO", "YES" };
TRIE *root;
int nodeptr;
TRIE node[STRN * MAXN];			//문자 1개당 노드 1개를 차지하니까

TRIE *myalloc() 
{
	TRIE *p = &node[nodeptr++];
	p->end = 0; 
	p->leaf = 1;
	for (int i = 0; i < CHILD; i++) 
		p->child[i] = NULL;

	return p;
}

void init() 
{
	nodeptr = 0;
	root = myalloc();
}

int calidx(char ch) { return ch - '0'; }

void insert(TRIE *p, char *str) 
{
	if (*str == 0) 					//입력받은 문자가 널문자라면,
	{
		p->end = 1;					//단어끝 표시
		return;
	}
	int idx = calidx(*str);
	if (p->child[idx] == NULL) 
	{
		p->child[idx] = myalloc();
		p->leaf = 0;				//leaf node 표시 해지
	}
	insert(p->child[idx], str + 1);
}

int check(TRIE *p, char *str) 
{
	/*
	911 9119
	9119 911
	어떤 순서로 입력받을지 모르니까 두 개의 이프 문이 필요하지
	*/
	if (*str == 0) return 0;						//현재 문자열이 다른 문자열의 접두어
	if (p->end) return 0;							//다른 문자열이 현재 문자열의 접두어
	int idx = calidx(*str);
	if (p->child[idx] == NULL) return 1;			//새로운 문자열
	return check(p->child[idx], str + 1);
}

int solve() 
{
	char str[STRN] = {0, }; 
	int N = 0;
	int flag = 1;
	scanf("%d", &N);
	for (int i = 0; i < N; i++) 
	{
		scanf("%s", str);
		if (!flag) continue;				//이전에 이미 일관성이 없으면 추가 및 확인 불필요(다만, 다음 테스트 케이스를 받기위해 문자열은 입력 받아야 함)
		flag = check(root, str);
		if (flag) insert(root, str);
	}
	return flag;
}

int main() 
{
#ifdef DEBUG
	freopen("input.txt", "r", stdin);
#endif
	int T;
	scanf("%d", &T);
	for (int t = 1; t <= T; t++) 
	{
		init();
		int ans = solve();
		printf("%s\n", message[ans]);
	}
	return 0;
}