//phonebook_V4

/*
 *email address, group add!
 *you don't have to add all things.
 *when name input, if many space exist, it makes one space.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define CAPACITY 100
#define BUFFER_SIZE 100

typedef struct _person
{
	char* name;
	char* number;
	char* email;
	char* group;
}person;

static int read_line(FILE* fp, char* str, int limit);
static void load(char* filename);
static void add(char* name, char* number, char* email, char* group);
static int compose_name(char* str, int limit);
static void handle_add(char* name);
static void save(char* filename);
static int search(char* name);
static void print_person(person p);
static void delete(char* name);
static void status();
static void find(char* name);

person directory[CAPACITY]; //global area

int num_people = 0; //the number of people in phonbook

void main()
{
	char command_line[BUFFER_SIZE] = {0, };	//command_line consist of command, argu.
	char* command = NULL;
	char* argu = NULL;
	char name_str[BUFFER_SIZE] = {0, };		//to compose name_ reference:phonebook_V4_png

	/*
 	 *add name
  	 phone:
  	 email:
  	 group:

 	 *find name
 	 *status
 	 *delete name
 	 *load fileName
 	 *save as fileName
 	 */
	while(1)
	{
		printf("$ ");
		//stdin is keyboard input
		if(read_line(stdin, command_line, BUFFER_SIZE) <= 0) { //(i == 0) is equal to nothing input
			continue; //comeback to while(1)
		}
		command = strtok(command_line, " "); //token for command
		
		//read filename
		if(strcmp(command, "read") == 0) 
		{
			argu = strtok(NULL, " ");	//fileName
			if(argu == NULL) {
				printf("File name required.\n");
				continue;
			}
			load(argu);
		}

		//add Name PhoneNumber
		else if(strcmp(command, "add") == 0) {
			if(compose_name(name_str, BUFFER_SIZE) <= 0) 
			{
				puts("name required.");
				continue;
			}
			handle_add(name_str);
		}

		//find name
		else if(strcmp(command, "find") == 0) {
			if(compose_name(name_str, BUFFER_SIZE) <= 0) 
			{
				puts("name required.");
				continue;
			}
			find(name_str);
		}

		//status
		else if(strcmp(command, "status") == 0) {
			status();
		}

		//delete name
		else if(strcmp(command, "delete") == 0) {
			if(compose_name(name_str, BUFFER_SIZE) <= 0) 
			{
				puts("Invalid arguments.");
				continue;
			}
			delete(name_str);
		}

		//save as filename
		else if(strcmp(command, "save") == 0) {
			argu = strtok(NULL, " ");	//as
			if(strcmp(argu, "as") != 0)
			{
				printf("Invalid arguments.\n");
				continue;
			}
			argu = strtok(NULL, " ");	//fileName
			if(argu == NULL)
			{
				printf("Invalid arguments.\n");
				continue;
			}
			save(argu);
		}

		//exit
		else if(strcmp(command, "exit") == 0) {
			break;
		}
	}
}

//to read line from keyboard and file
static int read_line(FILE* fp, char* str, int limit) //instead of "fgets", "getline" function
{
	int ch, i = 0;

	/*
	 fgetc function
 	 :파일 스트림의 버퍼에서 맨 앞의 문자의 ASCII 코드 값을 반환하는 함수
	*/
	
	//why are you add (ch != EOF)? because of last line in file 
	while((ch = fgetc(fp)) != '\n' && ch != EOF) //ch = one character
	{
		if(i < (limit - 1)) 
		{ 
			str[i] = ch;
			//printf("%d %c\n", i, str[i]);	//for debug
			i++; 
		}
	}
	str[i] = '\0';
	//printf("%d %c\n", i, str[i]);			//for debug
	//printf("strlen: %ld\n", strlen(str));	//for debug
	return i;
}

//txt -> memory
static void load(char* filename)
{
	char buf[BUFFER_SIZE] = { 0, };	//for command_line
	char* name = NULL;
	char* number = NULL;
	char* email = NULL;
	char* group = NULL;

	FILE* fp = fopen(filename, "r");
	if(fp == NULL) {				//file not exist
		puts("open failed.");
		return;
	}

	//file exist
	while(1)
	{
		if(read_line(fp, buf, BUFFER_SIZE) <= 0) { break; }
		name = strtok(buf, "#");
		number = strtok(NULL, "#");
		email = strtok(NULL, "#");
		group = strtok(NULL, "#");
		add(name, number, email, group);
	}
	fclose(fp);
}

