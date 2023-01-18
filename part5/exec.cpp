#include <dlfcn.h>

#include <iostream>

using foo_t = double(*)(int);

int main()
{
    foo_t foo_func = reinterpret_cast<foo_t>(dlsym(RTLD_NEXT, "foo"));
    if (foo_func == nullptr) {
        std::cerr << "Could not find \"foo\" function!" << std::endl;
        exit(1);
    }

    double result = foo_func(42);

    std::cout << "Received result: " << result << std::endl;
}
