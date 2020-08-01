/*
 *(180914)
 *pointer array
 *heap
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 100

char* create_string_instance(char*);
void print_word(char** words, int cnt);
void delete_word(char** words, int cnt);

void main()
{
	char* words[100] = {NULL, };			//pointer array
	char buffer[BUFFER_SIZE] = {0, };
	int cnt_word = 0;

	while( (cnt_word < 4) && (scanf("%s", buffer) != EOF) ) //to get input four times 
	{
		//buffer means buffer array's address.

		//words[cnt_word] = buffer; 					  //can excute, but this line makes it print out stuff input in last. 

		//words[cnt_word] = strdup(buffer);				  //method1. if we use this line, we don't have to make the func "create_string_instance"
		words[cnt_word] = create_string_instance(buffer); //method2. to allocate heap areas in words[n]
		
		cnt_word++;
	}

	//printf("%d\n", cnt_word); //for debug

	print_word(words, cnt_word);
	delete_word(words, cnt_word);
}

void print_word(char** words, int cnt)
{
	for(int i = 0; i < cnt; i++)
	{
		printf("%s\n", words[i]);
	}
}

void delete_word(char** words, int cnt)
{
	for(int i = 0; i < cnt; i++)
	{
		free(words[i]);
	}
}

char* create_string_instance(char* p) //argument means the string input.
{
	char* temp;
	if( (temp = (char*)malloc(sizeof(char)*strlen(p) + 1)) == NULL)
	{
		puts("not enough memory to allocate");
		return NULL;
	}
	strcpy(temp, p);
	return temp;
}