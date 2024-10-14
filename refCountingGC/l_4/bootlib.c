#include "include/bootlib.h"
#include <stdbool.h>
#include <stddef.h> 
#include <stdlib.h>

static size_t allocation_count = 0;  
static void* last_allocated_ptr = NULL; 

void* boot_malloc(size_t size) {
    void* ptr = malloc(size);
    if (ptr != NULL) {
        allocation_count++;  
        last_allocated_ptr = ptr; 
    }
    return ptr;
}

void boot_free(void* ptr) {
    if (ptr != NULL) {
        free(ptr);
        allocation_count--; 
        if (last_allocated_ptr == ptr) {
            last_allocated_ptr = NULL; 
        }
    }
}

bool boot_all_freed(void) {
    return allocation_count == 0; 
}

bool boot_is_freed(void* ptr) {
    if (ptr == NULL) {
        return false; 
    }

    return (last_allocated_ptr != ptr);
}
