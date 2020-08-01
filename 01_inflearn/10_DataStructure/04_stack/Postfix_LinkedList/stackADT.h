#ifndef STACKADT_H
#define STACKADT_H
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int item;					//it is good to change return type
typedef struct _node node;

typedef struct _node
{
	item data;
	node* next;
}node;

typedef struct _stack
{
	node* top;
}stack;

stack* create_stack_instance();
node* create_node_instance(int item);
void destroy(stack* s);
void make_empty(stack* s);
bool is_empty(stack* s);
bool is_full(stack* s);
void push(stack* s, item i);
item pop(stack* s);
item peek(stack* s);
void reallocate(stack* s);

#endif