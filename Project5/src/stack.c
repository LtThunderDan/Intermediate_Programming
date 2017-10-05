/*  stack.c
    This program will use the llist library to implement a queue.
    The program will repeatedly prompt the user for an operation and will
    recognize "+" for "push", "-" for "pop", "p" for "print", and "h"
    for "halt".  "+" prompts for the integer value to add to the stack and
    "-" displays the value that was popped.
*/
#include "./llist/llist.h"
#include <stdio.h>

void main(){
  char in;
  List* list = list_create();
  ListNode* node;
  int* intArray;
  int count;

  // Welcome message
  printf("Welcome to the Stack Demo\n");
  printf("\nWhen prompted, enter the one-letter commands '+' to push to the\n");
  printf("stack, '-' to pop an item, 'p' to print the current stack, and\n");
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
		case '+':
		          printf("You entered '+'.\n\n");
              //need to malloc each time q is pressed.
              intArray = malloc(sizeof(int));
              printf("Please enter an integer to push onto the stack: ");
              //scans in an integer.
              scanf("%d", intArray);
              //lets user know what they are pushing.
              printf("You inserted %d to your stack\n", *intArray);
              //pushes onto the stack.
              list_push(list, intArray);
		          break;
		case '-':
		          printf("You entered '-'.\n\n");
              //pops from the stack.
              intArray = (int*) list_pop(list);
		          break;
		case 'p':
		          printf("You entered 'p'.\n\n");
              //points to first node.
              node = list->last;
              //goes through each node and prints it out.
              printf("[");
              for(count = 0; count < list->count; count++)
              {
                intArray = (int*) node->value;
                printf("%d, ", *intArray);

                if(node->prev != NULL)
                {
                  node = node->prev;
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
