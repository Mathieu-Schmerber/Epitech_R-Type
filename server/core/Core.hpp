/*
** EPITECH PROJECT, 2020
** RType
** File description:
** Created by Emilien
*/

#ifndef RTYPE_CORE_HPP
#define RTYPE_CORE_HPP

#ifdef _WIN32
    #define _WIN32_WINNT  0x0601
#endif

#include <vector>
#include <memory>
#include "Client.hpp"
#include "LobbyManager.hpp"
#include "TcpSocket.hpp"

class Core {
public:
    explicit Core();
    [[noreturn]] void run();
private:
    Server server;
    std::vector<Client> _connected{};
    std::unique_ptr<LobbyManager> _lobbyManager;
};

#endif //RTYPE_CORE_HPP
