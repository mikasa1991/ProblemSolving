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
	if(q == NULL)
	{
		terminate("Error in create: queue could not be created.");
	}
	q->contents = create_item_instance(q);

	q->front = 0;
	q->rear = -1;
	q->size = 0;
	q->capacity = INIT_CAPACITY;	//the size of the item array
	return q;
}

item* create_item_instance(queue* q)
{
	item* it = (item*)malloc(INIT_CAPACITY*sizeof(item));
	if(it == NULL)
	{
		free(q);
		terminate("Error in create: items could not be created.");
	}

	for(int j = 0; j < INIT_CAPACITY; j++)
	{
		it[j].x = 0;
		it[j].y = 0;
	}

	return it;
}

void destroy(queue* q)
{
	free(q->contents);
	free(q);
}

void make_empty(queue* q)
{
	q->front = 0;
	q->rear = -1;
	q->size = 0;
}

bool is_empty(queue* q)
{
	return q->size == 0;
}

bool is_full(queue* q)
{
	return q->size == q->capacity;
}

void enqueue(queue* q, item i)
{
	if(is_full(q))
	{
		reallocate(q);
	}
	q->rear = (q->rear + 1) % (q->capacity);
	q->contents[q->rear] = i;
	q->size ++;
}

item dequeue(queue* q)
{
	if(is_empty(q))
	{
		terminate("Error in dequeue: queue is empty.");
	}
	item result = q->contents[q->front];
	q->front = (q->front + 1) % (q->capacity);
	q->size --;
	return result;
}

item peek(queue* q)
{
	if(is_empty(q))
	{
		terminate("Error in peek: queue is empty.");
	}
	return q->contents[q->front];
}

void reallocate(queue* q)
{
	item* tmp = (item*)malloc(2 * q->capacity * sizeof(item));
	if(tmp == NULL)
	{
		terminate("Error in create: queue could not be expanded.");
	}

	int j = q->front;
	for(int i = 0; i < q->size; i++)
	{
		tmp[i] = q->contents[j];
		j = (j+1)%(q->capacity);
	}
	free(q->contents);
	q->front = 0;
	q->rear = q->size - 1;
	q->contents = tmp;
	q->capacity *= 2;
}