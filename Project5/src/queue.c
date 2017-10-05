/*  queue.c
    This program will use the llist library to implement a queue.
    The program will repeatedly prompt the user for an operation and will
    recognize "q" for "queue", "d" for "dequeue", "p" for "print", and "h"
    for "halt".  "q" prompts for the integer value to add to the queue and
    "d" displays the value that was dequeued.
*/
#include "./llist/llist.h"
#include <stdio.h>

void main(){
  char in;
  int* intArray;
  List* list = list_create();
  ListNode* node;
  int count;

  // Welcome message
  printf("Welcome to the Queue Demo\n");
  printf("\nWhen prompted, enter the one-letter commands 'q' to add to the\n");
  printf("queue, 'd' to dequeue an item, 'p' to print the current queue, and\n");
  printf("'h' to halt the program.\n\n");

  //input loop
  while(1)
  {
    printf("Ok, enter your command: ");
    while (((in = getc(stdin)) != '\n') && (in != EOF)) // filter 'enter' character
    {
      switch(in)
      {
		case 'h':
		          printf("You entered 'h'.\n");
		          exit(0);
		case 'q':
		          printf("You entered 'q'.\n\n");
              //need to malloc each time q is pressed.
              intArray = malloc(sizeof(int));
              //scans in an integer.
              scanf("%d", intArray);
              //lets user know what they are pushing.
              printf("You inserted %d to your queue\n", *intArray);
              //enqueus to the queue.
              list_enqueue(list, intArray);
		          break;
		case 'd':
		          printf("You entered 'd'.\n\n");
              //dequeues from the queue.
              intArray = (int*) list_dequeue(list);
		          break;
		case 'p':
		          printf("You entered 'p'.\n\n");
              //points to first node.
              node = list->first;
              //goes through each node and prints it out.
              printf("[");
              for(count = 0; count < list->count; count++)
              {
                intArray = (int*) node->value;
                printf("%d, ", *intArray);

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
		          break;
		default:
		          printf("You entered an invalid command.\n\n");
		          break;
      }
    }
  }
}
