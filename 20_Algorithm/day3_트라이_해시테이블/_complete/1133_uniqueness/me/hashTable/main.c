/*
3356633	dong_hee.lee	1133	Success(100)	3MB	11ms	C	3329	2019-08-13 00:29:03	이동희
*/

#include <stdio.h>
#include <assert.h>

#define MAX_L (20 + 1)		//문자열 최대 길이
#define MAX_N (10000 + 10)	//문자열 최대 수
#define MAX_TB (26*26)

typedef struct _Node
{
	char str[MAX_L];
	int val;
	struct _Node *prev;	
	struct _Node *next;	
}Node;

Node HashTb_head[MAX_TB];
Node HashTb_tail[MAX_TB];
Node N_node[MAX_N];
int N_ptr;

int N;
char string[MAX_N][MAX_L];

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

void init()
{
	N_ptr = 0;

	for(int i = 0; i < MAX_TB; i++)
	{
		HashTb_head[i].prev = NULL;
		HashTb_head[i].next = &HashTb_tail[i];
		HashTb_tail[i].prev = &HashTb_head[i];
		HashTb_tail[i].next = NULL;
	}
}

//unsigned long hash(const char *str)
int hash(const char *str)
{
	unsigned long hash = 5381;
	int c;

	//get_hashcode
	while (c = *str++)
	{
		hash = (((hash << 5) + hash) + c) % MAX_TB;
	}

	//convertToIndex
	return hash % MAX_TB;
}

Node* my_alloc(char *str)
{
	Node *new_node = &N_node[N_ptr++];
	strCopy(new_node->str, str);
	new_node->val = N_ptr;
	new_node->prev = NULL;
	new_node->next = NULL;
	return new_node;
}

void print_hashTb()
{
	int first;
	for(int i = 0; i < MAX_TB; i++)
	{
		first = 1;
		Node *temp = HashTb_head[i].next;
		while(temp != &HashTb_tail[i])
		{
			if(first){
				printf("%2d: ", i);
				first = 0;
			}
			printf("%s(%d) ", temp->str, temp->val);
			temp = temp->next;
		}
		if(!first) puts("");
	}
}

//중복키도 추가한다
void add_node_inFrontOf_hashTb_tail(char *str)
{
	Node *new_node = my_alloc(str);
	int idx = hash(str);
	new_node->prev = HashTb_tail[idx].prev;
	new_node->next = &HashTb_tail[idx];
	
	HashTb_tail[idx].prev->next = new_node;
	HashTb_tail[idx].prev = new_node; 
}

void input_data()
{
	for(int i = 0; i < N; i++)
	{
		scanf("%s", string[i]);
		add_node_inFrontOf_hashTb_tail(string[i]);
	}
}

void print_data()
{
	for(int i = 0; i < N; i++)
	{
		printf("%s ", string[i]);
	}
	puts("");
}

void delete_node_inHashTb(Node *p_node)
{
	p_node->prev->next = p_node->next;
	p_node->next->prev = p_node->prev;
}

void solve()
{
	int idx;
	int step;
	int val_first;
	int flg = 1;

	Node *temp;

	/*
	(190813)
	flg, step을 사용하지 않고, 가독성 높게 코딩할 수 없을까?
	*/
	for(int i = 0; i < N; i++)
	{
		step = 2;
		idx = hash(string[i]);
		temp = HashTb_head[idx].next;
		while(temp!=NULL)
		{
			if(strComp(temp->str, string[i]) == 0)
			{
				if(step == 2){
					val_first = temp->val;
					step--;
				}
				else if(step == 1){
					printf("%s %d %d ", temp->str, val_first, temp->val);
					step--;	
					flg = 0;
				}
				else printf("%d ", temp->val);
				delete_node_inHashTb(temp);
			}
			temp = temp->next;
		}
		if(!step) puts("");
	}
	if(flg) printf("unique");
}

int main()
{
	freopen("input.txt", "r", stdin);
	scanf("%d", &N);

	init();
	input_data();
	//print_data();
	//print_hashTb();
	solve();
	return 0;
}