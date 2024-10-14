#include <stdlib.h>
#include "include/munit.h"
#include "include/snekobject.h"
#include "include/bootlib.h"

// Function to test creating an empty array
MunitResult test_create_empty_array(const MunitParameter params[], void* user_data) {
  snek_object_t *obj = new_snek_array(2);

  munit_assert_int(obj->kind, ==, ARRAY);
  munit_assert_int(obj->data.v_array.size, ==, 2);

  free(obj->data.v_array.elements);
  free(obj);

  munit_assert(boot_all_freed());

  return MUNIT_OK;
}

// Function to test calloc usage
MunitResult test_used_calloc(const MunitParameter params[], void* user_data) {
  snek_object_t *obj = new_snek_array(2);

  munit_assert_null(obj->data.v_array.elements[0]);
  munit_assert_null(obj->data.v_array.elements[1]);

  free(obj->data.v_array.elements);
  free(obj);

  munit_assert(boot_all_freed());

  return MUNIT_OK;
}

// Main function
int main(int argc, char* argv[]) {
  MunitTest tests[] = {
    { "/empty", test_create_empty_array, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/calloc", test_used_calloc, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
  };

  MunitSuite suite = {
    "object-array",  // The name of the test suite
    tests,           // The array of test cases
    NULL,            // Suites within this suite (none in this case)
    1,               // Number of iterations (1)
    MUNIT_SUITE_OPTION_NONE // Suite options
  };

  return munit_suite_main(&suite, NULL, argc, argv);
}
