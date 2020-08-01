#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define INIT_CAPACITY 50
#define BUFFER_SIZE 100		//to save command(string)
#define delimeter ";"

typedef struct _transaction
{
	char* date;		//거래일자
	char* time;		//거래시간
	char* brief;	//적요
	char* output;	//출금(원)
	char* input;	//입금(원)
	char* context;	//내용
	char* balance;	//잔액(원)
	char* place;	//거래점
}transaction;

//function declare
transaction* create_transaction();
int read_line(FILE* fp, char* chr_ptr, int limit);
void init();
void process_command();
void add(transaction* t);
void status();
void load(char* filename);
void reallocate();

//variable declare
transaction** info;
int capacity;		//저장 가능한 트랜잭션 수
int num;			//저장된 트랜잭션 수

int main()
{
	init();
	process_command();

	return 0;
}

void process_command()
{
	char command_line[BUFFER_SIZE] = {0, };
	char* command = NULL;
	char* argument = NULL;

	while(1)
	{
		printf("$ ");
		if(read_line(stdin, command_line, BUFFER_SIZE) <= 0)
			continue;

		command = strtok(command_line, " ");

		//load shinhan_transactional_bill_181201_181231.txt
		if(strcmp(command, "load") == 0)
		{
			argument = strtok(NULL, " ");
			if(argument == NULL)
			{
				puts("file name required.");
				continue;
			}
			load(argument);
		}

		//status
		else if(strcmp(command, "status") == 0)
		{
			status();
		}

		//exit
		else if(strcmp(command, "exit") == 0)
		{
			break;
		}

		else
		{
			puts("입력이 잘못됐습니다.");
			continue;
		}
	}
}

void add(transaction* t)
{
	if(num >= capacity)
	{
		puts("need to allocate!");
		reallocate();
	}

	int i = num - 1;

	/*
	2018-01-28
	strdup 함수는 힙 공간을 할당하고 그 주소를 반환한다.
	여기서 왜 필요한걸까? 그냥 t->date를 넣으면 어떻게 될까?

	t는 지역변수이기 때문에, add함수가 종료되고나서 메모리에서 지워진다.
	따라서 strdup가 필요하다.
	*/
	info[i+1] = create_transaction();

	info[i+1]->date    = strdup(t->date);
	info[i+1]->time   = strdup(t->time);
	info[i+1]->brief   = strdup(t->brief);
	
	if(t->output != NULL)
		info[i+1]->output  = strdup(t->output);
	
	if(t->input != NULL)
		info[i+1]->input   = strdup(t->input);
	
	info[i+1]->context = strdup(t->context);
	info[i+1]->balance = strdup(t->balance);
	info[i+1]->place   = strdup(t->place);
	num++;
}

void reallocate()
{
	capacity = capacity * 2;
	
	transaction** temp = (transaction**)malloc(sizeof(transaction*)*capacity);
	for(int i = 0; i < num; i++)
	{
		temp[i] = info[i];
	}
	free(info);
	info = temp;
}

void load(char* filename)
{
	char buffer[BUFFER_SIZE] = {0, };
	char* token = NULL;
	transaction t;
	memset(&t, 0, sizeof(transaction));

	FILE* fp = fopen(filename, "r");
	if(fp == NULL)
	{
		puts("open failed.");
		return;
	}

	while(1)
	{
		if(read_line(fp, buffer, BUFFER_SIZE) <= 0)
			break;

		t.date = strtok(buffer, delimeter);
		t.time = strtok(NULL, delimeter);
		t.brief = strtok(NULL, delimeter);
		
		token = strtok(NULL, delimeter);

		/*
		2018-01-29
		strtok에서 delimeter를 ";"로 설정했다.
		output;input;context 변수에 txt에서 값을 읽어 저장하고 싶다.
		출금의 경우에는, 예를 들어, 2800;;편의점
		입금의 경우에는, 예를 들어, ;;2900;편의점
		와 같은 형태로 txt파일에 저장된다.
		처음에 strtok 함수를 3번 호출해서, 위의 3개의 변수에 값을 저장하려 했다.
		그러나, ;;의 경우에는 그 앞의 호출된 strtok 함수에 의해서 NULL NULL이 된다.
		따라서, 위의 함수 3번 호출로 3개의 변수에 값을 저장할 수 없었다.
		그래서 이게 출금인지 입금인지를 하기의 if-else문으로 구분했다.
		*/
		if(buffer[token-buffer-2] == '\0') //input
		{
			t.input = token;
			t.output = NULL;
		}
		else							   //output
		{
			t.input = NULL;
			t.output = token;
		}

		t.context = strtok(NULL, delimeter);
		t.balance = strtok(NULL, delimeter);
		t.place = strtok(NULL, delimeter);
		add(&t);
	}
	puts("load success");
	fclose(fp);
}

void status()
{
	puts("거래일자;거래시간;적요;출금(원);입금(원);내용;잔액(원);거래점");
	
	for(int i = 0; i < num; i++)
	{
		printf("%s %s %s %s %s %s %s %s\n"
			, info[i]->date, info[i]->time, info[i]->brief, info[i]->output, 
			info[i]->input, info[i]->context, info[i]->balance, info[i]->place);
	}
	printf("total transaction: %d\n", num);
}

void init()
{
	info = (transaction**)malloc(INIT_CAPACITY*sizeof(transaction*));
	
	for(int i = 0; i < INIT_CAPACITY; i++)
	{
		info[i] = NULL;
	}
	
	capacity = INIT_CAPACITY;	//저장 가능한 트랜잭션 수 초기화
	num = 0;					//저장된 트랜잭션 수
}

transaction* create_transaction()
{
	transaction* t = (transaction*)malloc(sizeof(transaction));
	memset(t, 0, sizeof(transaction));
	return t;
}

int read_line(FILE* fp, char* chr_ptr, int limit)
{
	char ch = 0;
	char i = 0;

	//case1.엔터키 입력을 받는 순간에 반복문을 탈출하고자 한다
	//while((ch = getchar()) != '\n')
	
	//case2(+FILE_IO).엔터키 입력을 받거나 또는 파일 끝에 도달한 경우에 반복문을 탈출하고자 한다
	while((ch = fgetc(fp)) != '\n' && ch != EOF)
	{
		
		//limit-1보다 작다로 한 이유는 문자열 끝에 널값을 저장하기 위한 공간을 확보하기 위해
		if(i < limit - 1)
		{
			chr_ptr[i] = ch;
			i++;
		}
		/*
		엔터키 입력을 받기 전에 문자열을 저장할 수 있는 공간을 초과하는 경우에
		에러값을 반환한다.
		*/
		else
		{
			puts("range exceed!");
			return -1;
		}
	}
	chr_ptr[i] = '\0';
	return i;
}