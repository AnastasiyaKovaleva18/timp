#include <stdio.h>
#include <stdlib.h>

// структура узла списка
typedef struct Node_t 
{
	struct Node_t *next;
	int value;
} Node_t;

// сам список
typedef struct List 
{		
	struct Node_t* head;	
} List;

// инициализация списка
void init(List* list, int value) 
{
	struct Node_t* current = (Node_t*)malloc(sizeof(Node_t));
	current->value = value;
	current->next = 0;
	list->head = current;
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
			return 0;
	}
	return current;
}

// проверка списка на пустоту
int isEmpty(List* list) 
{
	return list->head == 0;
}

// очистка списка
int clear(List* list) 
{
	if (isEmpty(list) != 0) 
	{
		Node_t *tmp = list->head;
		Node_t *temp = 0;
		while (tmp != NULL)
		{
			temp = tmp->next;
			free(tmp);
			tmp = temp;
		}
		list->head = NULL;
	}
}

// вставка значения в начало списка
int push_front (List* list, int value) 
{
	if (isEmpty(list) == 1)
		init (list, value);
	else 
	{
		Node_t *current = (Node_t*)malloc(sizeof(Node_t));
		current->value = value;
		current->next = list->head;
		list->head = current;
	}
	return 0;
}

// вставка значения в конец списка
int push_back(List* list, int value) 
{
	if (isEmpty(list) != 1) 
	{
		Node_t* current = (Node_t*)malloc(sizeof(Node_t));
		current->value = value;
		current->next = NULL;
		
		Node_t* temp = list->head;
		
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = current;
	}
	else 
		init (list, value);

	return 0;
}

// удаление элемента
void _rmvElem(List* list, Node_t *temp) 
{
	if (temp != NULL) 
	{
		if (temp == list->head) 
		{
			list->head = temp->next;
		}
		else 
		{
			Node_t *node = (Node_t*)malloc(sizeof(Node_t));
			node = list->head;
			
			while (node->next != temp)
				node = node->next;
			node->next = temp->next;
		}
		free(temp);
	}
}

// удаление первого элемента с указанным значением
int removeFirst (List* list, int value) 
{
	Node_t* temp = find(list, value);

	if (temp != NULL)
	{
		_rmvElem(list, temp);
		return 0;
	}
	return -1;
}

// вставка после указанного узла
int insertAfter (List* list, int n, int value) 
{
	Node_t *current = malloc(sizeof(Node_t));
	current->value = value;

	Node_t* tmp = list->head;
	Node_t* pred_tmp = list->head;
	
	for (int i = 1; i < (n + 1); i++) 
	{
		pred_tmp = tmp;
		tmp = tmp->next;
		if (tmp == NULL) 
			return -1;
	}
	pred_tmp->next = current;
	current->next = tmp;

	return 0;   
}

// вывод элементов списка
void print(List* list) 
{
	Node_t* current = list->head;
	
	while (current->next != NULL) 
	{
		printf("%d ", current->value);
		current = current->next;
	}
	printf("%d\n", current->value);
}

int main()
{
	int n, a;
	/*Создание экземпляра списка*/
	List* list=(List*)malloc(sizeof(List));	
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
	List* num = (List*)malloc(sizeof(List)); // Список для bool
	for (int i = 0; i < 3; i++) {
		scanf("%d",&k);

		if (find(list, k)!= 0)
			push_front(num, 1);
		else 
			push_front(num, 0);
	}
	print(num);

	/*Вставка в конец списка*/
	int m;
	scanf("%d", &m);
	push_back(list, m);
	print(list);

	/*Вставка в начало списка*/
	int t;
	scanf("%d", &t);
	push_front(list, t);
	print(list);

	/*Вставка x после j-ого элемента*/
	int j, x;
	scanf("%d%d", &j, &x);
	insertAfter(list, j, x);
	print(list);

	/*Удаление первого элемента, хранящего z*/
	int z;
	scanf("%d", &z);
	removeFirst(list, z);
	print(list);

	/*Очистка списка*/
	clear(list);

	return 0;
}