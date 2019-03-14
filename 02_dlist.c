#include <stdio.h>
#include <stdlib.h>

// структура узла списка
typedef struct Node_t 
{
	struct Node_t *next;
	struct Node_t *prev;
	int value;
} Node_t;

// сам список
typedef struct List 
{		
	struct Node_t* head;
	struct Node_t* tail;	
} List;

// проверка списка на пустоту
int isEmpty(List* list) 
{
	return list->head == NULL && list->tail == NULL;
}

// инициализация списка
void init(List* list, int value) 
{
	Node_t* current = (Node_t*)malloc(sizeof(Node_t));

	current->value = value;
	current->next = NULL;
	current->prev = NULL;

	list->head = current;
	list->tail = current;
}

// очистка списка
int clear(List* list) 
{
	if (isEmpty(list) != 0) 
	{
		Node_t *tmp = list->head;
		Node_t *temp = NULL;
		
		while (tmp != NULL)
		{
			temp = tmp->next;
			free(tmp);
			tmp = temp;
		}
		list->head = NULL;
		list->tail = NULL;
	}
}

// поиск узла по значению
Node_t* find(List* list, int value) 
{
	Node_t *current = list->head;
	
	while (current->value != value) 
	{
		if (current->next != NULL)
			current = current->next;
		else 
			return NULL;
	}
	return current;
}

// поиск узла по значению с конца
Node_t* find_invers(List* list, int value) 
{
	Node_t *current = list->tail;
	
	while (current->value != value) 
	{
		if (current->prev != NULL)
			current = current->prev;
		else 
			return NULL;
	}
	return current;
}

// вставка значения в конец списка
int push_back(List* list, int value) 
{
	if (isEmpty(list) == 1)
		init (list, value);
	else 
	{
		Node_t* current = (Node_t*)malloc(sizeof(Node_t));

		current->value = value;
		current->prev = list->tail;
		current->next = NULL;
		
		list->tail = current;
		current->prev->next = current;
	}
	return 0;
}

// вставка значения в начало списка
int push_front(List* list, int value) 
{
	if (isEmpty(list) == 1)
		init (list, value);
	else 
	{
		Node_t *current = (Node_t*)malloc(sizeof(Node_t));

		current->value = value;
		current->prev = NULL;
		current->next = list->head;
		current->next->prev = current;

		list->head = current;
	}
	return 0;
}

// вставка после указанного узла
int insertAfter	(List* list, int n, int value) 
{
	Node_t *current = list->head;

	for (int i = 1; i < n; ++i) 
	{
		current = current->next;
		if (current == NULL) 
			return -1;
	}
	Node_t *tmp = malloc(sizeof(Node_t));

	tmp->value = value;
	tmp->next = current->next;
	tmp->prev = current;

	current->next->prev = tmp;
	current->next = tmp;
	
	return 0;
}

// вставка до указанного узла
int insertBefore(List* list, int n, int value) 
{
	Node_t *current = list->head;

	for (int i = 1; i < n; i++) 
	{
		current = current->next;
		if (current == NULL) 
			return -1;
	}
	Node_t *node = malloc(sizeof(Node_t));

	node->value = value;
	node->prev = current->prev;
	node->next = current;

	current->prev = node;
	node->prev->next = node;

	return 0;
}

// удаление элемента
void _rmvElem(List* list, Node_t *temp) 
{
	if (temp != NULL) {

		if (temp == list->head && temp == list->tail) 
		{
			clear(list);
			return;
		} 
		if (temp == list->head) 
		{
			list->head = temp->next;
			temp->next->prev = NULL;
		} 
		else if (temp == list->tail) 
		{
			list->tail = temp->prev;
			temp->prev->next = NULL;
		} 
		else if (temp != list->head && temp != list->tail) 
		{
			temp->next->prev = temp->prev;
			temp->prev->next = temp->next;
		}
		free(temp);
	}
}

// удаление последнего элемента с указанным значением
int removeLast(List* list, int value) 
{
	Node_t* temp = find_invers(list, value);

	if (temp != NULL)
	{
		_rmvElem(list, temp);
		return 0;
	}
	return -1;
}

// удаление первого элемента с указанным значением
int removeFirst(List* list, int value) 
{
	Node_t* temp = find(list, value);

	if (temp != NULL)
	{
		_rmvElem(list, temp);
		return 0;
	}
	return -1;
}

// вывод элементов списка
void print(List* list) 
{
	Node_t* current = list->head;
	
	while (current->next != NULL) {
		printf("%d ", current->value);
		current = current->next;
	}
	printf("%d\n", current->value);
}

// вывод элементов списка с конца
void print_invers (List* list) 
{
	Node_t* current = list->tail;
	while (current->prev != NULL) {
		printf("%d ", current->value);
		current = current->prev;
	}

	printf("%d\n", current->value);
}

int main(int argc, char const *argv[])
{
	int n, a;
	/*Создание экземпляра списка*/
	List* list = (List*)malloc(sizeof(List));	

	/*Заполняем список*/
	scanf("%d", &n);
	for (int i = 0; i < n; i++) 
	{
		scanf("%d", &a);
		push_back(list, a);
	}
	print(list);
	
	/*нахождение Ki*/
	int k;
	List* num = (List*)malloc(sizeof(List));
	for (int i = 0; i < 3; i++) 
	{
		scanf("%d",&k);

		if (find(list, k)!= NULL)
			push_front(num, 1);
		else 
			push_front(num, 0);
	}
	print(num);

	/*Вставка в конец списка*/
	int m;
	scanf("%d", &m);
	push_back(list, m);
	print_invers(list);

	/*Вставка в начало списка*/
	int t;
	scanf("%d", &t);
	push_front(list, t);
	print(list);

	/*Вставка x после j-ого элемента*/
	int j, x;
	scanf("%d%d", &j, &x);
	insertAfter(list, j, x);
	print_invers(list);

	/*Вставка y после u-ого элемента*/
	int u, y;
	scanf("%d%d", &u, &y);
	insertBefore(list, u, y);
	print(list);

	/*Удаление первого элемента, хранящего z*/
	int z;
	scanf("%d", &z);
	removeFirst(list, z);
	print_invers(list);

	/*Удаление последнего элемента, хранящего r*/
	int r;
	scanf("%d", &r);
	removeLast(list, r);
	print(list);

	/*Очистка списка*/
	clear(list);

	return 0;
}
