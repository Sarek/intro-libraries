#include <iostream>

void foobar(int value)
{
    std::cout << "The integer variant of foobar was called with " << value << std::endl;
}

void foobar(double value)
{
    std::cout << "The double variant of foobar was called with " << value << std::endl;
}

int main()
{
    foobar(42);
    foobar(42.0);
}
