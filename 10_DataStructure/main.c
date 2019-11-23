#pragma warning(disable: 4996)

/***********************************************************/

// [1-1] 정렬

/***********************************************************/

#if 0

#if 0



#include <stdio.h>

#include <string.h>



// 정렬에 사용 할 자료

typedef struct _score 

{

	int id;

	int jumsu;

	char name[10];

}SCORE;



#define MAX_ST (10)



SCORE exam[MAX_ST] = {{10, 50, "kim"}, {2, 80, "lew"}, {8, 50, "lew"}, {4, 45, "lee"}, {1, 90, "song"},\

                               {3, 45, "kim"}, {5, 50, "song"}, {9, 100, "lee"}, {7, 75, "moon"}, {6, 90, "park"}}; 



int Print_All_Data(void);



int Compare_Id(SCORE * x, SCORE* y);

int Compare_Name(SCORE * x, SCORE* y);

int Compare_Jumsu(SCORE * x, SCORE* y);



int Sort_Bubble(SCORE * d, int n, int order, int (*comp)(SCORE * x, SCORE * y));

int Sort_Select(SCORE * d, int n, int order, int (*comp)(SCORE * x, SCORE * y));

int Sort_Insertion(SCORE * d, int n, int order, int (*comp)(SCORE * x, SCORE * y));

int Sort_Quick(SCORE *d, int order, int s, int e, int (*comp)(SCORE * x, SCORE * y));

int Sort_Merge(SCORE *d, SCORE *tmp, int order, int s, int e, int (*comp)(SCORE * x, SCORE * y))



int Print_All_Data(void)

{

	int i;



	for(i=0; i<MAX_ST; i++)

	{

		printf("[%d] ID=%d, NAME=%s, SCORE=%d\n", i, exam[i].id, exam[i].name, exam[i].jumsu);

	}



	return i;

}



int Compare_Id(SCORE * x, SCORE* y)

{

	return x->id - y->id;

}



int Compare_Name(SCORE * x, SCORE* y)

{

	return strcmp(x->name,y->name);

}



int Compare_Jumsu(SCORE * x, SCORE* y)

{

	return x->jumsu - y->jumsu;

}



#endif





/***********************************************************/

// [1-1.1] Bubble Sort

/***********************************************************/



#if 0



int Sort_Bubble(SCORE * d, int n, int order, int (*comp)(SCORE * x, SCORE * y))

{

	int i, j;

	SCORE temp;



	for(i=0 ; i<n-1 ; i++)

	{

		for(j=0 ; j<n-1-i ; j++)

		{

			if(comp(&d[j], &d[j+1])*order > 0)

			{

				temp = d[j];

				d[j] = d[j+1];

				d[j+1] = temp;

			}

		}

	}



	return n;

}



#endif



#if 0



void main(void)

{

	printf("Printed Data Count = %d\n", Print_All_Data());



	printf("===================================================\n");

	printf("Sorted Data Count = %d\n", Sort_Bubble(exam, 10, 1, Compare_Id));

	printf("Printed Data Count = %d\n", Print_All_Data());

	printf("Sorted Data Count = %d\n", Sort_Bubble(exam, 10, -1, Compare_Id));

	printf("Printed Data Count = %d\n", Print_All_Data());

	printf("===================================================\n");

	printf("Sorted Data Count = %d\n", Sort_Bubble(exam, 10, 1, Compare_Name));

	printf("Printed Data Count = %d\n", Print_All_Data());

	printf("Sorted Data Count = %d\n", Sort_Bubble(exam, 10, -1, Compare_Name));

	printf("Printed Data Count = %d\n", Print_All_Data());

	printf("===================================================\n");

	printf("Sorted Data Count = %d\n", Sort_Bubble(exam, 10, 1, Compare_Jumsu));

	printf("Printed Data Count = %d\n", Print_All_Data());

	printf("Sorted Data Count = %d\n", Sort_Bubble(exam, 10, -1, Compare_Jumsu));

	printf("Printed Data Count = %d\n", Print_All_Data());

	printf("===================================================\n");

}



#endif



/***********************************************************/

// [1-1.2] 자료를 선택 정렬로 정렬하는 함수

/***********************************************************/



#if 0



int Sort_Select(SCORE * d, int n, int order, int (*comp)(SCORE * x, SCORE * y))

{

	int i, j, t;

	SCORE temp;



	for(i=0 ; i<n-1 ; i++)

	{

		for(t = 0, j=1 ; j<n-i; j++)

		{

			if(comp(&d[t], &d[j])*order < 0 ) t = j;

		}



		j--;



		if(j != t)

		{

			temp = d[j];

			d[j] = d[t];

			d[t] = temp;

		}

	}



	return n;

}



#endif



#if 0



void main(void)

{

	printf("Printed Data Count = %d\n", Print_All_Data());

	printf("===================================================\n");

	printf("Sorted Data Count = %d\n", Sort_Select(exam, 10, 1, Compare_Id));

	printf("Printed Data Count = %d\n", Print_All_Data());

	printf("Sorted Data Count = %d\n", Sort_Select(exam, 10, -1, Compare_Id));

	printf("Printed Data Count = %d\n", Print_All_Data());

	printf("===================================================\n");

	printf("Sorted Data Count = %d\n", Sort_Select(exam, 10, 1, Compare_Name));

	printf("Printed Data Count = %d\n", Print_All_Data());

	printf("Sorted Data Count = %d\n", Sort_Select(exam, 10, -1, Compare_Name));

	printf("Printed Data Count = %d\n", Print_All_Data());

	printf("===================================================\n");

	printf("Sorted Data Count = %d\n", Sort_Select(exam, 10, 1, Compare_Jumsu));

	printf("Printed Data Count = %d\n", Print_All_Data());

	printf("Sorted Data Count = %d\n", Sort_Select(exam, 10, -1, Compare_Jumsu));

	printf("Printed Data Count = %d\n", Print_All_Data());

	printf("===================================================\n");

}



#endif



/***********************************************************/

// [1-1.3] 자료를 삽입 정렬로 정렬하는 함수

/***********************************************************/



#if 0



int Sort_Insertion(SCORE * d, int n, int ord, int (*comp)(SCORE * x, SCORE * y))

{

	int i, j, k;

	SCORE temp;



	

	for(i=1 ; i<n ; i++)

	{

		for(j=0 ; j<i ; j++)

		{

			if(comp(&d[j], &d[i])*ord>0)

			{

				temp = d[i];

				for(k=i ; k>j ; k--) d[k] = d[k-1];

				d[j] = temp;

				break;

			}

		}

	}



	return i;

}



#endif



#if 0



void main(void)

{

	printf("Printed Data Count = %d\n", Print_All_Data());



	printf("===================================================\n");

	printf("Sorted Data Count = %d\n", Sort_Insertion(exam, 10, 1, Compare_Id));

	printf("Printed Data Count = %d\n", Print_All_Data());

	printf("Sorted Data Count = %d\n", Sort_Insertion(exam, 10, -1, Compare_Id));

	printf("Printed Data Count = %d\n", Print_All_Data());

	printf("===================================================\n");

	printf("Sorted Data Count = %d\n", Sort_Insertion(exam, 10, 1, Compare_Name));

	printf("Printed Data Count = %d\n", Print_All_Data());

	printf("Sorted Data Count = %d\n", Sort_Insertion(exam, 10, -1, Compare_Name));

	printf("Printed Data Count = %d\n", Print_All_Data());

	printf("===================================================\n");

	printf("Sorted Data Count = %d\n", Sort_Insertion(exam, 10, 1, Compare_Jumsu));

	printf("Printed Data Count = %d\n", Print_All_Data());

	printf("Sorted Data Count = %d\n", Sort_Insertion(exam, 10, -1, Compare_Jumsu));

	printf("Printed Data Count = %d\n", Print_All_Data());

	printf("===================================================\n");

}



#endif



/***********************************************************/

// [1-1.4] Quick Sort 함수 설계

/***********************************************************/



#if 0



int Sort_Quick(SCORE *d, int order, int s, int e, int (*comp)(SCORE * x, SCORE * y))

{

	SCORE temp;

	int pivot, left, t = s;



	pivot = e;



	if(s >= e) return -1;



	for(left=s ; left < e ; left++)

	{

		if(comp(&d[left], &d[pivot])*order<0)

		{

			if(t != left)

			{

				temp = d[left];

				d[left] = d[t];

				d[t] = temp;

			}

			t++;

		}

	}



	if(t < pivot)

	{

		temp = d[pivot];

		d[pivot] = d[t];

		d[t] = temp;

	}



	Sort_Quick(d, order, s, t-1, comp);

	Sort_Quick(d, order, t+1, e, comp);



	return e-s+1;

}



#endif



#if 0



void main(void)

{

	printf("Printed Data Count = %d\n", Print_All_Data());



	printf("===================================================\n");

	printf("Sorted Data Count = %d\n", Sort_Quick(exam, 1, 0, MAX_ST-1, Compare_Id));

	printf("Printed Data Count = %d\n", Print_All_Data());

	printf("Sorted Data Count = %d\n", Sort_Quick(exam, -1, 0, MAX_ST-1, Compare_Id));

	printf("Printed Data Count = %d\n", Print_All_Data());

	printf("===================================================\n");

	printf("Sorted Data Count = %d\n", Sort_Quick(exam, 1, 0, MAX_ST-1, Compare_Name));

	printf("Printed Data Count = %d\n", Print_All_Data());

	printf("Sorted Data Count = %d\n", Sort_Quick(exam, -1, 0, MAX_ST-1, Compare_Name));

	printf("Printed Data Count = %d\n", Print_All_Data());

	printf("===================================================\n");

	printf("Sorted Data Count = %d\n", Sort_Quick(exam, 1, 0, MAX_ST-1, Compare_Jumsu));

	printf("Printed Data Count = %d\n", Print_All_Data());

	printf("Sorted Data Count = %d\n", Sort_Quick(exam, -1, 0, MAX_ST-1, Compare_Jumsu));

	printf("Printed Data Count = %d\n", Print_All_Data());

	printf("===================================================\n");

}



#endif





/***********************************************************/

// [1-1.5] Merge Sort 함수 설계

/***********************************************************/



#if 0



int Sort_Merge(SCORE *d, SCORE *tmp, int order, int s, int e, int (*comp)(SCORE * x, SCORE * y))

{

	int m,idx1,idx2,idxtmp;

	if(s>=e) return -1;



	m = (s+e)/2;



	Sort_Merge(d, tmp, order, s, m, comp);

	Sort_Merge(d, tmp, order, m+1, e, comp);



	idx1 = s; idx2 = m+1; idxtmp = s;

	while(idx1<=m && idx2<=e)

	{

		if((order * comp(&d[idx1],&d[idx2]))<0) tmp[idxtmp++] = d[idx1++];

		else tmp[idxtmp++] = d[idx2++];

	}

	

	if(idx1<=m) while(idx1<=m) tmp[idxtmp++] = d[idx1++];

	else while(idx2<=e) tmp[idxtmp++] = d[idx2++];



	for(idxtmp = s;idxtmp<=e;idxtmp++) d[idxtmp] = tmp[idxtmp];

	return e-s+1;

}



#endif



#if 0



SCORE tmp[MAX_ST];



void main(void)

{

	printf("Printed Data Count = %d\n", Print_All_Data());



	printf("===================================================\n");

	printf("Sorted Data Count = %d\n", Sort_Merge(exam, tmp, 1, 0, MAX_ST-1, Compare_Id));

	printf("Printed Data Count = %d\n", Print_All_Data());

	printf("Sorted Data Count = %d\n", Sort_Merge(exam, tmp, -1, 0, MAX_ST-1, Compare_Id));

	printf("Printed Data Count = %d\n", Print_All_Data());

	printf("===================================================\n");

	printf("Sorted Data Count = %d\n", Sort_Merge(exam, tmp, 1, 0, MAX_ST-1, Compare_Name));

	printf("Printed Data Count = %d\n", Print_All_Data());

	printf("Sorted Data Count = %d\n", Sort_Merge(exam, tmp, -1, 0, MAX_ST-1, Compare_Name));

	printf("Printed Data Count = %d\n", Print_All_Data());

	printf("===================================================\n");

	printf("Sorted Data Count = %d\n", Sort_Merge(exam, tmp, 1, 0, MAX_ST-1, Compare_Jumsu));

	printf("Printed Data Count = %d\n", Print_All_Data());

	printf("Sorted Data Count = %d\n", Sort_Merge(exam, tmp, -1, 0, MAX_ST-1, Compare_Jumsu));

	printf("Printed Data Count = %d\n", Print_All_Data());

	printf("===================================================\n");

}

#endif



#endif



/***********************************************************/

// [1-2] 이진 탐색

/***********************************************************/



#if 0



#if 0



#include <stdio.h>

#include <string.h>



// 이진 탐색에 사용 할 자료

typedef struct _score 

{

	int id;

	int jumsu;

	char name[10];

}SCORE;



#define MAX_ST (10)



SCORE exam[MAX_ST] = {{10, 50, "kim"}, {2, 80, "lew"}, {8, 50, "lew"}, {4, 45, "lee"}, {1, 90, "song"},\

                               {3, 45, "kim"}, {5, 50, "song"}, {9, 100, "lee"}, {7, 75, "moon"}, {6, 90, "park"}}; 



int Print_All_Data(void);



int Compare_Id(SCORE * x, SCORE* y);

int Compare_Name(SCORE * x, SCORE* y);

int Compare_Jumsu(SCORE * x, SCORE* y);



int Sort_Bubble(SCORE * d, int n, int order, int (*comp)(SCORE * x, SCORE * y));

int Sort_Select(SCORE * d, int n, int order, int (*comp)(SCORE * x, SCORE * y));

int Sort_Insertion(SCORE * d, int n, int order, int (*comp)(SCORE * x, SCORE * y));

int Sort_Quick(SCORE *d, int order, int s, int e, int (*comp)(SCORE * x, SCORE * y));

int Sort_Merge(SCORE *d, SCORE *tmp, int order, int s, int e, int (*comp)(SCORE * x, SCORE * y));



int Print_All_Data(void)

{

	int i;



	for(i=0; i<MAX_ST; i++)

	{

		printf("[%d] ID=%d, NAME=%s, SCORE=%d\n", i, exam[i].id, exam[i].name, exam[i].jumsu);

	}



	return i;

}



void Print_Data(int n)

{

	if((n<0) || (n>=MAX_ST)) return;

	printf("[%d] ID=%d, NAME=%s, SCORE=%d\n", n, exam[n].id, exam[n].name, exam[n].jumsu);

}



int Compare_Id(SCORE * x, SCORE* y)

{

	return x->id - y->id;

}



int Compare_Name(SCORE * x, SCORE* y)

{

	return strcmp(x->name,y->name);

}



int Compare_Jumsu(SCORE * x, SCORE* y)

{

	return x->jumsu - y->jumsu;

}



SCORE tmp[MAX_ST];



