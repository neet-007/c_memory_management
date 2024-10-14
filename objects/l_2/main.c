#include "include/munit.h"
#include "include/snekobject.h"

// Define the test for positive integer values
static MunitResult test_positive(const MunitParameter params[], void* data) {
  snek_object_t *int_object = new_snek_integer(42);
  munit_assert_int(int_object->data.v_int, ==, 42);

  free(int_object);
  return MUNIT_OK;
}

// Define the test for zero integer value
static MunitResult test_zero(const MunitParameter params[], void* data) {
  snek_object_t *int_object = new_snek_integer(0);

  munit_assert_int(int_object->kind, ==, INTEGER);
  munit_assert_int(int_object->data.v_int, ==, 0);

  free(int_object);
  return MUNIT_OK;
}

// Define the test for negative integer values
static MunitResult test_negative(const MunitParameter params[], void* data) {
  snek_object_t *int_object = new_snek_integer(-5);

  munit_assert_int(int_object->kind, ==, INTEGER);
  munit_assert_int(int_object->data.v_int, ==, -5);

  free(int_object);
  return MUNIT_OK;
}

int main() {
  // Manually create the test array
  MunitTest tests[] = {
    { "/positive", test_positive, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/zero", test_zero, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/negative", test_negative, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }  // Null termination for the test array
  };

  // Define the test suite
  MunitSuite suite = {
    "/object-integer",  // Suite name
    tests,              // Array of tests
    NULL,               // Sub-suites (none in this case)
    1,                  // Number of iterations
    MUNIT_SUITE_OPTION_NONE  // Suite options
  };

  // Run the test suite
  return munit_suite_main(&suite, NULL, NULL, NULL);
}
