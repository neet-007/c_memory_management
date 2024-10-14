#include "stdlib.h"

#include "include/exercise.h"

void allocate_int(int **pointer_pointer, int value) {
  int *new_pointer = malloc(sizeof(int));

  if (new_pointer == (void *)0) {
    *pointer_pointer = (void *)0;
    return; 
  }

  *pointer_pointer = new_pointer;

  *new_pointer = value;
}
