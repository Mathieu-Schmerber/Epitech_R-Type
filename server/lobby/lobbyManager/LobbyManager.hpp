/*
** EPITECH PROJECT, 2020
** RType
** File description:
** Created by Emilien
*/

#ifndef RTYPE_LOBBYMANAGER_HPP
#define RTYPE_LOBBYMANAGER_HPP

#include "Lobby.hpp"
#include <vector>

class LobbyManager {
public:
    explicit LobbyManager();
    Lobby *addLobby(char nbSlots);
    [[nodiscard]] std::vector<Lobby *> getAvailableLobbies() const;
    void removeClientInLobbies(std::shared_ptr<Client> &cli);
    Lobby *getLobbyById(int id);
private:
    std::vector<Lobby *> _lobbys{};
    int _id = 1;
    int _port;
};

#endif //RTYPE_LOBBYMANAGER_HPP
