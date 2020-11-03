/*
** EPITECH PROJECT, 2020
** RType
** File description:
** Created by Emilien
*/

#include "CoreServer.hpp"

CoreServer::CoreServer() : _currentId(2), server(4242, this)
{
    std::cout << "Core init" << std::endl;
}

void CoreServer::run()
{
    server.start();
    while (true) {
        for (auto &a : _connected) {
            auto pouet = a->getNextMessage();
            if (pouet)
                std::cout << "New message : " << pouet << std::endl;
        }
    }
    server.stop();
}

void CoreServer::setNewClient(std::shared_ptr<Client>& client)
{
    this->_connected.push_back(client);
}

void CoreServer::removeClient(int id)
{
    if (_connected.begin() == _connected.end()) {
        std::cout << "=================" << std::endl;
        Sleep(5000);
        return;
    }
    std::cout << "id first " << _connected.begin()->get()->getId() << " && " << id << std::endl;
    for (auto i = _connected.begin(); i != _connected.end(); i++) {
        if (i->get()->getId() == id) {
            _connected.erase(i);
            std::cout << "ID : " << id << " deleted" << std::endl;
            return;
        }
    }
}

int CoreServer::getNewId()
{
    ++_currentId;
    std::cout << "New client ID : " << _currentId << std::endl;
    return (_currentId);
}
