// ***
// *** You MUST modify this file, only the ssort function
// ***

#include "sort.h"
#include <stdio.h>

// DO NOT MODIFY THIS FUNCTION
bool checkOrder(int * arr, int size)
// a static function is visible only in this file
// This function returns true if the array elements are
// in the ascending order.
// false, otherwise
{
  int ind;
  for (ind = 0; ind < (size - 1); ind ++)
    {
      if (arr[ind] > arr[ind + 1])
	{
	  return false;
	}
    }
  return true;
}


// YOU MUST MODIFY THIS FUNCTION
#ifdef TEST_SORT
void ssort(int * arr, int size)
{
  int a;
  int b;
  int min;
  int var;
  for (a = 0;a < size - 1;a++)
  {
    min = a;
    for (b = a + 1; b < size; b++)
    {
      if (arr[b] < arr[min])
        min = b;
    }
    if (a != min)
    {
      var = arr[a];
      arr[a] = arr[min];
      arr[min] = var;
    }
  }
return;
}
#endif
