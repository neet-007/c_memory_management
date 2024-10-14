#include "include/snekstack.h"
#include "stdlib.h"

void scary_double_push(stack_t *s) {
  stack_push(s, (void *)1337);
  int *new_int = malloc(sizeof(int));
  if (new_int == NULL){
    return;
  }

  *new_int = 1024;
  stack_push(s, new_int);
}
