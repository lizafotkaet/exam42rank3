#include <stdlib.h>

int  search_binary_tree(t_btree *root, int value)
{
  int  search_right;
  int  search_left;

  if (root == NULL)
    return (0);
  if (root->value == value)
  {
    return (1);
  }
  else
  {
    search_left = search_binary_tree(root->left, value);
    search_right = search_binary_tree(root->right, value);
    if (search_left == 1)
      return (search_left);
    else if (search_right == 1)
        return (search_right);
    else
        return (0);
  }
}
