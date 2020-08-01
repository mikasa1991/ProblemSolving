#include "stack.h"

static char open[] = "([{";		//parenthesis can be when you open
static char close[] = ")]}";	//parenthesis can be when you close

static int is_balanced(char*);
static int is_open(char);
static int is_close(char);
static int read_line(FILE* fp, char* str, int n);

void main()
{
	char expr[MAX_LENGTH] = {0, }; //expr must consist of parens
	puts("input your expression: ");

	while (read_line(stdin, expr, MAX_LENGTH) <= 0)	//until get a line collectly,
	{
		puts("input your expression: ");
	}

	if(is_balanced(expr))	//if parenthesis is balanced
	{
		printf("%s: balanced.\n", expr);
	}

	else //if parenthesis is not balanced
	{
		printf("%s: unbalanced.\n", expr);
	}
}

static int is_balanced(char* expr)
{
	int balanced = 1;
	int index = 0;

	while(balanced && (index < strlen(expr)))
	{
		char ch = expr[index];	//ch = one character of expr
		if(is_open(ch) > -1)	//if ch is the one of parenthesis open
			push(ch);			//push ch that is one of parenthesis open
		
		else if(is_close(ch) > -1) //if ch is the one of parenthesis close
		{
			char top_ch = pop();

			//case1.if stack is empty
			if(top_ch == -1)
			{
				balanced = 0;
				break;
			}

			//case2.the open paren is different from the close paren
			if (is_open(top_ch) != is_close(ch))
			{
				balanced = 0;
				break;
			}
		}
		index++;
	}
	return ((balanced == 1) && (is_empty() == 1));
}

static int is_close(char ch)	//parens makes returnVal different, that can be 0, 1, 2.
{
	for(int i = 0; i < strlen(close); i++) //i < 3
	{
		if(close[i] == ch)
		{
			return i;
		}
	}
	return -1; //error
}

static int is_open(char ch)	//parens makes returnVal different, that can be 0, 1, 2.
{
	for(int i = 0; i < strlen(open); i++) //i < 3
	{
		if(open[i] == ch)
		{
			return i;
		}
	}
	return -1;	//error
}

static int read_line(FILE* fp, char* str, int n)
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