#include <stdio.h>
#include <stdlib.h>
// Write a function that efficiently merges two already sorted arrays (allows duplicates) into a new sorted array

// Size of array MACRO
#define LEN(array) (sizeof(array) / sizeof(*array))

// Function Prototype: Merge sorted arrays into new sorted array
int* mergeSortedArray(int* array1, int numElements1, int* array2, int numElements2);

// Main Function
int main(void)
{
  int a[4] = {1,4,6,8};
  int b[6] = {3,5,5,6,9,10};

  int *merged = mergeSortedArray(a, LEN(a), b, LEN(b));
  int i, mergedLen = LEN(a)+LEN(b);
  for (i=0; i<mergedLen; i++)
  {
    printf("%d, ", *(merged+i));
  }
  free(merged);
  return 0;
}

// Function: Sorted Array Merger
int* mergeSortedArray(int* array1, int numElements1, int* array2, int numElements2)
{
  int *merged = malloc(sizeof(int) * (numElements1 + numElements2));
  int i, *p1 = array1, *p2 = array2;
  for (i=0; i<(numElements1+numElements2); i++){
    if ((*p1 < *p2) && (*p1 != NULL) && (*p2 != NULL)){
      *(merged+i) = *p1;
      p1++;
    }
    else{
      *(merged+i) = *p2;
      p2++;
    }
  }
  return merged;
}
