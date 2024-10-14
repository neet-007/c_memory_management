#include <stdlib.h>
#include "include/munit.h"
#include "include/snekstack.h"

// Define the tests manually instead of using macros
static MunitResult test_integer_constant(const MunitParameter params[], void* data) {
  munit_assert_int(INTEGER, ==, 0);
  return MUNIT_OK;
}

static MunitResult test_integer_obj(const MunitParameter params[], void* data) {
  snek_object_t *obj = malloc(sizeof(snek_object_t));
  obj->kind = INTEGER;
  obj->data.v_int = 0;

  munit_assert_int(obj->kind, ==, INTEGER);
  munit_assert_int(obj->data.v_int, ==, 0);

  free(obj);
  return MUNIT_OK;
}

int main() {
  // Manually creating test array
  MunitTest tests[] = {
    { "/integer_constant", test_integer_constant, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/integer_obj", test_integer_obj, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
  };

  // Create the test suite
  MunitSuite suite = {
    "/object-integer-def",  // Suite name
    tests,                  // Tests in the suite
    NULL,                   // Suites (can add more suites here)
    1,                      // Number of iterations (1 by default)
    MUNIT_SUITE_OPTION_NONE  // Suite options
  };

  // Run the test suite
  return munit_suite_main(&suite, NULL, NULL, NULL);
}
