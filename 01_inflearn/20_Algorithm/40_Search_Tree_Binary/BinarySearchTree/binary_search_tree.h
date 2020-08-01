#ifndef BINARY_SEARCH_TREE_H
#define	BINARY_SEARCH_TREE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct _Node Node;
typedef struct _Node
{
	int value;
	Node* left_child;
	Node* right_child;
	Node* parents;
}Node;

//global variables
//Node* g_root = NULL;

//function declares
void BST_print(Node* root);
Node* BST_insert(Node* t_node, Node* parents_node, int value);
Node* BST_search(Node* t_node, int value);
Node* BST_minimum(Node* t_node);
Node* BST_maximum(Node* t_node);
Node* BST_successor(Node* root, int value);
Node* BST_delete(Node* root, int value);
#endif
