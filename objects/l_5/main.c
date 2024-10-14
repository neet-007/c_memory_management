#include <stdlib.h>
#include "include/munit.h"
#include "include/snekobject.h"
#include "include/bootlib.h"
// Define the test for returning NULL when inputs are NULL
static MunitResult test_returns_null(const MunitParameter params[], void* data) {
  // Call the function with NULL inputs
  snek_object_t *vec = new_snek_vector3(NULL, NULL, NULL);

  // Check if the result is NULL
  munit_assert_null(vec);

  // Check if all memory has been freed
  munit_assert_true(boot_all_freed());

  return MUNIT_OK;
}

int main() {
  // Manually create the test array
  MunitTest tests[] = {
    { "/returns_null", test_returns_null, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }  // Null terminator for the array
  };

  // Create the test suite
  MunitSuite suite = {
    "/object-vector",  // Suite name
    tests,             // Array of tests
    NULL,              // Sub-suites (none in this case)
    1,                 // Number of iterations
    MUNIT_SUITE_OPTION_NONE  // Suite options
  };

  // Run the test suite
  return munit_suite_main(&suite, NULL, NULL, NULL);
}
