#ifndef BOOTLIB_H
#define BOOTLIB_H

#include <stdbool.h>  // for the bool type
#include <stddef.h>
// Function to check if all memory has been freed
bool boot_all_freed(void);

// Custom functions to track memory allocation and deallocation
void* boot_malloc(size_t size);
void boot_free(void* ptr);

#endif // BOOTLIB_H