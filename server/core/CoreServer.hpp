/*
** EPITECH PROJECT, 2020
** RType
** File description:
** Created by Emilien
*/

#ifndef RTYPE_CORESERVER_HPP
#define RTYPE_CORESERVER_HPP

#ifdef _WIN32
    #define _WIN32_WINNT  0x0601
#endif

#include <vector>
#include <memory>
#include "LobbyManager.hpp"

class Session;

class CoreServer {
public:
    explicit CoreServer();
    [[noreturn]] void run();
    void setNewClient(std::shared_ptr<Client>& session);
    void removeClient(int id);
    int getNewId();
private:
    Server server;
    std::vector<std::shared_ptr<Client>> _connected{};
    std::unique_ptr<LobbyManager> _lobbyManager;
    int _currentId = 2;
};


#endif //RTYPE_CORESERVER_HPP