static void add(char* name, char* number, char* email, char* group)
{
	int i = num_people - 1;
	
	//asscending sorting
	while((i >= 0) && (strcmp(directory[i].name, name) > 0))
	{
		directory[i+1] = directory[i];
		i--;
	}

	directory[i+1].name = strdup(name);
	directory[i+1].number = strdup(number);
	directory[i+1].email = strdup(email);
	directory[i+1].group = strdup(group);
	printf("'%s' was added successfully.\n", directory[i+1].name);
	num_people++;
}

/*
to study this func as static int compose_name(char* str, int limit), you should check these contents.

 char *strcat(char *_Destination, char const *_Source);
 최종 문자열을 반환

 char *strtok(char *_String, char const *_Delimiter);
 자른 문자열을 반환, 더 이상 자를 문자열이 없으면 NULL을 반환 

  Question) _Delimiter가 중복되서 나오는 경우는 어떻게 될까?
  Answer  ) 
   The Little Prince
   0x7ffe67ae3a40 The 3
   0x7ffe67ae3a44 Little 6
   0x7ffe67ae3a4b Prince 6
   
   The Little  Prince
   0x7ffe38e5a9f0 The 3
   0x7ffe38e5a9f4 Little 6
   0x7ffe38e5a9fc Prince 6
 */

/*
이름으로 문자열을 입력받을 때, 이름이 띄어쓰기를 포함하는 경우,
이름을 띄어쓰기 1개로 통일해서 문자열을 구성하는게 목적이다.
 */
static int compose_name(char* str, int limit)	//to make "many spacebars" "one spacebar"
{
	char* ptr = NULL;
	int length = 0;					//the length of name

	ptr = strtok(NULL, " "); 		//name token first
	
	//if first token not exist
	if(ptr == NULL) { return 0; }
	
	//else if first token exist
	strcpy(str, ptr);
	//printf("%ld, %s\n", strlen(ptr), str);			//for debug
	length = length + strlen(ptr);
	
	while((ptr = strtok(NULL, " ")) != NULL) 			//name token next
	{
		if(length + strlen(ptr) < limit - 1)
		{
			str[length++] = ' ';
			str[length]   = '\0';
			strcat(str, ptr);									//string concatenate
			//printf("%ld, %s\n", length + strlen(ptr), str);	//for debug
			length = length + strlen(ptr);
		}
	}
	return length;
}

//after input name, you would need to input another data.
static void handle_add(char* name)
{
	char number[BUFFER_SIZE] = {0, };
	char email[BUFFER_SIZE] = {0, };
	char group[BUFFER_SIZE] = {0, };
	char empty[] = " ";

	printf(" Phone: ");
	read_line(stdin, number, BUFFER_SIZE); //stdin is keyboard input.

	printf(" Email: ");
	read_line(stdin, email, BUFFER_SIZE); //stdin is keyboard input.

	printf(" Group: ");
	read_line(stdin, group, BUFFER_SIZE); //stdin is keyboard input.

	add(name, (char*)(strlen(number) > 0 ? number : empty),
			  (char*)(strlen(number) > 0 ? email  : empty),
			  (char*)(strlen(number) > 0 ? group  : empty));
}

//memory -> txt
static void save(char* filename)
{
	FILE* fp = fopen(filename, "w");
	if(fp == NULL)
	{
		puts("open failed.");
		return;
	}

	for(int i = 0; i < num_people; i++)
	{
		fprintf(fp, "%s#", directory[i].name);
		fprintf(fp, "%s#", directory[i].number);
		fprintf(fp, "%s#", directory[i].email);
		fprintf(fp, "%s#\n", directory[i].group);
	}
	fclose(fp);
	puts("save successfully.");
}

static int search(char* name)
{
	for(int i = 0; i < num_people; i++)
	{
		if(strcmp(name, directory[i].name) == 0) { return i; }
	}
	return -1;
}

static void print_person(person p)
{
	printf("%s:\n", p.name);
	printf("	Phone: %s\n", p.number);
	printf("	Email: %s\n", p.email);
	printf("	Group: %s\n", p.group);
}

static void delete(char* name)
{
	int i = search(name);
	if(i == -1)
	{
		printf("No person named '%s' exists.\n", name);
		return;
	}

	//to delete empty spaces
	int j = i;
	for(;j < num_people - 1; j++) 
	{ 
		directory[j] = directory[j+1]; 
	}
	num_people--;
	printf("'%s' was deleted successfully.\n", name);
}

static void status()
{
	for(int i = 0; i < num_people; i++)
	{
		print_person(directory[i]);
	}
	printf("Total %d persons.\n", num_people);
}

static void find(char* name)
{
	int index = search(name);
	if(index == -1) { printf("No person named '%s' exists.\n", name); }
	else 			{ print_person(directory[index]); }
}