#include <stdlib.h>

#include "include/exercise.h"

token_t** create_token_pointer_array(token_t* tokens, size_t count) {
  token_t** token_pointers = (token_t**)malloc(count * sizeof(token_t*));
  if (token_pointers == NULL) {
    exit(1);
  }
  for (size_t i = 0; i < count; ++i) {
    token_t *token = (token_t *)malloc(sizeof(token_t));
    if (token == NULL) {
      exit(1);
    }
    *token = tokens[i];
    token_pointers[i] = token;
  }
  return token_pointers;
}
