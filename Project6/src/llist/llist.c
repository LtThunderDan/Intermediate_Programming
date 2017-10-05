#include <llist/llist.h>
#include <llist/dbg.h>

/*
  Just initializes the list structure (the node pointers are NULL and
  the count = 0. Uses calloc() to guarantee the contents are 0 and not
  pointing to random locations.
*/
List*     list_create()
{
	return calloc(1, sizeof(List));
}

/*
  Just initializes a ListNode structure (the node pointers are NULL and
  the pointer to the data is set to payload.  Uses calloc() to guarantee
  that the pointers are 0 before pointing to the payload.
*/
ListNode* list_create_node(void* payload)
{
	ListNode* temp = calloc(1, sizeof(ListNode));
	temp->value = payload;
	return temp;
}

/*
  Frees any nodes in the list and then frees the list structure.  It
  uses the iterator macro to touch each node.  If the node has a previous
  then the previous is freed (this assumes a non-circular list).  When
  the end is reached, the last node is freed and finally the list itself.
*/
List*     list_destroy(List* list)
{
	LIST_FOREACH(list, first, next, cur)
	{
		if (cur->prev)
		{
			free(cur->prev);
		}
	}
	free(list->last);
	free(list);
	return NULL;
}

/*
  Frees any nodes in the list but leaves the list structure. It uses
  the iterator macro to touch each node.  If the node has a previous
  then the previous is freed (this assumes a non-circular list).  When
  the end is reached, the last node is freed and then the pointers in
  the list structure are set to null along with a count of 0.
*/
void      list_clear(List* list)
{
	LIST_FOREACH(list, first, next, cur)
	{
		if (cur->prev)
		{
			free(cur->prev);
		}
	}
	free(list->last);
    list->last = NULL;
    list->first = NULL;
    list->count = 0;
}

/*
  Returns the count in the list structure.
*/
int       list_count(List* list)
{
	return list->count;
}

/*
  Returns the first node in the list.
*/
ListNode* list_first(List* list)
{
	return list->first;
}

/*
  Returns the last node in the list.
*/
ListNode* list_last(List* list)
{
	return list->last;
}

/*
  Finds a node in the list by value and returns the pointer to the node.
  If no matching node is found, returns NULL.
*/
ListNode* list_find(List* list, void* value)
{
	LIST_FOREACH(list, first, next, cur)
    {
		if (cur->value ==  value) return cur;
	}
	return NULL;
}

/*
  Inserts a node in the list after the node containing value.  If no node
  has the passed value or if value == NULL, insert at the end of the list.
*/
void      list_insert_after(List* list, ListNode* node, void* value)
{
	// Three cases.  1)Empty list.
	if (list->first == NULL)
	{
		list->first = node;
		list->last = node;
		list->count = 1;
		return;
	}

    // Otherwise we search for the insertion point
    // and if it's not found set it at the end
	ListNode* insertpoint = list_find(list, value);
	if (insertpoint == NULL) insertpoint = list->last;

	// Now we get to the next case. 2)It's not at the end.
	if (insertpoint != list->last)
	{
		node->next = insertpoint->next;
		node->prev = insertpoint;
		insertpoint->next->prev = node;
		insertpoint->next = node;
		list->count++;
	}
	else  // last case.  3)Insert at end of list
	{
		node->prev = insertpoint;
		insertpoint->next = node;
		list->last = node;
		list->count++;
	}
}

/*
  Inserts a node in the list before the node containing value.  If no node has
  the passed value or if value == NULL, insert at the beginning of the list.
*/
void      list_insert_before(List* list, ListNode* node, void* value)
{
	// Three cases.  1)Empty list.
	if (list->first == NULL)
	{
		list->first = node;
		list->last = node;
		list->count = 1;
		return;
	}

    // Otherwise we search for the insertion point
    // and if it's not found set it at the beginning
	ListNode* insertpoint = list_find(list, value);
	if (insertpoint == NULL) insertpoint = list->first;

	// Now we get to the next case. 2)It's not at the beginning.
	if (insertpoint != list->first)
	{
		node->next = insertpoint;
		node->prev = insertpoint->prev;
		insertpoint->prev->next = node;
		insertpoint->prev = node;
		list->count++;
	}
	else  // last case.  3)Insert at beginning of list
	{
		node->next = insertpoint;
		insertpoint->prev = node;
		list->first = node;
		list->count++;
	}
}

/*
  Removes the specified node from the list and frees it.  The node's value
  is saved and returned.
*/
void*     list_remove_node(List* list, ListNode* node)
{
	void* value = node->value;
	// Four cases: node not in list, is first node, is last node, or in middle
	// Node not in list
	if ((node->next == NULL) && (node->prev == NULL) && (list->first != node)) return NULL;

	// Node is first node
	if (node->prev == NULL)
	{
		// subcase: node is only node
		if (node->next == NULL)
		{
			list->first = NULL;
			list->last = NULL;
		}
		else
		{
			node->next->prev = NULL;
			list->first = node->next;
		}
		free(node);
		list->count--;
		return value;
	}

	// Node is last node
	if (node->next == NULL)
	{
		node->prev->next = NULL;
		list->last = node->prev;
		free(node);
		list->count--;
		return value;
	}

	// otherwise must be in list but not at ends
	node->prev->next = node->next;
	node->next->prev = node->prev;
	free(node);
	list->count--;
	return value;
}

/*
  Removes the node with the specified value from the list.  The node's value
  is saved and returned.  If a node with the value is not found in the list,
  return NULL.  It uses the list_find() to find the node with the value.  If
  it exists, it uses list_remove_node() to remove the node from the list.
*/
void*     list_remove_value(List* list, void* value)
{
	ListNode* temp = list_find(list, value);
	if (temp == NULL) return NULL;
	return list_remove_node(list, temp);
}

// ----- The following functions are not needed until Project 5 ------------ //
/*
  Adds a node at one end of the list (your choice but document it).
*/
void      list_push(List* list, void* value);

/*
  Add a node at one end of the list (your choice, but document it).
*/
void      list_enqueue(List* list, void* value);

/*
  Removes a node from the same end of the list as list_push(). The value
  of the removed node is returned.
*/
void*     list_pop(List* list);

/*
  Removes a node from the opposite end of the list as list_enqueue().  The
  value of the removed node is returned.
*/
void*     list_dequeue(List* list);

ListNode* findIndex(List* list, int i)
{
	if(i >= list->count || i < 0)
	{
		return NULL;
	}
	else
	{
		int count;
		ListNode* node = list->first;

		for(count = 0; count != i; count++)
		{
			if(node->next != NULL)
			{
				node = node->next;
			}
		}

		return node;
	}
}