int Sort_Merge(SCORE *d, SCORE *tmp, int order, int s, int e, int (*comp)(SCORE * x, SCORE * y))

{

	int m,idx1,idx2,idxtmp;

	if(s>=e) return -1;



	m = (s+e)/2;



	Sort_Merge(d, tmp, order, s, m, comp);

	Sort_Merge(d, tmp, order, m+1, e, comp);



	idx1 = s; idx2 = m+1; idxtmp = s;

	while(idx1<=m && idx2<=e)

	{

		if((order * comp(&d[idx1],&d[idx2]))<0) tmp[idxtmp++] = d[idx1++];

		else tmp[idxtmp++] = d[idx2++];

	}

	

	if(idx1<=m) while(idx1<=m) tmp[idxtmp++] = d[idx1++];

	else while(idx2<=e) tmp[idxtmp++] = d[idx2++];



	for(idxtmp = s;idxtmp<=e;idxtmp++) d[idxtmp] = tmp[idxtmp];

	return e-s+1;

}



#endif



/***********************************************************/

// [1-2.1] Binary Search 함수 설계

/***********************************************************/



#if 0



int Binary_Search(SCORE *src, int s,int e,SCORE *d,int (*comp)(SCORE* x,SCORE *y))

{

	int m,ret;



	while(s<=e)

	{

		m = (s+e)/2;

		ret = comp(d,&src[m]);

		if(ret == 0) return m;

		else if(ret > 0) s = m+1;

		else e = m-1;

	}



	return -1;

}

#endif





#if 0

void main(void)

{

	int ret;

	SCORE d;

	

	printf("Binary Search Test\n");

	

	printf("Exam Data(Sort by ID)\n");

	Sort_Merge(exam,tmp,1,0,MAX_ST-1,Compare_Id);

	Print_All_Data();

	printf("============================================\n");



	d.id = 1;

	printf("Binary Search (ID : 1) = %d\n",ret = Binary_Search(exam,0,MAX_ST-1,&d,Compare_Id));

	Print_Data(ret);



	d.id = 7;

	printf("Binary Search (ID : 7) = %d\n",ret = Binary_Search(exam,0,MAX_ST-1,&d,Compare_Id));

	Print_Data(ret);

	

	d.id = 10;

	printf("Binary Search (ID : 10) = %d\n",ret = Binary_Search(exam,0,MAX_ST-1,&d,Compare_Id));

	Print_Data(ret);



	d.id = 15;

	printf("Binary Search (ID : 15) = %d\n",ret = Binary_Search(exam,0,MAX_ST-1,&d,Compare_Id));

	Print_Data(ret);

	printf("============================================\n");

	

	printf("Exam Data(Sort by Name)\n");

	Sort_Merge(exam,tmp,1,0,MAX_ST-1,Compare_Name);

	Print_All_Data();

	printf("============================================\n");



	strcpy(d.name,"moon");

	printf("Binary Search (Name : moon) = %d\n",ret = Binary_Search(exam,0,MAX_ST-1,&d,Compare_Name));

	Print_Data(ret);



	strcpy(d.name,"kim");

	printf("Binary Search (Name : kim) = %d\n",ret = Binary_Search(exam,0,MAX_ST-1,&d,Compare_Name));

	Print_Data(ret);



	strcpy(d.name,"song");

	printf("Binary Search (Name : song) = %d\n",ret = Binary_Search(exam,0,MAX_ST-1,&d,Compare_Name));

	Print_Data(ret);



	strcpy(d.name,"choi");

	printf("Binary Search (Name : choi) = %d\n",ret = Binary_Search(exam,0,MAX_ST-1,&d,Compare_Name));

	Print_Data(ret);

	printf("============================================\n");

	

}

#endif



/***********************************************************/

// [1-2.2] Binary Search 기반 Lower bound 탐색 함수 설계

/***********************************************************/



#if 0

int Binary_Search_Lower(SCORE *src, int s,int e,SCORE *d,int (*comp)(SCORE* x,SCORE *y))

{

	int m,ret,sol=-1;



	while(s<=e)

	{

		m = (s+e)/2;

		ret = comp(d,&src[m]);

		if(ret <= 0) 

		{

			sol = m;

			e = m-1;

		}

		else s = m+1;

	}



	return sol;

}

#endif



/***********************************************************/

// [1-2.3] Binary Search 기반 Uppwer bound 탐색 함수 설계

/***********************************************************/

#if 0

int Binary_Search_Upper(SCORE *src, int s,int e,SCORE *d,int (*comp)(SCORE* x,SCORE *y))

{

	int m,ret,sol=-1;



	while(s<=e)

	{

		m = (s+e)/2;

		ret = comp(d,&src[m]);

		if(ret >= 0) 

		{

			sol = m;

			s = m+1;

		}

		else e = m-1;

	}



	return sol;

}

#endif





#if 0

void main(void)

{

	int i;

	int lower,upper;

	SCORE ld,ud;

	

	printf("Binary Search Test(Upper, Lower bound)\n");

	

	printf("Exam Data(Sort by jumsu)\n");

	Sort_Merge(exam,tmp,1,0,MAX_ST-1,Compare_Jumsu);

	Print_All_Data();

	printf("============================================\n");



	ld.jumsu = 75;

	ud.jumsu = 100;

	lower = Binary_Search_Lower(exam,0,MAX_ST-1,&ld,Compare_Jumsu);

	upper = Binary_Search_Upper(exam,0,MAX_ST-1,&ud,Compare_Jumsu);

	printf("Binary Search (Jumsu : 75~100) = (%d,%d)\n",lower,upper);

	for(i=lower;i<=upper;i++)

	{

		Print_Data(i);

	}



	ld.jumsu = 0;

	ud.jumsu = 74;

	lower = Binary_Search_Lower(exam,0,MAX_ST-1,&ld,Compare_Jumsu);

	upper = Binary_Search_Upper(exam,0,MAX_ST-1,&ud,Compare_Jumsu);

	printf("Binary Search (Jumsu : 0~74) = (%d,%d)\n",lower,upper);

	for(i=lower;i<=upper;i++)

	{

		Print_Data(i);

	}



	ld.jumsu = 51;

	ud.jumsu = 74;

	lower = Binary_Search_Lower(exam,0,MAX_ST-1,&ld,Compare_Jumsu);

	upper = Binary_Search_Upper(exam,0,MAX_ST-1,&ud,Compare_Jumsu);

	printf("Binary Search (Jumsu : 51~74) = (%d,%d)\n",lower,upper);

}

#endif



#endif



/***********************************************************/

// [1-3.1] 선형 리스트 - stack

/***********************************************************/



#if 0



#include <stdio.h>



#define MAX_STACK		10

#define STACK_EMPTY	MAX_STACK

#define STACK_FULL		0



int Push_Stack(int data);

int Pop_Stack(int *p);

int Print_Stack(void);

int Count_Full_Data_Stack(void);

int Count_Empty_Data_Stack(void);



int a[MAX_STACK+1] = {1,2,3,4,5,6,7,8,9,10,11};

int Stack[MAX_STACK];

int Sptr = STACK_EMPTY;



int Push_Stack(int data)

{

	if(Sptr == STACK_FULL) return -1;

	Stack[--Sptr] = data;

	return 1;

}



int Pop_Stack(int *p)

{

	if(Sptr == STACK_EMPTY) return -1;

	*p = Stack[Sptr++];

	return 1;

}



int Print_Stack(void)

{

	int i;



	for(i = Sptr; i < MAX_STACK; i++)

	{

		printf("STACK[%d] = %d\n", i, Stack[i]);

	}



	return MAX_STACK - Sptr;

}



int Count_Full_Data_Stack(void)

{

	return STACK_EMPTY - Sptr;

}



int Count_Empty_Data_Stack(void)

{

	return Sptr - STACK_FULL;

}



void main(void)

{

	int i;



	for(i=0; i<(MAX_STACK+1); i++)

	{

		printf("%d, ", a[i]);

	}

	

	printf("\n");



	for(i=0; i<5; i++)

	{

		printf("Push Result = %d\n", Push_Stack(a[i]));

		printf("Print Result = %d, ", Print_Stack());

		printf("Full = %d ", Count_Full_Data_Stack());

		printf("Empty = %d\n", Count_Empty_Data_Stack());

		printf("Sptr = %d\n", Sptr);

	}



	for(i=0; i<5; i++)

	{

		printf("Pop Result = %d\n", Pop_Stack(&a[i]));

		printf("Print Result = %d, ", Print_Stack());

		printf("Full = %d ", Count_Full_Data_Stack());

		printf("Empty = %d\n", Count_Empty_Data_Stack());

		printf("Sptr = %d\n", Sptr);

	}



	for(i=0; i<(MAX_STACK+1); i++)

	{

		printf("%d, ", a[i]);

	}

	

	printf("\n");



	for(i=0; i<(MAX_STACK+1); i++)

	{

		printf("Push Result = %d\n", Push_Stack(a[i]));

		printf("Print Result = %d, ", Print_Stack());

		printf("Full = %d ", Count_Full_Data_Stack());

		printf("Empty = %d\n", Count_Empty_Data_Stack());

		printf("Sptr = %d\n", Sptr);

	}



	for(i=0; i<(MAX_STACK+1); i++)

	{

		printf("Pop Result = %d\n", Pop_Stack(&a[i]));

		printf("Print Result = %d, ", Print_Stack());

		printf("Full = %d ", Count_Full_Data_Stack());

		printf("Empty = %d\n", Count_Empty_Data_Stack());

		printf("Sptr = %d\n", Sptr);

	}



	for(i=0; i<(MAX_STACK+1); i++)

	{

		printf("%d, ", a[i]);

	}

	

	printf("\n");

}



#endif



/***********************************************************/

// [1-3.2] 선형 리스트 - Linear Queue

/***********************************************************/



#if 0



#include <stdio.h>



#define MAX_Q			5

#define Q_EMPTY		0

#define Q_FULL			MAX_Q



int In_Queue(int data);

int Out_Queue(int *p);

int Print_Queue(void);

int Count_Full_Data_Queue(void);

int Count_Empty_Data_Queue(void);



int a[MAX_Q+1] = {1,2,3,4,5,6};

int Queue[MAX_Q];

int Wrptr = Q_EMPTY;

int Rdptr = Q_EMPTY;



int In_Queue(int data)

{

	int i;



	if(Wrptr == Q_FULL)

	{

		if(Rdptr == Q_EMPTY) 

		{

			return -1;

		}



		for(i=0; i<(Wrptr-Rdptr); i++)

		{

			Queue[i] = Queue[Rdptr + i];

		}		

		

		Wrptr -= Rdptr;

		Rdptr = Q_EMPTY;

	}

	

	Queue[Wrptr++] = data;

	return 1;

}



int Out_Queue(int *p)

{

	if(Rdptr == Wrptr) return -2;



	*p = Queue[Rdptr++];

	return 1;

}



int Print_Queue(void)

{

	int i;



	for(i=Rdptr; i<Wrptr; i++)

	{

		printf("Queue[%d] = %d\n", i, Queue[i]);

	}



	return Wrptr - Rdptr;

}



int Count_Full_Data_Queue(void)

{

	return Wrptr - Rdptr;

}



int Count_Empty_Data_Queue(void)

{

	return MAX_Q - (Wrptr - Rdptr);

}



void main(void)

{

	int i;



	for(i=0; i<(MAX_Q+1); i++)

	{

		printf("%d, ", a[i]);

	}

	

	printf("\n");



	for(i=0; i<3; i++)

	{

		printf("Queue Result = %d\n", In_Queue(a[i]));

		printf("Print Result = %d, ", Print_Queue());

		printf("Full = %d ", Count_Full_Data_Queue());

		printf("Empty = %d\n", Count_Empty_Data_Queue());

		printf("Wrptr = %d, Rdptr = %d\n", Wrptr, Rdptr);

	}



	for(i=0; i<3; i++)

	{

		a[i] = 0;

	}



	for(i=0; i<3; i++)

	{

		printf("Dequeue Result = %d\n", Out_Queue(&a[i]));

		printf("Print Result = %d, ", Print_Queue());

		printf("Full = %d ", Count_Full_Data_Queue());

		printf("Empty = %d\n", Count_Empty_Data_Queue());

		printf("Wrptr = %d, Rdptr = %d\n", Wrptr, Rdptr);

	}



	for(i=0; i<(MAX_Q+1); i++)

	{

		printf("%d, ", a[i]);

	}



	printf("\n");



	for(i=0; i<(MAX_Q+1); i++)

	{

		printf("Queue Result = %d\n", In_Queue(a[i]));

		printf("Print Result = %d, ", Print_Queue());

		printf("Full = %d ", Count_Full_Data_Queue());

		printf("Empty = %d\n", Count_Empty_Data_Queue());

		printf("Wrptr = %d, Rdptr = %d\n", Wrptr, Rdptr);

	}



	for(i=0; i<(MAX_Q+1); i++)

	{

		a[i] = 0;

	}



	for(i=0; i<(MAX_Q+1); i++)

	{

		printf("Dequeue Result = %d\n", Out_Queue(&a[i]));

		printf("Print Result = %d, ", Print_Queue());

		printf("Full = %d ", Count_Full_Data_Queue());

		printf("Empty = %d\n", Count_Empty_Data_Queue());

		printf("Wrptr = %d, Rdptr = %d\n", Wrptr, Rdptr);

	}



	for(i=0; i<(MAX_Q+1); i++)

	{

		printf("%d, ", a[i]);

	}



	printf("\n");

}



#endif



/***********************************************************/

// [1-3.3] 선형 리스트 - Circular Queue

/***********************************************************/



#if 0



#include <stdio.h>



#define MAX_Q		8

#define Q_MIN		0

#define Q_MAX		MAX_Q



int In_Queue(int data);

int Out_Queue(int *p);

int Print_Queue(void);

int Count_Full_Data_Queue(void);

int Count_Empty_Data_Queue(void);



int a[MAX_Q+1] = {1,2,3,4,5,6,7,8,9};

int Queue[MAX_Q];

int Wrptr = Q_MIN;

int Rdptr = Q_MIN;



int In_Queue(int data)

{

	if(((Wrptr + 1) % MAX_Q) == Rdptr)

	{

		return -1;

	}



	Queue[Wrptr++] = data;

	Wrptr %= MAX_Q;

	return 1;

}



int Out_Queue(int *p)

{

	if(Rdptr == Wrptr)

	{

		return -2;

	}



	*p = Queue[Rdptr++];

	Rdptr %= MAX_Q;

	return 1;

}



int Print_Queue(void)

{

	int i;

	int rd = Rdptr;

	int n = Count_Full_Data_Queue();



	for(i=0; i<n; i++)

	{

		printf("Queue[%d] = %d\n", rd, Queue[rd++]);

		rd %= MAX_Q;

	}



	return n; 

}



int Count_Full_Data_Queue(void)

