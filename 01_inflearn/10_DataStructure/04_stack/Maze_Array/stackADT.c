#include "stackADT.h"

void terminate(const char* msg)
{
	puts(msg);
	exit(1);
}

void push(stack* s, item i)
{
	if(is_full(s))
	{
		reallocate(s);
	}
	s->top = (s->top) + 1;
	s->contents[s->top] = i;
}

item pop(stack* s)
{
	int index = s->top;
	if(is_empty(s))
	{
		terminate("Error in pop: stack is empty.");
	}
	s->top = (s->top) - 1;
	return s->contents[index];
}

item peek(stack* s)
{
	if(is_empty(s))
	{
		terminate("Error in peek: stack is empty.");
	}
	return s->contents[s->top];
}

stack* create_stack_instance() //stack is the pointer variable
{
	stack* s = (stack*)malloc(sizeof(stack));
	
	//if stack allocate fail
	if(s == NULL)
	{
		terminate("Error in create: stack could not be created.");
	}

	//if stack allocate success
	s->contents = create_item_instance(s);

	s->top = -1;
	s->size = INIT_CAPACITY;
	return s;
}

item* create_item_instance(stack* s)
{
	item* it = (item*)malloc(sizeof(item) * INIT_CAPACITY);
	
	//if it allcate fail
	if(it == NULL)
	{
		free(s);
		terminate("Error in create: stack could not be created.");
	}

	//if it allocate success
	for(int j = 0; j < INIT_CAPACITY; j++)
	{
		it[j].x = 0;
		it[j].y = 0;
		it[j].dir = 0;
	}
	return it;
}

void destroy(stack* s)	//allocated array delete
{
	free(s->contents);
	free(s);
}

void make_empty(stack* s)
{
	s->top = -1;
}

bool is_empty(stack* s)
{
	return ( s->top == -1 );
}

bool is_full(stack* s)
{
	return ( s->top == (s->size) - 1 );
}

void reallocate(stack* s)	//origin_size * 2 allocate
{
	item* tmp = (item*)malloc(2 * (s->size) * sizeof(item));
	if(tmp == NULL)
	{
		terminate("Error in create: stack could not be created.");
	}

	for(int i = 0; i < s->size; i++)
	{
		tmp[i] = s->contents[i];	//copy items
	}
	free(s->contents);	//delete the pre array
	s->contents = tmp;
	s->size *= 2;
}