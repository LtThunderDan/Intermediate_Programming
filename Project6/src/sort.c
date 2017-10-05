/*  sort.c
    This program will demonstrate both the selection sort and the insertion
    sort using the list ADT we've previously created.  It will generate a list
    of random values 15 items long.  That list will be sorted by selection sort
    and at each iteration through the outer loop it will print both the sorted
    and unsorted list, finally displaying only the finished sorted list.  It
    will then repeat the process using insertion sort.
*/
#include "./llist/llist.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static List* unsorted = NULL;
static List* sorted = NULL;
void selSort();
void insSort();
/* NOTE: if you use the LIST_FOREACH macro, you can't use it twice in a single
   function.  In that case, it is acceptable to 1) change print_list to accept
   a parameter specifying the list it should print or 2) create separate
   functions to print each list (print_sorted_list() and print_unsorted_list())
   or 3) avoid the whole issue and write your own iterations. */
void print_list(List*);

/*
Used to populate the unsorted array full of random integers.
Just fills it with 10 ints.
*/
void randomList()
{
  int *ptr;
  int i;
  for(i = 0; i < 10; i++)
  {
    ptr = malloc(sizeof(int));
    *ptr = rand() % 100;
    ListNode* node = list_create_node(ptr);
    list_insert_after(unsorted, node, NULL);
  }
}


void main()
{
  // Welcome message
  printf("Welcome to the Sort Demonstration\n");
  printf("\nThis program sorts two random lists, once using Selection Sort,\n");
  printf("and once using Insertion Sort.  For each sort, the iterations are\n");
  printf("displayed so you can see the progress.\n\n");

  srand(time(NULL));


  // do the work here
  unsorted = list_create();
  sorted = list_create();
  randomList();
  selSort();
  list_destroy(unsorted);
  list_destroy(sorted);

  unsorted = list_create();
  sorted = list_create();
  randomList();
  insSort();
  list_destroy(unsorted);
  list_destroy(sorted);

}

/* void selSort()
   does selection sort.
   Starts at the beginning of the unsorted array and moves down the list.
   Places each value in the correct postion in the new sorted array.
*/
void selSort()
{
  printf("This is the selection sort routine:\n");
  printf("Original Unsorted list: ");
  print_list(unsorted);

  ListNode* minNode = NULL;
  ListNode* node = NULL;

  int i;

  while(unsorted->count != 0)
  {
    minNode = findIndex(unsorted, 0);

    //finds the smallest value.
    for(i = 1; i < unsorted->count; i++)
    {
      node = findIndex(unsorted, i);

      if(*(int*)node->value < *(int*)minNode->value)
      {
        minNode = node;
      }
    }

    ListNode* n = list_create_node(minNode->value);
    list_insert_after(sorted, n, NULL);
    list_remove_node(unsorted, minNode);

    printf("\nUnsorted List: ");
    print_list(unsorted);
    printf("Sorted List: ");
    print_list(sorted);
    printf("\n");
  }
}

/* void insSort()
   does insertion sort.
   Finds and selects the smallest value and places it into the sorted array.
*/
void insSort()
{
  void* ptr;

  printf("This is the insertion sort routine:\n");
  printf("Original Unsorted list: ");
  print_list(unsorted);

  ListNode* sortNode = NULL;
  ListNode* node = NULL;

  while(unsorted->count != 0)
  {
    node = unsorted->first;

    ListNode* n = list_create_node(node->value);
    list_insert_after(sorted, n, NULL);
    list_remove_node(unsorted, node);

    sortNode = sorted->last;

    //finds the smallest value.
    while(sortNode->prev != NULL && *(int*)sortNode->prev->value > *(int*)sortNode->value)
    {
      ptr = sortNode->value;
      sortNode->value = sortNode->prev->value;
      sortNode->prev->value = ptr;
      sortNode = sortNode->prev;
    }
    printf("\nUnsorted List: ");
    print_list(unsorted);
    printf("Sorted List: ");
    print_list(sorted);
    printf("\n");
  }
}

/* void print_list()
   Just prints off the array.
*/
void print_list(List* list)
{
  int i;
  int* ptr;

  ListNode* node = list->first;

  printf("[");
  for(i = 0; i < list->count; i++)
  {
    ptr = node->value;
    printf("%d, ", *ptr);
    if(node->next != NULL)
    {
      node = node->next;
    }
    else
    {
      break;
    }
  }
  printf("]\n");
}
