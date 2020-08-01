#ifndef BINARY_TREE_TRAVERSAL_H
#define BINARY_TREE_TRAVERSAL_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX 20

typedef struct _Node Node;
typedef struct _Node{
	char name;
	Node* left;
	Node* right;
}Node;

//global variables
extern Node input[MAX];

//function declare
int insert_next(char data);
void print_binary_tree();
void pre_order_traversal(Node* root);
void in_order_traversal(Node* root);
void post_order_traversal(Node* root);
//void level_order_traversal(Node* root);
#endif