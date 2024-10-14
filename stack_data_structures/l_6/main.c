#include "include/bootlib.h"
#include "include/exercise.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

// Test to create a stack and verify its properties
void create_stack() {
    stack_t *s = stack_new(10);
    
    assert(s->capacity == 10 && "Sets capacity to 10");
    assert(s->count == 0 && "No elements in the stack yet");
    assert(s->data != NULL && "Allocates the stack data");

    // Clean up allocated data
    free(s->data);
    free(s);

    // Check if all memory is freed
    assert(boot_all_freed() && "Memory should be freed");
    
    printf("create_stack passed\n");
}

// Test pushing elements into the stack
void push_stack() {
    stack_t *s = stack_new(2);
    assert(s != NULL && "Must allocate a new stack");

    assert(s->capacity == 2 && "Sets capacity to 2");
    assert(s->count == 0 && "No elements in the stack yet");
    assert(s->data != NULL && "Allocates the stack data");

    int a = 1;

    stack_push(s, &a);
    stack_push(s, &a);

    assert(s->capacity == 2 && "Capacity should remain 2");
    assert(s->count == 2 && "Stack should contain 2 elements");

    // Clean up allocated data
    free(s->data);
    free(s);

    // Check if all memory is freed
    assert(boot_all_freed() && "Memory should be freed");
    
    printf("push_stack passed\n");
}

// Test doubling the stack capacity after pushing more elements
void push_double_capacity() {
    stack_t *s = stack_new(2);
    assert(s != NULL && "Must allocate a new stack");

    assert(s->capacity == 2 && "Sets capacity to 2");
    assert(s->count == 0 && "No elements in the stack yet");
    assert(s->data != NULL && "Allocates the stack data");

    int a = 1;

    stack_push(s, &a);
    stack_push(s, &a);

    assert(s->capacity == 2 && "Capacity should remain 2");
    assert(s->count == 2 && "Stack should contain 2 elements");

    stack_push(s, &a);
    assert(s->capacity == 4 && "Capacity should be doubled to 4");
    assert(s->count == 3 && "Stack should contain 3 elements");

    // Clean up allocated data
    free(s->data);
    free(s);

    // Check if all memory is freed
    assert(boot_all_freed() && "Memory should be freed");
    
    printf("push_double_capacity passed\n");
}

int main() {
    printf("Running tests...\n");
    
    create_stack();
    push_stack();
    push_double_capacity();

    printf("All tests passed!\n");

    return 0;
}
