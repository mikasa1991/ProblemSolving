

/***********************************************************/
// [1-4-2] 배열 기반 연결 리스트 - 더블 링크
/***********************************************************/

#if 1
/***********************************************************/
// [1-4-2.1] 기존 Linked List 방식중 그대로 사용하는 함수들
// 단, 인쇄할 때 Prev Node 값도 인쇄하도록 추가한다
/***********************************************************/

#if 01

#include <stdio.h>
#include <string.h>
#include <malloc.h>

typedef struct _score 
{
	int id;
	int jumsu;
	char name[10];
	struct _score  * next; 
	struct _score  * prev; 
}SCORE;

SCORE Head;
SCORE Tail;	//190609_Tail added

#define MAX_ST		20
SCORE exam[MAX_ST];

// 이제부터 설계되는 모든 함수는 이 부분에 선언을 추가한다

int Print_All_Data(void);
int Print_Data(int no);
int Count_Data(void);
int Create_Data(SCORE * p);
int Insert_Data(SCORE * p);
int Insert_Node(SCORE * head, SCORE * d);
int Print_All_Node(SCORE * head);
int Print_All_Node_Reverse(SCORE * head);
SCORE * Search_Id_Node(SCORE * head, int id);
int Count_Node(SCORE * head);
int Print_Node(SCORE * head, int id); 
int Delete_Node(SCORE * head, int id);
int Copy_All_Node(SCORE * head, SCORE * buf);
int Count_Name_Node(SCORE * head, char * name);
int Count_Score_Node(SCORE * head, int jumsu);
int Copy_Name_Node(SCORE * head, char * name, SCORE * buf);
int Copy_Score_Node(SCORE * head, int jumsu, SCORE * buf);
int Print_Selected_Node(SCORE *head, int id, int num);
int Print_Selected_Node_Reverse(SCORE *head, int id, int num);


SCORE test[MAX_ST] = {{10, 50, "kim"}, {2, 80, "lew"}, {8, 50, "lew"}, {4, 45, "lee"}, {1, 90, "song"},
					  {3, 45, "kim"}, {5, 50, "song"}, {9, 100, "lee"}, {7, 75, "moon"}, {6, 90, "park"},
					  {15, 90, "ki"}, {11, 20, "kong"}, {14, 40, "shin"}, {12, 50, "son"}, {17, 48, "lee"},
					  {20, 100, "min"}, {19, 80, "you"}, {13, 45, "song"}, {16, 54, "no"}, {18, 100, "yang"}}; 

void Make_Test_Data(int n)
{
	int i;

	for(i=0; i<n; i++)
	{
		exam[i] = test[i];
	}
}

int Create_Data(SCORE * p)
{
	printf("\n사번을 입력하시오 => ");
	scanf("%d", &p->id);
	fflush(stdin);
	printf("이름을 입력하시오 => ");
	scanf("%s", p->name);
	fflush(stdin);
	printf("점수를 입력하시오 => ");
	scanf("%d", &p->jumsu);
	fflush(stdin);
	p->next = (SCORE *)0x0;
	p->prev = (SCORE *)0x0;

	return 1;
}

int Print_All_Data(void)
{
	int i;

	printf("Head = %p, Head.next = %p, Head.prev = %p\n", &Head, Head.next, Head.prev);
	printf("Tail = %p, Tail.next = %p, Tail.prev = %p\n", &Tail, Tail.next, Tail.prev);	//190609_Tail added

	for(i=0; i<MAX_ST; i++)
	{
		if(exam[i].id == 0) break;
		printf("[%d] addr = %p, ID=%d, NAME=%s, SCORE=%d, next=%p, prev=%p\n", 
			i, &exam[i], exam[i].id, exam[i].name, exam[i].jumsu, exam[i].next, exam[i].prev);
	}
	return i;
}

int Print_Data(int no)
{
	if(exam[no].id == 0) return -1;
	printf("[%d] addr=%p, ID=%d, NAME=%s, SCORE=%d, next=%p, prev=%p\n", 
		no, &exam[no], exam[no].id, exam[no].name, exam[no].jumsu, exam[no].next, exam[no].prev);
	return 1;

}

