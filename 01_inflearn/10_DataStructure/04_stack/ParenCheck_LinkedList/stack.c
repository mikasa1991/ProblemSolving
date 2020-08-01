#include "stack.h"

static node* top = NULL;	//top is like head

void push(char item)	//add_node_front
{
	node* p = create_node(item);
	p->next = top;
	top = p;
}

char pop()	//remove_node_front
{
	char result = top->data;
	node* tmp = NULL;

	if(is_empty())	//top == NULL
	{
		return -1;
	}

	tmp = top;
	top = top->next;
	free(tmp);
	return result;
}

char peek()
{
	if(is_empty())
	{
		return -1;
	}
	return top->data;
}

bool is_empty()
{
	return top == NULL;
}

node* create_node(char item)
{
	node* p = (node*)malloc(sizeof(node));
	p->data = item;
	p->next = NULL;
	return p;
}