#include <stdlib.h>
#include "include/munit.h"
#include "include/snekobject.h"
#include "include/bootlib.h"

// Test positive float values
static MunitResult test_positive(const MunitParameter params[], void* data) {
  snek_object_t *obj = new_snek_float(42.0);
  munit_assert_double(obj->data.v_float, ==, 42.0);

  free(obj);
  munit_assert_true(boot_all_freed());
  return MUNIT_OK;
}

// Test zero float value
static MunitResult test_zero(const MunitParameter params[], void* data) {
  snek_object_t *obj = new_snek_float(0.0);

  munit_assert_int(obj->kind, ==, FLOAT);
  munit_assert_double(obj->data.v_float, ==, 0.0);

  free(obj);
  munit_assert_true(boot_all_freed());
  return MUNIT_OK;
}

// Test negative float values
static MunitResult test_negative(const MunitParameter params[], void* data) {
  snek_object_t *obj = new_snek_float(-5.0);

  munit_assert_int(obj->kind, ==, FLOAT);
  munit_assert_double(obj->data.v_float, ==, -5.0);

  free(obj);
  munit_assert_true(boot_all_freed());
  return MUNIT_OK;
}

int main() {
  // Manually creating test array
  MunitTest tests[] = {
    { "/positive", test_positive, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/zero", test_zero, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/negative", test_negative, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
  };

  // Defining the test suite
  MunitSuite suite = {
    "/object-float",  // Suite name
    tests,            // Array of tests
    NULL,             // Sub-suites (none in this case)
    1,                // Number of iterations
    MUNIT_SUITE_OPTION_NONE  // Suite options
  };

  // Running the test suite
  return munit_suite_main(&suite, NULL, NULL, NULL);
}