{

	if(Rdptr > Wrptr) return MAX_Q - (Rdptr - Wrptr);

	return Wrptr - Rdptr;

}



int Count_Empty_Data_Queue(void)

{

	return MAX_Q - Count_Full_Data_Queue() - 1;

}



void main(void)

{

	int i;



	for(i=0; i<(MAX_Q+1); i++)

	{

		printf("%d, ", a[i]);

	}

	

	printf("\n");



	for(i=0; i<3; i++)

	{

		printf("Queue Result = %d\n", In_Queue(a[i]));

		printf("Print Result = %d, ", Print_Queue());

		printf("Full = %d ", Count_Full_Data_Queue());

		printf("Empty = %d\n", Count_Empty_Data_Queue());

		printf("Wrptr = %d, Rdptr = %d\n", Wrptr, Rdptr);

	}



	for(i=0; i<3; i++)

	{

		a[i] = 0;

	}



	for(i=0; i<3; i++)

	{

		printf("Dequeue Result = %d\n", Out_Queue(&a[i]));

		printf("Print Result = %d, ", Print_Queue());

		printf("Full = %d ", Count_Full_Data_Queue());

		printf("Empty = %d\n", Count_Empty_Data_Queue());

		printf("Wrptr = %d, Rdptr = %d\n", Wrptr, Rdptr);

	}



	for(i=0; i<(MAX_Q+1); i++)

	{

		printf("%d, ", a[i]);

	}



	printf("\n");



	for(i=0; i<(MAX_Q+1); i++)

	{

		printf("Queue Result = %d\n", In_Queue(a[i]));

		printf("Print Result = %d, ", Print_Queue());

		printf("Full = %d ", Count_Full_Data_Queue());

		printf("Empty = %d\n", Count_Empty_Data_Queue());

		printf("Wrptr = %d, Rdptr = %d\n", Wrptr, Rdptr);

	}



	for(i=0; i<(MAX_Q+1); i++)

	{

		a[i] = 0;

	}



	for(i=0; i<(MAX_Q+1); i++)

	{

		printf("Dequeue Result = %d\n", Out_Queue(&a[i]));

		printf("Print Result = %d, ", Print_Queue());

		printf("Full = %d ", Count_Full_Data_Queue());

		printf("Empty = %d\n", Count_Empty_Data_Queue());

		printf("Wrptr = %d, Rdptr = %d\n", Wrptr, Rdptr);

	}



	for(i=0; i<(MAX_Q+1); i++)

	{

		printf("%d, ", a[i]);

	}



	printf("\n");

}



#endif



/***********************************************************/

// [1-4] Linked List

/***********************************************************/



/***********************************************************/

// [1-4-1] 배열 기반 연결 리스트
// 최대 얼마나 연결리스트를 할당받아야 하는지 알고 있는 경우에,

/***********************************************************/



#if 0
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

#endif



/***********************************************************/
// [1-4-2] 배열 기반 연결 리스트 - 더블 링크
/***********************************************************/

#if 0
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









/***********************************************************/

// [1-4-3] Heap 기반 연결 리스트

/***********************************************************/

#if 0



#if 0



/***********************************************************/

// [1-4-3.1] 기존 배열 기반 linked list 방식중 그대로 사용하는 함수들

/***********************************************************/



#include <stdio.h>

#include <string.h>

#include <conio.h>

#include <malloc.h>



typedef struct _score 

{

	int id;

	int jumsu;

	char name[10];

	struct _score  * next; 

}SCORE;



SCORE Head;



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



#define MAX_ST  20



SCORE test[MAX_ST] = {{10, 50, "kim"}, {2, 80, "lew"}, {8, 50, "lew"}, {4, 45, "lee"}, {1, 90, "song"},\

                               {3, 45, "kim"}, {5, 50, "song"}, {9, 100, "lee"}, {7, 75, "moon"}, {6, 90, "park"}, \

                               {15, 90, "ki"}, {11, 20, "kong"}, {14, 40, "shin"}, {12, 50, "son"}, {17, 48, "lee"}, \

                               {20, 100, "min"}, {19, 80, "you"}, {13, 45, "song"}, {16, 54, "no"}, {18, 100, "yang"}}; 



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



int Print_All_Node(SCORE * head)

{

	int n = 0;



	printf("Head.next = 0x%.8X\n", head->next);

	if(head->next == (SCORE *)0x0) return 0;

	head = head -> next;



	for(;;)

	{

		printf("addr = 0x%.8X, ID=%d, NAME=%s, SCORE=%d, next = 0x%.8X\n", head, head->id, head->name, head->jumsu, head->next);

		n++;

		if(head->next == (SCORE *)0x0) return n;

		head = head -> next;		

	}

}



SCORE * Search_Id_Node(SCORE * head, int id)

{

	if(head->next == (SCORE *)0x0) return (SCORE *)0x0;

	head = head -> next;



	for(;;)

	{

		if(head->id == id) return head;

		if(head->next == (SCORE *)0x0) return (SCORE *)0x0;

		head = head -> next;		

	}

}



int Count_Node(SCORE * head)

{

	int n = 0;



	if(head->next == (SCORE *)0x0) return 0;

	head = head -> next;



	for(;;)

	{

		n++;

		if(head->next == (SCORE *)0x0) return n;

		head = head -> next;		

	}

}



int Print_Node(SCORE * head, int id)

{

	SCORE * p = Search_Id_Node(head, id);



	if(p != (SCORE *)0x0)

	{

		printf("ID=%d, NAME=%s, SCORE=%d, next = 0x%.8X\n", p->id, p->name, p->jumsu, p->next);

		return 1;

	}



	return -1;

}



int Copy_All_Node(SCORE * head, SCORE * buf)

{

	int n = 0;



	if(head->next == (SCORE *)0x0) return -1;

	head = head -> next;



	for(;;)

	{

		buf[n] = *head;

		buf[n].next = &buf[n+1];

		if(head->next == (SCORE *)0x0)

		{

			buf[n].next = (SCORE *)0x0;

			return n+1;

		}

		n++;

		head = head -> next;

	}

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



		if(head->next == (SCORE *)0x0) 

		{

			buf[n-1].next = (SCORE *)0x0;

			return n;

		}



		head = head -> next;		

	}

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

		

		if(head->next == (SCORE *)0x0) 

		{

			buf[n-1].next = (SCORE *)0x0;

			return n;

		}



		head = head -> next;		

	}

}

#endif

/***********************************************************/

// [1-4-3.2] 전달받은 데이터를 힙에 생성하고 Linked List에 추가하는 함수 (calloc 사용)

/***********************************************************/



#if 0



int Insert_Node(SCORE * head, SCORE * d)

{

	SCORE * p;



	for(;;)

	{

		if((head->next == (SCORE *)0x0) || (d->id < head->next->id))

		{

			p = calloc(1, sizeof(SCORE));



			if(p == (void *)0x0) return -1;

			*p = *d;

			

			p->next = head->next;

			head->next = p;

			return 1;

		}

				

		if(d->id == head->next->id) return -2;



		head = head -> next;

	}

}



#endif



#if 0



void main(void)

{

	int i;

	SCORE * p;



	for(i=0; i<8; i++)

	{

		printf("Insert Node Result = %d\n", Insert_Node(&Head, &test[i]));

	}



	printf("Printed Node Count = %d\n", Print_All_Node(&Head));



	printf("Searched Node Address = 0x%.8X\n", p = Search_Id_Node(&Head, 8));

	

	if(p != (SCORE *)0x0)

	{

		printf("ID=%d, NAME=%s, SCORE=%d, next = 0x%.8X\n", p->id, p->name, p->jumsu, p->next);

	}



	printf("Searched Node Address = 0x%.8X\n", p = Search_Id_Node(&Head, 7));



	if(p != (SCORE *)0x0)

	{

		printf("ID=%d, NAME=%s, SCORE=%d, next = 0x%.8X\n", p->id, p->name, p->jumsu, p->next);

	}

}



#endif



/***********************************************************/

// [1-4-3.3] 전달받은 사번의 자료를 링크와 힙에서 삭제하는 함수 (free 사용)

/***********************************************************/



#if 0



int Delete_Node(SCORE * head, int id)

{

	SCORE * prev;



	if(head->next == (SCORE *)0x0) return -1;

	prev = head;

	head = head -> next;



	for(;;)

	{

		if(head->id == id)

		{

			prev->next = head->next;

			free(head);

			return 1;

		}



		if(head->next == (SCORE *)0x0) return -1;



		prev = head;

		head = head -> next;		

	}

}



#endif



#if 0



void main(void)

{

	int i;



	for(i=0; i<8; i++)

	{

		printf("Insert Node Result = %d\n", Insert_Node(&Head, &test[i]));

	}



	printf("Printed Node Count = %d\n", Print_All_Node(&Head));

	printf("Delete Node Result = %d\n", Delete_Node(&Head, 8)); 

	printf("Delete Node Result = %d\n", Delete_Node(&Head, 7)); 

	printf("Delete Node Result = %d\n", Delete_Node(&Head, 1)); 

	printf("Delete Node Result = %d\n", Delete_Node(&Head, 10)); 

	printf("Printed Node Count = %d\n", Print_All_Node(&Head));

}



#endif



#endif





/***********************************************************/

// [1-4-4] 힙 기반 연결 리스트 - 더블 링크

/***********************************************************/



#if 0



/***********************************************************/

// [1-4-4.0] 기존 Linked List 방식중 그대로 사용하는 함수들

/***********************************************************/



#if 0



#include <stdio.h>

#include <string.h>

#include <conio.h>

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



#define MAX_ST		20





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



SCORE test[MAX_ST] = {{10, 50, "kim"}, {2, 80, "lew"}, {8, 50, "lew"}, {4, 45, "lee"}, {1, 90, "song"},\

                               {3, 45, "kim"}, {5, 50, "song"}, {9, 100, "lee"}, {7, 75, "moon"}, {6, 90, "park"}, \

                               {15, 90, "ki"}, {11, 20, "kong"}, {14, 40, "shin"}, {12, 50, "son"}, {17, 48, "lee"}, \

                               {20, 100, "min"}, {19, 80, "you"}, {13, 45, "song"}, {16, 54, "no"}, {18, 100, "yang"}}; 





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



SCORE * Search_Id_Node(SCORE * head, int id)

{

	for(;;)

	{

		if(head->next == (SCORE *)0x0) return (SCORE *)0x0;

		if(head->next->id == id) return head->next;      

		head = head->next;		

	}

}



int Count_Node(SCORE * head)

{

	int i=0;



	for(;;)

	{

		if(head->next == (SCORE *)0x0) return i;

		head = head->next;		

		i++;

	}

}



int Print_Node(SCORE * head, int id)

{

	SCORE * p = Search_Id_Node(head, id);



	if(p != (SCORE *)0x0)

	{

		printf("ID=%d, NAME=%s, SCORE=%d, next=0x%.8X, prev=0x%.8X\n", p->id, p->name, p->jumsu, p->next, p->prev);

		return 1;

	}



	return -1;

}



int Copy_All_Node(SCORE * head, SCORE * buf)

