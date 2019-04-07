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

// Инициализация пустого дерева
void init(Tree* t) 
{
	t->root = 0;
	t->size = 0;
}

// Удалить минимальный узел
int removeMin(Node *n, Tree *t)
{
	t->size--;

	if (t->size != 1) {

		while (n->left != 0)
			n = n->left;

		if (n->right != 0) {
			n->right->parent = n->parent;

			if (n == t->root)
				t->root = n->right;
			else 
				n->parent->left = n->right;
		}
		else 
			n->parent->left = 0;
		
		int data = n->data;
		free(n);

		return data;
	} 
	else 
	{
		t->root = 0;
		t->size = 0;
		free(t->root);

		return 0;
	}
}

// Удалить все элементы из дерева
void clear(Tree *t)
{
	while (t->root != 0)
		removeMin(t->root, t);
}

// Поиск элемента по значению
int find(Tree *t, int data, Node **n)
{
	Node *temp = t->root;

	while (temp != 0)
	{
		if (data < temp->data)
			temp = temp->left;
		else if (data > temp->data)
			temp = temp->right;
		else { 
			*n = temp;

			return 0;
		}
	}
	*n = temp;

	return 1;
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
       
       	if (t->root == 0)
       		return 2;
        t->size++;
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

// Удалить элемент из дерева
int removeElement(Tree* t, int data)
{
	Node *n = t->root;
	if (t->root == 0)
		return 1;

	while (1)
	{
		if (n == 0)
			break;
    	else if (n->data == data)
			break;
		else if (data > n->data)
			n = n->right; 
		else 
			n = n->left;	
	}

	if ((n->left == 0) && (n->right == 0))
	{
		if (n->parent->right->data == n->data)
			n->parent->right = 0;
		else 
			n->parent->left = 0;
	} 
	else if (n->right == 0)
		*n = *n->left;
	else if (n->left == 0)
		*n = *n->right;
	else 
	{
		Node *tmp = n->right;
		Node *temp;
		int k = 0;
		while (1)
		{
			if (tmp != 0) 
			{
				temp = tmp;
				k = tmp->data;
				tmp = tmp->left;
			}
			else 
				break;
		}
		n->data = temp->data;
		n = temp;
		if ((n->left == 0) && (n->right == 0))
		{
			if (n->parent->right->data == n->data)
				n->parent->right = 0;
			else 
				n->parent->left = 0;
		} 
		else if (n->right == 0)
			*n = *n->left;
		else
			*n = *n->right;

	}
	t->size--;
	free(n);
	return 0;
}

// Правое вращение поддерева
int rotateRight(Tree *t)
{
	Node *buf = t->root->left;
	if (buf == 0)
		return 1;
	t->root->left = buf->right;
	buf->right = t->root;
	buf->parent = t->root->parent;
	t->root->parent = buf;
	t->root = buf;
	return 0;
}

// Левое вращение поддерева
int rotateLeft(Tree *t)
{
	Node *buf = t->root->right;
	if (buf == 0)
		return 1;
	t->root->right = buf->left;
	buf->left = t->root;
	buf->parent = t->root->parent;
	t->root->parent = buf;
	t->root = buf;
	return 0;
}

// Вывод узла
void printNode(Node * n, int now, int lvl, int root)
{
	if (now == lvl)
	{
		if (root > 0)
			printf(" ");
		if (n == 0)
			printf("_");
		else
			printf("%d", n->data);
	} 
	else if (n != 0)
	{
		printNode(n->left, now + 1, lvl, root);
		printNode(n->right, now + 1, lvl, root + 1);
	} 
	else 
	{
		printNode(n, now + 1, lvl, root);
		printNode(n, now + 1, lvl, root + 1);
	}
}

// Глубина дерева
int getLevel(Node * n, int lvl)
{
	if (n == 0)
		return lvl;

	int u1 = getLevel(n->left, lvl + 1), 
	u2 = getLevel(n->right, lvl + 1);
	if (u1 > u2)
		return u1;
	else 
		return u2;
}

// Вывод значений из поддерева
void print(Node * n)
{	
	int lvl = getLevel(n, 0), i;
	for (i = 1; i <= lvl; i++)
	{
		printNode(n, 1, i, 0);
		printf("\n");
	}
}

// Вывод всех значений дерева
void printTree(Tree *t)
{
	if (t->root == 0)
		printf("-\n");
	else
    	print(t->root);
}

// Вывод предков и потомков
void display(Node *n, int elem)
{
	if (elem == 0)
	{
		if (n->parent != 0)
			printf("%d ", n->parent->data);
		else 
			printf("_ ");

		if (n->left != 0)
			printf("%d ", n->left->data);
		else 
			printf("_ ");

		if (n->right != 0)
			printf("%d\n", n->right->data);
		else 
			printf("_\n");
	}
	else 
		printf("-\n");
}

int main()
{
	Tree *tree;
	init(tree);

	int a, i;
	for (i = 0; i < 4; i++)
	{
		scanf("%d", &a);
		insert(tree, a);
	}
	printTree(tree);

	for (i = 0; i < 3; i++)
	{
		scanf("%d", &a);
		insert(tree, a);
	}
	printTree(tree);

	int m;
	for (i = 0; i < 2; i++)
	{
		scanf("%d", &m);
		Node *node;
		int unit = find(tree, m, &node);
		display(node, unit);
		
	}
	
	scanf("%d", &m); 
	removeElement(tree, m);
	printTree(tree);

	while (rotateLeft(tree) == 0) {
		rotateLeft(tree);
	} 
	printTree(tree);

	while (rotateRight(tree) == 0) {
		rotateRight(tree);
	} 
	printTree(tree);

	printf("%d\n", tree->size);

	clear(tree);
	printTree(tree);

	return 0;
}