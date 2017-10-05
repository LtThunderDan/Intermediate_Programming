
#include <btree/btree.h>
#include <btree/dbg.h>

/*
Just initializes the Tree structure (the node pointer is NULL and the count
	is 0).
*/
Tree* tree_create()
{
	return calloc(1, sizeof(Tree));
}

/*
	Just initializes a TreeNode structure (the node pointers are NULL and
	the integer data is set to payload.  Notice we are using integers
	explicitly this time.
*/
TreeNode* tree_create_node(int payload)
{
	TreeNode* temp = calloc(1, sizeof(TreeNode));
	temp->value = payload;
	return temp;
}

/*
  Frees any nodes in the tree and then frees the tree structure.
  TRUST ME - for these next two procedures, you want to do a post-order
  traversal of the tree to remove nodes.
*/
Tree* tree_destroy(Tree* tree)
{
	tree_clear(tree);
	free(tree);
	return NULL;
}

/*
  Frees any nodes in the tree but leaves the tree structure.
*/
void tree_clear(Tree* tree)
{
	tree_clear_recursive(tree->root);
	tree->root = NULL;
	tree->count = 0;
}

/*
  Recursive call to remove nodes from the tree for the above functions.
  Deallocate nodes in this function.

	if the nodes to the left or the right are not null, free them.
*/
void tree_clear_recursive(TreeNode* node)
{
	if(node->left != NULL)
	{
	  tree_clear_recursive(node->left);
	}
	if(node->right != NULL)
	{
	  tree_clear_recursive(node->right);
	}
	free(node);
}

/*
  Returns the root node in the tree.
*/
TreeNode* tree_root(Tree* tree)
{
	return tree->root;
}

/*
  Returns the number of nodes in the tree.
*/
int tree_count(Tree* tree)
{
	return tree->count;
}

/*
  Finds a node in the tree by value and returns the pointer to the node.
  If no matching node is found, returns NULL.

	while cur, current node, is not NULL, check its value, if value is equal,
	return that node. If value is not equal, go to the left or right depending
	on if greater than or lesser than.
*/
TreeNode* bst_find(Tree* tree, int value)
{
	TreeNode* cur = tree->root;

	while(cur != NULL)
	{
		if (cur->value == value)
		{
			return cur;
		}
		if (value < cur->value)
		{
			cur = cur->left;
		}
		else
		{
			cur = cur->right;
		}
	}
	return NULL;
}

/*
  Finds a successor node in the tree and returns the pointer to the node.
  Assumes the node has a right child (called from bst_remove_value where
  the node to be remove has been checked for children). Cut the successor's
  tie to it's parent but don't reduce the tree count; it's going to be
  reattached by the calling routine.

	if there is no right child, there can't be a successor.

	while there is a left child, set succ to prev and keep moving.
	once we hit the left most child, check the previous right and left.
*/
TreeNode* bst_find_successor(TreeNode* node)
{
	TreeNode* succ = node->right;
	TreeNode* prev = node;

	if(succ == NULL)
	{
		return NULL;
	}

	while (succ->left != NULL)
	{
		prev = succ;
		succ = succ->left;
	}

	if (prev == node)
	{
		prev->right = NULL;
	}
	else
	{
		prev->left = NULL;
	}
	return succ;
}

/*
  Inserts a node in the tree using Binary Search Tree rules.

	If tree's root is null, set the tree's root.

	otherwise, while cur is not NULL, lets find where the node should be.
	Once we find its correct location, we set it in the tree.
	And increase the tree count.
*/
void bst_insert_node(Tree* tree, TreeNode* node)
{
	TreeNode* cur = tree->root;
	TreeNode* prev = NULL;

	if (tree->root == NULL)
	{
		tree->root = node;
	}
	else
	{
		while(cur != NULL)
		{
			prev = cur;

			if (node->value < cur->value)
			{
				cur = cur->left;
			}
			else
			{
				cur = cur->right;
			}
		}

		if (prev->value < node->value)
		{
	    prev->right = node;
		}
		else
		{
			prev->left = node;
		}
	}
	tree->count = tree->count + 1;
}

/*
  Inserts a node in the tree using Binary Search Tree rules after creating
  a node with the passed value.
*/
void bst_insert_value(Tree* tree, int value)
{
	TreeNode* temp = tree_create_node(value);
	bst_insert_node(tree, temp);
}