{

	int i=0;

	if(head->next == NULL) return -1;



	for(;;)

	{

		if(head->next == NULL) break;

		buf[i] = *head->next;

		buf[i].next = &buf[i+1];

		head = head->next;

		i++;

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



int Print_All_Node(SCORE * head)

{

	int i=0;



	printf("Head.next = 0x%.8X Head.prev = 0x%.8X\n", head->next, head->prev);



	for(;;)

	{

		if(head->next == (SCORE *)0x0) return i;

		printf("addr = 0x%.8X, ID=%d, NAME=%s, SCORE=%d, next=0x%.8X, prev=0x%.8X\n", head->next, head->next->id, head->next->name, head->next->jumsu, head->next->next, head->next->prev);

		head = head->next;		

		i++;

	}

}



int Print_All_Node_Reverse(SCORE * head)

{

	int i=0;



	printf("Head.next = 0x%.8X Head.prev = 0x%.8X\n", head->next, head->prev);



	while(head->next != (SCORE *)0x0)

	{

		head = head->next;

	}



	printf("Tail.next = 0x%.8X Tail.prev = 0x%.8X\n", head->next, head->prev);



	for(;;)

	{

		if(head->prev == (SCORE *)0x0) return i;

		printf("addr = 0x%.8X, ID=%d, NAME=%s, SCORE=%d, next=0x%.8X, prev=0x%.8X\n", head, head->id, head->name, head->jumsu, head->next, head->prev);

		head = head->prev;		

		i++;

	}

}



int Print_Selected_Node(SCORE * head, int id, int num)

{

	int i = 0;



	head = Search_Id_Node(head, id);

	

	if(head == (SCORE *)0x0) return -1;



	printf("==================================================================================\n");



	while(i<num)

	{

		printf("addr = 0x%.8X, ID=%d, NAME=%s, SCORE=%d, next=0x%.8X, prev=0x%.8X\n", head, head->id, head->name, head->jumsu, head->next, head->prev);

		i++;

		if(head->next == (SCORE *)0x0) break;

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

		printf("addr = 0x%.8X, ID=%d, NAME=%s, SCORE=%d, next=0x%.8X, prev=0x%.8X\n", head, head->id, head->name, head->jumsu, head->next, head->prev);

		i++;

		if(head->prev->prev == (SCORE *)0x0) break;

		head = head->prev;		

	}



	return i;

}



#endif



/***********************************************************/

// [1-4-4.1] 데이터 하나를 생성하여 Linked List에 추가하는 함수 (calloc 사용)

/***********************************************************/



#if 0



int Insert_Node(SCORE * head, SCORE * d)

{

	SCORE * p;



	for(;;)

	{

		if((head->next == (SCORE *)0x0) || (d->id < head->next->id))

		{

			p = calloc(1, sizeof(SCORE));



			if(p == (void *)0x0) return -1;

			*p = *d;



			p->next = head->next;

			p->prev = head;

			if(head->next) head->next->prev = p;

			head->next = p;

			return 1;

		}



		if(d->id == head->next->id) return -2;



		head = head->next;

	}

}



#endif



#if 0



void main(void)

{

	int i;



	for(i=0; i<8; i++)

	{

		printf("Insert Node Result = %d\n", Insert_Node(&Head, &test[i]));

		printf("Printed Node Count = %d\n", Print_All_Node(&Head));

	}

}



#endif



/***********************************************************/

// [1-4-4.2] 주어진 사번의 node를 찾아서 삭제하는 함수

/***********************************************************/



#if 0



int Delete_Node(SCORE * head, int id)

{

	SCORE *p = 	Search_Id_Node(head, id);



	if(p == (SCORE *)0x0) return -1;



	p->prev->next = p->next;

	if(p->next) p->next->prev = p->prev;

	free(p);



	return 1;

}



#endif



#if 0



void main(void)

{

	int i;



	for(i=0; i<8; i++)

	{

		printf("Insert Node Result = %d\n", Insert_Node(&Head, &test[i]));

	}



	printf("Printed Node Count = %d\n", Print_All_Node(&Head));

	printf("Delete Node Result = %d\n", Delete_Node(&Head, 8)); 

	printf("Printed Node Count = %d\n", Print_All_Node(&Head));

	printf("Delete Node Result = %d\n", Delete_Node(&Head, 7)); 

	printf("Printed Node Count = %d\n", Print_All_Node(&Head));

	printf("Delete Node Result = %d\n", Delete_Node(&Head, 1)); 

	printf("Printed Node Count = %d\n", Print_All_Node(&Head));

	printf("Delete Node Result = %d\n", Delete_Node(&Head, 10)); 

	printf("Printed Node Count = %d\n", Print_All_Node(&Head));

}



#endif



#endif





/***********************************************************/

// [1-5] 연결리스트 기반 스택과 큐

/***********************************************************/



/***********************************************************/

// [1-5-1] 힙 기반 stack

/***********************************************************/



#if 0



#include <stdio.h>

#include <malloc.h>



typedef struct _stk

{

	int num;

	struct _stk * next; 

}STACK;



STACK * Sptr = (STACK *)0;

STACK a[10] = {{1,0},{2,0},{3,0},{4,0},{5,0},{6,0},{7,0},{8,0},{9,0},{10,0}};



int Push_Stack(STACK * data);

int Pop_Stack(STACK * p);

int Print_Stack(void);

int Count_Full_Data_Stack(void);



int Push_Stack(STACK *data)

{

	STACK * p;



	p = calloc(1, sizeof(STACK));

	if(p == (void *)0x0) return -1;

	*p = *data;

	p->next = Sptr;

	Sptr = p;



	return 1;

}



int Pop_Stack(STACK *p)

{

	STACK * temp = Sptr;



	if(Sptr == (STACK *)0x0) return -1;



	*p = *Sptr;

	Sptr = Sptr->next;

	free(temp);



	return 1;

}



int Print_Stack(void)

{

	int i = 0;



	STACK * temp = Sptr;



	while(temp)

	{

		printf("[%d] addr=0x%.8x, num=%d, next=0x%.8x\n", i++, temp, temp->num, temp->next);

		temp = temp->next;

	};



	return i;

}



int Count_Full_Data_Stack(void)

{

	int i = 0;



	STACK * temp = Sptr;



	while(temp) 

	{

		temp = temp->next;

		i++;

	}



	return i;

}



void main(void)

{

	int i;



	for(i=0; i<5; i++)

	{

		printf("Push Result = %d\n", Push_Stack(&a[i]));

		printf("Print Result = %d, ", Print_Stack());

		printf("Full = %d\n", Count_Full_Data_Stack());

	}



	for(i=0; i<6; i++)

	{

		printf("Pop Result = %d\n", Pop_Stack(&a[i]));

		printf("Print Result = %d, ", Print_Stack());

		printf("Full = %d\n ", Count_Full_Data_Stack());

	}



	for(i=0; i<3; i++)

	{

		printf("Push Result = %d\n", Push_Stack(&a[i]));

		printf("Print Result = %d, ", Print_Stack());

		printf("Full = %d\n", Count_Full_Data_Stack());

	}



	for(i=0; i<5; i++)

	{

		printf("Pop Result = %d\n", Pop_Stack(&a[i]));

		printf("Print Result = %d, ", Print_Stack());

		printf("Full = %d\n ", Count_Full_Data_Stack());

	}



	printf("\n");

}



#endif



/***********************************************************/

// [1-5-2] 힙 기반  Linear Queue

/***********************************************************/

#if 0



#include <stdio.h>

#include <malloc.h>



typedef struct _que

{

	int num;

	struct _que * next; 

}QUEUE;



QUEUE * Wrptr = (QUEUE *)0;;

QUEUE * Rdptr = (QUEUE *)0;;



QUEUE a[10] = {{1,0},{2,0},{3,0},{4,0},{5,0},{6,0},{7,0},{8,0},{9,0},{10,0}};



int In_Queue(QUEUE * data);

int Out_Queue(QUEUE * p);

int Print_Queue(void);

int Count_Full_Data_Queue(void);



int In_Queue(QUEUE * data)

{

	QUEUE * p;



	p = calloc(1, sizeof(QUEUE));

	if(p == (void *)0x0) return -1;

	*p = *data;

	p->next = (QUEUE *)0;

	if(Wrptr) Wrptr->next = p;

	Wrptr = p;

	if(Rdptr == (void *)0x0) Rdptr = p;



	return 1;

}



int Out_Queue(QUEUE * p)

{

	QUEUE * temp = Rdptr;



	if(Rdptr == (QUEUE *)0) return -1;

	*p = *Rdptr;

	Rdptr = Rdptr->next;

	if(Rdptr == (QUEUE *)0) Wrptr = (QUEUE *)0;

	free(temp);



	return 1;

}



int Print_Queue(void)

{

	int i = 0;



	QUEUE * temp = Rdptr;



	while(temp)

	{

		printf("[%d] addr=0x%.8x, num=%d, next=0x%.8x\n", i++, temp, temp->num, temp->next);

		temp = temp->next;

	};



	return i;

}



int Count_Full_Data_Queue(void)

{

	int i = 0;

	QUEUE * temp = Rdptr;



	while(temp) 

	{

		temp = temp->next;

		i++;

	}



	return i;

}



void main(void)

{

	int i;



	for(i=0; i<3; i++)

	{

		printf("Queue Result = %d\n", In_Queue(&a[i]));

		printf("Print Result = %d, ", Print_Queue());

		printf("Full = %d\n", Count_Full_Data_Queue());

	}



	for(i=0; i<2; i++)

	{

		printf("Dequeue Result = %d\n", Out_Queue(&a[i]));

		printf("Print Result = %d, ", Print_Queue());

		printf("Full = %d\n", Count_Full_Data_Queue());

	}



	for(i=0; i<4; i++)

	{

		printf("Queue Result = %d\n", In_Queue(&a[i]));

		printf("Print Result = %d, ", Print_Queue());

		printf("Full = %d\n", Count_Full_Data_Queue());

	}



	for(i=0; i<7; i++)

	{

		printf("Dequeue Result = %d\n", Out_Queue(&a[i]));

		printf("Print Result = %d, ", Print_Queue());

		printf("Full = %d\n", Count_Full_Data_Queue());

	}



	for(i=0; i<3; i++)

	{

		printf("Queue Result = %d\n", In_Queue(&a[i]));

		printf("Print Result = %d, ", Print_Queue());

		printf("Full = %d\n", Count_Full_Data_Queue());

	}



	for(i=0; i<3; i++)

	{

		printf("Dequeue Result = %d\n", Out_Queue(&a[i]));

		printf("Print Result = %d, ", Print_Queue());

		printf("Full = %d\n", Count_Full_Data_Queue());

	}

}



#endif





/***********************************************************/

// [2-1] 그래프  

/***********************************************************/



#if 01

#include <stdio.h>

#include <stdlib.h>



/***********************************************************/

// [2-1.1] Graph 기본 자료

/***********************************************************/



#define NUM_NODE 6

#define NUM_EDGE 16



typedef struct

{

	int s;

	int e;

	int cost;

}EDGE;

EDGE edge[16] = {{1,2,3},{1,4,6},{1,5,12},{2,3,2},{2,4,9},{3,2,4},{3,5,6},{3,6,7},{4,1,8},{4,5,5},{5,2,11},{5,3,8},{5,4,7},{5,6,5},{6,2,13},{6,3,5}};





/***********************************************************/

// [2-1.2] 인접 행렬

/***********************************************************/



#if 0



#define NOT_CONNECTED	(0x7fffffff)

int matrix[NUM_NODE+1][NUM_NODE+1];



void Init_Graph_Adjacency_Matrix(void)

{

	int i,j;



	for(i=1;i<=NUM_NODE;i++)

	{

		for(j=i;j<=NUM_NODE;j++)

		{

			matrix[i][j] = matrix[j][i] = NOT_CONNECTED;

		}

	}



	for(i=0;i<NUM_EDGE;i++)

	{

		matrix[edge[i].s][edge[i].e] = edge[i].cost;

	}

}





int visited[100];

int path_cnt;

int path[100];

void DFS(int cur, int e, int sum_cost)

{

	int i;

	visited[cur] = 1;

	path[path_cnt++] = cur;	

	

	if(cur == e)

	{

		printf("%d ",path[0]);

		for(i=1;i<path_cnt;i++) printf("- %d ",path[i]);

		printf("[total cost : %d]\n",sum_cost);

		visited[cur] = 0;

		path_cnt--;

		return;

	}



	for(i=1;i<=NUM_NODE;i++)

	{

		if(matrix[cur][i] != NOT_CONNECTED && !visited[i])

		{

			DFS(i,e,sum_cost+matrix[cur][i]);

		}

	}



	visited[cur] = 0;

	path_cnt--;

}



int main(void)

{

	printf("Graph - Adjacency matrix\n\n");



	Init_Graph_Adjacency_Matrix();



	printf("[Path] Node 1 -> Node 6\n");

	DFS(1,6,0);



	printf("\n[Path] Node 3 -> Node 5\n");

	DFS(3,5,0);

}

#endif

/***********************************************************/
// [2-1.3] 인접 리스트 (배열 기반)
/***********************************************************/
#if 01 

typedef struct list
{
	int node;
	int cost;
}LIST;

LIST list[NUM_NODE+1][NUM_NODE];
int list_cnt[NUM_NODE+1];

void Init_Graph_Adjacency_list(void)
{
	int i;
	for(i=0;i<NUM_EDGE;i++)
	{
		list[edge[i].s][list_cnt[edge[i].s]].node = edge[i].e;
		list[edge[i].s][list_cnt[edge[i].s]].cost = edge[i].cost;
		list_cnt[edge[i].s]++;
	}
}


int visited[100];
int path_cnt;
int path[100];

void DFS(int cur, int e, int sum_cost)
{
	int i;
	visited[cur] = 1;
	path[path_cnt++] = cur;	

	if(cur == e)
	{
		printf("%d ",path[0]);
		for(i=1;i<path_cnt;i++) printf("- %d ",path[i]);
		printf("[total cost : %d]\n",sum_cost);
		visited[cur] = 0;
		path_cnt--;
		return;
	}

	for(i=0;i<list_cnt[cur];i++)
	{
		if(!visited[list[cur][i].node])
		{
			DFS(list[cur][i].node,e,sum_cost+list[cur][i].cost);
		}
	}

	visited[cur] = 0;
	path_cnt--;
}

int main(void)
{
	printf("Graph - Adjacency list\n\n");
	Init_Graph_Adjacency_list();
	printf("[Path] Node 1 -> Node 6\n");
	DFS(1,6,0);
	printf("\n[Path] Node 3 -> Node 5\n");
	DFS(3,5,0);
	return 0;
}
#endif

/***********************************************************/
// [2-1.4] 인접 리스트 (Heap 기반)
/***********************************************************/

#if 0

typedef struct list
{
	int node;
	int cost;
	struct list *next;
}LIST;

LIST list[NUM_NODE+1];



int Init_Graph_Adjacency_list(void)

{

	int i;

	LIST *p;



	LIST* last[NUM_NODE+1];



	for(i=1;i<=NUM_NODE;i++)

	{

		last[i] = &list[i];

	}



	for(i=0;i<NUM_EDGE;i++)

	{

		p = (LIST*)malloc(sizeof(LIST));

		if(p == (LIST*)0) {printf("calloc() failed\n"); return 0;}



		p->node = edge[i].e;

		p->cost = edge[i].cost;

		p->next = (LIST*)0;



		last[edge[i].s]->next = p;

		last[edge[i].s] = p;

	}



	return 1;

}





int visited[100];

int path_cnt;

int path[100];

void DFS(int cur, int e, int sum_cost)

{

	int i;

	LIST* p;

	visited[cur] = 1;

	path[path_cnt++] = cur;	

	

	if(cur == e)

	{

		printf("%d ",path[0]);

		for(i=1;i<path_cnt;i++) printf("- %d ",path[i]);

		printf("[total cost : %d]\n",sum_cost);

		visited[cur] = 0;

		path_cnt--;

		return;

	}



	p = list[cur].next;

	while(p != (LIST*)0)

	{

		if(!visited[p->node])

		{

			DFS(p->node,e,sum_cost+p->cost);

		}

		p = p->next;

	}



	visited[cur] = 0;

	path_cnt--;

}



int main(void)

{

	int ret;

	

	printf("Graph - Adjacency list\n\n");



	ret = Init_Graph_Adjacency_list();

	if(!ret) return 0;



	printf("[Path] Node 1 -> Node 6\n");

	DFS(1,6,0);



	printf("\n[Path] Node 3 -> Node 5\n");

	DFS(3,5,0);



	return 0;

}

#endif



#endif





/***********************************************************/

// [2-2] Hash Table

/***********************************************************/



#if 0



/***********************************************************/

// [2-2.1] Hash Table을 위한 기본 함수들

/***********************************************************/



#if 0



#include <stdio.h>

#include <string.h>

#include <conio.h>



#include <malloc.h>



typedef struct _score 

{

	int id;

	int jumsu;

	char name[10];

}SCORE;



#define MAX_ST		20

#define HASH_KEY	10

#define STEP		1



SCORE Hash_table[MAX_ST];



// 이제부터 설계되는 모든 함수는 이 부분에 선언을 추가한다



int Create_Data(SCORE * p);

int Get_Hash_Key(int id);

void Init_Hash_Table(void);

void Print_All_Data(void);

int Insert_Data(SCORE * d);

SCORE * Search_Data(int id);

int Delete_Data(int id);



SCORE test[MAX_ST+2] = {{10, 50, "kim"}, {2, 80, "lew"}, {8, 50, "lew"}, {4, 45, "lee"}, {1, 90, "song"},\

                               {3, 45, "kim"}, {5, 50, "song"}, {9, 100, "lee"}, {7, 75, "moon"}, {6, 90, "park"}, \

                               {15, 90, "ki"}, {11, 20, "kong"}, {14, 40, "shin"}, {12, 50, "son"}, {17, 48, "lee"}, \

                               {20, 100, "min"}, {19, 80, "you"}, {13, 45, "song"}, {16, 54, "no"}, {18, 100, "yang"}, \

							   {21, 58, "seo"}, {23, 88, "oh"}}; 



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



	return 1;

}



int Get_Hash_Key(int id)

{

	return id % HASH_KEY;

}



void Init_Hash_Table(void)

{

	int i;



	for(i=0; i<MAX_ST; i++)

	{

		Hash_table[i].id = -1;

	}

}



#endif



#if 0



void Print_All_Data(void)

{

	int i;



	for(i=0; i<MAX_ST; i++)

	{

		if(Hash_table[i].id != -1) printf("[%d] ID: %d, NAME: %s\n", i, Hash_table[i].id, Hash_table[i].name);

	}

}



#endif



/***********************************************************/

// [2-2.2] Insert => Open Address 방법

/***********************************************************/



#if 0



int Insert_Data(SCORE * d)

{

	int pos;

	int key;

	

	pos = key = Get_Hash_Key(d->id);



	for(;;)

	{

		if(Hash_table[pos].id == -1)

		{

			Hash_table[pos] = *d;

			return pos;

		}



		pos += STEP;

		if(pos == key) return -1;

		if(pos >= MAX_ST) pos = 0;

	}

}



#endif



#if 0



void main(void)

{

	int i;

	int r;



	Init_Hash_Table();



	for(i=0; i<(MAX_ST+2); i++)

	{

		printf("[Loop: %d] Inserted Position=%d, ID=%d\n", i, r = Insert_Data(&test[i]), test[i].id);

		Print_All_Data();

	}

}



#endif



/***********************************************************/

// [2-2.3] Search

/***********************************************************/



#if 0



SCORE * Search_Data(int id)

{

	int pos;

	int key;

	

	pos = key = Get_Hash_Key(id);



	for(;;)

	{

		if(Hash_table[pos].id == id) return &Hash_table[pos];

		if(Hash_table[pos].id == -1) return (SCORE *)0;

		pos += STEP;

		if(pos == key) return (SCORE *)0;;

		if(pos >= MAX_ST) pos = 0;

	}

}



#endif



#if 0



void main(void)

{

	int i;

	int r;

	SCORE * p;



	Init_Hash_Table();



	for(i=0; i<15; i++)

	{

		printf("[Loop: %d] Inserted Position=%d, ID=%d\n", i, r = Insert_Data(&test[i]), test[i].id);

	}



	Print_All_Data();

	printf("Serch Result=0x%.8X\n", p = Search_Data(3));

	if(p) printf("ID=%d, NAME=%s\n", p->id, p->name);

	printf("Serch Result=0x%.8X\n", p = Search_Data(12));

	if(p) printf("ID=%d, NAME=%s\n", p->id, p->name);

	printf("Serch Result=0x%.8X\n", p = Search_Data(25));

	if(p) printf("ID=%d, NAME=%s\n", p->id, p->name);

}



#endif



/***********************************************************/

// [2-2.4] Delete 함수의 예

/***********************************************************/



#if 0



int Delete_Data(int id)

{

	SCORE * p;



	p = Search_Data(id);

	if(p == (SCORE *)0) return -1;

	p->id = -1;

	return 1;

}



#endif



/***********************************************************/

// [2-2.5] 삭제 노드 ID를 -2로 하도록 delete 함수 설계를 다시 진행한다

// 삭제 전략이 달라지면서 Insert 전략도 수정되어야 한다. 

// 새로은 Insert 함수가 설계되면 [3-3.2]에서 설계된 Insert_Data 함수는 삭제한다

/***********************************************************/



#if 0



int Delete_Data(int id)

{

	SCORE * p;



	p = Search_Data(id);

	if(p == (SCORE *)0) return -1;

	p->id = -2;

	return 1;

}



int Insert_Data(SCORE * d)

{

	int pos;

	int key;

	

	pos = key = Get_Hash_Key(d->id);



	for(;;)

	{

		if((Hash_table[pos].id == -1) || (Hash_table[pos].id == -2))

		{

			Hash_table[pos] = *d;

			return pos;

		}



		pos += STEP;

		if(pos == key) return -1;

		if(pos >= MAX_ST) pos = 0;

	}

}



void Print_All_Data(void)

{

	int i;



	for(i=0; i<MAX_ST; i++)

	{

		if((Hash_table[i].id != -1) && (Hash_table[i].id != -2)) printf("[%d] ID: %d, NAME: %s\n", i, Hash_table[i].id, Hash_table[i].name);

	}

}



#endif



#if 0



void main(void)

{

	int i;

	int r;



	Init_Hash_Table();



	for(i=0; i<15; i++)

	{

		printf("[Loop: %d] Inserted Position=%d, ID=%d\n", i, r = Insert_Data(&test[i]), test[i].id);

	}



	Print_All_Data();

	printf("[3] Delete Result=%d\n", r = Delete_Data(3));

	printf("[12] Delete Result=%d\n", r = Delete_Data(12));

	printf("[25] Delete Result=%d\n", r = Delete_Data(25));

	printf("[3] Delete Result=%d\n", r = Delete_Data(3));

	printf("[12] Delete Result=%d\n", r = Delete_Data(12));

	Print_All_Data();



	printf("Inserted Position=%d, ID=%d\n", r = Insert_Data(&test[13]), test[13].id);

	printf("Inserted Position=%d, ID=%d\n", r = Insert_Data(&test[5]), test[5].id);

	Print_All_Data();

}



#endif



#endif



/***********************************************************/

// [2-2.6] Hash Table => 해시 키 발생 함수의 변경

/***********************************************************/



#if 0



/***********************************************************/

// [2-2.6] Hash Table을 위한 기본 함수들

/***********************************************************/



#if 0



#include <stdio.h>

#include <string.h>

#include <conio.h>

#include <malloc.h>



typedef struct _score 

{

	int id;

	int jumsu;

	char name[10];

}SCORE;



#define MAX_ST		20



#if 0

	#define HASH_KEY	10

	#define STEP		1

#else

	#define HASH_KEY	7  // 가급적 소수

	#define STEP		9  // 테이블의 요소수와 서로 소 관계인 수

#endif



SCORE Hash_table[MAX_ST];



// 이제부터 설계되는 모든 함수는 이 부분에 선언을 추가한다



int Create_Data(SCORE * p);

int Get_Hash_Key(int id);

void Init_Hash_Table(void);

void Print_All_Data(void);

int Insert_Data(SCORE * d);

SCORE * Search_Data(int id);

int Delete_Data(int id);



SCORE test[MAX_ST+2] = {{10, 50, "kim"}, {2, 80, "lew"}, {8, 50, "lew"}, {4, 45, "lee"}, {1, 90, "song"},\

                               {3, 45, "kim"}, {5, 50, "song"}, {9, 100, "lee"}, {7, 75, "moon"}, {6, 90, "park"}, \

                               {15, 90, "ki"}, {11, 20, "kong"}, {14, 40, "shin"}, {12, 50, "son"}, {17, 48, "lee"}, \

                               {20, 100, "min"}, {19, 80, "you"}, {13, 45, "song"}, {16, 54, "no"}, {18, 100, "yang"}, \

							   {21, 58, "seo"}, {23, 88, "oh"}}; 



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



	return 1;

}



