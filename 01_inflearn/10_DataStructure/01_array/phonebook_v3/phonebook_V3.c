//phonebook_V3

/*
 *line input can
 *phonebook is allocated in heap area
 */

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

#define INIT_CAPACITY 100
#define BUFFER_SIZE   50

char** names;	//double pointer
char** numbers;	//double pointer

int capacity = INIT_CAPACITY;	//size of arrays
int num_people = 0;						//number of people in phonebook

//char delim[] = " ";	//same expression
char* delim = " ";		//delimeter

static void init_directory();
static void process_command();
static int read_line(char*, int);
static void load(char*);
static void reallocate();
static void delete(char*);
static int search(char*);
static void status();
static void find(char*);
static void add(char*, char*);
static void save(char*);
static char** create_char_double_pointer();

void main()
{
	init_directory();	//make phonebook heap area
	process_command();
}

static void init_directory()
{
	//double pointer <=(allocate) pointer array
	names = create_char_double_pointer();
	numbers = create_char_double_pointer();
}

static char** create_char_double_pointer()
{
	char** ptr_char = (char**)malloc(INIT_CAPACITY*sizeof(char*));
	//initialize
	for(int i = 0; i < INIT_CAPACITY; i++)
	{
		ptr_char[i] = NULL;
	}
	//return the address of double pointer
	return ptr_char;
}

static void process_command()
{
	char command_line[BUFFER_SIZE] = {0, }; //49 characters
	//command_line divide => command, argu1, argu2
	char* command = NULL;
	char* argu1 = NULL;
	char* argu2 = NULL;

	while(1)
	{
		printf("$ ");

		//아무 입력을 받지 못하면 반복문의 처음으로 돌아간다
		if(read_line(command_line, BUFFER_SIZE) <= 0) { //(i == 0) is equal to nothing input
			continue; //comeback to while(1)
		}
		
		/*
		add name phonenumber
		find name
		status
		delete name
		read phonebook_V2.txt
		save as phonebook_V2.txt
		exit
		*/

		//입력을 받았을 때
		command = strtok(command_line, delim); //token for command
		//printf("command_line %p, %s\n", command_line, command_line);
		//printf("command      %p, %s\n", command, command);

		//read filename
		if(strcmp(command, "read") == 0) { //if token of cmd is "read"
			argu1 = strtok(NULL, delim);   //fileName	
			if(argu1 == NULL) {
				printf("File name required.\n");
				continue;
			}
			load(argu1);
		}

		//add Name PhoneNumber
		else if(strcmp(command, "add") == 0) {
			argu1 = strtok(NULL, delim);	//name
			argu2 = strtok(NULL, delim);	//phoneNum
			if(argu1 == NULL || argu2 == NULL) {
				puts("invalid argument");
				continue;
			}
			add(argu1, argu2);
		}

		//find name
		else if(strcmp(command, "find") == 0) {
			argu1 = strtok(NULL, delim);	//name
			if(argu1 == NULL) {
				puts("invalid argument");
				continue;
			}
			find(argu1);
		}

		//status
		else if(strcmp(command, "status") == 0) {
			status();
		}

		//delete name
		else if(strcmp(command, "delete") == 0) {
			argu1 = strtok(NULL, delim);	//name
			if(argu1 == NULL) {
				puts("invalid argument");
				continue;
			}
			delete(argu1); 
		}

		//save as filename
		else if(strcmp(command, "save") == 0) {
			argu1 = strtok(NULL, delim);	//as
			argu2 = strtok(NULL, delim);	//name
			if(argu1 == NULL || strcmp("as", argu1) != 0 || argu2 == NULL) {
				puts("invalid argument");
				continue;
			}
			save(argu2);
		}

		//exit
		else if(strcmp(command, "exit") == 0) {
			break;
		}
	}
}

//to read line
//instead of "fgets", "getline" function
//to read line from keyboard only
static int read_line(char* str, int limit)
{
	int ch, i = 0;
	while((ch = getchar()) != '\n')	//getchar() returns '\n' at last.
	{
		if(i < limit - 1)			//limit - 1 is for '\0'
		{
			str[i] = ch;
			//printf("%d %c\n", i, str[i]);	//for debug
			i++;
		}
	}
	str[i] = '\0';
	//printf("%d %c\n", i, str[i]);			//for debug; print NULL
	//printf("strlen: %ld\n", strlen(str));	//for debug
	return i;
}

static void load(char* filename)
{
	char buf1[BUFFER_SIZE] = {0, };
	char buf2[BUFFER_SIZE] = {0, };

	FILE* fp = fopen(filename, "r");
	if(fp == NULL) 
	{				//file not exist
		puts("open failed.");
		return;
	}

	//file exist
	while( (fscanf(fp, "%s", buf1) != EOF) )	//buf1 = &nameWrited
	{
		fscanf(fp, "%s", buf2);	//buf2 = &numberWrited
		add(buf1, buf2);
	}
	fclose(fp);
}

static void add(char* name, char* number)
{
	if(num_people >= capacity) reallocate();

	int i = num_people - 1;	//index

	//assending sorting
	//reference: phonebook_V2
	while ( (i >= 0) && (strcmp(names[i], name) > 0) )
	{
		names[i+1] = names[i];
		numbers[i+1] = numbers[i];
		i--;
	}
	names[i+1] = strdup(name);
	numbers[i+1] = strdup(number);

	num_people++;	//upcounting the number of phonebook
	printf("%s was added successfully.\n", name);
}

static void find(char* name)
{
	int index = search(name); //return index
	if (index == -1)		  //일치하는 이름이 전화번호부에 있다면
		printf("No person named '%s' exists.\n", name);
	else					  //없을 경우
		printf("%s\n", numbers[index]);
}

static void status() 
{
	for(int i = 0; i < num_people; i++)
	{
		printf("%s %s\n", names[i], numbers[i]);
	}
	printf("Total %d persons.\n", num_people);
}

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

static void delete(char* name)
{
	int index = search(name); //returns - 1 if not exists
	if(index == -1)
	{
		printf("No person named '%s' exists.\n", name);
		return;
	}

	int j = index;
	if(names[j] != NULL)   free(names[j]);
	if(numbers[j] != NULL) free(numbers[j]);

	for(; j < num_people - 1; j++)	//to delete empty space
	{
		names[j] = names[j+1];
		numbers[j] = numbers[j+1];
	}
	num_people--;
	printf("'%s' was deleted successfully. \n", name);
}

static void reallocate() // * 2 make
{
	int i = 0;

	capacity = capacity * 2;
	char** tmp1 = (char**)malloc(capacity*sizeof(char**));
	char** tmp2 = (char**)malloc(capacity*sizeof(char**));

	for (i = 0; i < num_people; i++)
	{
		tmp1[i] = names[i];
		tmp2[i] = numbers[i];
	}

	//free pre-heap area
	free(names);
	free(numbers);

	names = tmp1;
	numbers = tmp2;
}

//memory -> phonebook.txt0
static void save(char* filename)
{
	FILE* fp = fopen(filename, "w");
	if(fp == NULL) {
		puts("Open failed");
		return;
	}

	for(int i = 0; i < num_people; i++)
	{
		fprintf(fp, "%s %s\n", names[i], numbers[i]);
	}
	fclose(fp);
	puts("save success");
}