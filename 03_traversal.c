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
Tree *init(Tree* t) 
{	
	t = malloc(sizeof(Tree)); 
	t->root = 0;
	t->size = 0;
	return t;
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

int LNR(Node *n) 
{
	if (n == NULL)
		return -1;

	LNR(n->left);
	LNR(n->right);

	printf("%d ", n->data);

	return 0;
}

int main()
{
	Tree *tree = init(tree);

	int n, i;
	for (i = 0; i < 7; i++) 
	{
		scanf("%d", &n);
		insert(tree, n);
	}
	Node *node = tree->root;
	LNR(node);

	printf("\n");

	return 0;
}