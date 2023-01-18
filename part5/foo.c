#include <stdio.h>

double foo(int value)
{
    double retval = value * value;
    printf("Foo was called with %d, returning %f\n", value, retval);

    return retval;
}
