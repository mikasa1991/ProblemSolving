#include "polynomial.h"
#include "string_tools.h"

static void handle_definition(char* expression);
static void handle_print(char name);
static void handle_calc(char name, char* x_str);
static void process_command();

void main()
{
	process_command();
}

static void process_command()
{
	char command_line[BUFFER_LENGTH] = {0, };
	char copied[BUFFER_LENGTH] = {0, };
	char* cmd = NULL;
	char* arg1 = NULL;
	char* arg2 = NULL;

	while(1)
	{
		printf("$ ");
		if(read_line(stdin, command_line, BUFFER_LENGTH) <= 0)	//input command is empty
		{
			continue;	//comeback to starting point of endless loop
		}
		strcpy(copied, command_line);	//for case4: handle_definition
		cmd = strtok(command_line, " ");

		//case1: print functionName(arg1)
		//for example, print f
		if(strcmp(cmd, "print") == 0)	//if cmd is print
		{
			arg1 = strtok(NULL, " ");
			if(arg1 == NULL)
			{
				printf("Invalid arguments.\n");
				continue;
			}
			handle_print(arg1[0]);	//the character of string arg1
		}

		//case2: calc functionName(arg1) functionArgument(arg2)
		//for example, calc f 1, it means f(1)
		else if(strcmp(cmd, "calc") == 0) //if cmd is calc
		{
			arg1 = strtok(NULL, " ");	//functionName
			if(arg1 == NULL)
			{
				printf("Invalid arguments.\n");
				continue;
			}

			arg2 = strtok(NULL, " ");	//functionArgument
			if(arg2 == NULL)
			{
				printf("Invalid arguments.\n");
				continue;
			}
			handle_calc(arg1[0], arg2);	//arg1[0]: the character of string arg1
		}

		//case3: exit
		else if(strcmp(cmd, "exit") == 0)	//if cmd is exit
		{
			break;
		}

		//case4: function definition
		//for example, f = x^2 + x + 1
		else
		{
			handle_definition(copied);	//char copied[BUFFER_LENGTH];
		}
	}
}

/*
atoi
 */
static void handle_calc(char name, char* x_str)
{
	//empty
	for(int i = 0; i < n; i++)
	{
		if(name == polys[i]->name)	//character
		{
			printf("%d\n", eval_poly(polys[i], atoi(x_str)));
			return;
		}
	}
	puts("there isn't");
}

/*
입력받은 이름과 일치하는 다항식을 찾으면 출력하고 반복문을 나간다.
*/
static void handle_print(char name)
{
	for(int i = 0; i < n; i++)
	{
		if(name == polys[i]->name)	//character
		{
			//printf("%c\n", polys[i]->name);	//for debug
			printf_poly(polys[i]);
			return;
		}
	}
	puts("there isn't");
}

static void handle_definition(char* expression)
{
	erase_blanks(expression);
	//puts(expression); //for debug
	
	//함수명이 제대로 입력되지 않았을 때
	char* f_name = strtok(expression, "=");
	if(f_name == NULL || strlen(f_name) != 1) //function name must be 1 character
	{
		printf("Unsupported command.\n");
		return;
	}
	
	//함수 내용이 제대로 입력되지 않았을 때
	char* exp_body = strtok(NULL, "=");
	if(exp_body == NULL || strlen(exp_body) <= 0)
	{
		printf("Invalid expression format.\n");
		return;
	}

	//puts(f_name);		//for debug
	//puts(exp_body);	//for debug

	//case1: f=g+h 
	//caution_'x' can not be used for function name 
	if(exp_body[0] >= 'a' && exp_body[0] <= 'z' && exp_body[0] != 'x')
	{
		char* former = strtok(exp_body, "+");
		if(former == NULL || strlen(former) != 1)
		{
			printf("Invalid expression format.\n");
			return;
		}

		char* later = strtok(NULL, "+");
		if(later == NULL || strlen(later) != 1)
		{
			printf("Invalid expression format.\n");
			return;	
		}

		//puts(f_name);	//for debug
		//puts(former);	//for debug
		//puts(later);	//for debug
		polynomial* pol = create_by_add_two_polynomials(f_name[0], former[0], later[0]);	//arguments: function name
		if(pol == NULL)
		{
			printf("Invalid expression format.\n");
			return;	
		}
		insert_polynomial(pol);
	}

	//case2: f=3x^2+2x-3
	else
	{
		polynomial* pol = create_by_parse_polynomial(f_name[0], exp_body);
		if(pol == NULL)
		{
			printf("Invalid expression format.\n");
			return;
		}
		insert_polynomial(pol);
	}
}