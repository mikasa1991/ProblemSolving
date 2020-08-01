#include "binary_tree_traversal.h"

Node input[MAX];
/*
int insert_next(char data)

이진검색트리의 complete한 경우로,
여기서 linked list를 사용할 필요없이 배열로 해서 구현했음.
(굳이 자식관계를 위한 포인터 변수도 필요없지)
*/
int insert_next(char data)
{
	int count = 0;			//to check if it has the son of nodes
	static int index = 0;	//for the input matrix

	//if it is not empty,
	while(input[count].name != 0)
	{
		if(input[count].left == NULL)
		{
			input[index].name = data;
			input[count].left = &input[index];
			index++;
			return 0;
		}
		else if(input[count].right == NULL)
		{
			input[index].name = data;
			input[count].right = &input[index];
			index++;
			return 0;
		}
		else count++;
	}

	//if it is empty,
	input[index++].name = data;
	return -1;
}

void print_binary_tree()
{
	int n = 2;
	while(n < MAX)
	{
		//n = 2,  i = 0; i < 1
		//n = 4,  i = 1; i < 3
		//n = 8,  i = 3; i < 7
		//n = 16, i = 7; i < 15  
		for(int i = n / 2 - 1; i < n - 1; i++)
		{
			printf("%c ", input[i].name);
		}
		puts("");
		n = n * 2;
	}
}

void pre_order_traversal(Node* root)
{
	if(root != NULL)
	{
		printf("%c ", root->name);
		pre_order_traversal(root->left);
		pre_order_traversal(root->right);
	}
}

void in_order_traversal(Node* root)
{
	if(root != NULL)
	{
		in_order_traversal(root->left);
		printf("%c ", root->name);
		in_order_traversal(root->right);
	}
}

void post_order_traversal(Node* root)
{
	if(root != NULL)
	{
		post_order_traversal(root->left);
		post_order_traversal(root->right);
		printf("%c ", root->name);
	}
}