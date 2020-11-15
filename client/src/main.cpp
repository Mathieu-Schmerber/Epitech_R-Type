#include <iostream>
#include "Core.hpp"

int main(int ac, char **av)
{
    if (ac != 2) {
        std::cerr << "./r-type_client ip_server" << std::endl;
        return (84);
    }
    auto core = std::make_unique<Core>(std::string(av[1]));

    core->start();
    return 0;
}