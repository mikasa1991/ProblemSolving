#ifndef STACK_H
#define STACK_H

#define MAX_CAPACITY 100

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct _node node;

typedef struct _node
{
	char data;	//1Byte
	node* next;
}node;

//function declared
node* create_node(char item);
void push(char item);
char pop();
char peek();
bool is_empty();

#endif