#ifndef MEMEXT_H
#define MEMEXT_H

#include <stdlib.h>

void* memalloc(size_t block_size);
void* memcalloc(size_t block_size, size_t elem_size);
void* memrealloc(void* memblock, size_t new_size);
void memfree(void* memblock);

#endif