int Get_Hash_Key(int id)

{

	return id % HASH_KEY;

}



void Init_Hash_Table(void)

{

	int i;



	for(i=0; i<MAX_ST; i++)

	{

		Hash_table[i].id = -1;

	}

}



void Print_All_Data(void)

{

	int i;



	for(i=0; i<MAX_ST; i++)

	{

		if((Hash_table[i].id != -1) && (Hash_table[i].id != -2)) printf("[%d] ID: %d, NAME: %s\n", i, Hash_table[i].id, Hash_table[i].name);

	}

}



int Delete_Data(int id)

{

	SCORE * p;



	p = Search_Data(id);

	if(p == (SCORE *)0) return -1;

	p->id = -2;

	return 1;

}



int Insert_Data(SCORE * d)

{

	int pos;

	int cnt = 0;

	static int insert_cnt;

	

	pos = Get_Hash_Key(d->id);



	for(;;)

	{

		if((Hash_table[pos].id == -1) || (Hash_table[pos].id == -2))

		{

			Hash_table[pos] = *d;

			insert_cnt += cnt+1;

			printf("cnt = %d, total insert count = %d\n", cnt+1, insert_cnt);

			return pos;

		}



		pos += STEP;

		cnt++;

		if(cnt >= MAX_ST) return -1;

		if(pos >= MAX_ST) pos %= MAX_ST;

	}

}



SCORE * Search_Data(int id)

{

	int pos;

	int cnt = 0;

	static int search_cnt; 



	pos = Get_Hash_Key(id);



	for(;;)

	{

		if(Hash_table[pos].id == id) return &Hash_table[pos];

		if(Hash_table[pos].id == -1) return (SCORE *)0;

		pos += STEP;

		cnt++;

		search_cnt += cnt+1;

		printf("cnt = %d, total search count = %d\n", cnt+1, search_cnt);

		if(cnt >= MAX_ST) return (SCORE *)0;

		if(pos >= MAX_ST) pos %= MAX_ST;

	}

}



#endif



/***********************************************************/

// [2-2.6] Insert 효율

/***********************************************************/



#if 0



void main(void)

{

	int i;

	int r;



	Init_Hash_Table();



	for(i=0; i<MAX_ST; i++)

	{

		printf("[Loop: %d] Inserted Position=%d, ID=%d\n", i, r = Insert_Data(&test[i]), test[i].id);

		Print_All_Data();

	}

}



#endif



/***********************************************************/

// [2-2.7] Search 효율

/***********************************************************/



#if 0



void main(void)

{

	int i;

	int r;

	SCORE * p;



	Init_Hash_Table();



	for(i=0; i<15; i++)

	{

		printf("[Loop: %d] Inserted Position=%d, ID=%d\n", i, r = Insert_Data(&test[i]), test[i].id);

	}



	Print_All_Data();

	printf("Serch Result=0x%.8X\n", p = Search_Data(3));

	if(p) printf("ID=%d, NAME=%s\n", p->id, p->name);

	printf("Serch Result=0x%.8X\n", p = Search_Data(12));

	if(p) printf("ID=%d, NAME=%s\n", p->id, p->name);

	printf("Serch Result=0x%.8X\n", p = Search_Data(25));

	if(p) printf("ID=%d, NAME=%s\n", p->id, p->name);

}



#endif



/***********************************************************/

// [2-2.8] Insert, Search, Delete

/***********************************************************/



#if 0



void main(void)

{

	int i;

	int r;



	Init_Hash_Table();



	for(i=0; i<15; i++)

	{

		printf("[Loop: %d] Inserted Position=%d, ID=%d\n", i, r = Insert_Data(&test[i]), test[i].id);

	}



	Print_All_Data();

	printf("[3] Delete Result=%d\n", r = Delete_Data(3));

	printf("[12] Delete Result=%d\n", r = Delete_Data(12));

	printf("[25] Delete Result=%d\n", r = Delete_Data(25));

	printf("[3] Delete Result=%d\n", r = Delete_Data(3));

	printf("[12] Delete Result=%d\n", r = Delete_Data(12));

	Print_All_Data();



	printf("Inserted Position=%d, ID=%d\n", r = Insert_Data(&test[13]), test[13].id);

	printf("Inserted Position=%d, ID=%d\n", r = Insert_Data(&test[5]), test[5].id);

	Print_All_Data();

}



#endif



#endif



/***********************************************************/

// [2-2.9] Hash Table => Chainning 방법의 구현

/***********************************************************/



#if 0



/***********************************************************/

// [2-2.9] Hash Table을 위한 기본 함수들

/***********************************************************/



#if 0



#include <stdio.h>

#include <string.h>

#include <conio.h>

#include <malloc.h>



typedef struct _score 

{

	int id;

	int jumsu;

	char name[10];

	struct _score * next;

}SCORE;



#define MAX_ST		20

#define HASH_KEY	5



SCORE Hash_table[HASH_KEY];







int Create_Data(SCORE * p);

int Get_Hash_Key(int id);

void Init_Hash_Table(void);

void Print_All_Data(void);

int Insert_Data(SCORE * d);

SCORE * Search_Data(int id);

int Delete_Data(int id);



SCORE test[MAX_ST+2] = {{10, 50, "kim"}, {2, 80, "lew"}, {8, 50, "lew"}, {4, 45, "lee"}, {1, 90, "song"},\

                               {3, 45, "kim"}, {5, 50, "song"}, {9, 100, "lee"}, {7, 75, "moon"}, {6, 90, "park"}, \

                               {15, 90, "ki"}, {11, 20, "kong"}, {14, 40, "shin"}, {12, 50, "son"}, {17, 48, "lee"}, \

                               {20, 100, "min"}, {19, 80, "you"}, {13, 45, "song"}, {16, 54, "no"}, {18, 100, "yang"}, \

							   {21, 58, "seo"}, {23, 88, "oh"}}; 



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



	return 1;

}



int Get_Hash_Key(int id)

{

	return id % HASH_KEY;

}



void Init_Hash_Table(void)

{

	int i;



	for(i=0; i<MAX_ST; i++)

	{

		Hash_table[i].next = (SCORE *)0;

	}

}



void Print_All_Data(void)

{

	int i;

	SCORE * p;



	for(i=0; i<MAX_ST; i++)

	{

		p = Hash_table[i].next;



		for(;;)

		{

			if(p == (SCORE *)0) break;

			printf("[%d] address:0x%.8X, ID: %d, NAME: %s, next: 0x%.8X\n", i, p, p->id, p->name, p->next);

			p = p->next;

		}

	}

}



#endif



/***********************************************************/

// [2-2.10] Insert

/***********************************************************/



#if 0



int Insert_Data(SCORE * d)

{

	SCORE * p;

	SCORE * q;



	p = &Hash_table[Get_Hash_Key(d->id)];

	q = calloc(1, sizeof(SCORE));

	if(q == (void *)0) return -1;

	*q = *d;



	for(;;)

	{

		if(p->next == (SCORE *)0) break;

		p = p->next;

	}



	p->next = q;

	q->next = (SCORE *)0;

	return 1;

}



#endif



#if 0



void main(void)

{

	int i;

	int r;



	Init_Hash_Table();



	for(i=0; i<MAX_ST; i++)

	{

		printf("[Loop: %d] Insert Result=%d, ID=%d\n", i, r = Insert_Data(&test[i]), test[i].id);

		Print_All_Data();

	}

}



#endif



/***********************************************************/

// [2-2.11] Delete

/***********************************************************/



#if 0



int Delete_Data(int id)

{

	SCORE * p;

	SCORE * prev;



	prev = &Hash_table[Get_Hash_Key(id)];

	p = prev->next;



	for(;;)

	{

		if(p->id == id)

		{

			prev->next = p->next;

			free(p);

			return 1;

		}



		if(p->next == (SCORE *)0) return -1;



		prev = p;

		p = p->next;

	}

}



#endif



#if 0



void main(void)

{

	int i;

	int r;



	Init_Hash_Table();



	for(i=0; i<MAX_ST; i++) printf("[Loop: %d] Insert Result=%d, ID=%d\n", i, r = Insert_Data(&test[i]), test[i].id);

	Print_All_Data();



	printf("[1] Delete Result=%d\n", r = Delete_Data(1));

	printf("[11] Delete Result=%d\n", r = Delete_Data(11));

	printf("[16] Delete Result=%d\n", r = Delete_Data(16));

	printf("[9] Delete Result=%d\n", r = Delete_Data(9));

	printf("[10] Delete Result=%d\n", r = Delete_Data(10));

	Print_All_Data();



	printf("Inserted Position=%d, ID=%d\n", r = Insert_Data(&test[1]), test[1].id);

	printf("Inserted Position=%d, ID=%d\n", r = Insert_Data(&test[11]), test[11].id);

	Print_All_Data();

}



