typedef struct s_btree
{
	int value;
	struct s_btree *right;
	struct s_btree *left;
}	t_btree;
