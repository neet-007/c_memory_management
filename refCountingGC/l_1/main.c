#include <stdio.h>
#include <stdlib.h>

#include "include/bootlib.h"
#include "include/munit.h"
#include "include/snekobject.h"

void test_int_has_refcount() {
  snek_object_t *obj = new_snek_integer(10);
  if (obj->refcount != 1) {
    fprintf(stderr, "Refcount should be 1 on creation for int\n");
    exit(EXIT_FAILURE);
  }
  free(obj);
}

void test_float_has_refcount() {
  snek_object_t *obj = new_snek_float(42.0);
  if (obj->refcount != 1) {
    fprintf(stderr, "Refcount should be 1 on creation for float\n");
    exit(EXIT_FAILURE);
  }
  free(obj);
}

int main() {
  MunitTest tests[] = {
    { "test_int_has_refcount", test_int_has_refcount, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "test_float_has_refcount", test_float_has_refcount, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
  };

  MunitSuite suite = {
    "/refcount",   
    tests,         
    NULL,         
    1,           
    MUNIT_SUITE_OPTION_NONE
  };

  return munit_suite_main(&suite, NULL, NULL, NULL);
}
