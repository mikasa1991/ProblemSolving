#include "string_tools.h"

int read_line(FILE* fp, char* str, int limit) //instead of "fgets", "getline" function
{
	int ch = 0;
	int i = 0;

	//why are you add (ch != EOF)? because of last line in file 
	while((ch = fgetc(fp)) != '\n' && ch != EOF) //ch = one character
	{
		if(i < (limit - 1)) 
		{ 
			str[i] = ch;
			i++; 
		}
	}
	str[i] = '\0';
	return i;
}

void erase_blanks(char* expression) //expression is arrayName
{
	int j = 0;
	for(int i = 0; i < strlen(expression); i++)
	{
		if(expression[i] != ' ') 
		{
			expression[j] = expression[i];
			j++;
		}
	}
	expression[j] = '\0';
}