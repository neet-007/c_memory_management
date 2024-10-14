#include <stdio.h>
#include <assert.h>
#include "include/exercise.h"  // Assumes swap_strings is defined here

void test_swap_str() {
    char *a = "Hello";
    char *b = "Goodbye";

    swap_strings(&a, &b);  // Function assumed to be from exercise.h

    // Use standard C assert to check conditions
    assert(a == "Goodbye" && "a should now point to 'Goodbye'");
    assert(b == "Hello" && "b should now point to 'Hello'");

    printf("test_swap_str passed\n");
}

void test_swap_str_long() {
    char *a = "terminal.shop";
    char *b = "ssh";

    swap_strings(&a, &b);  // Function assumed to be from exercise.h

    // Use standard C assert to check conditions
    assert(a == "ssh" && "a should now point to 'ssh'");
    assert(b == "terminal.shop" && "b should now point to 'terminal.shop'");

    printf("test_swap_str_long passed\n");
}

int main() {
    printf("Running tests...\n");

    // Run each test manually
    test_swap_str();
    test_swap_str_long();

    printf("All tests passed!\n");

    return 0;
}
