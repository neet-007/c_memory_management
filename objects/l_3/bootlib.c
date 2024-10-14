#include "include/bootlib.h"
#include <stdlib.h>

static size_t allocation_count = 0;  // Tracks the number of active allocations

// A function that returns true if all memory allocations have been freed
bool boot_all_freed(void) {
    return allocation_count == 0;
}

// Custom malloc that increments the allocation count
void* boot_malloc(size_t size) {
    void* ptr = malloc(size);
    if (ptr != NULL) {
        allocation_count++;
    }
    return ptr;
}

// Custom free that decrements the allocation count
void boot_free(void* ptr) {
    if (ptr != NULL) {
        free(ptr);
        allocation_count--;
    }
}
