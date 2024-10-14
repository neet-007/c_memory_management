#include "include/bootlib.h" 
#include "include/exercise.h"    // Assuming swap is implemented here
#include <stdint.h>
#include <stdio.h>
#include <assert.h>

typedef struct CoffeShop {
    uint64_t quality;
    uint64_t taste;
    uint64_t branding;
} coffee_shop_t;

void test_generic_ints() {
    int i1 = 1234;
    int i2 = 5678;

    swap(&i1, &i2, sizeof(int));  // Assuming swap is implemented in exercise.h

    // Use standard C assert to check values
    assert(i1 == 5678 && "i1 should be i2's original value");
    assert(i2 == 1234 && "i2 should be i1's original value");

    // Check memory management if applicable
    assert(boot_all_freed() && "All memory should be freed");

    printf("test_generic_ints passed\n");
}

void test_generic_strings() {
    char *s1 = "dax";
    char *s2 = "adam";

    swap(&s1, &s2, sizeof(char *));  // Assuming swap is implemented in exercise.h

    assert(s1 == "adam" && "s1 should be s2's original value");
    assert(s2 == "dax" && "s2 should be s1's original value");

    assert(boot_all_freed() && "All memory should be freed");

    printf("test_generic_strings passed\n");
}

void test_generic_structs() {
    coffee_shop_t sbucks = {2, 3, 4};
    coffee_shop_t terminalshop = {10, 10, 10};

    swap(&sbucks, &terminalshop, sizeof(coffee_shop_t));  // Assuming swap is implemented

    // Assert the values of the structs after swap
    assert(sbucks.quality == 10 && "sbucks.quality should be terminalshop.quality");
    assert(sbucks.taste == 10 && "sbucks.taste should be terminalshop.taste");
    assert(sbucks.branding == 10 && "sbucks.branding should be terminalshop.branding");

    assert(terminalshop.quality == 2 && "terminalshop.quality should be sbucks.quality");
    assert(terminalshop.taste == 3 && "terminalshop.taste should be sbucks.taste");
    assert(terminalshop.branding == 4 && "terminalshop.branding should be sbucks.branding");

    printf("test_generic_structs passed\n");
}

int main() {
    printf("Running tests...\n");

    // Call each test function directly
    test_generic_ints();
    test_generic_strings();
    test_generic_structs();

    printf("All tests passed!\n");
    return 0;
}
