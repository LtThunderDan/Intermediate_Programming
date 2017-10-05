#include <llist/llist.h>
#include <llist/dbg.h>
#include <stdio.h>
#include <stdbool.h>

/*
  Just initializes the list structure (the node pointers are NULL and
  the count = 0.
*/
List* list_create()
{
  List* list = calloc(1, sizeof(List));
  list->count = 0;
  list->first = NULL;
  list->last = NULL;
  return list;
}

/*
  Just initializes a ListNode structure (the node pointers are NULL and
  the pointer to the data is set to payload.
*/
ListNode* list_create_node(void* payload)
{
  ListNode* node = calloc(1, sizeof(ListNode));
  node->value = payload;
  node->next = NULL;
  node->prev = NULL;
  return node;
}

/*
  Frees any nodes in the list and then frees the list structure.
*/
List* list_destroy(List* list)
{
  free(list);
}

/*
  Frees any nodes in the list but leaves the list structure.
*/
void list_clear(List* list)
{
  list->first = NULL;
  list->last = NULL;
  list->count = 0;
}

/*
  Returns the count in the list structure.
*/
int list_count(List* list)
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
  ListNode* temp = list->first;

  while(temp != NULL)
  {
    if(temp->value == value)
    {
      return temp;
    }
    temp = temp->next;
  }
  return NULL;
}

void insertIntoEmptyList(List* list, ListNode* node)
{
  list->first = node;
  list->last = node;
  list->count++;
}

bool isEmpty(List* list)
{
  if(list->count == 0)
  {
    return true;
  }
  else
  {
    return false;
  }
}

/*
  Inserts a node in the list after the node containing value.  If no node
  has the passed value or if value == NULL, insert at the end of the list.
*/
void list_insert_after(List* list, ListNode* node, void* value)
{
  ListNode* temp = list_find(list, value);

  if(isEmpty(list))
  {
    insertIntoEmptyList(list, node);
  }
  else if(temp == NULL || value == NULL || temp->next == NULL)
  {
    // insert at the end
    list->last->next = node;
    node->prev = list->last;
    list->last = node;
    list->count++;
  }
  else
  {
    // insert after another node inbetween the beginning & end of list
    node->next = temp->next;
    temp->next->prev = node;
    node->prev = temp;
    temp->next = node;
    list->count++;
  }
}

/*
  Inserts a node in the list before the node containing value.  If no node has
  the passed value or if value == NULL, insert at the beginning of the list.
*/
void list_insert_before(List* list, ListNode* node, void* value)
{
  ListNode* temp = list_find(list, value);

  if(isEmpty(list))
  {
    insertIntoEmptyList(list, node);
  }
  else if(temp == NULL || value == NULL || temp->prev == NULL)
  {
    // insert at the beginning
    list->first->prev = node;
    node->next = list->first;
    list->first = node;
    list->count++;
  }
  else
  {
    // insert before another node inbetween the beginning & end of list
    node->prev = temp->prev;
    temp->prev->next = node;
    node->next = temp;
    temp->prev = node;
    list->count++;
  }
}

/*
  Removes the specified node from the list and frees it.  The node's value
  is saved and returned.
*/
void* list_remove_node(List* list, ListNode* node)
{
  void* value = node->value;

  if(isEmpty(list))
  {
    return NULL;
  }
  else if(node->next == NULL)
  {
    node->prev = list->last;
    node->prev->next = NULL;
    list->count--;
  }
  else if(node->prev == NULL)
  {
    node->next = list->first;
    node->next->prev = NULL;
    list->count--;
  }
  else
  {
    node->next->prev = node->prev;
    node->prev->next = node->next;
    list->count--;
  }
  return value;
}

/*
  Removes the node with the specified value from the list.  The node's value
  is saved and returned.  If a node with the value is not found in the list,
  return NULL
*/
void* list_remove_value(List* list, void* value)
{
  ListNode* temp = list_find(list, value);

  if(temp == NULL)
  {
    return NULL;
  }
  else if(isEmpty(list))
  {
    return NULL;
  }
  else if(list->count == 1)
  {
    list->first = NULL;
    list->last = NULL;
    list->count--;
  }
  else if(list->last == temp)
  {
    list->last = temp->prev;
    list->last->next = NULL;
    list->count--;
  }
  return temp->value;
}

// ----- The following functions are not needed until Project 5 ------------ //
/*
  Adds a node at one end of the list (your choice but document it).
*/
void list_push(List* list, void* value);

/*
  Add a node at one end of the list (your choice, but document it).
*/
void list_enqueue(List* list, void* value);

/*
  Removes a node from the same end of the list as list_push(). The value
  of the removed node is returned.
*/
void* list_pop(List* list);

/*
  Removes a node from the opposite end of the list as list_enqueue().  The
  value of the removed node is returned.
*/
void* list_dequeue(List* list);
