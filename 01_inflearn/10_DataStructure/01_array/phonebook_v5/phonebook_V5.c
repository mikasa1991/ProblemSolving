//phonebook_V6

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define INIT_CAPACITY 100
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
static void print_person(person* p);
static void delete(char* name);
static void status();
static void find(char* name);
static void release_person(person* p);
static void reallocate();
static void init();
static void process_command();
static person* create_person_instance();

//person* directory[100]
person** directory;	//double pointer
int capacity;
int num_people;

void main()
{
	init();
	process_command();
}

static void init()
{
	directory = (person**)malloc(INIT_CAPACITY*sizeof(person*));
	for(int i = 0; i < INIT_CAPACITY; i++)
	{
		directory[i] = NULL;
	}

	capacity = INIT_CAPACITY;	//100
	num_people = 0;				//the num
}

static void process_command()
{
	char command_line[BUFFER_SIZE] = {0, };	//command_line consist of command, argu.
	char* command = NULL;
	char* argu = NULL;
	char name_str[BUFFER_SIZE] = {0, };		//to compose name_ reference:phonebook_V4_png

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

//txt -> memory
static void load(char* filename)
{
	char buffer[BUFFER_SIZE] = {0, };
	char* name = NULL;
	char* number = NULL;
	char* email = NULL;
	char* group = NULL;
	char* token = NULL;
	
	FILE* fp = fopen(filename, "r");
	if(fp == NULL)	//if file not exist
	{
		puts("Open failed.\n");
		return;
	}

	//if file exist
	while(1)
	{
		if(read_line(fp, buffer, BUFFER_SIZE)<=0) { break; }
		name = strtok(buffer, "#");	//name must be input 
		
		token = strtok(NULL, "#");
		if(strcmp(token, " ") == 0) { number = NULL; }
		else 						{ number = token; }

		token = strtok(NULL, "#");
		if(strcmp(token, " ") == 0) { email = NULL; }
		else 						{ email = token; }

		token = strtok(NULL, "#");
		if(strcmp(token, " ") == 0) { group = NULL; }
		else 						{ group = token; } 

		add(name, number, email, group);
	}
	fclose(fp);
}

//to read line from keyboard and file
static int read_line(FILE* fp, char* str, int limit) //instead of "fgets", "getline" function
{
	int ch, i = 0;

	//why are you add (ch != EOF)? because of last line in file 
	while((ch = fgetc(fp)) != '\n' && ch != EOF) //ch = one character
	{
		if(i < (limit - 1)) { str[i++] = ch; }
	}
	str[i] = '\0';
	return i;
}

static void add(char* name, char* number, char* email, char* group)
{
	if(num_people >= capacity) { reallocate(); }
	int i = num_people - 1;
	
	//asscending sorting
	while((i >= 0) && (strcmp(directory[i]->name, name) > 0))
	{
		directory[i+1] = directory[i];
		i--;
	}

	//directory[i+1] = (person*)malloc(sizeof(person));
	//memset(directory[i+1], NULL, sizeof(person));
	directory[i+1] = create_person_instance();

	directory[i+1]->name = strdup(name);	//name must be input.
	if(directory[i+1]->number != NULL) directory[i+1]->number = strdup(number);
	if(directory[i+1]->email  != NULL) directory[i+1]->email = strdup(email);
	if(directory[i+1]->group  != NULL) directory[i+1]->group = strdup(group);

	printf("%p\n", directory[i+1]->name);
	printf("%p\n", directory[i+1]->number);
	printf("%p\n", directory[i+1]->email);
	printf("%p\n", directory[i+1]->group);

	printf("'%s' was added successfully.\n", directory[i+1]->name);
	num_people++;
}

static person* create_person_instance()
{
	person* p = (person*)malloc(sizeof(person));
	p->name = NULL;
	p->number = NULL;
	p->email = NULL;
	p->group = NULL;
	return p;
}

static void reallocate()
{
	capacity *= 2;
	person** tmp = (person**)malloc(capacity * sizeof(person*));
	for(int i = 0; i < num_people; i++)
	{
		tmp[i] = directory[i];
	}
	free(directory);	//free the prev pointer
	directory = tmp;
}

static void delete(char* name)
{
	int i = search(name);
	if ( i == -1 )
	{
		printf("No person named '%s' exists.\n", name);
		return;
	}

	person* p = directory[i];
	for(int j = 1; j < num_people - 1; j++)
	{
		directory[j] = directory[j+1];
	}
	num_people--;
	release_person(p);
	printf("'%s' was deleted successfully.\n", name);
}

static void release_person(person* p)
{
	free(p->name);	//name must be input
	if(p->number != NULL) free(p->number);
	if(p->email  != NULL) free(p->email);
	if(p->group  != NULL) free(p->group);
	free(p);
}

static int compose_name(char* str, int limit)
{
	char* ptr = NULL;
	int length = 0;					//the length of name

	ptr = strtok(NULL, " "); 		//name token first
	
	//if first token not exist
	if(ptr == NULL) { return 0; }

	//if first token exist
	strcpy(str, ptr);
	length = length + strlen(ptr);
	
	while((ptr = strtok(NULL, " ")) != NULL) //name token next
	{
		if(length + strlen(ptr) < limit - 1)
		{
			str[length++] = ' ';
			str[length]   = '\0';
			strcat(str, ptr);	//string concatenate
			length = length + strlen(ptr);
		}
	}
	return length;
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
		fprintf(fp, "%s#", directory[i]->name);
		fprintf(fp, "%s#", directory[i]->number);
		fprintf(fp, "%s#", directory[i]->email);
		fprintf(fp, "%s#\n", directory[i]->group);
	}
	fclose(fp);
	puts("save successfully.");
}

static int search(char* name)
{
	for(int i = 0; i < num_people; i++)
	{
		if(strcmp(name, directory[i]->name) == 0) { return i; }
	}
	return -1;
}

static void print_person(person* p)
{
	printf("%s:\n", p->name);
	printf("	Phone: %s\n", p->number);
	printf("	Email: %s\n", p->email);
	printf("	Group: %s\n", p->group);
	printf("%p\n", p->name);
	printf("%p\n", p->number);
	printf("%p\n", p->email);
	printf("%p\n", p->group);
	puts("");
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

//after input name, you would need to input another data.
static void handle_add(char* name)
{
	char number[BUFFER_SIZE];
	char email[BUFFER_SIZE];
	char group[BUFFER_SIZE];
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