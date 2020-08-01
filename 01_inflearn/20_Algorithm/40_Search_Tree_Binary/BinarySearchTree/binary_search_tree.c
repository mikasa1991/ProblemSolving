#include "binary_search_tree.h"

void BST_print(Node* root)
{
	if(root == NULL)
		return;

	//pre_order_traversal
	printf("%d ", root->value);

	//recursive case
	BST_print(root->left_child);
	BST_print(root->right_child);

	//base case
}

/*
 easy
 */
Node* BST_insert(Node* t_node, Node* parents_node, int value)
{
	if(t_node == NULL)	//base case
	{
		t_node = (Node*)malloc(sizeof(Node));
		//init
		t_node->parents = parents_node;
		t_node->value = value;
		t_node->left_child = NULL;
		t_node->right_child = NULL;
		return t_node;
	}
	else	//recursive case
	{
		if(t_node->value > value)
			t_node->left_child  = BST_insert(t_node->left_child, t_node, value);
		else
			t_node->right_child = BST_insert(t_node->right_child, t_node, value);
	}

	return t_node;	//base case; 메인함수에서 처음으로 콜했을 때의 반환값을 root로 하기 위함.
}

//같은 값을 가지는 노드는 없다고 가정
/*
 easy
 */
Node* BST_search(Node* t_node, int value)
{
	//base case
	if(t_node == NULL)
		return NULL;

	if(t_node->value == value) 
		return t_node;

	///recursive case
	else if(t_node->value > value) 
		BST_search(t_node->left_child, value);
	
	else 
		BST_search(t_node->right_child, value);

}

Node* BST_minimum(Node* t_node)
{
	if(t_node == NULL)	//if root is NULL
		return NULL;

	while(t_node->left_child != NULL)
		t_node = t_node->left_child;

	return t_node;
}

Node* BST_maximum(Node* t_node)
{
	if(t_node == NULL)	//if root is NULL
		return NULL;

	while(t_node->right_child != NULL)
		t_node = t_node->right_child;

	return t_node;
}

/*
successor란, key[x]보다 크면서 가장 작은 키를 가진 노드(나보다 크면서 가장 가까운 노드); 반대개념은 predecessor임.
case1. 오른쪽 부트리가 있는 경우, 그 부트리에서 최소값을 가지는 노드를 의미함.
case2. 오른쪽 부트리가 없는 경우, 부모를 따라 루트까지 올라가는 중에,
       처음으로 누군가를 왼쪽 자식으로 만드는 부모노드를 의미함.
       (단, 이를 만족하는 부모노드가 없으면 NULL을 반환하면 됨)
*/
Node* BST_successor(Node* root, int value)
{
	Node* t_node = BST_search(root, value);
	//case1. Exist; if the sub tree right_sided
	if(t_node->right_child != NULL) 
		return BST_minimum(t_node->right_child);
	
	/*
	//case2. Not exist; if the sub tree right_sided
	  부모노드가 NULL이거나 또는 처음으로 임시노드가 부모노드의 왼쪽 자식노드가 될 때,
	*/
	Node* p_node = t_node->parents;
	while(p_node != NULL && t_node == p_node->right_child)
	{
		t_node = p_node;
		p_node = p_node->parents;
	}
	 
	return p_node;
}

/*
difficult

삭제할 노드의
case1.자식노드가 없는 경우
 just delete

case2.자식노드가 1개인 경우
 자신의 자식 노드를 원래 자신의 위치로!

case3.자식노드가 2개인 경우
	삭제하려는 노드의 successor를 삭제하려는 노드로 복사한다.
	그 다음, successor노드를 대신 삭제한다.
	이 경우 successor는 자식을 가진다고 해도 최대 1개밖에 못가지므로, case1과 case2에 수렴한다.
	(왜냐하면 successor자체가 오른쪽 부트리가 있는 경우에 해당했기 때문이다)
*/
Node* BST_delete(Node* root, int value)
{
	Node* t_node = BST_search(root, value);
	Node* y_node = NULL;	//the node you wanna delete
	Node* x_node = NULL;	//the child of y_node

	//찾고자 하는 노드가 없는 경우, 리턴
	if(t_node == NULL)
	{
		puts("can not find the node input");
		return NULL;
	}

	if(t_node->left_child == NULL || t_node->right_child == NULL)	//case1, case2
		y_node = t_node;
	else															//case3
		y_node = BST_successor(root, value);

//deleting y_node; cf.BST_delete.jpg
//////////////////////////////////////////////////////////////////	
	if(y_node->left_child != NULL)
		x_node = y_node->left_child;
	else
		x_node = y_node->right_child;

	//double linked list_link_1
	if(x_node != NULL)			//case2, case3 
		x_node->parents = y_node->parents;
	//else if(x_node == NULL)	//case1. x_node = NULL
		//pass

	//이 경우에는 root_node의 부모노드가 당연히 없으니까, 노드끼리 linking하는게 필요하지 않지
	if(y_node->parents == NULL)	//if y_node is root_node,
		root = x_node;
	//double linked list_link_2
	else if(y_node == y_node->parents->left_child)
		y_node->parents->left_child = x_node;
	else
		y_node->parents->right_child = x_node;
//////////////////////////////////////////////////////////////////
	
	//case3
	//copy "the val of the successor" to "the node you wanna delete"
	if(y_node != t_node)
		t_node->value = y_node->value;

	return y_node;
}