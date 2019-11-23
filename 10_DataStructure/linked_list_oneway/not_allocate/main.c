
/***********************************************************/
// [1-4] Linked List
/***********************************************************/

/***********************************************************/
// [1-4-1] 배열 기반 연결 리스트
// 최대 얼마나 연결리스트를 할당받아야 하는지 알고 있는 경우에,
/***********************************************************/

/***********************************************************/
// [1-4-1.1] 데이터 모델링
/***********************************************************/
#if 01

#include <stdio.h>
#include <string.h>
//#include <conio.h>
#include <malloc.h>

typedef struct _score 
{
	int id;
	int jumsu;
	char name[10];
	struct _score  * next; 
}SCORE;

SCORE Head;
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
SCORE * Search_Id_Node(SCORE * head, int id);
int Count_Node(SCORE * head);
int Print_Node(SCORE * head, int id); 
int Delete_Node(SCORE * head, int id);
int Copy_All_Node(SCORE * head, SCORE * buf);
int Count_Name_Node(SCORE * head, char * name);
int Count_Score_Node(SCORE * head, int jumsu);
int Copy_Name_Node(SCORE * head, char * name, SCORE * buf);
int Copy_Score_Node(SCORE * head, int jumsu, SCORE * buf);

//id는 중복되지 않는다고 가정한다
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
#endif

/***********************************************************/
// [1-4-1.2] 데이터 생성, 인쇄, 계수 함수 설계
/***********************************************************/
#if 01

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
	return 1;
}

int Print_All_Data(void)
{

	int i;
	printf("Head.next = %p\n", Head.next);

	for(i=0; i<MAX_ST; i++)
	{
		if(exam[i].id == 0) break;
		printf("[%d] addr = %p, ID=%d, NAME=%s, SCORE=%d, next = %p\n", 
			i, &exam[i], exam[i].id, exam[i].name, exam[i].jumsu, exam[i].next);
	}
	return i;
}

int Print_Data(int no)
{
	if(exam[no].id == 0) return -1;
	printf("[%d] addr = %p, ID=%d, NAME=%s, SCORE=%d, next = %p\n", 
		no, &exam[no], exam[no].id, exam[no].name, exam[no].jumsu, exam[no].next);
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
		if(exam[i].id == 0)		//exam[i]가 할당되지 않은 공간이라면,
		{
			exam[i] = (*p);		//exam[i]에 p구조체 값을 복사한다
			return i;			//i를 반환한다
		}

		if(exam[i].id == p->id)	//id가 중복되는 경우
		{
			return -2;			//error
		}
	}
	return -1;					//최대할당범위를 넘어간 경우, error
}
#endif


/***********************************************************/
// [1-4-1.3] 데이터 하나를 생성하여 Linked List에 추가하는 함수
/***********************************************************/

#if 01

int Insert_Node(SCORE *head, SCORE *d)	//d는 삽입을 원하는 노드의 주소를 받는다.
{
	int i;
	for(i=0; i<MAX_ST; i++)
	{
		/*
		head 변수를 포인터 변수로 선언했다면,
		head가 NULL인 경우와, 아닌 경우를 나눠서 설계해야한다.
		*/


		/*
		head->next가 NULL이거나,
		head->next->id보다 d->id가 작다면,(오름차순 정렬을 하기 위해서)
		head뒤에 삽입한다.
		*/
		if((head->next == NULL) || (d->id < head->next->id))
		{
			d->next = head->next;
			head->next = d;
			return 1;
		}

		if(d->id == head->next->id) return -2;
		head = head->next;
	}
	return -1;
}
#endif

