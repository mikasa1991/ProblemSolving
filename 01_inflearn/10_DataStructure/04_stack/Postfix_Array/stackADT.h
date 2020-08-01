#ifndef STACKADT_H
#define STACKADT_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define INIT_CAPACITY 100

typedef int item;					//it is good to change return type

typedef struct _stack
{
	item* contents; //array
	int top;
	int size;
}stack;

stack* create_stack_instance();
item* create_item_instance();
void destroy(stack* s);
void make_empty(stack* s);
bool is_empty(stack* s);
bool is_full(stack* s);
void push(stack* s, item i);
item pop(stack* s);
item peek(stack* s);
void reallocate(stack* s);

#endif	//STACKADT_H