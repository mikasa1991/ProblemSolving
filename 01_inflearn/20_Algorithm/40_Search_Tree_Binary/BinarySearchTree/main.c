/*
이진탐색트리는 dynamic set의 일종이다.
dynamic set이란, 여러 개의 값을 저장하며, 삽입(insert), 탐색(search), 삭제(delete)의 연산을 지원하는 자료구조다.
for example,
 - binary search tree
 - red black tree
 - AVL tree
 - direct address table
 - hash table

이진탐색트리가 되려면,
1. 이진트리이면서; 항상 complete binary tree가 아니기 때문에 배열이 아닌 링크드 리스트로 구현해야한다.
2. 각 노드에 하나의 키를 저장하며,
3. 각 노드 v에 대해서 그 노드의 왼쪽 부트리에 있는 키들은 key[v]보다 작거나 같고, 
   오른쪽 부트리에 있는 키들은 key[v]보다 크거나 같아야한다.
*/
#include "binary_search_tree.h"

void main()
{
	Node* root = NULL;
	Node* min_node = NULL;
	Node* max_node = NULL;
	Node* successor = NULL;
	root = BST_insert(root, NULL, 5);
	printf("root: %p\n", root);
	root = BST_insert(root, root->parents, 3);
	printf("root: %p\n", root);
	root = BST_insert(root, root->parents, 8);
	printf("root: %p\n", root);
	root = BST_insert(root, root->parents, 1);
	root = BST_insert(root, root->parents, 9);
	root = BST_insert(root, root->parents, 6);
	root = BST_insert(root, root->parents, 7);
	
	BST_print(root);
	puts("");
	//(void)BST_delete(root, 100);
	
	free(BST_delete(root, 5));
	BST_print(root);
	puts("");
	
	free(BST_delete(root, 9));
	BST_print(root);
	puts("");
	
	free(BST_delete(root, 3));
	BST_print(root);
	puts("");

	min_node = BST_minimum(root);
	max_node = BST_maximum(root);
	//successor = BST_successor(root, 9);

	printf("minimum: %d\n", min_node->value);
	printf("maximum: %d\n", max_node->value);
	if(successor != NULL) 
		printf("successor: %d\n", successor->value);
}