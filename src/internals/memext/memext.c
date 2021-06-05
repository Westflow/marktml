#include <internals/errors/error.h>
#include <internals/memext/memext.h>

void* memalloc(size_t block_size)
{
    if (block_size == 0)
    {
        return NULL;
    }
    void* memblock = malloc(block_size);
    if (!memblock)
    {
        throw_error(ErrorOutOfMemory, "malloc");
    }
    return memblock;
}

void* memcalloc(size_t elem_count, size_t elem_size)
{
    if (elem_count == 0 || elem_size == 0)
    {
        return NULL;
    }
    void* memblock = calloc(elem_count, elem_size);
    if (!memblock)
    {
        throw_error(ErrorOutOfMemory, "calloc");
    }
    return memblock;
}

void* memrealloc(void* memblock, size_t new_size)
{
    void* new_block = realloc(memblock, new_size);
    if (!new_block)
    {
        throw_error(ErrorOutOfMemory, "realloc");
    }
    return new_block;
}

void memfree(void* memblock)
{
    if (memblock)
    {
        free(memblock);
    }
}