int Count_Data(void)
{
	int i;

	for(i=0; i<MAX_ST; i++)
	{
		if(exam[i].id == 0) break;
	}
	return i;
}

int Insert_Data(SCORE * p)
{
	int i;

	for(i=0; i<MAX_ST; i++)
	{
		if(exam[i].id == 0) 
		{
			exam[i] = (*p);
			return i;
		}

		if(exam[i].id == p->id)
		{
			return -2;
		}
	}
	return -1;
}

int Print_All_Node(SCORE * head)
{
	int i;
	printf("Head.next = %p, Head.prev = %p\n", head->next, head->prev);
	printf("Tail.next = %p, Tail.prev = %p\n", Tail.next, Tail.prev);	//190609_Tail added

	for(i=0 ; i<MAX_ST ; i++)
	{
		//if(head->next == NULL) return i;
		if(head->next == &Tail) return i;	//190609_Tail added
		printf("addr = %p, ID=%d, NAME=%s, SCORE=%d, next=%p, prev=%p\n", 
			head->next, head->next->id, head->next->name, head->next->jumsu, head->next->next, head->next->prev);
		head = head->next;		
	}
	return i;
}

int Count_Node(SCORE * head)
{
	int i;

	for(i=0 ; i<MAX_ST ; i++)
	{
		if(head->next == NULL) return i;
		head = head->next;		
	}
	return i;
}

SCORE * Search_Id_Node(SCORE * head, int id)
{
	for(;;)
	{
		if(head->next == NULL) return NULL;
		if(head->next->id == id) return head->next;   
		head = head->next;		
	}
}

int Print_Node(SCORE * head, int id)
{
	SCORE * p = Search_Id_Node(head, id);

	if(p != (SCORE *)0x0)
	{
		printf("ID=%d, NAME=%s, SCORE=%d, next=%p, prev=%p\n", p->id, p->name, p->jumsu, p->next, p->prev);
		return 1;
	}
	return -1;
}

int Copy_All_Node(SCORE * head, SCORE * buf)
{
	int i;
	if(head->next == NULL) return -1;

	for(i=0 ; i<MAX_ST ; i++)
	{
		if(head->next == NULL) break;
		buf[i] = *head->next;
		buf[i].next = &buf[i+1];
		head = head->next;
	}
	buf[i-1].next = NULL;
	return i;
}

int Count_Name_Node(SCORE * head, char * name)
{
	int n = 0;

	if(head->next == (SCORE *)0x0) return 0;
	head = head -> next;

	for(;;)
	{
		if(!strcmp(head->name, name)) n++;
		if(head->next == (SCORE *)0x0) return n;
		head = head -> next;		
	}
}

int Count_Score_Node(SCORE * head, int jumsu)
{
	int n = 0;

	if(head->next == (SCORE *)0x0) return 0;
	head = head -> next;

	for(;;)
	{
		if(head->jumsu == jumsu) n++;
		if(head->next == (SCORE *)0x0) return n;
		head = head -> next;		
	}
}

int Copy_Name_Node(SCORE * head, char * name, SCORE * buf)
{
	int n = 0;

	if(head->next == (SCORE *)0x0) return 0;
	head = head -> next;

	for(;;)
	{
		if(!strcmp(head->name, name))
		{
			buf[n] = *head;
			buf[n].next = &buf[n+1];
			n++;
		}

		if(head->next == (SCORE *)0x0) break;
		head = head -> next;		
	}
	buf[n-1].next = (SCORE *)0x0;
	return n;
}

int Copy_Score_Node(SCORE * head, int jumsu, SCORE * buf)
{
	int n = 0;

	if(head->next == (SCORE *)0x0) return 0;
	head = head -> next;
	
	for(;;)
	{
		if(head->jumsu == jumsu)
		{
			buf[n] = *head;
			buf[n].next = &buf[n+1];
			n++;
		}
		if(head->next == (SCORE *)0x0) break;
		head = head -> next;		
	}
	buf[n-1].next = (SCORE *)0x0;
	return n;
}
#endif

