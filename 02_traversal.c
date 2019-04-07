#include <stdio.h>
#include <stdlib.h>

// Структура для хранения узла дерева
typedef struct node 
{
	struct node *parent;
	struct node *left;
	struct node *right;
	int data;
} Node;

// Структура для хранения дерева
typedef struct 
{
	Node *root;
	int size;
} Tree;

// Структура для хранения узла очереди
typedef struct nodequeue 
{
	struct nodequeue *next;
	Node *current;
} nodeQueue;

// Структура для хранения  очереди
typedef struct queue 
{
	nodeQueue *first;
	nodeQueue *last;
	int size;
} Queue;

// Вставка в очередь
void push(Queue *q, Node *n) 
{
	nodeQueue *queue = malloc(sizeof(nodeQueue));
	queue->current = n;
	q->size++;

	if (q->first == 0)
	{
		queue->next = 0;
		q->first = queue;
	}
	else 
	{	
		queue->next = q->first;
		q->first = queue;
	}
	q->last = queue;
}

// Очистка очереди
int clearQ(Queue *q) 
{
	if (q->first == 0)
		return -1;

	nodeQueue *tmp1, *tmp2;
	tmp1 = q->first;

	while(tmp1 != 0) 
	{
		tmp2 = tmp1;
		tmp1 = tmp2->next;
		free(tmp2);
	}
	q->first = 0;
	q->last = 0;
	return 0;
}

// Инициализация пустого дерева
void init(Tree* t) 
{
	t->root = 0;
	t->size = 0;
}

// Вставка значения в дерево
int insert(Tree *t, int data)
{
    Node *tmp = 0;

    if (t->root == 0) 
    {	
    	Node *tmp = (Node*)malloc(sizeof(Node));
		tmp->left = tmp->right = 0;
		tmp->data = data;
		tmp->parent = 0;
        t->root = tmp;
        t->size++;

       	if (t->root == 0)
       		return 2;
    }	  
    tmp = t->root;
    while (tmp) 
    {
        if (data > tmp->data) 
        {
            if (tmp->right) 
            {
                tmp = tmp->right;
                continue;
            } 
            else 
            {	
            	t->size++;
            	Node *temp = (Node*)malloc(sizeof(Node));
				temp->left = tmp->right = 0;
				temp->data = data;
				temp->parent = tmp;
                tmp->right = temp;
                return 0;
            }
        } 
        else if (data < tmp->data) 
        {
            if (tmp->left) 
            {
                tmp = tmp->left;
                continue;
            } 
            else 
            {	
            	t->size++;
            	Node *temp = (Node*)malloc(sizeof(Node));
				temp->left = tmp->right = 0;
				temp->data = data;
				temp->parent = tmp;
                tmp->left = temp;
				return 0;
            }
        } 
        else 
            return 1;
    }
}

int NLR(Tree *t) 
{
	if (t == 0)
		return -1;

	Queue *queue = (Queue*)malloc(sizeof(Queue*));;
	Node *n = t->root;
	queue->first = queue->last = 0;
	push(queue, n);

	while (queue->first) 
	{
		if (queue->first != 0) 
		{
			nodeQueue *tmp = queue->first;
			Node *buf = queue->first->current;
			queue->first = queue->first->next;

			if (queue->first == 0)
				queue->last = 0;
			free(tmp);
			queue->size--;
			n = buf;
		}
		else 
			n = 0;

		printf("%d ", n->data);

		if (n->right)
			push (queue, n->right);
		if (n->left)
			push(queue, n->left);
	}
	printf("\n");
	clearQ(queue);

	return 0;
}

int main()
{
	Tree *tree;
	init(tree);

	int n, i;
	for (i = 0; i < 7; i++) 
	{
		scanf("%d", &n);
		insert(tree, n);
	}
	NLR(tree);

	return 0;
}