#include "stack.h"

static char stack[MAX_CAPACITY] = {0, };
static int top = -1;

void push(char ch)
{
	if(is_full())
	{
		puts("stack is full."); 
		return; 
	}
	
	//is not full
	top++;
	stack[top] = ch;
}

char pop() //return val that top indicates, and remove the val.
{
	if(is_empty())
	{
		puts("stack is empty."); 
		return -1; //error 
	}
	char tmp = stack[top];
	top--;
	return tmp;
}

char peek() //return val that top indicates
{
	return stack[top];
}

bool is_empty()
{
	return (top == -1);
}

bool is_full()
{
	return (top == (MAX_CAPACITY - 1));
}