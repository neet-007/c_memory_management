#include "include/exercise.h"
#include <stdio.h>

void test_zero_out_integer() {
    snek_int_t integer;
    integer.value = 42;
    snek_zero_out(&integer, INTEGER);
    if (integer.value != 0) {
        printf("Test failed: Integer should be zeroed out to 0, but got %d\n", integer.value);
    } else {
        printf("Test passed: Integer zeroed out correctly.\n");
    }
}

void test_zero_out_float() {
    snek_float_t float_num;
    float_num.value = 3.14;
    snek_zero_out(&float_num, FLOAT);
    if (float_num.value != 0.0) {
        printf("Test failed: Float should be zeroed out to 0.0, but got %f\n", float_num.value);
    } else {
        printf("Test passed: Float zeroed out correctly.\n");
    }
}

void test_zero_out_bool() {
    snek_bool_t boolean;
    boolean.value = 1;
    snek_zero_out(&boolean, BOOL);
    if (boolean.value != 0) {
        printf("Test failed: Boolean should be zeroed out to 0, but got %d\n", boolean.value);
    } else {
        printf("Test passed: Boolean zeroed out correctly.\n");
    }
}

void test_zero_out_nonzero_values() {
    snek_int_t integer;
    snek_float_t float_num;
    snek_bool_t boolean;

    integer.value = -100;
    float_num.value = -99.99;
    boolean.value = 255;

    snek_zero_out(&integer, INTEGER);
    snek_zero_out(&float_num, FLOAT);
    snek_zero_out(&boolean, BOOL);

    if (integer.value != 0) {
        printf("Test failed: Negative integer should be zeroed out to 0, but got %d\n", integer.value);
    } else {
        printf("Test passed: Negative integer zeroed out correctly.\n");
    }

    if (float_num.value != 0.0) {
        printf("Test failed: Negative float should be zeroed out to 0.0, but got %f\n", float_num.value);
    } else {
        printf("Test passed: Negative float zeroed out correctly.\n");
    }

    if (boolean.value != 0) {
        printf("Test failed: Non-zero boolean should be zeroed out to 0, but got %d\n", boolean.value);
    } else {
        printf("Test passed: Non-zero boolean zeroed out correctly.\n");
    }
}

int main() {
    // Execute each test
    printf("Running tests...\n");
    test_zero_out_integer();
    test_zero_out_float();
    test_zero_out_bool();
    test_zero_out_nonzero_values();

    return 0; // Return 0 to indicate success
}
