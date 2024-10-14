#include <stdlib.h>
#include "include/munit.h"
#include "include/snekobject.h"
#include "include/bootlib.h"
// Define the test for string copy
static MunitResult test_str_copied(const MunitParameter params[], void* data) {
  char *input = "Hello, World!";
  snek_object_t *obj = new_snek_string(input);

  // Ensure the object is of type STRING
  munit_assert_int(obj->kind, ==, STRING);

  // Ensure the string has been copied, not just referenced
  munit_assert_ptr_not_equal(obj->data.v_string, input);

  // Ensure the copied string is identical to the input string
  munit_assert_string_equal(obj->data.v_string, input);

  // Free the copied string and the object itself
  free(obj->data.v_string);
  free(obj);

  // Ensure memory is freed correctly
  munit_assert_true(boot_all_freed());

  return MUNIT_OK;
}

int main() {
  // Manually create the test array
  MunitTest tests[] = {
    { "/copies_value", test_str_copied, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }  // Null terminator for the array
  };

  // Create the test suite
  MunitSuite suite = {
    "/object-string",  // Suite name
    tests,             // Array of tests
    NULL,              // Sub-suites (none in this case)
    1,                 // Number of iterations (1 is default)
    MUNIT_SUITE_OPTION_NONE  // Suite options
  };

  // Run the test suite
  return munit_suite_main(&suite, NULL, NULL, NULL);
}