/*
  Removes the node with the specified value from the tree.  The node's value
  is saved and returned.  If a node with the value is not found in the list,
  return 0.

	while cur is not NULL we want to find the node we are looking for.
	if we do find it, we have some scenarios that could happen.
		if there are no children, just remove said node.
		and make its left and right leafs, NULL.
		else if we have two children we need to find the successor,
		thanks to our method from before.
		so we know where to rearange the children.
		else if we have just one child, either a left or a right,
		depending on which, just remove root and reapply child to prev.
	whenver we remove, we decrease the tree count. and free the node.
	and if we never find the value we are looking for, we just move to the next
	node in the tree depending on value's size.
*/
int bst_remove_value(Tree* tree, int value)
{
	TreeNode* cur = tree->root;
	TreeNode* prev = NULL;

	while(cur != NULL)
	{
		if (cur->value == value)
		{
			if ((cur->left == NULL) && (cur->right == NULL))
			{
				if (cur == tree->root)
				{
					tree->root = NULL;
					tree->count--;
					free(cur);
					return value;
				}

				if (prev->left == cur)
				{
			    prev->left = NULL;
				}
				else
				{
					prev->right = NULL;
				}
				tree->count--;
				free(cur);
				return value;
			}

			if ((cur->left != NULL) && (cur->right != NULL))
			{
				TreeNode* succ = bst_find_successor(cur);
				succ->left = cur->left;

				if (prev->left == cur)
				{
			    prev->left = succ;
				}
				else
				{
					prev->right = succ;
				}

				if (cur->right != NULL)
				{
					while (succ->right != NULL)
					{
						succ = succ->right;
					}
					succ->right = cur->right;
				}
				tree->count--;
				free(cur);
				return value;
			}

			if (cur == tree->root)
			{
				if (cur->left != NULL)
				{
					tree->root = cur->left;
				}
        else
				{
					tree->root = cur->right;
				}
        tree->count--;
        free(cur);
        return value;
			}

			if (cur->left != NULL)
			{
				if (prev->left == cur)
				{
					prev->left = cur->left;
				}
				else
				{
					prev->right = cur->left;
				}
			}
			else
			{
				if (prev->left == cur)
				{
					prev->left = cur->right;
				}
				else
				{
					prev->right = cur->right;
				}
			}
			tree->count--;
			free(cur);
			return value;
		}

		prev = cur;
		if (value < cur->value)
		{
			cur = cur->left;
		}
		else
		{
			cur = cur->right;
		}
	}
	return 0;
}

/*
  The following pair of functions do a post_order traversal of a binary
  search tree and fill the passed array with the results.  The first
  function calls the recursive function while the recursive function
  calls itself, keeping track of the current printing index.
*/
void bst_post_order(Tree* tree, int* output)
{
	bst_post_order_recursive(tree->root, output, 0);
}

/*
in post order we do the left node, right node, then root.
*/
int	bst_post_order_recursive(TreeNode* node, int* output, int index)
{
	int i = index;

	//left node
	if(node->left != NULL)
	{
		i = bst_post_order_recursive(node->left, output, index);
	}

	//right node
  if (node->right != NULL)
	{
		i = bst_post_order_recursive(node->right, output, i);
	}

	//root
	output[i++] = node->value;
	return i;
}

/*
  The following pair of functions do a pre_order traversal of a binary
  search tree and fill the passed array with the results.  The first
  function calls the recursive function while the recursive function
  calls itself, keeping track of the current printing index.
*/
void	bst_pre_order(Tree* tree, int* output)
{
	bst_pre_order_recursive(tree->root, output, 0);
}

//pre order does root, left, right.
int	bst_pre_order_recursive(TreeNode* node, int* output, int index)
{
	int i = index;

	//root
	output[i++] = node->value;

	//left node
	if (node->left != NULL)
	{
		i = bst_pre_order_recursive(node->left, output, i);
	}

	//right node
  if (node->right != NULL)
	{
		i = bst_pre_order_recursive(node->right, output, i);
	}

	return i;
}

/*
  The following pair of functions do an in_order traversal of a binary
  search tree and fill the passed array with the results.  The first
  function calls the recursive function while the recursive function
  calls itself, keeping track of the current printing index.
*/
void	bst_in_order(Tree* tree, int* output)
{
	bst_in_order_recursive(tree->root, output, 0);
}

//in, in order, we do left node, root, right node.
int	bst_in_order_recursive(TreeNode* node, int* output, int index)
{
	int i = index;

	//left node
	if (node->left != NULL)
	{
		i = bst_in_order_recursive(node->left, output, index);
	}

	//root
	output[i++] = node->value;

	//right node
  if (node->right != NULL)
	{
		i = bst_in_order_recursive(node->right, output, i);
	}

	return i;
}