/***********************************************************/
// [1-4-2.2] 데이터 하나를 생성하여 Linked List에 추가하는 함수
/***********************************************************/

#if 01

/*
이 문제에서 삽입을 할 때,
head를 기준으로 삽입을 하는 걸로 구현했기 때문에,
tail을 파라미터로 따로 받지 않았다
*/
int Insert_Node(SCORE * head, SCORE * d)
{
	int i;

	for(i=0; i<MAX_ST; i++)
	{
		//if((head->next == NULL) || (d->id < head->next->id))	//190609_Tail added
		if((head->next == &Tail) || (d->id < head->next->id))
		{
			d->next = head->next;
			d->prev = head;
			head->next->prev = d;								//190609_Tail added
			//if(head->next != NULL) head->next->prev = d;		//190609_Tail added
			head->next = d;
			return 1;
		}

		if(d->id == head->next->id) return -2;
		head = head->next;
	}
	return -1;
}
#endif

#if 01

void init()
{
	Head.next = &Tail;
	Tail.prev = &Head;
}

#endif

#if 0

void main(void)
{
	int i;
	int r;

	init();	//190609_Tail add
	for(i=0; i<8; i++)
	{
		printf("[Loop: %d] Insert Result = %d\n", i, r = Insert_Data(&test[i]));
		printf("Printed Data Count = %d\n", Print_All_Data());
		printf("Insert Node Result = %d\n", Insert_Node(&Head, &exam[r]));
		printf("Printed Data Count = %d\n", Print_All_Data());
		puts("");
	}
}

#endif



/***********************************************************/

// [1-4-2.3] 주어진 사번의 node를 찾아서 삭제하는 함수

/***********************************************************/
#if 01

/*
-삭제 구현이 편하다.
더블 링크드리스트에서 삭제가 유리한 게,
해당 id를 가지고 있는 구조체 주소를 찾으면,
바로 삭제할 수 있다.
*/
int Delete_Node(SCORE * head, int id)
{
	SCORE *p = 	Search_Id_Node(head, id);

	if(p == NULL) return -1;

	p->id = 0;
	p->prev->next = p->next;
	//if(p->next) p->next->prev = p->prev;
	p->next->prev = p->prev;
	return 1;
}

#endif

#if 0

void main(void)
{
	int i;
	int r;

	init();	//190609_Tail add

	for(i=0; i<8; i++)
	{
		printf("[Loop: %d] Insert Result = %d\n", i, r = Insert_Data(&test[i]));
		printf("Insert Node Result = %d\n", Insert_Node(&Head, &exam[r]));
		puts("");
	}

	printf("Printed Node Count = %d\n", Print_All_Node(&Head));
	puts("");

	printf("id:8 Delete Node Result = %d\n", Delete_Node(&Head, 8)); 
	printf("Printed Node Count = %d\n", Print_All_Node(&Head));
	puts("");
	
	printf("id:7 Delete Node Result = %d\n", Delete_Node(&Head, 7)); 
	printf("Printed Node Count = %d\n", Print_All_Node(&Head));
	puts("");

	printf("id:1 Delete Node Result = %d\n", Delete_Node(&Head, 1)); 
	printf("Printed Node Count = %d\n", Print_All_Node(&Head));
	puts("");

	printf("id: 10 Delete Node Result = %d\n", Delete_Node(&Head, 10)); 
	printf("Printed Node Count = %d\n", Print_All_Node(&Head));
}



#endif



/***********************************************************/
// [1-4-2.4] 더블 링크 사용의 장점 1, 내림차순 검색
/***********************************************************/

