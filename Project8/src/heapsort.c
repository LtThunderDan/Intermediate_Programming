/*  sort.c
    This program will demonstrate both the selection sort and the insertion
    sort using the list ADT we've previously created.  It will generate a list
    of random values 15 items long.  That list will be sorted by selection sort
    and at each iteration through the outer loop it will print both the sorted
    and unsorted list, finally displaying only the finished sorted list.  It
    will then repeat the process using insertion sort.
*/
#include "./btree/btree.h"
#include <stdio.h>

void heapSort();

int unsorted[15];
int sorted[15];
int i;

void main(){
  // Welcome message
  printf("Welcome to the Heap Sort Demonstration\n");
  printf("\nThis program sorts a random list, by building a heap and then using,\n");
  printf("the Heap Sort algorithm to produce a sorted list  Because of the nature\n");
  printf("of the algorithm, no iterations will be printed out.  Only the unsorted\n");
  printf("and sorted lists get printed.\n\n");

  /* initialize random seed: */
  srand (time(NULL));

  for(i = 0; i < 15; i++)
  {
    sorted[i] = 0;
    unsorted[i] = (int)(rand() % 100 + 1);
  }

  // do the work here
  heapSort();

  printf("\nThat's all, folks!\n");
}

/* void heapSort()
   *YOUR COMMENTS GO HERE*
*/
void heapSort(){
  // YOUR CODE GOES HERE
}