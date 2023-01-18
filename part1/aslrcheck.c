#include <stdio.h>

void myfunc()
{
    printf("Location of myfunc is: %p\n", myfunc);
}

int main()
{
    printf("Location of main is: %p\n", main);
    myfunc();
    printf("Difference between locations is %d bytes\n", ((void*) myfunc) - ((void*) main));
}
