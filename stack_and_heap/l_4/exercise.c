#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/exercise.h"

char* get_full_greeting(char *greeting, char *name, int size) {
  char *full_greeting = (char *)malloc(size * sizeof(char));
  if (full_greeting == NULL){
    printf("could not get memory");
    exit(1);
  }
  snprintf(full_greeting, size, "%s %s", greeting, name);
  return full_greeting;
}
