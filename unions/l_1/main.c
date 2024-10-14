#include <stdio.h>
#include "include/exercise.h"
#include "include/munit.h"

MunitResult test_formats_int1(const MunitParameter params[], void* user_data) {
    (void) params; 
    (void) user_data; 
    char buffer[100];
    snek_object_t i = new_integer(5);
    format_object(i, buffer);
    munit_assert_string_equal(buffer, "int:5");  // Correct assertion function
    return MUNIT_OK;
}

MunitResult test_formats_string1(const MunitParameter params[], void* user_data) {
    (void) params; 
    (void) user_data; 
    char buffer[100];
    snek_object_t s = new_string("Hello!");
    format_object(s, buffer);
    munit_assert_string_equal(buffer, "string:Hello!");  // Correct assertion function
    return MUNIT_OK;
}

MunitResult test_formats_int2(const MunitParameter params[], void* user_data) {
    (void) params; 
    (void) user_data; 
    char buffer[100];
    snek_object_t i = new_integer(2014);
    format_object(i, buffer);
    munit_assert_string_equal(buffer, "int:2014");  // Correct assertion function
    return MUNIT_OK;
}

MunitResult test_formats_string2(const MunitParameter params[], void* user_data) {
    (void) params; 
    (void) user_data; 
    char buffer[100];
    snek_object_t s = new_string("nvim btw");
    format_object(s, buffer);
    munit_assert_string_equal(buffer, "string:nvim btw");  // Correct assertion function
    return MUNIT_OK;
}

int main(int argc, char* const argv[]) {
    MunitTest tests[] = {
        { "/integer_1", test_formats_int1, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
        { "/string_1", test_formats_string1, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
        { "/integer_2", test_formats_int2, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
        { "/string_2", test_formats_string2, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
        { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },   // Terminates the array
    };

    MunitSuite suite = {
        "/format_tests",     // Suite name
        tests,               // The test cases
        NULL,                // Suites (for grouping)
        1,                   // Number of iterations
        MUNIT_SUITE_OPTION_NONE // Suite options
    };

    // Run the suite
    return munit_suite_main(&suite, NULL, argc, argv);
}
