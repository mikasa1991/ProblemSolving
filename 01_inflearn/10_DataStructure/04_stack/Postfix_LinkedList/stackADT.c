#include "stackADT.h"

void terminate(const char* msg)
{
	puts(msg);
	exit(EXIT_FAILURE);
}

stack* create_stack_instance()	//create top
{
	stack* s = (stack*)malloc(sizeof(stack));
	if(s == NULL)
	{
		terminate("Error in create: stack could not be created.");
	}
	s->top = NULL;
	return s;
}

node* create_node_instance(int item)
{
	node* n = (node*)malloc(sizeof(node));
	if(n == NULL)
	{
		terminate("Error in create: node could not be created.");
	}
	n->data = item;
	n->next = NULL;
	return n;
}

void destroy(stack* s)
{
	make_empty(s);
	free(s);
}

void make_empty(stack* s)	//until empty, do pop!
{
	while(!is_empty(s))	//if stack is not empty
	{
		pop(s);
	}
}

bool is_empty(stack* s)
{
	return s->top == NULL;
}

void push(stack* s, item i)
{
	node* new_node = create_node_instance(i);

	new_node->next = s->top;
	s->top = new_node;
}

item pop(stack* s)
{
	node* old_top = NULL;
	item tmp = 0;

	if(is_empty(s))
	{
		terminate("Error in pop: stack is empty.");
	}

	old_top = s->top;
	tmp = old_top->data;
	s->top = old_top->next;
	free(old_top);
	return tmp;
}

item peek(stack* s)
{
	if(is_empty(s))
	{
		terminate("Error in peek: stack is empty.");
	}
	return s->top->data;
}