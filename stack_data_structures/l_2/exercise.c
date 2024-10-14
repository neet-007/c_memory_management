#include "include/exercise.h"
#include <assert.h>
#include <stddef.h>
#include <stdlib.h>

void stack_push(stack_t *stack, void *obj) {
  if (stack->count == stack->capacity){
      stack->data = realloc(stack->data, 2 * stack->capacity * sizeof(void*));
      if (stack->data == NULL){
        free(stack->data);
        free(stack);
        return;
      }
      stack->capacity = stack->capacity * 2;
  }
    stack->data[stack->count] = obj;
    stack->count ++;
}

// don't touch below this line

stack_t *stack_new(size_t capacity) {
  stack_t *stack = malloc(sizeof(stack_t));
  if (stack == NULL) {
    return NULL;
  }

  stack->count = 0;
  stack->capacity = capacity;
  stack->data = malloc(stack->capacity * sizeof(void *));
  if (stack->data == NULL) {
    free(stack);
    return NULL;
  }

  return stack;
}
