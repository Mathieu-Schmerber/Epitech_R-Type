/*
** EPITECH PROJECT, 2020
** RType
** File description:
** Created by Emilien
*/

#include "CoreServer.hpp"

CoreServer::CoreServer() : server(4242, this)
{

}

void CoreServer::run()
{
    server.start();
    while (true) {
        std::cout << this->_connected.size() << std::endl;
        Sleep(1000);
    };
    server.stop();
}

void CoreServer::setNewClient(std::shared_ptr<Client>& client)
{
    this->_connected.push_back(client);
}