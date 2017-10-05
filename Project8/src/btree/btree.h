#ifndef __libbtree_btree_h__
#define __libbtree_btree_h__

#include <stdlib.h>

// ----- List and list node declarations ----------------------------------- //
struct TreeNode;

typedef struct TreeNode {
	struct TreeNode *left;
	struct TreeNode *right;
	int value;
} TreeNode;

typedef struct Tree {
	TreeNode *root;
	int	count;
} Tree;

// ----- For use with heaps, so you can keep track of the last node added ---//
typedef struct HeapTree {
	TreeNode *root;
	TreeNode *last;
	int	count;
} HeapTree;

// ----- Function prototypes ----------------------------------------------- //
/*
  Just initializes the Tree structure (the node pointer is NULL and the count
  is 0).
*/
Tree*     tree_create();

/*
  Just initializes a TreeNode structure (the node pointers are NULL and
  the integer data is set to payload.  Notice we are using integers
  explicitly this time.
*/
TreeNode* tree_create_node(int payload);

/*
  Frees any nodes in the tree and then frees the tree structure.
*/
Tree*     tree_destroy(Tree* tree);

/*
  Frees any nodes in the tree but leaves the tree structure.
*/
void      tree_clear(Tree* tree);
void	tree_clear_recursive(TreeNode* node);

/*
  Returns the root node in the tree.
*/
TreeNode* tree_root(Tree* tree);

/*
  Returns the number of nodes in the tree.
*/
int tree_count(Tree* tree);

/*
  Finds a node in the tree by value and returns the pointer to the node.
  If no matching node is found, returns NULL.
*/
TreeNode* bst_find(Tree* tree, int value);

/*
  Finds a successor node in the tree and returns the pointer to the node.
  Assumes the node has a right child (called from bst_remove_value where
  the node to be remove has been checked for children).
*/
TreeNode* bst_find_successor(TreeNode* node);

/*
  Inserts a node in the tree using Binary Search Tree rules.
*/
void      bst_insert_node(Tree* tree, TreeNode* node);

/*
  Inserts a node in the tree using Binary Search Tree rules after creating
  a node with the passed value.
*/
void      bst_insert_value(Tree* tree, int value);

/*
  Removes the node with the specified value from the tree.  The node's value
  is saved and returned.  If a node with the value is not found in the list,
  return NULL
*/
int     bst_remove_value(Tree* tree, int value);

/*
  The following pair of functions do a post_order traversal of a binary
  search tree and fill the passed array with the results.  The first
  function calls the recursive function while the recursive function
  calls itself, keeping track of the current printing index.
*/
void	bst_post_order(Tree* tree, int* output);
int	bst_post_order_recursive(TreeNode* node, int* output, int index);

/*
  The following pair of functions do a pre_order traversal of a binary
  search tree and fill the passed array with the results.  The first
  function calls the recursive function while the recursive function
  calls itself, keeping track of the current printing index.
*/
void	bst_pre_order(Tree* tree, int* output);
int	bst_pre_order_recursive(TreeNode* node, int* output, int index);
/*
  The following pair of functions do an in_order traversal of a binary
  search tree and fill the passed array with the results.  The first
  function calls the recursive function while the recursive function
  calls itself, keeping track of the current printing index.
*/

void	bst_in_order(Tree* tree, int* output);
int	bst_in_order_recursive(TreeNode* node, int* output, int index);

// ----- The following functions are not needed until Project 9 ------------ //
/*
  Inserts a node in the tree using Heap Tree rules.
*/
void      heap_insert_node(Tree* tree, TreeNode* node);

/*
  Inserts a node in the tree using Heap Tree rules after creating
  a node with the passed value.
*/
void      heap_insert_value(Tree* tree, int value);

/*
  Removes the root node from the heap and frees it.  The node's value
  is saved and returned.
*/
int     heap_remove_root(Tree* tree);

#endif
