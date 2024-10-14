#include <stdlib.h>
#include <string.h>

#include "include/snekobject.h"

snek_object_t *new_snek_string(char *value) {
  snek_object_t *obj = malloc(sizeof(snek_object_t));
  if (obj == NULL){
    return NULL;
  }

  char *string = malloc(strlen(value) + 1);
  if (string == NULL){
    free(obj);
    return NULL;
  }


  stpcpy(string, value);
  obj->kind = STRING;
  obj->data.v_string = string;

  return obj;
}

// don't touch below this line

snek_object_t *new_snek_integer(int value) {
  snek_object_t *obj = malloc(sizeof(snek_object_t));
  if (obj == NULL) {
    return NULL;
  }

  obj->kind = INTEGER;
  obj->data.v_int = value;
  return obj;
}

snek_object_t *new_snek_float(float value) {
  snek_object_t *obj = malloc(sizeof(snek_object_t));
  if (obj == NULL) {
    return NULL;
  }

  obj->kind = FLOAT;
  obj->data.v_float = value;
  return obj;
}
