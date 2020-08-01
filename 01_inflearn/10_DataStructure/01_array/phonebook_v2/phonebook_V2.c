//phonebook2
/*
 *add name phoneNumber
 *find name
 *status
 *delete name
 *load fileName
 *save as fileName
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define CAPACITY 100
#define BUFFER_SIZE 20

char* names[CAPACITY];		//pointer array
char* numbers[CAPACITY];	//pointer array
int num_people = 0;			//number of people in phonebook

static void add();
static void find();
static void status();
static void delete();
static void load();
static void save();
static int search(char*);

void main()
{
	char command[BUFFER_SIZE] = {0, }; 						//MAX characters 19 
	while(1)
	{
		printf("$ ");
		scanf("%s", command);

		/*
		add name phonenumber
		find name
		status
		delete name
		read phonebook_V2.txt
		save as phonebook_V2.txt
		exit
		*/

		if     (strcmp(command, "add") 	  == 0) add();		//add name phoneNumber
		else if(strcmp(command, "find")   == 0) find();
		else if(strcmp(command, "status") == 0) status();
		else if(strcmp(command, "delete") == 0) delete();
		else if(strcmp(command, "read")   == 0) load();
		else if(strcmp(command, "save")   == 0) save();
		else if(strcmp(command, "exit")   == 0) break;
		else 
		{
			puts("Invalid Command."); 
			continue; 
		}
	}
}

static void add()
{
	char buf1[BUFFER_SIZE] = {0, } ;	//MAX characters 19
	char buf2[BUFFER_SIZE] = {0, } ; 	//MAX characters 19
	scanf("%s", buf1);					//buf1 is name
	scanf("%s", buf2);					//buf2 is phoneNumber

	/*
	 * strcmp
	 * aaa\0 == aaa\0 ->  return  0
	 * aab\0 >  aaa\0 ->  return  1
	 * aab\0 <  aac\0 ->  return -1
	 */
	
	//assending sort
	/*
	 *삽입되는 이름을 가장 끝에 저장된 전화번호부 이름부터 비교한다.
	 *ㄱ ㄴ ㄷ 순이라면, 기존 전화번호부 항목을 한칸 뒤로 이동시킨다.
	 */
	int i = num_people - 1;	//index of array
	while ( (i >= 0) && (strcmp(names[i], buf1) > 0) )
	{
		names[i+1]   = names[i];
		numbers[i+1] = numbers[i];
		i--;
	}
	//strdup; memory allocate, return address
	//strdup is not ANCI standard func.
	names[i+1]   = strdup(buf1);
	numbers[i+1] = strdup(buf2);

	num_people++;	//upcounting the num of people
	printf("%s was added successfully.\n", buf1);
}

static void find()
{
	char buf[BUFFER_SIZE] = {0, };
	scanf("%s", buf);	//name
#if 0
	int i;
	for(i = 0; i < n; i++)
	{
		if(strcmp(buf, names[i]) == 0) {
			printf("%s\n", numbers[i]);
			return;
		}
	}
	printf("No person named '%s' exists.\n", buf);
#endif
	int index = search(buf);
	if (index == -1)			//일치하는 이름이 전화번호부에 있다면
		printf("No person named '%s' exists.\n", buf);
	else 						//없을 경우
		printf("%s\n", numbers[index]);
}

static void status() 
{
	for(int i = 0; i < num_people; i++)	//n is the number of people in phonebook
	{
		printf("%s %s\n", names[i], numbers[i]);
	}
	printf("Total %d persons.\n", num_people);
}

static void delete()
{
	char buf[BUFFER_SIZE] = {0, };
	scanf("%s", buf);	//name
#if 0
	int i;
	for (i = 0; i < n; i++)
	{
		if(strcmp(buf, names[i]) == 0) {
			names[i] = names[n -1];
			numbers[i] = numbers[n -1];
			n--;
			printf("'%s' was deleted successfully. \n", buf);
			return;
		}
	}
	printf("No person named '%s' exists.\n", buf);
#endif

	int index = search(buf);

	//일치하는 이름이 전화번호부에 없다면
	if(index == -1)
	{
		printf("No person named '%s' exists.\n", buf);
		return;
	}

	//일치하는 이름이 전화번호부에 있다면
	int j = index;

	if(names[j]   != NULL) free(names[j]);
	if(numbers[j] != NULL) free(numbers[j]);
	
	for(; j < num_people-1; j++)	//to delete empty space
	{
		names[j] = names[j+1];
		numbers[j] = numbers[j+1];
	}
	num_people--;
	printf("'%s' was deleted successfully. \n", buf);
}

//phonebook.txt -> array in memory
static void load()
{
	char fileName[BUFFER_SIZE] = {0, };
	char buf1[BUFFER_SIZE] = {0, };
	char buf2[BUFFER_SIZE] = {0, };

	scanf("%s", fileName);	//fileName

	FILE* fp = fopen(fileName, "r");
	
	//일치하는 파일이 없다면
	if(fp == NULL) {
		puts("Open failed");
		return;
	}

	//일치하는 파일이 있다면
	/*
	 buf1  : name
	 buf2  : phone number
	 fscanf: 서식을 지정하여 파일에서 문자열 읽기
	 */
	while((fscanf(fp, "%s", buf1)!= EOF))	//if name exist in txt file
	{
		fscanf(fp, "%s", buf2);				//phoneNumber
		names[num_people] = strdup(buf1);
		numbers[num_people] = strdup(buf2);
		num_people++;						//upcounting the num of people
	}
	fclose(fp);
	puts("load success");
}

//array in memory -> phonebook.txt
static void save()
{
	char fileName[BUFFER_SIZE] = {0, };
	char tmp[BUFFER_SIZE] = {0, };

	scanf("%s", tmp);			//which is "as", discarded
	scanf("%s", fileName);

	FILE* fp = fopen(fileName, "w");
	
	//일치하는 파일이 없다면
	if(fp == NULL) {
		puts("Open failed");
		return;
	}

	//일치하는 파일이 있다면
	/*
	 fprintf: 서식을 지정하여 파일에 문자열 쓰기
	 */
	for(int i = 0; i < num_people; i++)
	{
		fprintf(fp, "%s %s\n", names[i], numbers[i]);
	}
	fclose(fp);
	puts("save success");
}

/*
일치하는 이름이 전화번호부에 있다면, 0이상의 숫자를 반환한다.
그러나 없을 경우, -1을 반환한다.
*/
static int search(char* name)
{
	for(int i = 0; i < num_people; i++)
	{
		if(strcmp(name, names[i]) == 0)
		{
			return i;
		}
	}
	return -1;
}