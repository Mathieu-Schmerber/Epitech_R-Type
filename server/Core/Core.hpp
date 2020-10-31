/*
** EPITECH PROJECT, 2020
** RType
** File description:
** Created by Emilien
*/

#ifndef RTYPE_CORE_HPP
#define RTYPE_CORE_HPP

#include <vector>
#include <memory>
#include "Client.hpp"
#include "LobbyManager.hpp"

class Core {
public:
    explicit Core();
    void run();
private:
    std::vector<Client> _connected{};
    std::unique_ptr<LobbyManager> _lobbyManager;
};

#endif //RTYPE_CORE_HPP
