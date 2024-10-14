#include "include/munit.h"
#include <string.h>
#include <stdbool.h>
#include "include/exercise.h"

// Helper function to check if a pointer is on the stack
bool is_on_stack(void *ptr) {
    void *stack_top = __builtin_frame_address(0);
    uintptr_t stack_top_addr = (uintptr_t)stack_top;
    uintptr_t ptr_addr = (uintptr_t)ptr;

    // Check within a threshold in both directions (e.g., 1MB)
    uintptr_t threshold = 1024;

    return ptr_addr >= (stack_top_addr - threshold) && ptr_addr <= (stack_top_addr + threshold);
}

// Test function for basic greeting
static MunitResult test_basic_greeting(const MunitParameter params[], void* data) {
    (void)params; // Unused
    (void)data; // Unused

    char *result = get_full_greeting("Hello", "Alice", 20);
    munit_assert_string_equal(result, "Hello Alice");
    munit_assert_false(is_on_stack(result));
    free(result);

    return MUNIT_OK;
}

// Test function for short buffer handling
static MunitResult test_short_buffer(const MunitParameter params[], void* data) {
    (void)params; // Unused
    (void)data; // Unused

    char *result = get_full_greeting("Hey", "Bob", 4); // Buffer size of 4
    munit_assert_string_equal(result, "Hey");
    munit_assert_false(is_on_stack(result));
    free(result);

    return MUNIT_OK;
}

int main(int argc, char* argv[]) {
    /* Define the test cases */
    MunitTest tests[] = {
        { "/test_basic_greeting", test_basic_greeting, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
        { "/test_short_buffer", test_short_buffer, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
        { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
    };

    /* Define the test suite */
    MunitSuite suite = {
        "get_full_greeting", /* name */
        tests,               /* tests */
        NULL,                /* suites */
        1,                   /* iterations */
        MUNIT_SUITE_OPTION_NONE
    };

    /* Run the test suite */
    return munit_suite_main(&suite, NULL, argc, argv);
}