#endif



/***********************************************************/

// [2-2.12] Search

/***********************************************************/



#if 0



SCORE * Search_Data(int id)

{

	SCORE * p;



	p = Hash_table[Get_Hash_Key(id)].next;

	if(p==(SCORE *)0) return (SCORE *)0;

	for(;;)

	{

		if(p->id == id) return p;

		if(p->next == (SCORE *)0) return (SCORE *)0;

		p = p->next;

	}

}



#endif



#if 0



void main(void)

{

	int i;

	int r;

	SCORE * p;



	Init_Hash_Table();



	for(i=0; i<MAX_ST; i++) printf("[Loop: %d] Insert Result=%d, ID=%d\n", i, r = Insert_Data(&test[i]), test[i].id);

	Print_All_Data();



	printf("Serch Result=0x%.8X\n", p = Search_Data(3));

	if(p) printf("[%d] address:0x%.8X, ID: %d, NAME: %s, next: 0x%.8X\n", i, p, p->id, p->name, p->next);

	printf("Serch Result=0x%.8X\n", p = Search_Data(12));

	if(p) printf("[%d] address:0x%.8X, ID: %d, NAME: %s, next: 0x%.8X\n", i, p, p->id, p->name, p->next);

	printf("Serch Result=0x%.8X\n", p = Search_Data(25));

	if(p) printf("[%d] address:0x%.8X, ID: %d, NAME: %s, next: 0x%.8X\n", i, p, p->id, p->name, p->next);

}



#endif



#endif



/***********************************************************/
// [2-3] Tree
/***********************************************************/

/***********************************************************/
// [2-3-1] Heap 
/***********************************************************/

#if 0

/***********************************************************/
// [2-3-1.1] Heap 자료
/***********************************************************/

#if 01

#include <stdio.h>

#define NUM_DATA	(8)
#define MAX_DATA	(NUM_DATA)
#define MAX_HEAP	(MAX_DATA+1)
#define LAST_NODE	(MAX_DATA)

int heap[MAX_HEAP];
int lastnode = 0;

int exam[NUM_DATA+1] = {0,4,8,2,7,1,3,6,5}; // 0번 index 공간 무시

#define PRINT_TREE {int j;printf("( ");	for(j = 1;j <= LAST_NODE; j++){printf("%3d ",heap[j]);}printf(")\n");}

// 이제부터 설계되는 모든 함수는 이 부분에 선언을 추가한다
int Heap_Push_Minheap(int *heap, int size, int *lastnode, int d);
int Heap_Pop_Minheap(int *heap, int *lastnode, int *d);
int Heap_Push_Maxheap(int *heap, int size, int *lastnode, int d);
int Heap_Pop_Maxheap(int *heap, int *lastnode, int *d);
void Heap_Sort(int *data,int cnt,int order);
#endif

/***********************************************************/
// [2-3-1.2] Heap Push (Min Heap)
/***********************************************************/

/*
완전 이진 트리
인덱스를 1부터 시작하면,
어떤 자식이든 2로 나누면 부모를 찾는다.
*/

void swap(int *a, int *b)
{
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

#if 01
/*
int Heap_Push_Minheap(int *heap, int size, int *lastnode, int d)
{
	int n, p, temp;
	if(*lastnode == size) return 0;
	heap[++(*lastnode)] = d;
	n = *lastnode; 
	p = n / 2;

	while(p > 0)
	{
		if(heap[n] < heap[p])
		{
			temp = heap[n];
			heap[n] = heap[p];
			heap[p] = temp;
			n = p; 
			p = n / 2;
		}
		else break;
	}

	return 1;
}
*/

int Heap_Push_Minheap(int *heap, int size, int *lastnode, int d)
{
	int n_idx, p_idx;
	if(*lastnode == size) return 0;		//fail
	heap[++(*lastnode)] = d;			//끝에 노드를 추가(완전이진트리)

	n_idx = *lastnode;					//현재 노드의 인덱스
	p_idx = n_idx / 2;						//그 노드 부모의 인덱스

	while(p_idx > 0)					//부모노드가 존재하면,
	{
		if(heap[n_idx] < heap[p_idx])	//부모노드보다 작다면,
		{
			swap(&heap[n_idx], &heap[p_idx]);
			n_idx = p_idx;
			p_idx = n_idx / 2;
		}
		else break;
	}
	return 1;	//success
}
#endif

#if 0

int main(void)
{
	printf("Heap Push Test (Minheap)\n");

	for(int i = 1; i <= NUM_DATA; i++)
	{
		printf("[%d] Heap_Push_Minheap(%d) => %d",
			i, exam[i], Heap_Push_Minheap(heap, MAX_DATA, &lastnode, exam[i]));
		
		PRINT_TREE;
	}
	printf("[9] Heap_Push_Minheap(9) => %d\n", Heap_Push_Minheap(heap, MAX_DATA, &lastnode, 9));
	return 0;
}
#endif

/***********************************************************/
// [2-3-1.3] Heap Pop (Min Heap)
/***********************************************************/

#if 01
int Heap_Pop_Minheap(int *heap, int *lastnode, int *d)
{
	int n,c,lc,rc,temp;
	if(*lastnode == 0) return 0;

	*d = heap[1];
	heap[1] = heap[(*lastnode)--];	//last에 위치한 노드를 root로 옮긴다

	n  = 1; 
	lc = 2; 
	rc = 3;

	while(lc <= *lastnode)
	{
		if(*lastnode == lc) c = lc;	//오른쪽 자식이 없을 때,
		else c = (heap[lc] < heap[rc]) ? (lc) : (rc);

		if(heap[c] < heap[n])
		{
			swap(&heap[c], &heap[n]);
			n = c; 
			lc = n * 2; 
			rc = lc + 1;
		}
		else break;
	}
	return 1;
}
#endif

#if 0

int main(void)
{
	int i, ret;
	printf("Heap Pop Test (Minheap)\n");

	for(i = 1; i <= NUM_DATA; i++)
	{
		printf("[%d] Heap_Push_Minheap(%d) => %d",
			i, exam[i], Heap_Push_Minheap(heap,MAX_DATA,&lastnode,exam[i]));
		PRINT_TREE;
	}

	for(i =1; i <= NUM_DATA; i++)
	{
		printf("[%d] Heap_Pop_Minheap() => %d - ", i, Heap_Pop_Minheap(heap, &lastnode, &ret));
		printf("%d\n",ret);
	}
	printf("[9] Heap_Pop_Minheap() => %d\n", Heap_Pop_Minheap(heap, &lastnode, &ret));
	return 0;
}
#endif





/***********************************************************/

// [2-3-1.4] Heap Push (Max Heap)

/***********************************************************/

#if 01
int Heap_Push_Maxheap(int *heap, int size, int *lastnode, int d)
{
	int n,p,temp;

	if(*lastnode == size) return 0;
	heap[++(*lastnode)] = d;
	n = *lastnode; 
	p = n/2;

	while(p>0)
	{
		if(heap[n] > heap[p])
		{
			temp = heap[n];
			heap[n] = heap[p];
			heap[p] = temp;
			n = p; 
			p = n / 2;
		}
		else break;
	}
	return 1;
}
#endif

#if 0

int main(void)

{

	int i;
	printf("Heap Push Test (Maxheap)\n");

	for(i=1;i<=NUM_DATA;i++)
	{
		printf("[%d] Heap_Push_Maxheap(%d) => %d",
			i,exam[i],Heap_Push_Maxheap(heap,MAX_DATA,&lastnode,exam[i]));
		PRINT_TREE;
	}
	printf("[9] Heap_Push_Maxheap(9) => %d\n",Heap_Push_Maxheap(heap,MAX_DATA,&lastnode,9));
	return 0;
}

#endif



/***********************************************************/
// [2-3-1.5] Heap Pop (Max Heap)
/***********************************************************/

#if 01

int Heap_Pop_Maxheap(int *heap, int *lastnode, int *d)
{
	int n,c,lc,rc,temp;

	if(*lastnode == 0) return 0;

	*d = heap[1];
	heap[1] = heap[(*lastnode)--];

	n = 1; lc = 2; rc = 3;

	while(lc<=*lastnode)
	{
		if(*lastnode == lc) c = lc;
		else c = (heap[lc]>heap[rc])?(lc):(rc);

		if(heap[c]>heap[n])
		{
			temp = heap[c];
			heap[c] = heap[n];
			heap[n] = temp;
			n = c; lc = n*2; rc = lc+1;
		}
		else break;
	}
	return 1;
}
#endif

#if 01

int main(void)

{
	int i,ret;
	printf("Heap Pop Test (Maxheap)\n");

	for(i=1;i<=NUM_DATA;i++)
	{
		printf("[%d] Heap_Push_Maxheap(%d) => %d",
			i,exam[i],Heap_Push_Maxheap(heap,MAX_DATA,&lastnode,exam[i]));
		PRINT_TREE;
	}

	for(i=1;i<=NUM_DATA;i++)
	{
		printf("[%d] Heap_Pop_Maxheap() => %d - ",i,Heap_Pop_Maxheap(heap,&lastnode,&ret));
		printf("%d\n",ret);
	}
	printf("[9] Heap_Pop_Maxheap() => %d\n",Heap_Pop_Maxheap(heap,&lastnode,&ret));
	return 0;
}
#endif



/***********************************************************/
// [2-3-1.6] Heap Sort 
/***********************************************************/

#if 0

typedef int (*HEAP_PUSH)(int*,int,int*,int);

typedef int (*HEAP_POP)(int*,int*,int*);



void Heap_Sort(int *data,int cnt,int order)

{

	int i,ret,lastnode=0;

	HEAP_PUSH Heap_Push[2] = {Heap_Push_Maxheap,Heap_Push_Minheap};

	HEAP_POP Heap_Pop[2] = {Heap_Pop_Maxheap,Heap_Pop_Minheap};



	for(i=0;i<cnt;i++)

	{

		Heap_Push[order](data-1,MAX_DATA,&lastnode,data[i]);

	}



	for(i=cnt-1;i>=0;i--)

	{

		Heap_Pop[order](data-1,&lastnode,&ret);

		data[i] = ret;

	}

}



#endif



#if 0

int main(void)

{

	int i,data[NUM_DATA+1];

	printf("Heap Sort Test\n\n");

	

	printf("Original data : ");

	for(i=0;i<NUM_DATA;i++)

	{

		data[i] = exam[i+1];

		printf("%d ",data[i]);

	}

	printf("\n");



	Heap_Sort(data,NUM_DATA,0);

	printf("Sorted data : ");

	for(i=0;i<NUM_DATA;i++)

	{

		printf("%d ",data[i]);

	}

	printf("\n");



	return 0;

}



#endif





#endif





/***********************************************************/

// [2-3-2.1~4] Segment Tree

/***********************************************************/



#if 01



/***********************************************************/

// [2-3-2.1] Segment Tree 자료 확인

/***********************************************************/

#if 01

#include <stdio.h>



#define NUM_DATA	(5)

#define MAX_DATA	(NUM_DATA)

#define MAX_TREE	(MAX_DATA*2)

#define LAST_NODE	(MAX_DATA*2-1)



int tree[MAX_TREE];



int exam[NUM_DATA+1] = {0,1,2,3,4,5}; // 0번 index 공간 무시



#define PRINT_TREE {int j;printf("( ");	for(j=1;j<=LAST_NODE;j++){printf("%3d ",tree[j]);}printf(")\n");}





// 이제부터 설계되는 모든 함수는 이 부분에 선언을 추가한다

void Update_New_Data(int node,int s,int e,int idx,int data);

void Update_Add(int node,int s,int e,int us,int ue,int add);

int Query(int node,int s,int e,int qs,int qe);

#endif

/***********************************************************/

// [2-3-2.2] 새로운 데이터의 추가 및 데이터 업데이트 함수

/***********************************************************/

#if 01

void Update_New_Data(int node,int s,int e,int idx,int data)

{

	int m;

	if(s==e) 

	{

		tree[node] = data;

		return;

	}



	m=(s+e)/2;

	if(idx<=m) Update_New_Data(node*2,s,m,idx,data);

	else Update_New_Data(node*2+1,m+1,e,idx,data);



	tree[node] = tree[node*2] + tree[node*2+1];

}

#endif



#if 01

void main(void)

{

	int i;



	printf("Update_New_Data() Test\n");



	for(i=1;i<=NUM_DATA;i++)

	{

		Update_New_Data(1,1,NUM_DATA,i,exam[i]);

		printf("[%d] data : %d ",i,exam[i]);

		PRINT_TREE;

	}

}

#endif





/***********************************************************/

// [2-3-2.3] 구간 정보 요청

/***********************************************************/

#if 01

int Query(int node,int s,int e,int qs,int qe)

{

	int m,l,r;



	if(qs<=s && e<=qe) return tree[node];

	else if(qs>e || s>qe) return 0;



	m = (s+e)/2;

	l = Query(node*2,s,m,qs,qe);

	r = Query(node*2+1,m+1,e,qs,qe);



	return l+r;

}

#endif



#if 0

void main(void)

{

	int i;



	printf("Query() Test\n");



	for(i=1;i<=NUM_DATA;i++)

	{

		Update_New_Data(1,1,NUM_DATA,i,exam[i]);

	}



	printf("Query[1~5] : result = %d\n",Query(1,1,NUM_DATA,1,5));

	printf("Query[1~3] : result = %d\n",Query(1,1,NUM_DATA,1,3));

	printf("Query[4~5] : result = %d\n",Query(1,1,NUM_DATA,4,5));

	printf("Query[2~4] : result = %d\n",Query(1,1,NUM_DATA,2,4));

	printf("Query[3~5] : result = %d\n",Query(1,1,NUM_DATA,3,5));

}

#endif





/*************************************************************/

// [2-3-2.4] 특정 구간 데이터 변경 함수 - 데이터 증가/감소

/*************************************************************/

#if 0

void Update_Add(int node,int s,int e,int us,int ue,int add)

{

	int m;

	if(s==e) 

	{

		if(us<=s && s<=ue) tree[node] += add;

		return;

	}

	else if(us>e || s>ue) return;



	m=(s+e)/2;

	Update_Add(node*2,s,m,us,ue,add);

	Update_Add(node*2+1,m+1,e,us,ue,add);



	tree[node] = tree[node*2] + tree[node*2+1];

}

#endif



#if 0

void main(void)

{

	int i;



	printf("Update_Add() Test\n");



	for(i=1;i<=NUM_DATA;i++)

	{

		Update_New_Data(1,1,NUM_DATA,i,exam[i]);

	}



	printf("[Before Range Update] ");

	PRINT_TREE;

	printf("Query[1~5] : result = %d\n",Query(1,1,NUM_DATA,1,5));

	printf("Query[1~3] : result = %d\n",Query(1,1,NUM_DATA,1,3));

	printf("Query[4~5] : result = %d\n",Query(1,1,NUM_DATA,4,5));

	printf("Query[2~4] : result = %d\n",Query(1,1,NUM_DATA,2,4));

	printf("Query[3~5] : result = %d\n",Query(1,1,NUM_DATA,3,5));



	Update_Add(1,1,NUM_DATA,2,4,2);



	printf("\n[After Range Update] ");

	PRINT_TREE;

	printf("Query[1~5] : result = %d\n",Query(1,1,NUM_DATA,1,5));

	printf("Query[1~3] : result = %d\n",Query(1,1,NUM_DATA,1,3));

	printf("Query[4~5] : result = %d\n",Query(1,1,NUM_DATA,4,5));

	printf("Query[2~4] : result = %d\n",Query(1,1,NUM_DATA,2,4));

	printf("Query[3~5] : result = %d\n",Query(1,1,NUM_DATA,3,5));

}

#endif

#endif





/***********************************************************/

// [2-3-2.5~9] Segment Tree with Lazy Propagation

/***********************************************************/



#if 01



/***********************************************************/

// [2-3-2.5] Segment Tree with Lazy Propagation 자료 확인

/***********************************************************/

#if 01

#include <stdio.h>



#define NUM_DATA	(5)

#define MAX_DATA	(NUM_DATA)

#define MAX_TREE	(MAX_DATA*2)

#define LAST_NODE	(MAX_DATA*2-1)



int tree[MAX_TREE];

int lazy[MAX_TREE];



int exam[NUM_DATA+1] = {0,1,2,3,4,5}; // 0번 index 공간 무시



#define PRINT_TREE {int j;printf("( ");	for(j=1;j<=LAST_NODE;j++){printf("%3d ",tree[j]);}printf(")\n");}





// 이제부터 설계되는 모든 함수는 이 부분에 선언을 추가한다

void Propagate(int n,int s,int e);

void Update_New_Data_Lazy(int node,int s,int e,int idx,int data);

void Update_Add_Lazy(int node,int s,int e,int us,int ue,int add);

int Query_Lazy(int node,int s,int e,int qs,int qe);

#endif





/***********************************************************/

// [2-3-2.6] Propagate 함수

/***********************************************************/

#if 01



void Propagate(int node,int s,int e)

{

	if(lazy[node]!=0)

	{

		if(s!=e)

		{

			lazy[node*2] += lazy[node];

			if(node*2+1 <= LAST_NODE) lazy[node*2+1] += lazy[node];

		}

		tree[node] += (e-s+1)*lazy[node];

		lazy[node] = 0;

	}

}

#endif



/***********************************************************/

// [2-3-2.7] 새로운 data 추가/Update

/***********************************************************/



#if 01

void Update_New_Data_Lazy(int node,int s,int e,int idx,int data)

{

	int m;



	Propagate(node,s,e);



	if(s==e) 

	{

		tree[node] = data;

		return;

	}



	m=(s+e)/2;

	if(idx<=m) Update_New_Data_Lazy(node*2,s,m,idx,data);

	else Update_New_Data_Lazy(node*2+1,m+1,e,idx,data);



	tree[node] = tree[node*2] + tree[node*2+1];

}

#endif



#if 01

void main(void)

{

	int i;



	printf("Update_New_Data() Test\n");



	for(i=1;i<=NUM_DATA;i++)

	{

		Update_New_Data_Lazy(1,1,NUM_DATA,i,exam[i]);

		printf("[%d] data : %d ",i,exam[i]);

		PRINT_TREE;

	}

}

#endif





/***********************************************************/

// [2-3-2.8] 구간 정보 요청

/***********************************************************/

#if 01

int Query_Lazy(int node,int s,int e,int qs,int qe)

{

	int m,l,r;

	

	Propagate(node,s,e);



	if(qs<=s && e<=qe) return tree[node];

	else if(qs>e || s>qe) return 0;



	m = (s+e)/2;

	l = Query_Lazy(node*2,s,m,qs,qe);

	r = Query_Lazy(node*2+1,m+1,e,qs,qe);



	return l+r;

}

#endif



#if 01

void main(void)

{

	int i;



	printf("Query() Test\n");



	for(i=1;i<=NUM_DATA;i++)

	{

		Update_New_Data_Lazy(1,1,NUM_DATA,i,exam[i]);

	}



	printf("Query[1~5] : result = %d\n",Query_Lazy(1,1,NUM_DATA,1,5));

	printf("Query[1~3] : result = %d\n",Query_Lazy(1,1,NUM_DATA,1,3));

	printf("Query[4~5] : result = %d\n",Query_Lazy(1,1,NUM_DATA,4,5));

	printf("Query[2~4] : result = %d\n",Query_Lazy(1,1,NUM_DATA,2,4));

	printf("Query[3~5] : result = %d\n",Query_Lazy(1,1,NUM_DATA,3,5));

}

#endif





/*************************************************************/

// [2-3-2.9] 특정 구간 데이터 변경 함수 - 데이터 증가/감소

/*************************************************************/

#if 01

void Update_Add_Lazy(int node,int s,int e,int us,int ue,int add)

{

	int m;



	Propagate(node,s,e);

	

	if(us<=s && e<=ue) 

	{

		lazy[node] += add;

		Propagate(node,s,e);

		return;

	}

	else if(us>e || s>ue) return;



	m=(s+e)/2;

	Update_Add_Lazy(node*2,s,m,us,ue,add);

	Update_Add_Lazy(node*2+1,m+1,e,us,ue,add);



	tree[node] = tree[node*2] + tree[node*2+1];

}

#endif



#if 01

void main(void)

{

	int i;



	printf("Update_Add() Test\n");



	for(i=1;i<=NUM_DATA;i++)

	{

		Update_New_Data_Lazy(1,1,NUM_DATA,i,exam[i]);

	}



	printf("[Before Range Update] ");

	PRINT_TREE;

	printf("Query[1~5] : result = %d\n",Query_Lazy(1,1,NUM_DATA,1,5));

	printf("Query[1~3] : result = %d\n",Query_Lazy(1,1,NUM_DATA,1,3));

	printf("Query[4~5] : result = %d\n",Query_Lazy(1,1,NUM_DATA,4,5));

	printf("Query[2~4] : result = %d\n",Query_Lazy(1,1,NUM_DATA,2,4));

	printf("Query[3~5] : result = %d\n",Query_Lazy(1,1,NUM_DATA,3,5));



	Update_Add_Lazy(1,1,NUM_DATA,2,4,2);



	printf("\n[After Range Update] ");

	PRINT_TREE;

	printf("Query[1~5] : result = %d\n",Query_Lazy(1,1,NUM_DATA,1,5));

	printf("Query[1~3] : result = %d\n",Query_Lazy(1,1,NUM_DATA,1,3));

	printf("Query[4~5] : result = %d\n",Query_Lazy(1,1,NUM_DATA,4,5));

	printf("Query[2~4] : result = %d\n",Query_Lazy(1,1,NUM_DATA,2,4));

	printf("Query[3~5] : result = %d\n",Query_Lazy(1,1,NUM_DATA,3,5));

}

#endif

#endif





/***********************************************************/

// [2-3-3] Fenwick Tree

/***********************************************************/



#if 0



/***********************************************************/

// [2-3-3.1] Fenwick Tree 자료 확인

/***********************************************************/

#if 0

#include <stdio.h>



#define NUM_DATA	(16)

#define MAX_DATA	(NUM_DATA)

#define MAX_TREE	(MAX_DATA+1)

#define LAST_NODE	(MAX_DATA)



#define LSB(X) ((X)&(-(X)))



int fenwick_tree[MAX_TREE];

int exam[NUM_DATA+1] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16}; // 0번 index 공간 무시



