/*
** EPITECH PROJECT, 2020
** RType
** File description:
** Created by Emilien
*/

#include "LobbyManager.hpp"
#include "Client.hpp"

LobbyManager::LobbyManager() : _port(4243)
{}

Lobby *LobbyManager::addLobby(char nbSlots = 4)
{
    try {
        auto *nLobby = new Lobby(this->_id++, nbSlots, _port++);

        this->_lobbys.push_back(nLobby);
        return nLobby;
    } catch (std::bad_alloc &a) {
        std::cerr << "Error Lobby alloc " << a.what() << std::endl;
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
    std::cout << "Return size lobbies : " << output.size() << " && " << this->_lobbys.size() << std::endl;
    return output;
}

void LobbyManager::removeClientInLobbies(std::shared_ptr<Client> &cli)
{
    for (auto &a : _lobbys)
        a->leave(cli);
}

Lobby *LobbyManager::getLobbyById(int id)
{
    for (auto &a : this->_lobbys) {
        if (a->getId() == id)
            return (a);
    }
    return nullptr;
}
