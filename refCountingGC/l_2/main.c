#include <stdio.h>
#include <stdlib.h>

#include "include/bootlib.h"
#include "include/munit.h"
#include "include/snekobject.h"

void test_inc_refcount() {
  snek_object_t *obj = new_snek_integer(10);
  if (obj->refcount != 1) {
    fprintf(stderr, "Refcount should be 1 on creation\n");
    exit(EXIT_FAILURE);
  }

  refcount_inc(obj);
  if (obj->refcount != 2) {
    fprintf(stderr, "Refcount should be incremented to 2\n");
    exit(EXIT_FAILURE);
  }

  free(obj);
}

void test_inc_refcount_more() {
  snek_object_t *obj = new_snek_float(4.20);
  if (obj->refcount != 1) {
    fprintf(stderr, "Refcount should be 1 on creation\n");
    exit(EXIT_FAILURE);
  }

  refcount_inc(obj);
  refcount_inc(obj);
  refcount_inc(obj);
  refcount_inc(obj);
  refcount_inc(obj);

  if (obj->refcount != 6) {
    fprintf(stderr, "Refcount should be incremented to 6\n");
    exit(EXIT_FAILURE);
  }

  free(obj);
}

void test_null_obj() {
  refcount_inc(NULL);
  if (1 != 1) {
    fprintf(stderr, "Unexpected behavior with NULL object\n");
    exit(EXIT_FAILURE);
  }
}

int main() {
  MunitTest tests[] = {
    { "/test_inc_refcount", test_inc_refcount, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/test_inc_refcount_more", test_inc_refcount_more, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/test_null_obj", test_null_obj, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
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
