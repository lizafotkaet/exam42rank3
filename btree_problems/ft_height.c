#include <stdlib.h>
#include "ft_height.h"

int btree_height(t_btree *root)
{
	int	left_height; 
	int	right_height;
		
	if (root == NULL)
		return (0);
	left_height = btree_height(root->left);
	right_height = btree_height(root->right);
	if (left_height > right_height)
		return (left_height + 1);
	else
		return (right_height + 1);
}

/* test

// создать ноду
t_btree *new_node(int value)
{
    t_btree *node = malloc(sizeof(t_btree));

    node->value = value;
    node->left = NULL;
    node->right = NULL;
    return (node);
}

// освободить все дерево
void free_btree(t_btree *root)
{
    if (root == NULL)
        return;
    free_btree(root->left);   // освобождаем поветочно
    free_btree(root->right);  // 
    free(root);               // корневая нода в конце освобождается
}
#include <stdio.h>
int main(void)
{
	t_btree *root = new_node(1);
	root->left = new_node(2);
	root->right = new_node(3);
	root->left->left = new_node(4);
	root->left->left->left = new_node(5);

	printf("Height of tree: %d\n", btree_height(root));
	return 0;
}

*/