#define PRINT_TREE {int j;printf("( ");	for(j=1;j<=LAST_NODE;j++){printf("%3d ",fenwick_tree[j]);}printf(")\n");}





// 이제부터 설계되는 모든 함수는 이 부분에 선언을 추가한다

void Init_Fenwick_Tree(void);

int Get_Psum(int idx);

void Update_Add(int idx,int val);

#endif



/***********************************************************/

// [2-3-3.2] Fenwick Tree 초기화

/***********************************************************/

#if 0

void Init_Fenwick_Tree(void)

{

	int i;



	for(i=1;i<=LAST_NODE;i++)

	{

		if(i+LSB(i)<=LAST_NODE) fenwick_tree[i+LSB(i)] += fenwick_tree[i]; 

	}

}

#endif



#if 0

int main(void)

{

	int i;

	for(i=1;i<=MAX_DATA;i++)

	{

		fenwick_tree[i] = exam[i];

	}



	printf("Fenwick Tree Initialization Test\n\n");



	Init_Fenwick_Tree();



	PRINT_TREE;



	return 0;

}

#endif



/***********************************************************/

// [2-3-3.3] Fenwick Tree Prefix Sum 얻기

/***********************************************************/

#if 0

int Get_Psum(int idx)

{

	int ret=0;

	while(idx>0)

	{

		ret += fenwick_tree[idx];

		idx -= LSB(idx);

		//idx &= (idx-1);

	}

	return ret;

}

#endif



#if 0

int main(void)

{

	int i;

	for(i=1;i<=MAX_DATA;i++)

	{

		fenwick_tree[i] = exam[i];

	}



	printf("Fenwick Tree prefix sum Test\n");

	Init_Fenwick_Tree();



	PRINT_TREE;

	

	printf("\n[Prefix Sum]\n");

	printf("Prefix sum[3] = %d\n",Get_Psum(3));

	printf("Prefix sum[5] = %d\n",Get_Psum(5));

	printf("Prefix sum[8] = %d\n",Get_Psum(8));

	printf("Prefix sum[10] = %d\n",Get_Psum(10));

	printf("Prefix sum[13] = %d\n",Get_Psum(13));



	printf("\n[Interval Sum]\n");

	printf("Sum [3~5] = %d\n",Get_Psum(5)-Get_Psum(3-1));

	printf("Sum [2~7] = %d\n",Get_Psum(7)-Get_Psum(2-1));

	printf("Sum [6~13] = %d\n",Get_Psum(13)-Get_Psum(6-1));



	return 0;

}

#endif



/***********************************************************/

// [2-3-3.4] 구간 값 변경

/***********************************************************/

#if 0

void Update_Add(int idx,int val)

{

	while(idx<=LAST_NODE)

	{

		fenwick_tree[idx] += val;

		idx += LSB(idx);

	}

}

#endif



#if 0

int main(void)

{

	int i;

	for(i=1;i<=MAX_DATA;i++)

	{

		fenwick_tree[i] = exam[i];

	}



	printf("Fenwick Tree Uadate Test\n");

	Init_Fenwick_Tree();



	PRINT_TREE;

	

	printf("[Prefix Sum]\n");

	printf("Prefix sum[3] = %d\n",Get_Psum(3));

	printf("Prefix sum[5] = %d\n",Get_Psum(5));

	printf("Prefix sum[8] = %d\n",Get_Psum(8));



	Update_Add(4,2);



	printf("\n[Prefix Sum after Update]\n");

	printf("Prefix sum[3] = %d\n",Get_Psum(3));

	printf("Prefix sum[5] = %d\n",Get_Psum(5));

	printf("Prefix sum[8] = %d\n",Get_Psum(8));



	return 0;

}

#endif

#endif



/***********************************************************/

// [2-3-4] Binary Search Tree

/***********************************************************/



#if 0



/***********************************************************/

// [2-3-4.1] 이진 Tree의 인쇄

/***********************************************************/



#if 0



#include <stdio.h>



struct node

{

	char *name;

	struct node *left;

	struct node *right;

};



void Print_All_Node1(struct node *p);

void Print_All_Node2(struct node *p);

void Print_All_Node3(struct node *p);



void main(void)

{

	struct node root, node1, node2, node3, node4;



	root.left = &node1;

	root.right = &node2;

	root.name = "root";

	node1.left = &node3;

	node1.right = &node4;

	node1.name = "node1";

	node2.left = NULL;

	node2.right = NULL;

	node2.name = "node2";

	node3.left = NULL;

	node3.right = NULL;

	node3.name = "node3";

	node4.left = NULL;

	node4.right = NULL;

	node4.name = "node4";



	printf("In-order Traverse===============\n");

	Print_All_Node1(&root);

	printf("Pre-order Traverse===============\n");

	Print_All_Node2(&root);

	printf("Post-order Traverse===============\n");

	Print_All_Node3(&root);

}



void Print_All_Node1(struct node *p)

{

	if(p->left) Print_All_Node1(p->left);

	printf("Name = %s\n", p->name);

	if(p->right) Print_All_Node1(p->right);

}



void Print_All_Node2(struct node *p)

{

	printf("Name = %s\n", p->name);

	if(p->left) Print_All_Node2(p->left);

	if(p->right) Print_All_Node2(p->right);

}



void Print_All_Node3(struct node *p)

{

	if(p->left) Print_All_Node3(p->left);

	if(p->right) Print_All_Node3(p->right);

	printf("Name = %s\n", p->name);

}



#endif



/***********************************************************/

// [2-3-4.2] 이진 트리를 위한 기본 함수들

/***********************************************************/



#if 0



#include <stdio.h>

#include <string.h>

#include <conio.h>

#include <malloc.h>



typedef struct _score

{

	int id;

	int jumsu;

	char name[10];

	struct _score  * left;

	struct _score  * right;

	struct _score  * parent;

}SCORE;



SCORE *Root;



#define MAX_ST		20



// 이제부터 설계되는 모든 함수는 이 부분에 선언을 추가한다



void Print_All_Node(SCORE * p);

void Delete_All_Node(SCORE * p);

int Insert_Node(SCORE * head, SCORE * d);

SCORE * Search_Node(SCORE * head, int id);

int Delete_Node(SCORE * head, int id);

SCORE * Creat_Node(SCORE * d);

int Create_Data(SCORE * p);



SCORE test[MAX_ST] = { { 10, 50, "kim" }, { 2, 80, "lew" }, { 8, 50, "lew" }, { 4, 45, "lee" }, { 1, 90, "song" }, \

{3, 45, "kim"}, { 5, 50, "song" }, { 9, 100, "lee" }, { 7, 75, "moon" }, { 6, 90, "park" }, \

{15, 90, "ki"}, { 11, 20, "kong" }, { 14, 40, "shin" }, { 12, 50, "son" }, { 17, 48, "lee" }, \

{20, 100, "min"}, { 19, 80, "you" }, { 13, 45, "song" }, { 16, 54, "no" }, { 18, 100, "yang" } };



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

	p->left = (SCORE *)0x0;

	p->right = (SCORE *)0x0;



	return 1;

}



void Print_All_Node(SCORE * p)

