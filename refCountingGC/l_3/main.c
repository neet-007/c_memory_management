#include <stdio.h>
#include <stdlib.h>

#include "include/bootlib.h"
#include "include/munit.h"
#include "include/snekobject.h"

void test_int_has_refcount() {
  snek_object_t *obj = new_snek_integer(10);
  if (obj->refcount != 1) {
    fprintf(stderr, "Refcount should be 1 on creation\n");
    exit(EXIT_FAILURE);
  }

  free(obj);
}

void test_inc_refcount() {
  snek_object_t *obj = new_snek_float(4.20);
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

void test_dec_refcount() {
  snek_object_t *obj = new_snek_float(4.20);

  refcount_inc(obj);
  if (obj->refcount != 2) {
    fprintf(stderr, "Refcount should be incremented to 2\n");
    exit(EXIT_FAILURE);
  }

  refcount_dec(obj);
  if (obj->refcount != 1) {
    fprintf(stderr, "Refcount should be decremented to 1\n");
    exit(EXIT_FAILURE);
  }

  if (boot_is_freed(obj)) {
    fprintf(stderr, "Object should not be freed yet\n");
    exit(EXIT_FAILURE);
  }

  free(obj);
}

void test_refcount_free_is_called() {
  snek_object_t *obj = new_snek_float(4.20);

  refcount_inc(obj);
  if (obj->refcount != 2) {
    fprintf(stderr, "Refcount should be incremented to 2\n");
    exit(EXIT_FAILURE);
  }

  refcount_dec(obj);
  if (obj->refcount != 1) {
    fprintf(stderr, "Refcount should be decremented to 1\n");
    exit(EXIT_FAILURE);
  }

  refcount_dec(obj);
  if (!boot_is_freed(obj)) {
    fprintf(stderr, "Object should be freed after refcount reaches 0\n");
    exit(EXIT_FAILURE);
  }

  if (!boot_all_freed()) {
    fprintf(stderr, "All objects should be freed\n");
    exit(EXIT_FAILURE);
  }
}

void test_allocated_string_is_freed() {
  snek_object_t *obj = new_snek_string("Hello @wagslane!");

  refcount_inc(obj);
  if (obj->refcount != 2) {
    fprintf(stderr, "Refcount should be incremented to 2\n");
    exit(EXIT_FAILURE);
  }

  refcount_dec(obj);
  if (obj->refcount != 1) {
    fprintf(stderr, "Refcount should be decremented to 1\n");
    exit(EXIT_FAILURE);
  }

  if (strcmp(obj->data.v_string, "Hello @wagslane!") != 0) {
    fprintf(stderr, "String should match the expected value\n");
    exit(EXIT_FAILURE);
  }

  refcount_dec(obj);
  if (!boot_is_freed(obj)) {
    fprintf(stderr, "Object should be freed after refcount reaches 0\n");
    exit(EXIT_FAILURE);
  }

  if (!boot_all_freed()) {
    fprintf(stderr, "All objects should be freed\n");
    exit(EXIT_FAILURE);
  }
}

int main() {
  MunitTest tests[] = {
    { "/has_refcount", test_int_has_refcount, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/inc_refcount", test_inc_refcount, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/dec_refcount", test_dec_refcount, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/free_refcount", test_refcount_free_is_called, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/string_freed", test_allocated_string_is_freed, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
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
