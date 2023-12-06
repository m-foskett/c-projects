#include <stdio.h>

// Write a function that reverses an array of ints

// MACRO: Get length of array
#define LEN(array) (sizeof(array)/sizeof(*array))

// Function Prototype: Reverse an array of ints
void reverse(int* array, int numElements);

// Main Function
int main(void)
{
  // Test array of size 6
  int testArray[] = {3,6,8,1,4,6};
  int length, i;
  length = LEN(testArray);
  // Calling array reverse Function
  reverse(testArray, length);
  for (i = 0; i < length; i++)
  {
    printf("%d, ", *(testArray+i));
  }

  return 0;
}

// Function: Reverse an array of ints
void reverse(int* array, int numElements){
  int i, j = 0, reversedArray[numElements];
  for (i = numElements-1; i >= 0; i--){
    reversedArray[j] = *(array+i);
    j++;
  }
  for (i = 0; i < numElements; i++){
    *(array+i) = reversedArray[i];
  }
}
