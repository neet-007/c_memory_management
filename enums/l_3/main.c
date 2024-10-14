#include "include/munit.h"
#include "include/http.h"

// Test function for checking HTTP error code string representations
static MunitResult
test_switch_enum(const MunitParameter params[], void* user_data) {
    (void) params;   // To avoid unused parameter warnings
    (void) user_data; // To avoid unused parameter warnings

    munit_assert_string_equal(http_to_str(HTTP_BAD_REQUEST), "400 Bad Request");
    munit_assert_string_equal(http_to_str(HTTP_UNAUTHORIZED), "401 Unauthorized");
    munit_assert_string_equal(http_to_str(HTTP_NOT_FOUND), "404 Not Found");
    munit_assert_string_equal(http_to_str(HTTP_TEAPOT), "418 I AM A TEAPOT!");
    munit_assert_string_equal(http_to_str(HTTP_INTERNAL_SERVER_ERROR), "500 Internal Server Error");

    return MUNIT_OK;  // Return MUNIT_OK to indicate the test passed
}

// Test function for checking the default case for unknown HTTP status codes
static MunitResult
test_switch_enum_default(const MunitParameter params[], void* user_data) {
    (void) params;   // To avoid unused parameter warnings
    (void) user_data; // To avoid unused parameter warnings

    munit_assert_string_equal(http_to_str((HttpErrorCode)999), "Unknown HTTP status code");

    return MUNIT_OK;  // Return MUNIT_OK to indicate the test passed
}

// Array of test cases
static MunitTest tests[] = {
    { "/switch_enum", test_switch_enum, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/switch_enum_default", test_switch_enum_default, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL } // End of tests array
};

// Define the test suite
static const MunitSuite suite = {
    "/http",          // Suite name
    tests,            // Array of tests
    NULL,             // No child suites
    1,                // Number of iterations
    MUNIT_SUITE_OPTION_NONE // No special options
};

// Main function to run the test suite
int main() {
    return munit_suite_main(&suite, NULL, 0, NULL);  // Removed command line args
}
