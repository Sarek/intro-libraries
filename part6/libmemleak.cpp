#include <dlfcn.h>
#include <malloc.h>

#include <iostream>

using malloc_t = void*(*)(size_t);

extern "C" {

void* malloc(size_t size)
{
    static std::ios_base::Init streamGuard;

    malloc_t nextMalloc = reinterpret_cast<malloc_t>(dlsym(RTLD_NEXT, "malloc"));
    if (nextMalloc == nullptr) {
        return nullptr;
    }

    void* allocation = nextMalloc(size);
    size_t usableSize = malloc_usable_size(allocation);
    std::cerr << "Request to allocate " << size << " bytes, actually allocated " << usableSize << " bytes." << std::endl;
    return allocation;
}

}
