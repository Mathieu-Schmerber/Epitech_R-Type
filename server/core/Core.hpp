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

#ifdef _WIN32
    #define _WIN32_WINNT  0x0601
#endif

class Core {
public:
    explicit Core();
    void run();
private:
    std::vector<Client> _connected{};
    std::unique_ptr<LobbyManager> _lobbyManager;
};

#endif //RTYPE_CORE_HPP
