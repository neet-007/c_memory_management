#ifndef BOOTLIB_H
#define BOOTLIB_H

#include <stdbool.h>  
#include <stddef.h>

bool boot_all_freed(void);


bool boot_is_freed(void* ptr);

void* boot_malloc(size_t size);
void boot_free(void* ptr);

#endif 
