/*
https://www.acmicpc.net/problem/5926
*/
#include <stdio.h>
#include <assert.h>

#if 01
#define MAX_TB 		((int)5e5 + 1)	//500,000 + 1
#define MAX_COW 	((int)5e4 + 1)	// 50,000 + 1
#endif

#if 0
#define MAX_TB 5
#define MAX_COW 5
#endif
typedef struct _Data
{
	int id;
	int x;	//x position
}Data;

typedef struct _Node
{
	int key;	//id
	int val;	//newid
	struct _Node *next;
}Node;

Node HashTb[MAX_TB];
Node N_node[MAX_COW];	//최대 MAX_COW만큼 Node가 필요하므로, 전역변수로 할당.
Data Cow[MAX_COW];		//최대 MAX_COW만큼 소들의 x와 id를 저장할 공간을 전역변수로 할당.
int Cow_cnt[MAX_COW];

int N;
int N_ptr;
int NewId;

int hash(int key)		//get_hash, convert_index
{
	return key % MAX_TB;
}

Node *myAlloc(int key)
{
	Node *new_node = &N_node[N_ptr++];
	new_node->key = key;
	new_node->val = 0;
	new_node->next = NULL;
	return new_node;
}

int find_same_key(int id, int key)
{
	Node* temp = HashTb[id].next;

	while(temp != NULL)
	{
		if(temp->key == key) 
			return temp->val; 

		temp = temp->next;
	}

	return 0;
}

int get_newId(int key)
{
	int index = hash(key);
	int id;

	//중복키가 있으면, 같은 id로 발급한다.
	if(id = find_same_key(index, key))
	{
		return id; 
	}

	//중복키가 없으면, 새로운 id를 발급한다.
	//해시 테이블에 기록한다.
	else
	{
		Node* new_node = myAlloc(key);
		assert(new_node != NULL);

		new_node->next = HashTb[index].next;
		HashTb[index].next = new_node;
		new_node->val = ++NewId;
		return new_node->val;
	}
}

void print_data()
{
	for(int i = 0; i < N; i++)
	{
		printf("%d %d\n", Cow[i].x, Cow[i].id);
	}
}

void input_data()
{
	scanf("%d", &N);
	for(int i = 0; i < N; i++)
	{
		scanf("%d %d", &Cow[i].x, &Cow[i].id);
		Cow[i].id = get_newId(Cow[i].id);
	}
}

void merge(int s, int e)
{
	Data tmp[e+1];
	int m = (s + e) / 2;
	int s1 = s;
	int s2 = m + 1;
	int t = s;

	while((s1 <= m) && (s2 <= e)) //탈출조건: (s1 > m || s2 > e)
	{
		if(Cow[s1].x < Cow[s2].x) 
			tmp[t++] = Cow[s1++];
		else 
			tmp[t++] = Cow[s2++];
	}
	while(s1 <= m) tmp[t++] = Cow[s1++];
	while(s2 <= e) tmp[t++] = Cow[s2++];

	for(int i = s; i <= e; i++)
	{
		Cow[i] = tmp[i];
	}
}

void merge_sort(int s, int e)
{
	if(s >= e) return;
	
	int m = (s + e) / 2;
	merge_sort(s    , m);
	merge_sort(m + 1, e);
	merge(s, e);
}

int solve()
{
	int s = 0;
	int e = 0;
	int id_cnt = 0;
	int min = Cow[N-1].x - Cow[0].x;
	int dist = 0;

	while(e <= N)	//e가 N에 도달할 때, 탈출하려고 한다.
	{
		if(id_cnt < NewId)
		{
			Cow_cnt[Cow[e].id]++;
			if(Cow_cnt[Cow[e].id] == 1) id_cnt++;
			e++;
		}

		else if(id_cnt == NewId)
		{
			dist = Cow[e-1].x - Cow[s].x; 
			if(min > dist)
			{
				min = dist;
			}
			Cow_cnt[Cow[s].id]--;
			s++;
			id_cnt--;
		}

		else{ /* nothing */}

		while(Cow_cnt[Cow[s].id] > 1)
		{
			Cow_cnt[Cow[s].id]--;
			s++;
		}
	}

	return min;
}

int main()
{
	int ans;
	freopen("input.txt", "r", stdin);
	input_data();
	//print_data();

	//Cow의 x값에 따라서 오름차순으로 정렬한다.
	merge_sort(0, N-1);
	//puts("");
	//print_data();
	
	//
	ans = solve();
	printf("%d", ans);
	return 0;
}