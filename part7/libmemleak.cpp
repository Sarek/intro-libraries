#include <dlfcn.h>
#include <malloc.h>
#include <stdlib.h>
#include <stdio.h>

#include <iostream>

using malloc_t = void*(*)(size_t);
using free_t = void(*)(void*);

size_t& getAllocatedMemory()
{
    static size_t allocatedMemory;
    return allocatedMemory;
}

extern "C" {

void* malloc(size_t size) {
    static std::ios_base::Init streamGuard;
    static malloc_t nextMalloc = reinterpret_cast<malloc_t>(dlsym(RTLD_NEXT, "malloc"));
    if (nextMalloc == nullptr) {
        return nullptr;
    }

    void* allocation = nextMalloc(size);
    size_t usableSize = malloc_usable_size(allocation);
    std::cerr << "Request to allocate " << size << " bytes, actually allocated " << usableSize << " bytes." << std::endl;

    auto& allocatedMemory = getAllocatedMemory();
    allocatedMemory += usableSize;

    return allocation;
}


void free(void* ptr) {
    static free_t nextFree = reinterpret_cast<free_t>(dlsym(RTLD_NEXT, "free"));
    if (nextFree == nullptr) {
        return;
    }

    size_t usableSize = malloc_usable_size(ptr);
    auto& allocatedMemory = getAllocatedMemory();
    allocatedMemory -= usableSize;
    nextFree(ptr);
}

__attribute__((__destructor__)) void printResult()
{
    std::ios_base::Init streamGuard;
    auto& remainingMemory = getAllocatedMemory();
    if (remainingMemory <= 73744) { // The C++ standard library allocates 73477 bytes on startup
        std::cerr << "No memory leak detected!" << std::endl;
        return;
    }

    std::cerr << remainingMemory - 73744 << " bytes of memory were leaked!" << std::endl;
}

__attribute__((__constructor__)) void startup()
{
    std::ios_base::Init streamGuard;
    std::cout << "Executing with instrumentation" << std::endl;
}

}
