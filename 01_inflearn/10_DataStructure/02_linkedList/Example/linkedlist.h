#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _node node;
typedef struct _node
{
	char* data;
	node* next;
}node;

//variables declared
extern node* head;	//head is global variable

//functions declared
node* create_node_instance(char* item);
void add_first(char* item); 					//head is global variables
void add_first_2(node** ptr_head, char* item);	//head is local variables
node* add_first_3(node* head, char* item);		//head is local variables
int add_after(node* prev, char* item); 			//if success, return 1. otherwise, return 0
node* remove_first();
node* remove_after(node* prev);
node* find_item(char* item);
node* find_index(int index);
int add(int index, char* item);
node* remove_index(int index);
node* remove_item(char* item);
void add_to_ordered_list(char* item);
void print_node(node* head);

#endif //LINKEDLIST_H