#include "include/exercise.h"
#include <stdlib.h>

stack_t *stack_new(size_t capacity) {
  stack_t *stack = malloc(sizeof(stack_t));

  if (stack == (void *)0){
    return (void *)0;
  }

  stack->count = 0;
  stack->capacity = capacity;

  void **data = malloc(capacity * sizeof(void *));
  if (data == (void *)0){
    free(stack);
    return (void *)0;
  }
  stack->data = data;

  return stack;
}