#if 0
void main(void)
{
	int i;
	int r;
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
// [1-4-1.4] link에 따라서 각 노드의 정보를 인쇄하도록 함수
/***********************************************************/

/***********************************************************/
// [1-4-1.5] link에 따라서 주어진 사번에 맞는 노드 를 찾아 주소를 리턴하는 함수
/***********************************************************/

#if 01
int Print_All_Node(SCORE * head)
{
	int i;
	printf("Head.next = %p\n", head->next);

	for(i=0 ; i<MAX_ST ; i++)
	{
		if(head->next == NULL) return i;
		printf("addr = %p, ID=%d, NAME=%s, SCORE=%d, next = %p\n", 
			head->next, head->next->id, head->next->name, head->next->jumsu, head->next->next);

		head = head->next;		
	}
	return i;
}

SCORE * Search_Id_Node(SCORE * head, int id)
{
	//for(;;)
	while(1)
	{
		if(head->next == NULL) return NULL;
		if(head->next->id == id) return head->next;   
		head = head->next;		
	}
}
#endif

#if 0
void main(void)
{
	int i;
	int r;
	SCORE * p; 

	for(i=0; i<8; i++)
	{
		printf("[Loop: %d] Insert Result = %d\n", i, r = Insert_Data(&test[i]));
		printf("Printed Data Count = %d\n", Print_All_Data());
		printf("Insert Node Result = %d\n", Insert_Node(&Head, &exam[r]));
		printf("Printed Node Count = %d\n", Print_All_Node(&Head));
		puts("");
	}
	//search case1
	printf("ID:%d_Searched Node Address = %p\n", 8, p = Search_Id_Node(&Head, 8));
	if(p != NULL)	//search가 성공했다면,
	{
		printf("ID=%d, NAME=%s, SCORE=%d, next = %p\n", p->id, p->name, p->jumsu, p->next);
	}
	puts("");

	//search case2
	printf("ID:%d_Searched Node Address = %p\n", 7, p = Search_Id_Node(&Head, 7));
	if(p != NULL)	//search가 성공했다면,
	{
		printf("ID=%d, NAME=%s, SCORE=%d, next = %p\n", p->id, p->name, p->jumsu, p->next);
	}
}
#endif



/***********************************************************/
// [1-4-1.6] list에 저장된 자료의 총수를 계산하는 함수
/***********************************************************/
#if 01
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
#endif

/***********************************************************/
// [1-4-1.7] link에 따라서 주어진 사번에 맞는 자료를 인쇄하는 함수
/***********************************************************/
#if 01
int Print_Node(SCORE * head, int id)
{
	SCORE * p = Search_Id_Node(head, id);

	if(p != NULL)
	{
		printf("ID=%d, NAME=%s, SCORE=%d, next = %p\n", p->id, p->name, p->jumsu, p->next);
		return 1;
	}
	return -1;
}
#endif

#if 0
void main(void)
{
	int i;
	int r;

	for(i=0; i<8; i++)
	{
		printf("[Loop: %d] Insert Result = %d\n", i, r = Insert_Data(&test[i]));
		printf("Printed Data Count = %d\n", Print_All_Data());
		printf("Insert Node Result = %d\n", Insert_Node(&Head, &exam[r]));
		printf("Printed Node Count = %d\n", Print_All_Node(&Head));
		printf("Node Count = %d\n", Count_Node(&Head));
		puts("");
	}

	printf("Print Node Result = %d\n", Print_Node(&Head, 8));
	printf("Print Node Result = %d\n", Print_Node(&Head, 7));
}
#endif

/***********************************************************/
// [1-4-1.8] link에 따라서 주어진 사번의 node를 찾아서 삭제하는 함수
/***********************************************************/
#if 01
int Delete_Node(SCORE * head, int id)
{
	int i;

	for(i=0 ; i<MAX_ST ; i++)
	{
		if(head->next == NULL) return -1;	//head->next가 NULL인 경우, head->next->next는 성립하지 않으니까
		if(head->next->id == id)
		{
			head->next->id = 0;
			head->next = head->next->next;
			return 1;
		}
		if(head->next->id > id) return -1;
		head = head->next;
	}
	return -1;
}
#endif

#if 0
void main(void)
{
	int i;
	int r;

	for(i=0; i<8; i++)
	{
		printf("[Loop: %d] Insert Result = %d\n", i, r = Insert_Data(&test[i]));
		printf("Insert Node Result = %d\n", Insert_Node(&Head, &exam[r]));
		puts("");
	}

	printf("Printed Node Count = %d\n", Print_All_Node(&Head));
	printf("ID:%d_Delete Node Result = %d\n", 8, Delete_Node(&Head, 8)); 
	printf("ID:%d_Delete Node Result = %d\n", 7, Delete_Node(&Head, 7)); 
	printf("ID:%d_Delete Node Result = %d\n", 1, Delete_Node(&Head, 1)); 
	printf("ID:%d_Delete Node Result = %d\n", 10, Delete_Node(&Head, 10)); 
	printf("Printed Node Count = %d\n", Print_All_Node(&Head));
}
#endif



/***********************************************************/
// [1-4-1.9] 주어진 버퍼에 자료를 모두 복사해 주는 함수 
/***********************************************************/
#if 01
/*
head와 연결된 리스트는 id의 오름차순으로 정렬되어있다.
이를 buf에 순서대로 담는다.
*/
int Copy_All_Node(SCORE * head, SCORE * buf)
{
	int i;
	if(head->next == NULL) return -1;
	for(i=0 ; i<MAX_ST ; i++)
	{
		if(head->next == NULL) break;
		buf[i] = *(head->next);
		buf[i].next = &buf[i+1];
		head = head->next;
	}
	buf[i-1].next = NULL;
	return i;
}
#endif

#if 0
void main(void)
{
	int i;
	int r;
	SCORE * p;
	SCORE new_head;

	for(i=0; i<8; i++)
	{
		printf("[Loop: %d] Insert Result = %d\n", i, r = Insert_Data(&test[i]));
		printf("Insert Node Result = %d\n", Insert_Node(&Head, &exam[r]));
		puts("");
	}

	printf("Printed Node Count = %d\n", Print_All_Node(&Head));
	printf("Node Count = %d\n", r = Count_Node(&Head)); 
	p = (SCORE *)calloc(r, sizeof(SCORE));	//sizeof(SCORE) * r 개 할당받기 
	printf("Copy All Node Result = %d\n", Copy_All_Node(&Head, p)); 
	new_head.next = p;
	printf("Printed Node Count = %d\n", Print_All_Node(&new_head));
	free(p);
}
#endif


/***********************************************************/
// [1-4-1.10] node에서 요청한 자료의 수를 계수하거나 버퍼에 복사해 주는 함수
/***********************************************************/
#if 01

int Count_Name_Node(SCORE * head, char * name)
{
	int n = 0;
	if(head->next == NULL) return 0;
	head = head -> next;
	
	for(;;)
	{
		if(strcmp(head->name, name) == 0) n++;
		if(head->next == NULL) return n;
		head = head -> next;		
	}
}

int Count_Score_Node(SCORE * head, int jumsu)
{
	int n = 0;

	if(head->next == NULL) return 0;
	head = head -> next;

	for(;;)
	{
		if(head->jumsu == jumsu) n++;
		if(head->next == NULL) return n;
		head = head -> next;		
	}
}

int Copy_Name_Node(SCORE * head, char * name, SCORE * buf)
{
	int n = 0;

	if(head->next == NULL) return 0;
	head = head -> next;

	for(;;)
	{
		if(strcmp(head->name, name) == 0)
		{
			buf[n] = *head;
			buf[n].next = &buf[n+1];
			n++;
		}

		if(head->next == NULL) break;
		head = head -> next;		
	}

	if(n!=0) buf[n-1].next = NULL;
	return n;
}

int Copy_Score_Node(SCORE * head, int jumsu, SCORE * buf)
{
	int n = 0;

	if(head->next == NULL) return 0;
	head = head -> next;

	for(;;)
	{
		if(head->jumsu == jumsu)
		{
			buf[n] = *head;
			buf[n].next = &buf[n+1];
			n++;
		}

		if(head->next == NULL) break;
		head = head -> next;		
	}

	buf[n-1].next = NULL;
	return n;
}
#endif


#if 01
void main(void)
{
	int i;
	int r;
	SCORE * p;
	SCORE new_head;

	for(i=0; i<20; i++)
	{
		printf("[Loop: %d] Insert Result = %d\n", i, r = Insert_Data(&test[i]));
		printf("Insert Node Result = %d\n", Insert_Node(&Head, &exam[r]));
		puts("");
	}

	printf("Printed Node Count = %d\n", Print_All_Node(&Head));
	printf("Name Node Count = %d\n", r = Count_Name_Node(&Head, "lew")); 

	p = calloc(r, sizeof(SCORE));
	printf("Copy Name Node Result = %d\n", Copy_Name_Node(&Head, "lew", p)); 

	new_head.next = p;
	printf("Printed Node Count = %d\n", Print_All_Node(&new_head));
	free(p);

	printf("Score Node Count = %d\n", r = Count_Score_Node(&Head, 100)); 
	p = calloc(r, sizeof(SCORE));
	printf("Copy Score Node Result = %d\n", Copy_Score_Node(&Head, 100, p)); 

	new_head.next = p;
	printf("Printed Node Count = %d\n", Print_All_Node(&new_head));
	free(p);
}
#endif
