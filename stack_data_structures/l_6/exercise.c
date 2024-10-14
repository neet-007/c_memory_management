#include "include/snekstack.h"
#include "stdlib.h"
#include <string.h>

void stack_push_multiple_types(stack_t *s) {
  float *new_float = malloc(sizeof(float));
  if (new_float == NULL){
    return;
  }

  *new_float = 3.14;

  stack_push(s, new_float);

  char *new_string = malloc(strlen("Sneklang is blazingly slow!") + 1);
  if (new_string == NULL) {
      free(new_float); 
      return; 
  }
  strcpy(new_string, "Sneklang is blazingly slow!");

  stack_push(s, new_string);
}
