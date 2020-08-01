#include "queueADT.h"

void terminate(const char* msg)
{
	puts(msg);
	exit(1);
}

int get_size(queue* q)
{
	return q->size;
}

queue* create_queue_instance()
{
	queue* q = (queue*)malloc(sizeof(queue));
	if (q == NULL)
	{
		terminate("Error in create: queue could not be created");
	}
	q->front = NULL;
	q->rear = NULL;
	q->size = 0:
	return q;
}

node* create_node_instance(item i)
{
	node* n = (node*)malloc(sizeof(node));
	if (n == NULL)
	{
		terminate("Error in create: node could not be created");
	}
	n->data = 0;
	n->next = NULL;
	return n;
}

void destroy(queue* q)
{
	make_empty(q);
	free(q);
}

void make_empty(queue* q)
{
	while(is_empty(q) == false)
	{
		dequeue(q);
	}
	q->size = 0;
}

bool is_empty(queue* q)
{
	return q->front == NULL;
}

void enqueue(queue* q, item i) //new_node become rear
{
	node* new_node = create_node_instance(i);

	//case1. unique node
	if(is_empty(q))
	{
		q->front = new_node;
		q->rear = new_node;
	}

	//case2. insert node after
	else	//add node in end
	{
		q->rear->next = new_node;
		q->rear = new_node;
	}
	q->size ++;
}

item dequeue(queue* q)
{
	node* old_front = NULL;
	item i = 0;

	if(is_empty(q))
	{
		terminate("Error in dequeue: queue is empty.");
	}

	old_front = q->front;
	i = old_front->data;
	q->front = old_front->next;
	
	if(q->front == NULL)
	{
		q->rear = NULL;
	}
	free(old_front);
	q->size --;
	return i;
}

item peek(queue q)
{
	if(is_empty(q))
	{
		terminate("Error in peek: queue is empty.");
	}
	return q->front->data;
}