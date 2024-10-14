#include <stdlib.h>
#include <stdio.h>

#include "include/exercise.h"
#include "include/munit.h"

void test_allocate() {
    int *pointer = NULL;
    allocate_int(&pointer, 10);

    if (pointer == NULL) {
        printf("Failed to allocate pointer\n");
        return; // Exit the test if allocation failed
    }
    if (*pointer != 10) {
        printf("Expected value to be 10, but got %d\n", *pointer);
    } else {
        printf("Pointer allocated successfully with value: %d\n", *pointer);
    }

    free(pointer); // Free the allocated memory
}

void test_does_not_overwrite() {
    int value = 5;
    int *pointer = &value;

    allocate_int(&pointer, 20);

    // Free the previous pointer if it's not pointing to a stack variable
    if (pointer != &value) {
        free(pointer);
    }

    if (value != 5) {
        printf("Original value was overwritten. Expected: 5, Got: %d\n", value);
    } else {
        printf("Original value remains unchanged: %d\n", value);
    }

    if (pointer == NULL) {
        printf("Failed to allocate pointer\n");
    } else {
        if (*pointer != 20) {
            printf("Expected value to be 20, but got %d\n", *pointer);
        } else {
            printf("Pointer allocated successfully with value: %d\n", *pointer);
        }

        free(pointer); // Free the new allocation
    }
}

int main() {
    printf("Running tests...\n");
    
    printf("Test: Allocate\n");
    test_allocate();

    printf("Test: Does Not Overwrite\n");
    test_does_not_overwrite();

    return 0;
}
