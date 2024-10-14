#include <stdlib.h>
#include <stdio.h>
#include "include/munit.h"
#include "include/snekobject.h"
#include "include/bootlib.h"

void test_integer_add() {
  snek_object_t *one = new_snek_integer(1);
  snek_object_t *three = new_snek_integer(3);
  snek_object_t *four = snek_add(one, three);

  printf("%d + %d = %d", one->data.v_int, three->data.v_int, four->data.v_int);
  munit_assert_not_null(four);
  munit_assert_int(four->kind, ==, INTEGER);
  munit_assert_int(four->data.v_int, ==, 4);

  free(one);
  free(three);
  free(four);
  munit_assert(boot_all_freed());
}

void test_float_add() {
  snek_object_t *one = new_snek_float(1.5);
  snek_object_t *three = new_snek_float(3.5);
  snek_object_t *five = snek_add(one, three);

  printf("%f + %f = %f\n", one->data.v_float, three->data.v_float, five->data.v_float);
  munit_assert_not_null(five);
  munit_assert_int(five->kind, ==, FLOAT);
  munit_assert_double(five->data.v_float, ==, 5.0);

  free(one);
  free(three);
  free(five);
  munit_assert(boot_all_freed());
}

void test_string_add() {
  snek_object_t *hello = new_snek_string("hello");
  snek_object_t *world = new_snek_string(", world");
  snek_object_t *greeting = snek_add(hello, world);

  printf("%s + %s = %s\n", hello->data.v_string, world->data.v_string, greeting->data.v_string);
  munit_assert_not_null(greeting);
  munit_assert_int(greeting->kind, ==, STRING);
  munit_assert_string_equal(greeting->data.v_string, "hello, world");

  free(hello->data.v_string);
  free(hello);
  free(world->data.v_string);
  free(world);
  free(greeting->data.v_string);
  free(greeting);
  munit_assert(boot_all_freed());
}

void test_string_add_self() {
  snek_object_t *repeated = new_snek_string("(repeated)");
  snek_object_t *result = snek_add(repeated, repeated);

  printf("%s + %s = %s\n", repeated->data.v_string, repeated->data.v_string, result->data.v_string);
  munit_assert_not_null(result);
  munit_assert_int(result->kind, ==, STRING);
  munit_assert_string_equal(result->data.v_string, "(repeated)(repeated)");

  free(repeated->data.v_string);
  free(repeated);
  free(result->data.v_string);
  free(result);
  munit_assert(boot_all_freed());
}

void test_vector3_add() {
  snek_object_t *one = new_snek_float(1.0);
  snek_object_t *two = new_snek_float(2.0);
  snek_object_t *three = new_snek_float(3.0);
  snek_object_t *four = new_snek_float(4.0);
  snek_object_t *five = new_snek_float(5.0);
  snek_object_t *six = new_snek_float(6.0);

  snek_object_t *v1 = new_snek_vector3(one, two, three);
  snek_object_t *v2 = new_snek_vector3(four, five, six);
  snek_object_t *result = snek_add(v1, v2);

  printf("%f + %f = %f\n", v1->data.v_vector3.x->data.v_float, v2->data.v_vector3.x->data.v_float, result->data.v_vector3.x->data.v_float);
  printf("%f + %f = %f\n", v1->data.v_vector3.y->data.v_float, v2->data.v_vector3.y->data.v_float, result->data.v_vector3.y->data.v_float);
  printf("%f + %f = %f\n", v1->data.v_vector3.z->data.v_float, v2->data.v_vector3.z->data.v_float, result->data.v_vector3.z->data.v_float);
  munit_assert_not_null(result);
  munit_assert_int(result->kind, ==, VECTOR3);
  munit_assert_double(result->data.v_vector3.x->data.v_float, ==, 5.0);
  munit_assert_double(result->data.v_vector3.y->data.v_float, ==, 7.0);
  munit_assert_double(result->data.v_vector3.z->data.v_float, ==, 9.0);

  free(v1->data.v_vector3.x);
  free(v1->data.v_vector3.y);
  free(v1->data.v_vector3.z);
  free(v1);

  free(v2->data.v_vector3.x);
  free(v2->data.v_vector3.y);
  free(v2->data.v_vector3.z);
  free(v2);

  free(result->data.v_vector3.x);
  free(result->data.v_vector3.y);
  free(result->data.v_vector3.z);
  free(result);
  munit_assert(boot_all_freed());
}

void test_array_add() {
  snek_object_t *one = new_snek_integer(1);
  snek_object_t *ones = new_snek_array(2);
  munit_assert(snek_array_set(ones, 0, one));
  munit_assert(snek_array_set(ones, 1, one));

  snek_object_t *hi = new_snek_string("hi");
  snek_object_t *hellos = new_snek_array(3);
  munit_assert(snek_array_set(hellos, 0, hi));
  munit_assert(snek_array_set(hellos, 1, hi));
  munit_assert(snek_array_set(hellos, 2, hi));

  snek_object_t *result = snek_add(ones, hellos);

  munit_assert_not_null(result);
  munit_assert_int(result->kind, ==, ARRAY);

  snek_object_t *first = snek_array_get(result, 0);
  munit_assert_not_null(first);
  munit_assert_int(first->data.v_int, ==, 1);

  snek_object_t *third = snek_array_get(result, 2);
  munit_assert_not_null(third);
  munit_assert_string_equal(third->data.v_string, "hi");

  free(one);
  free(ones->data.v_array.elements);
  free(ones);

  free(hi->data.v_string);
  free(hi);
  free(hellos->data.v_array.elements);
  free(hellos);
  free(result->data.v_array.elements);
  free(result);
  munit_assert(boot_all_freed());
}

int main() {
  MunitTest tests[] = {
    {"/integer", test_integer_add},
    {"/float", test_float_add},
    {"/string", test_string_add},
    {"/string-repeated", test_string_add_self},
    {"/array", test_array_add},
    {"/vector3", test_vector3_add},
    {NULL, NULL}  // terminator
  };

  MunitSuite suite = {
    "/object-add", tests, NULL, 1, MUNIT_SUITE_OPTION_NONE
  };

  return munit_suite_main(&suite, NULL, NULL, NULL);
}
