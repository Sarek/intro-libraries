#include <stdio.h>

__asm__(".symver foo_v1,foo@VER_1");
__asm__(".symver foo_v2,foo@@VER_2");

void foo_v1()
{
    printf("Foo v1\n");
}

void foo_v2()
{
    printf("Foo v2\n");
}

void bar()
{
    printf("bar\n");
}