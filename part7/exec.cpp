#include <iostream>
#include <memory>

struct my_struct
{
    uint8_t alpha;
    double beta;
    uint16_t delta;
    uint64_t gamma;
};

struct my_other_struct
{
    double beta;
    uint64_t gamma;
    uint16_t delta;
    uint8_t alpha;
};

int main()
{
    std::cout << "Started main" << std::endl;
    auto my_struct_ptr = std::make_unique<my_struct>();
    auto my_other_struct_ptr = std::make_unique<my_other_struct>();
    std::cout << "main executed" << std::endl;
}
