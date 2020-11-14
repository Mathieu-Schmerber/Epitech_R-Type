/*!
 * @file main.cpp
 * @brief client main
 * @authors Paul.S
 * @version 1.0
 * @date 14/11/2020
 *
*/

#include <iostream>
#include <Core.hpp>

/*!
 * \brief Client main
 *
 * Call start function of the core and then return 0
*/

int main()
{
    auto core = std::make_unique<Core>();

    core->start();
    return 0;
}