/*
** EPITECH PROJECT, 2020
** RType
** File description:
** Created by Emilien
*/

#include "LobbyManager.hpp"

LobbyManager::LobbyManager()
{

}

Lobby *LobbyManager::addLobby(char nbSlots = 4)
{
    try {
        auto *nLobby = new Lobby(this->_id, nbSlots);

        ++this->_id;
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