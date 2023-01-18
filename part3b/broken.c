#include <stdio.h>

void foobar(int value)
{
    printf("The integer variant of foobar was called with %d\n", value);
}

void foobar(double value)
{
    printf("The double variant of foobar was called with %d\n", value);
}

int main()
{
    foobar(42);
    foobar(42.0);
}