{



	if (p == (SCORE *)0)

	{

		printf("No Data\n");

		return;

	}



	if (p->left) Print_All_Node(p->left);

	printf("addr=0x%.8X, ID=%d, left=0x%.8X, right=0x%.8X, parent=0x%.8X\n", p, p->id, p->left, p->right, p->parent );

	if (p->right) Print_All_Node(p->right);

}



#endif



/***********************************************************/

// [2-3-4.3] 데이터 하나를 생성하여 Linked List에 추가하는 함수 (calloc 사용)

/***********************************************************/



#if 0



SCORE * Creat_Node(SCORE * d)

{

	SCORE * p;



	p = calloc(1, sizeof(SCORE));

	if (p == (void *)0x0) return p;

	*p = *d;

	return p;

}



int Insert_Node(SCORE * head, SCORE * d)

{

	SCORE * p;



	//추가할 자료 생성(p = 추가할 노드)

	p = Creat_Node(d);



	if(!p) return -1;

	

	for (;;)

	{

		if (head == NULL)

		{

			Root = p;

			return 1;

		}



		// 중복체크, ID가 동일하면 free하고 리턴

		if (head->id == d->id)

		{

			free(p);

			return -2;

		}



		// left로 이동

		if (head->id > d->id)

		{

			if (head->left) head = head->left;



			// left 노드가 더이상 없는 leaf에 도달

			else

			{

				head->left = p;

				p->parent = head;

				return 1;

			}

		}



		// right로 이동

		else

		{

			if (head->right) head = head->right;



			// right 노드가 더이상 없는 leaf에 도달

			else

			{

				head->right = p;

				p->parent = head;

				return 1;

			}

		}	

	}

}



#endif



#if 0



void main(void)

{

	int i;

	int r;



	for (i = 0; i<MAX_ST; i++)

	{

		printf("[Loop: %d] Insert Node Result=%d, ID=%d\n", i, r = Insert_Node(Root, &test[i]), test[i].id);

		Print_All_Node(Root);

	}

}



#endif



/***********************************************************/

// [2-3-4.4] 주어진 사번의 node를 찾아서 노드의 주소를 리턴하는 함수

/***********************************************************/



#if 0



SCORE * Search_Node(SCORE * head, int id)

{

	if (head == (SCORE *)0) return (SCORE *)0;



	for (;;)

	{

		if (head == NULL) return NULL;

		

		if (head->id > id)

		{

			head=head->left;

		}



		else if (head->id<id)

		{

			head = head->right;

		}



		else return head;

	}

}



#endif



#if 0



void main(void)

{

	int i;

	int r;

	SCORE * p;



	for (i = 0; i<8; i++)

	{

		printf("[Loop: %d] Insert Node Result=%d, ID=%d\n", i, r = Insert_Node(Root, &test[i]), test[i].id);

	}



	Print_All_Node(Root);



	printf("Search Result = 0x%.8X\n", p = Search_Node(Root, 1));

	if (p) 	printf("addr=0x%.8X, ID=%d, left=0x%.8X, right=0x%.8X, parent=0x%.8X\n", p, p->id, p->left, p->right, p->parent );



	printf("Search Result = 0x%.8X\n", p = Search_Node(Root, 10));

	if (p)  printf("addr=0x%.8X, ID=%d, left=0x%.8X, right=0x%.8X, parent=0x%.8X\n", p, p->id, p->left, p->right, p->parent );



	printf("Search Result = 0x%.8X\n", p = Search_Node(Root, 9));

	if (p) 	printf("addr=0x%.8X, ID=%d, left=0x%.8X, right=0x%.8X, parent=0x%.8X\n", p, p->id, p->left, p->right, p->parent );



	printf("Search Result = 0x%.8X\n", p = Search_Node(Root, 4));

	if (p) 	printf("addr=0x%.8X, ID=%d, left=0x%.8X, right=0x%.8X, parent=0x%.8X\n", p, p->id, p->left, p->right, p->parent );



	printf("Search Result = 0x%.8X\n", p = Search_Node(Root, 7));

	if (p) 	printf("addr=0x%.8X, ID=%d, left=0x%.8X, right=0x%.8X, parent=0x%.8X\n", p, p->id, p->left, p->right, p->parent );

}





#endif



/***********************************************************/

// [2-3-4.5] 주어진 사번의 node를 찾아서 삭제하는 함수

/***********************************************************/



#if 0



void Delete_All_Node(SCORE * p)

{

	if (p->left) Delete_All_Node(p->left);

	if (p->right) Delete_All_Node(p->right);

	if (p == Root) Root  = (SCORE *)0;

	free(p);

}



#endif



#if 0



// 삭제할 대상 노드가 leaf인 경우 삭제 함수

// main 함수에서 "자식 없는 노드의 삭제" 부분만 실험



int Delete_Node(SCORE * head, int id)

{

	SCORE * r;



	r = Search_Node(head,id);



	// 탐색 실패 

	if (r == NULL) return -1;

	

	if(r != Root)

	{

		// 삭제 대상 노드가 부모의 left인지 right인지에 따라서 부모의 left나 rght에 NULL을 연결한다

		if(r == r->parent->left ) r->parent->left = NULL;

		else  r->parent->right = NULL;

	}

	

	// 삭제할 노드가 leaf 노드 상태의 Root일 경우 Root에 NULL 복사

	else

	{

		Root = NULL;

	}



	free(r);

	return 1;

}



#endif



#if 0



// 삭제할 대상 노드가 leaf 또는 자식이 하나인 경우 삭제 함수

// main 함수에서 "자식 없는 노드의 삭제" 부분과 "자식이 1인 노드의 삭제" 까지 실험



int Delete_Node(SCORE * head, int id)

{

	SCORE * r;

	SCORE * next; 



	r = Search_Node(head,id);



	// 탐색 실패 

	if (r == NULL) return -1;



	// 후계자 선정 

	// 자식이 하나일 경우 어느 측에 자식이 있는지를 찾아서 자식을 next로 설정한다

	// leaf이면 후계자는 NULL을 대입(단, 어차피 leaf이면 r-> left와 r->right는 NULL이다)

	if(r->left) next = r->left;

	else next =  r->right;



	// 후계자가 있을 경우 후계자의parent = 삭제 노드의 parent 대입

	if(next) next->parent = r->parent;



	// 삭제 대상이 Root가 아닌 경우 삭제 대상 노드의 parent와 후계자를 연결한다(leaf이면 NULL이 대입된다)

	if(r != Root)

	{

		// 삭제 대상 노드가 부모의 left인지 right인지에 따라서 부모의 left나 rght에 후계자를 연결한다

		if(r == r->parent->left ) r->parent->left = next;

		else  r->parent->right = next;

	}

	

	// 삭제할 노드가 Root일 경우 후계자를 Root에 복사(leaf이면 NULL이 대입된다)

	else

	{

		Root = next;

	}



	free(r);

	return 1;

}



#endif



#if 0



// 삭제할 대상 노드가 자식 둘 인 경우까지 포함하는 최종 삭제 함수

// main 함수에서 모든 단계를 실험 실시



int Delete_Node(SCORE * head, int id)

{

	// 후계자 저장 변수

	SCORE * next; 

	SCORE * r;



	r = Search_Node(head,id);



	// 탐색 실패 

	if (r == NULL) return -1;



	// 자식이 둘이면 후계자 탐색 및 후계자를 삭제할 노드의 데이터에 복사하고 r에 후계자 주소를 대입

	if ((r->left != NULL) && (r->right != NULL))

	{

		// 후계자 탐색을 위해 사용할 임시 변수

		SCORE * temp = r;

		// 삭제할 노드 주소 백업을 위한 변수

		SCORE * del = r;

		// 노드 복사를 위한 임시 변수

		SCORE back = *r;



		if (temp->right->left)

		{

			temp = temp->right;



			while(temp->left->left)

			{

				temp = temp->left; 

			}



			r = temp->left;

		}



		else

		{

			r = temp->right;

		}



		// 삭제대상에 후계자 데이터 복사 단, 데이터를 제외한 링크 정보는 원래 삭제할 노드값 사용해야 함

		*del = *r;

		del->left = back.left;

		del->right = back.right;

		del->parent = back.parent;

	}

	

	// 자식이 둘이면 r에 삭제할 대상 주소가 저장되어 있고 하나거나 leaf이면 처음부터 삭제 대상이 들어 있음

	// 따라서 아래 코드는 자식 수와 무관하게 동일함



	// 후계자 선정 

	// 자식이 하나일 경우 어느 측에 자식이 있는지를 찾아서 자식을 next로 설정한다

	// leaf이면 후계자는 NULL을 대입(단, 어차피 leaf이면 r-> left와 r->right는 NULL이다)

	if(r->left) next = r->left;

	else next =  r->right;



	// 후계자가 있을 경우 후계자의parent = 삭제 노드의 parent 대입

	if(next) next->parent = r->parent;



	// 삭제 대상이 Root가 아닌 경우 삭제 대상 노드의 parent와 후계자를 연결한다(leaf이면 NULL이 대입된다)

	if(r != Root)

	{

		// 삭제 대상 노드가 부모의 left인지 right인지에 따라서 부모의 left나 rght에 후계자를 연결한다

		if(r == r->parent->left ) r->parent->left = next;

		else  r->parent->right = next;

	}

	

	// 삭제할 노드가 Root일 경우 후계자를 Root에 복사(leaf이면 NULL이 대입된다)

	else

	{

		Root = next;

	}



	free(r);

	return 1;

}



#endif



#if 0



void main(void)

{

	int i;

	int r;



	/* 자식 없는 노드의 삭제 */



#if 0



	// 1. Root Only 삭제	



	printf("[Loop: %d] Insert Node Result=%d, ID=%d\n", 0, r = Insert_Node(Root, &test[0]), test[0].id);

	Print_All_Node(Root);

	printf("Delete Node #10 Result = %d, Root = %d\n", Delete_Node(Root, 10), Root->id);

	printf("Root=%#.8x\n", Root);

	Print_All_Node(Root);



#endif



#if 0



	// 2. Left Leaf 노드 삭제 



	for (i = 0; i<7; i++) printf("[Loop: %d] Insert Node Result=%d, ID=%d\n", i, r = Insert_Node(Root, &test[i]), test[i].id);

	Print_All_Node(Root);

	printf("Delete Node #3 Result = %d, Root = %d\n", Delete_Node(Root, 3), Root->id);

	printf("Delete Node #1 Result = %d, Root = %d\n", Delete_Node(Root, 1), Root->id);

	Print_All_Node(Root);

	Delete_All_Node(Root);



#endif



#if 0



	// 3. Right Leaf 노드 삭제 



	for (i = 0; i<20; i++) printf("[Loop: %d] Insert Node Result=%d, ID=%d\n", i, r = Insert_Node(Root, &test[i]), test[i].id);

	Print_All_Node(Root);

	printf("Delete Node #13 Result = %d, Root = %d\n", Delete_Node(Root, 13), Root->id);

	printf("Delete Node #9 Result = %d, Root = %d\n", Delete_Node(Root, 9), Root->id);

	Print_All_Node(Root);

	Delete_All_Node(Root);



#endif



	/* 자식이 1인 노드의 삭제 */



#if 0



	// 1. Left만 있는 Root 삭제 



	for (i = 0; i<10; i++) printf("[Loop: %d] Insert Node Result=%d, ID=%d\n", i, r = Insert_Node(Root, &test[i]), test[i].id);

	Print_All_Node(Root);

	printf("Delete Node #10 Result = %d, Root = %d\n", Delete_Node(Root, 10), Root->id);

	Print_All_Node(Root);

	Delete_All_Node(Root);



#endif



#if 0



	// 2. Right만 있는 Root 삭제 



	printf("[Loop: %d] Insert Node Result=%d, ID=%d\n", 0, r = Insert_Node(Root, &test[0]), test[0].id);

	for (i = 10; i<20; i++) printf("[Loop: %d] Insert Node Result=%d, ID=%d\n", i, r = Insert_Node(Root, &test[i]), test[i].id);

	Print_All_Node(Root);

	printf("Delete Node #10 Result = %d, Root = %d\n", Delete_Node(Root, 10), Root->id);

	printf("Delete Node #8 Result = %d, Root = %d\n", Delete_Node(Root, 8), Root->id);

	Print_All_Node(Root);

	Delete_All_Node(Root);



#endif



#if 0



	// 3. Left만 있는 노드 삭제 



	for (i = 0; i<20; i++) printf("[Loop: %d] Insert Node Result=%d, ID=%d\n", i, r = Insert_Node(Root, &test[i]), test[i].id);

	Print_All_Node(Root);

	printf("Delete Node #7 Result = %d, Root = %d\n", Delete_Node(Root, 7), Root->id);

	printf("Delete Node #19 Result = %d, Root = %d\n", Delete_Node(Root, 19), Root->id);

	printf("Delete Node #14 Result = %d, Root = %d\n", Delete_Node(Root, 14), Root->id);

	Print_All_Node(Root);

	Delete_All_Node(Root);



#endif



#if 0



	// 4. Right만 있는 노드 삭제 



	for (i = 0; i<20; i++) printf("[Loop: %d] Insert Node Result=%d, ID=%d\n", i, r = Insert_Node(Root, &test[i]), test[i].id);

	Print_All_Node(Root);

	printf("Delete Node #5 Result = %d, Root = %d\n", Delete_Node(Root, 5), Root->id);

	printf("Delete Node #12 Result = %d, Root = %d\n", Delete_Node(Root, 12), Root->id);

	printf("Delete Node #11 Result = %d, Root = %d\n", Delete_Node(Root, 11), Root->id);

	Print_All_Node(Root);

	Delete_All_Node(Root);



#endif



	/* 자식이 2인 노드의 삭제  */



#if 0



	// 1. Root 삭제 



	for (i = 0; i<20; i++) printf("[Loop: %d] Insert Node Result=%d, ID=%d\n", i, r = Insert_Node(Root, &test[i]), test[i].id);

	Print_All_Node(Root);

	printf("Delete Node #10 Result = %d, Root = %d\n", Delete_Node(Root, 10), Root->id);

	Print_All_Node(Root);

	Delete_All_Node(Root);



#endif



#if 0



	// 2. 중간 노드 삭제 



	for (i = 0; i<20; i++) printf("[Loop: %d] Insert Node Result=%d, ID=%d\n", i, r = Insert_Node(Root, &test[i]), test[i].id);

	Print_All_Node(Root);

	printf("Delete Node #2 Result = %d, Root = %d\n", Delete_Node(Root, 2), Root->id);

	Print_All_Node(Root);

	printf("Delete Node #15 Result = %d, Root = %d\n", Delete_Node(Root, 15), Root->id);

	Print_All_Node(Root);

	printf("Delete Node #3 Result = %d, Root = %d\n", Delete_Node(Root, 3), Root->id);

	Print_All_Node(Root);

	printf("Delete Node #4 Result = %d, Root = %d\n", Delete_Node(Root, 4), Root->id);

	Print_All_Node(Root);

	Delete_All_Node(Root);



#endif

}



#endif



#endif



