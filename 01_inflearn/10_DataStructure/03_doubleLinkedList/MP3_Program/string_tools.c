#include "string_tools.h"

int read_line(FILE* fp, char* str, int n)
{
	int ch = 0;
	int i = 0;
	while((ch = fgetc(fp)) != '\n' && ch != EOF)
	{
		if(i < n - 1)
		{
			str[i] = ch;
			i++;
		}
	}
	str[i] = '\0';
	return i;
}