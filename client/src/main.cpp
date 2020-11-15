/*!
 * @file main.cpp
 * @brief client main
 * @authors Paul.S
 * @version 1.0
 * @date 14/11/2020
 *
*/

/*!
 * \brief Client main
 *
 * Call start function of the core and then return 0
*/

#include <iostream>
#include "tools/EngineExceptions.hpp"
#include "Core.hpp"

int main(int ac, char **av)
{
    if (ac != 2) {
        std::cerr << "./r-type_client ip_server" << std::endl;
        return (84);
    }
    std::unique_ptr<Core> core = nullptr;
    try {
        core = std::make_unique<Core>(std::string(av[1]));
    } catch (Engine::EngineException &e) {
        std::cerr << e << std::endl;
        return (84);
    }
    if (core)
        core->start();
    else
        return (84);
    return 0;
}