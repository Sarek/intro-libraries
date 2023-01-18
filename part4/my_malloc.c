#include <malloc.h>
#include <stdio.h>

// Imagine this somewhere in a larger application
void* __real_malloc(size_t c);

void* __wrap_malloc(size_t c)
{
    void* memory = __real_malloc(c);
    size_t mem_size = malloc_usable_size(memory);

    printf("Allocated %d bytes of memory at %p\n", mem_size, memory);

    return memory;
}
