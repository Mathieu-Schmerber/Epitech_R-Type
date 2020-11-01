/*
** EPITECH PROJECT, 2020
** RType
** File description:
** Created by Emilien
*/

#ifndef RTYPE_LOBBY_HPP
#define RTYPE_LOBBY_HPP

#include "Client.hpp"
#include <vector>
#include <thread>

class Lobby {
public:
    explicit Lobby(int id, char nbSlots);
    void run();

    void join(Client *cli);
    void leave(Client *cli);

    int getId() const;
    bool isInGame() const;
    char getSlots() const;
    char getEmptySlots() const;
private:
    std::vector<Client> _players{};
    std::thread _thread{};
    int _id;
    char _nbSlots;
    bool _gameRunning;
};

#endif //RTYPE_LOBBY_HPP