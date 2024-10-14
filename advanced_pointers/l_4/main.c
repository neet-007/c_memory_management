#include <stdio.h>
#include <assert.h>

#include "include/exercise.h"
#include "include/munit.h"

void test_swap_ints() {
    int a = 5;
    int b = 6;

    swap_ints(&a, &b);

    assert(a == 6 && "a is now 6");
    assert(b == 5 && "b is now 5");

    printf("test_swap_ints passed\n");
}

void test_swap_ints_same() {
    int a = 5;

    swap_ints(&a, &a);

    assert(a == 5 && "a is still 5");

    printf("test_swap_ints_same passed\n");
}

int main() {
    printf("Running tests...\n");

    // Run each test
    test_swap_ints();
    test_swap_ints_same();

    printf("All tests passed!\n");

    return 0;
}
