/*
** EPITECH PROJECT, 2020
** RType
** File description:
** Created by Emilien
*/

#ifndef RTYPE_CORE_HPP
#define RTYPE_CORE_HPP

#include <vector>
#include "Client.hpp"

class Core {
public:
    explicit Core();
    void run();
private:
    std::vector<Client> _connected{};
};

#endif //RTYPE_CORE_HPP
