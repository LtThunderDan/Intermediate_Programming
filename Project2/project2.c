/*
Created by: Daniel Williamson
Monday Feburary 13th, 2017

This programs function is to ask the user for how long of array they would
like to create and the values they would like to fill it with.
It will then sort the array and print it out.
*/


#include <stdio.h>
#include <stdlib.h>

//global array/variable
int getArray[100];
int getArraySize;

//This functions purpose is to gather the users input.
//It will prompt for a size for which the array will be.
//It will then ask for the values you want the array to be filled with.
void getUserInfo()
{
  int i;
  int getArrayDigit;
  printf("\nHello! Welcome to Bubble Sort\n");
  printf("How many numbers would you like to sort?: ");
  scanf("%d", &getArraySize);

  //This insures the size of the array can not be greater than 100 or less than 0.
  while(getArraySize > 100 || getArraySize < 2)
  {
    printf("Please enter a number that is less then 100 and greater than 2: ");
    scanf("%d", &getArraySize);
  }

  for(i = 0; i < getArraySize; i++)
  {
    printf("Please enter a number: ");
    scanf("%d", &getArrayDigit);
    getArray[i] = getArrayDigit;
  }
}

//This function is where the array that was previously created is sorted.
//Using the bubble sort pseude code the instructor provided.
void bubbleSort()
{
  int i;
  int j;
  int temp;
  for(i = 0; i < getArraySize-1 ; i++)
  {
    for(j = 0; j < getArraySize-1-i; j++)
    {
      if(getArray[j] > getArray[j+1])
      {
        temp = getArray[j];
        getArray[j] = getArray[j+1];
        getArray[j+1] = temp;
      }
    }
  }
}

//This functions purpose is to print out the array.
//It will print out the array before and after being sorted.
void printArray()
{
  int j;
  printf("[");
  for(j = 0; j < getArraySize; j++)
  {
    printf(" %d", getArray[j]);
    printf(",");
  }
  printf("]\n");
}

//The main function that calls all functions.
int main()
{
  getUserInfo();
  printf("This is your unordered array: \n");
  printArray();
  bubbleSort();
  printf("This is now your new ordered array using bubble sort: \n");
  printArray();
  return 0;
}
