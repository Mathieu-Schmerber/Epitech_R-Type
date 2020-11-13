/*
** EPITECH PROJECT, 2020
** RType
** File description:
** Created by Emilien
*/

#include "LobbyManager.hpp"
#include "Client.hpp"

LobbyManager::LobbyManager() : _port(4243)
{
    auto *nLobby = new Lobby(this->_id, 4, _port++);

    this->_lobbys.push_back(nLobby);
}

Lobby *LobbyManager::addLobby(char nbSlots = 4)
{
    try {
        auto *nLobby = new Lobby(this->_id++, nbSlots, _port++);

        this->_lobbys.push_back(nLobby);
        nLobby->run();
        return nLobby;
    } catch (std::bad_alloc &) {
        return nullptr;
    }
}

std::vector<Lobby *> LobbyManager::getAvailableLobbies() const
{
    std::vector<Lobby *> output;

    for (auto a : this->_lobbys) {
        if (a && !a->isInGame())
            output.push_back(a);
    }
    return output;
}

Lobby *LobbyManager::getLobbyById(int id)
{
    for (auto &a : this->_lobbys) {
        if (a->getId() == id)
            return (a);
    }
    return nullptr;
}
