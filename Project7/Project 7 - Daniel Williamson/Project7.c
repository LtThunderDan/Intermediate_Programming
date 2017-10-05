#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>

void merge();
void mergeRecursive();

/*
Prints out our array. Since we print it off so often, I made it a helper method.
*/
void printArray(int* array, int size)
{
  int i;

  printf("[");
  for(i = 0; i < size; i++)
  {
    printf("%d, ", array[i]);
  }
  printf("\b\b]\n");
}

int main()
{
  int mergeArray[18];
  int arrayLength = ((&mergeArray)[1] - mergeArray);
  int i;
  int randomNumber;

  //randomly generates an array. Used from previous project.
  for (i = 0; i < arrayLength; i++)
  {
    randomNumber = (rand() % 100 + 1);
    mergeArray[i] = randomNumber;
  }

  printf("This is the randomly generated unsorted array:");
  printArray(mergeArray, arrayLength);

  mergeRecursive(mergeArray, arrayLength);

  printf("Your now sorted array:");
  printArray(mergeArray, arrayLength);

  return 0;
}

/*
Breaks the original array down to just length of one.
Which is our base case. And gets sent back and merged.
*/
void mergeRecursive(int* mergeArray, int arrayLength)
{
  int i;
  int pivot = arrayLength/2;

  int leftSide[pivot];
  int leftLength = ((&leftSide)[1] - leftSide);

  int rightSide[arrayLength - pivot];
  int rightLength = ((&rightSide)[1] - rightSide);

  //base case
  if(arrayLength == 1)
  {
    return;
  }

  for(i = 0; i < pivot; i++)
  {
    leftSide[i] = mergeArray[i];
  }

  for(i = 0; pivot + i < arrayLength; i++)
  {
    rightSide[i] = mergeArray[pivot + i];
  }

  //let's do some recursion. For both sides of arrays.
  mergeRecursive(leftSide, leftLength);
  mergeRecursive(rightSide, rightLength);

  merge(leftSide, leftLength, rightSide, rightLength, mergeArray);

  printf("Current Array: ");
  printArray(mergeArray, arrayLength);
  printf("\n");
}

/*
Takes two sides of an array. And makes them into one sorted array.
*/
void merge(int* leftSide, int leftLength, int* rightSide, int rightLength, int* mergeArray)
  {
    int* left = leftSide;
    int* right = rightSide;
    int* mainArray = mergeArray;

    int leftIndex = 0;
    int rightIndex = 0;

    while(leftIndex < leftLength && rightIndex < rightLength)
    {
      if(*left < *right)
      {
        *mainArray = *left;
        leftIndex++;
        left++;
      }
      else
      {
        *mainArray = *right;
        rightIndex++;
        right++;
      }
      mainArray++;
    }

    while(leftIndex < leftLength)
    {
      *mainArray = *left;
      leftIndex++;
      left++;
      mainArray++;
    }

    while(rightIndex < rightLength)
    {
      *mainArray = *right;
      rightIndex++;
      right++;
      mainArray++;
    }
  }
