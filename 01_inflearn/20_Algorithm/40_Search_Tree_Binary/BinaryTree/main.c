//#include "binary_tree_traversal.h"

//complete binary tree
#include "queue.h"

void main()
{
	char data[] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o'};
	int n = sizeof(data) / sizeof(char);

	for(int i = 0; i < n; i++)
	{
		insert_next(data[i]);
	}

	puts("<Binary Tree INPUTED>");
	print_binary_tree();

	printf("\npre  order traversal: ");
	pre_order_traversal(input+0);

	printf("\nin   order traversal: ");
	in_order_traversal(input+0);

	printf("\npost order traversal: ");
	post_order_traversal(input+0);

	printf("\nlvl  order traversal: ");
	level_order_traversal(input+0);
	puts("");
}