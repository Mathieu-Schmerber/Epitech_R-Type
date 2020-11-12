#include <iostream>
#include <Core.hpp>

int main()
{
    auto core = std::make_unique<Core>();

    core->start();
    return 0;
}