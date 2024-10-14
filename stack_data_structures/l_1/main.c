#include "include/bootlib.h"
#include "include/exercise.h"
#include <assert.h>
#include <stdio.h>

// Function to test creating a small stack
void create_stack_small() {
    stack_t *s = stack_new(3);

    // Assert the properties of the stack
    assert(s->capacity == 3 && "Sets capacity to 3");
    assert(s->count == 0 && "No elements in the stack yet");
    assert(s->data != NULL && "Allocates the stack data");

    // Free the stack memory
    free(s->data);
    free(s);

    // Check if all allocated memory is freed
    assert(boot_all_freed() && "All memory should be freed");

    printf("create_stack_small passed\n");
}

// Function to test creating a large stack
void create_stack_large() {
    stack_t *s = stack_new(100);

    // Assert the properties of the stack
    assert(s->capacity == 100 && "Sets capacity to 100");
    assert(s->count == 0 && "No elements in the stack yet");
    assert(s->data != NULL && "Allocates the stack data");

    // Free the stack memory
    free(s->data);
    free(s);

    // Check if all allocated memory is freed
    assert(boot_all_freed() && "All memory should be freed");

    printf("create_stack_large passed\n");
}

// Main function to run the tests
int main() {
    printf("Running tests...\n");

    // Call each test function manually
    create_stack_small();
    create_stack_large();

    printf("All tests passed!\n");
    return 0;
}
