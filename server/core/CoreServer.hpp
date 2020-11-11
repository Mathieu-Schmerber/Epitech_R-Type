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

class Client;

class CoreServer {
public:
    explicit CoreServer();
private:
};


#endif //RTYPE_CORESERVER_HPP
