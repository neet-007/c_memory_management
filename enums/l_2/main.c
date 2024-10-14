#include "include/munit.h"
#include "include/color.h"

// Test function for checking color enumeration values
static MunitResult
test_colors_defined(const MunitParameter params[], void* user_data) {
    (void) params;   // To avoid unused parameter warnings
    (void) user_data; // To avoid unused parameter warnings

    munit_assert_int(RED, ==, 55);    // Use munit_assert_int instead of assert_int
    munit_assert_int(GREEN, ==, 176);
    munit_assert_int(BLUE, ==, 38);

    return MUNIT_OK;  // Return MUNIT_OK to indicate the test passed
}

// Test function for checking that color enumeration values are not equal to incorrect values
static MunitResult
test_colors_defined_correctly(const MunitParameter params[], void* user_data) {
    (void) params;   // To avoid unused parameter warnings
    (void) user_data; // To avoid unused parameter warnings

    munit_assert_int(RED, !=, 0);
    munit_assert_int(GREEN, !=, 120);
    munit_assert_int(BLUE, !=, 215);

    return MUNIT_OK;  // Return MUNIT_OK to indicate the test passed
}

// Array of test cases
static MunitTest tests[] = {
    { "/defined", test_colors_defined, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/defined_vscode", test_colors_defined_correctly, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL } // End of tests array
};

// Define the test suite
static const MunitSuite suite = {
    "/colors",         // Suite name
    tests,             // Array of tests
    NULL,              // No child suites
    1,                 // Number of iterations
    MUNIT_SUITE_OPTION_NONE // No special options
};

// Main function to run the test suite
int main(int argc, char* argv[]) {
    return munit_suite_main(&suite, NULL, argc, argv);
}
