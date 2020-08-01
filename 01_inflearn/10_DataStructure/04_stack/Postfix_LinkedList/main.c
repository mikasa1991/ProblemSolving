#include "stackADT.h"
#define MAX_LENGTH 100

static char operators[] = "+-*/";
static stack* operand_stack = NULL;

static int is_operator(char ch);
static int eval(char* expr);
static void handle_exception(const char* err_msg);
static int eval_op(char op);
static int read_line(FILE* fp, char* str, int n);

void main()
{
	char expr[MAX_LENGTH] = {0, }; //expr must consist of parens
	puts("input your postfix expression: ");
	while (read_line(stdin, expr, MAX_LENGTH) <= 0)	//get a line
	{
		puts("input your postfix expression: ");
	}
	printf("%d\n", eval(expr));
}

static int eval(char* expr)
{
	operand_stack = create_stack_instance();
	char* token = strtok(expr, " "); //for example, 2 4 * 7 +
	
	while(token != NULL) //if token exist
	{
		//if token[0] is operand
		if( (token[0] >= '0') && (token[0] <= '9') )
		{
			int value = atoi(token);
			push(operand_stack, value);
		}
		
		//if token[0] is operator
		else if(is_operator(token[0]) > -1)
		{
			int result = eval_op(token[0]);
			push(operand_stack, result);
		}

		else
		{
			handle_exception("Syntax Error: invalid character encountered.");
		}
		token = strtok(NULL, " ");
	}

	if(is_empty(operand_stack))
	{
		handle_exception("Syntax Error: Stack empty in eval_op.");
	}
	
	int answer = pop(operand_stack);
	
	if(is_empty(operand_stack))
	{
		return answer;
	}
	else
	{
		handle_exception("Syntax Error: Stack should be empty.");
		return -1;
	}
}

static int eval_op(char op)
{
	if(is_empty(operand_stack))
	{
		handle_exception("Syntax Error: Stack empty in eval_op");
	}
	int rhs = pop(operand_stack);

	if(is_empty(operand_stack))
	{
		handle_exception("Syntax Error: Stack empty in eval_op");
	}
	int lhs = pop(operand_stack);
	int result = 0;
	switch(op)
	{
		case '+':
			result = lhs + rhs;
			break;
		case '-':
			result = lhs - rhs;
			break;
		case '*':
			result = lhs * rhs;
			break;
		case '/':
			result = lhs / rhs;
			break;
	}
	return result;
}

static int is_operator(char ch)
{
	for(int i = 0; i < strlen(operators); i++)
	{
		if(operators[i] == ch)
		{
			return i; //+:0, -:1, *:2, /:3
		}
	}
	return -1; //error
}

static void handle_exception(const char* err_msg)
{
	puts(err_msg);
	exit(1);
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