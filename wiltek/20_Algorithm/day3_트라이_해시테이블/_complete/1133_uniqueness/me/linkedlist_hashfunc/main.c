/*
3355156	dong_hee.lee	1133	Success(100)	1MB	217ms	C	2955	2019-08-12 01:13:04	이동희
*/

#include <stdio.h>
#include <assert.h>

#define MAX_L (20 + 1)		//문자열 최대 길이
#define MAX_N (10000 + 10)	//문자열 최대 수

int N;

typedef struct _Node
{
	char str[MAX_L];
	int val;
	unsigned long hashCode;
	//int len;
	struct _Node *prev;	
	struct _Node *next;	
}Node;

Node Head;
Node Tail;
Node N_node[MAX_N];
int N_ptr;

/// 문자열 길이구하기
int strLength(char *s){
	int i = 0;
	while (s[i]) i++;
	/// if (i && s[i - 1] == '\n') s[--i] = 0;
	/// if (i && s[i - 1] == '\r') s[--i] = 0;
	return i;
}

/// 문자열 비교하기
int strComp(const char *s, const char *t){
	while (*s && *s == *t) s++, t++;
	return *s - *t;
}

/// 문자열 복사하기
void strCopy(char *dest, char *src){
	while (*dest++ = *src++);
}

unsigned long hash(const char *str)
{
	unsigned long hash = 5381;
	int c;

	//get_hashcode
	while (c = *str++)
	{
		hash = (((hash << 5) + hash) + c) % MAX_N;
	}

	//convertToIndex
	return hash % MAX_N;
}

void init()
{
	N_ptr = 0;

	Head.prev = NULL;
	Head.next = &Tail;
	Tail.prev = &Head;
	Tail.next = NULL;
} 

void print_linkedList()
{
	Node *temp = Head.next;
	while(temp != &Tail)
	{
		printf("%s (%d, %ld) ", temp->str, temp->val, temp->hashCode);
		temp = temp->next;
	}
	puts("");
}

Node *my_alloc(char *str)
{
	Node *new_node = &N_node[N_ptr++];
	
	strCopy(new_node->str, str);
	//new_node->len = strLength(str);
	new_node->hashCode = hash(str);
	new_node->val = N_ptr;	
	new_node->prev = NULL;
	new_node->next = NULL;

	return new_node;
}

void add_node_inFrontOf_tail(char *str)
{
	Node *new_node = my_alloc(str);
	new_node->prev = Tail.prev;
	new_node->next = &Tail;
	
	assert(Tail.prev != NULL);
	assert(Tail.prev->next != NULL);
	Tail.prev->next = new_node;
	Tail.prev = new_node;
}

void input_data()
{
	char str[MAX_L] = {0,};
	scanf("%d", &N);
	for(int i = 0; i < N; i++)
	{
		scanf("%s", str);
		//printf("%s\n", str);
		add_node_inFrontOf_tail(str);
	}
}

void delete_node(Node *p_node)
{
	p_node->prev->next = p_node->next;
	p_node->next->prev = p_node->prev;
}

void solve()
{
	Node *temp = Head.next;
	int flg = 1;
	while(temp != Tail.prev && temp != &Tail)
	{
		Node *temp2 = temp->next;
		int first = 1;
		assert(temp2 != NULL);
		while(temp2 != &Tail)
		{
			/*
			*/
			if((temp->hashCode == temp2->hashCode) && (strComp(temp->str, temp2->str) == 0))
			//if(strComp(temp->str, temp2->str) == 0)
			{
				flg = 0;
				if(first)
				{
					printf("%s %d ", temp->str, temp->val);
					first = 0;
				}
				printf("%d ", temp2->val);
				delete_node(temp2);
			}
			temp2 = temp2->next;
		}
		temp = temp->next;
		if(!flg) puts("");	
	}
	if(flg) printf("unique");
}

int main()
{
	freopen("input.txt", "r", stdin);
	
	//하나의 테스트 케이스
	init();
	input_data();
	//print_linkedList();
	solve();
	return 0;
}