#if 01
/*
아래 함수는 Tail을 정의하지 않았을 때,
더블 링크드 리스트에서 역순으로 출력하는 함수이다.
*/
int Print_All_Node_Reverse(SCORE * head)
{
	int i;

	printf("Head.next = %p Head.prev = %p\n", head->next, head->prev);
	printf("Tail.next = %p Tail.prev = %p\n", Tail.next, Tail.prev);

	//while(head->next != (SCORE *)0x0)	//190609_Tail added
	while(head->next != &Tail)	//190609_Tail added
	{
		head = head->next;
	}

	//printf("Tail.next = %p Tail.prev = %p\n", head->next, head->prev);

	for(i=0 ; i<MAX_ST ; i++)
	{
		if(head->prev == NULL) return i;
		printf("addr = %p, ID=%d, NAME=%s, SCORE=%d, next=%p, prev=%p\n", 
			head, head->id, head->name, head->jumsu, head->next, head->prev);
		head = head->prev;		
	}
	return i;
}

#endif

#if 0

void main(void)
{
	int i;
	int r;

	init();	//190609_Tail added

	for(i=0; i<8; i++)
	{
		printf("[Loop: %d] Insert Result = %d\n", i, r = Insert_Data(&test[i]));
		printf("Insert Node Result = %d\n", Insert_Node(&Head, &exam[r]));
		puts("");
	}

	printf("Printed Node Count(Up) = %d\n", Print_All_Node(&Head));
	puts("");
	printf("Printed Node Count(Down) = %d\n", Print_All_Node_Reverse(&Head));
	puts("");
	printf("id: 8 Delete Node Result = %d\n", Delete_Node(&Head, 8)); 
	printf("Printed Node Count(Down) = %d\n", Print_All_Node_Reverse(&Head));
}

#endif

/***********************************************************/
// [1-4-2.5] 더블 링크 사용의 장점 2, 역방향으로 일정 범위 인쇄
/***********************************************************/

#if 01

int Print_Selected_Node(SCORE * head, int id, int num)
{
	int i = 0;
	head = Search_Id_Node(head, id);
	if(head == (SCORE *)0x0) return -1;
	printf("==================================================================================\n");

	while(i<num)
	{
		printf("addr = %p, ID=%d, NAME=%s, SCORE=%d, next=%p, prev=%p\n", 
			head, head->id, head->name, head->jumsu, head->next, head->prev);
		i++;
		if(head->next == &Tail) break;
		//if(head->next == (SCORE *)0x0) break;
		head = head->next;		
	}
	return i;
}

int Print_Selected_Node_Reverse(SCORE *head, int id, int num)
{
	int i = 0;

	head = Search_Id_Node(head, id);
	if(head == (SCORE *)0x0) return -1;
	printf("==================================================================================\n");

	while(i<num)
	{
		printf("addr = %p, ID=%d, NAME=%s, SCORE=%d, next=%p, prev=%p\n", 
			head, head->id, head->name, head->jumsu, head->next, head->prev);
		i++;
		//if(head->prev->prev == (SCORE *)0x0) break;
		if(head->prev == &Head) break;
		head = head->prev;		
	}
	return i;
}

#endif

#if 01

void main(void)
{
	int i;
	int r;
	init();

	for(i=0; i<MAX_ST; i++)
	{
		printf("[Loop: %d] Insert Result = %d\n", i, r = Insert_Data(&test[i]));
		printf("Insert Node Result = %d\n", Insert_Node(&Head, &exam[r]));
	}
	puts("");

	printf("Printed Node Count(Up) = %d\n", Print_All_Node(&Head));
	puts("");
	printf("Printed Node Count(Down) = %d\n", Print_All_Node_Reverse(&Head));
	puts("");

	//단, id범위를 넘지않는 개수까지만 출력한다.
	r = Print_Selected_Node(&Head, 7, 3);			//id:7을 시작으로, 오름차순으로 3개
	printf("Printed Data Number => %d\n", r);

	r = Print_Selected_Node(&Head, 19, 3);			//id:19를 시작으로, 내림차순으로 3개
	printf("Printed Data Number => %d\n", r);

	r = Print_Selected_Node_Reverse(&Head, 7, 3);
	printf("Printed Data Number => %d\n", r);

	r = Print_Selected_Node_Reverse(&Head, 2, 3);
	printf("Printed Data Number => %d\n", r);
}

#endif

#endif