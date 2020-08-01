#include "linkedlist.h"

/*
linkedlist의 경우, node를 추가하거나 삭제할 때,
앞의 node의 주소를 알아야 뒤에 추가하거나 삭제할 수 있다.(case2)
그런데 내가 추가하려는게 head node인 경우에는 참조할 앞의 node가 없다.(case1)
따라서 2가지 경우에 있어서 로직을 나눠서 함수를 만드는게 좋다.

case1. add_first / remove_first
case2. add_after / remove_after
*/

node* head = NULL;	//head is global variable

node* create_node_instance(char* item)
{
	node* p = (node*)malloc(sizeof(node));
	p->data = item;
	p->next = NULL;
	return p;
}

/*
 *if head is global variable, how can i add a new node in front?
 */
void add_first(char* item)
{
	node* new_node = create_node_instance(item);
	new_node->next = head;
	head = new_node;
}

/*
 *if head is local variable, how can i add a new node in front?
 */
//Call: add_first(&head, item_to_store)
//head is pointer variables, so need to pointer of pointer
void add_first_2(node** ptr_head, char* item)
{
	node* new_node = create_node_instance(item);
	new_node->next = *ptr_head;
	*ptr_head = new_node;
}

//Call: head = add_first(head, item_to_store)
//return the address of first node
node* add_first_3(node* head, char* item)
{
	node* new_node = create_node_instance(item);
	new_node->next = head;
	return new_node;
}

/*
 *insert node betweens nodes
 */
//we need to know about the address of prev node
int add_after(node* prev, char* item)
{
	if(prev == NULL)
	{
		return 0;	//error
	}
	node* new_node = create_node_instance(item);
	new_node->next = prev->next;
	prev->next = new_node;
	return 1;		//success
}

/*
 *remove node on the front
 *return the address of node removed
 */
node* remove_first()
{
	//if first node not exists
	if(head == NULL)
	{
 		return NULL;
 	}
 
 	//if first node exist
 	node* tmp = head;
 	head = head->next;
 	return tmp;
 }

/*
 *remove the node between nodes
 *return the address of node removed
 */
node* remove_after(node* prev)
{
	//if prev node not exist
	if(prev == NULL)
	{
		puts("prev node not exist!");
		return NULL;
	}

	node* tmp = prev->next;
	
	//if the node (you wanna delete) not exist
	if((tmp == NULL))
	{
		puts("the node you wanna delete not exist!");
		return NULL;
	}

	//if the node (yo wanna delete) exist
	prev->next = tmp->next;
	return tmp;
}

/*
 *traverse from head

 노드를 순회하면서 일치하는 것을 찾는 시점에, 일치한 노드의 주소를 반환한다.
 순회가 종료했음에도 일치하는 것이 없는 경우에는 NULL을 반환한다.
 */
node* find_item(char* item)
{
	node* p = head;
	while(p != NULL)
	{
		if(strcmp(p->data, item) == 0)
		{
			puts("Found:");			 //for debug
			printf("%s\n", p->data); //for debug
			return p;
		}
		p = p->next;
	}
	puts("we can't find your item");
	return NULL;
}

/*
 *return address of index node

입력받은 인덱스까지 이동한다.
이동 완료 후에, p가 존재하는 노드 범위를 벗어나 있다면
이는 존재하는 노드보다 인덱스 범위가 초과한 것으로 에러를 발생시켜야한다.
 */
node* find_index(int index)
{
	//index input error
	if(index < 0)
	{
		return NULL;
	}

	//index >= 0
	node* p = head;
	for(int i = 0; (i < index) && (p != NULL); i++)
	{
		p = p->next;
	}

	 //index range exceed!
	if(p == NULL)
	{
		puts("index range exceed!");
		return NULL;
	}

	 //found!
	puts("Found:");			 //for debug
	printf("%s\n", p->data); 				 //for debug
	return p;
}

/*
 *insert node where the specific index
 */
int add(int index, char* item)	//add_index
{
	//index input error
	if(index < 0)
	{
		return 0;
	}

	//first node
	else if(index == 0)
	{
		add_first(item);
		return 1;	//success
	}

	//if index > 0,
	else
	{
		//prev는 노드 주소 또는 NULL
		node* prev = find_index(index-1);
		
		/*
		if(prev != NULL)
		{
			add_after(prev, item);
			return 1;	//success
		}
		return 0;	//fail
		*/
		
		//case1. prev는 노드 주소
		if(add_after(prev, item) == 1)	//prev is not NULL
		{
			return 1;	//success
		}
		
		//case2. prev는 NULL
		else
		{
			return 0;	//fail
		}
	}
}

/*
 *remove node where the specific index
 */
node* remove_index(int index)
{
	//index input error
	if(index < 0)
	{
		return NULL;
	}

	//first node
	else if(index == 0)
	{
		return remove_first();
	}

	//if index > 0
	else
	{
		//prev는 노드 주소 또는 NULL
		node* prev = find_index(index-1);
		
		/*
		if(prev == NULL)
		{
			return NULL;
		}
		else
		{
			return remove_after(prev);
		}
		*/
		return remove_after(prev);	//노드 주소 또는 NULL
	}
}

/*
 *remove node where the item is saved
 */
node* remove_item(char* item)
{
	node* p = head;
	node* q = NULL;

	while(p != NULL && strcmp(p->data, item) != 0)
	{
		q = p;	//q is the prev of p
		p = p->next;
	}

	/*
	//case1. Nothing
	if((p == NULL) && (q == NULL))
	{
		return NULL;
	}
	*/
	printf("p: %p, q: %p\n", p, q);
	
	//case1. Not exist any node or(p == NULL && q == NULL) 
	//Can't find input in items   (p == NULL)
	if(p == NULL)
		return NULL;
	
	//case2. item is equal to head
	if((p == head) && (q == NULL))
		return remove_first();

	//case3.
	else	//p node is the next node of q
		return remove_after(q);
}

/*
 *add the node in ordered list
 */
void add_to_ordered_list(char* item)
{
	node* p = head;
	node* q = NULL;

	/*
	strcmp(a1, a2)
	가나다 순으로 왼쪽인자가 더 크면 양의 값 반환
	가나다 순으로 오른쪽인자가 더 크면 음의 값 반환
	*/
	//p is not NULL, and 입력받은 item의 가나다 순이 같거나 큰 경우
	while( (p != NULL) && (strcmp(p->data, item) <= 0) )
	{
		q = p;
		p = p->next;
	}

	//if any node exist, or
	//if input node has to be first node by assending order. 
	if(q == NULL)
	{
		add_first(item);
	}

	else
	{
		add_after(q, item);
	}
}

void print_node(node* head)
{
	node* p = head;
	int i = 0;
	while(p != NULL)
	{
		printf("%d: %s\n", i, p->data);
		p = p->next;
		i++;
	}
}
