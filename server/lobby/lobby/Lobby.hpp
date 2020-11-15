/*
** EPITECH PROJECT, 2020
** RType
** File description:
** Created by Emilien
*/

#ifndef RTYPE_LOBBY_HPP
#define RTYPE_LOBBY_HPP

#include <vector>
#include <thread>
#include "networking/UDP/UdpSocketInput.hpp"

class Client;
class Game;

class Lobby {
public:
    explicit Lobby(int id, char nbSlots, int port);
    void run();

    void join(const std::shared_ptr<Client> &cli);
    void leave(const std::shared_ptr<Client> &cli);

    [[nodiscard]] int getId() const;
    [[nodiscard]] bool isInGame() const;
    [[nodiscard]] char getSlots() const;
    [[nodiscard]] char getNbPlayers() const;
    [[nodiscard]] int getPort() const;
private:
    std::vector<std::shared_ptr<Client>> _players{};
    std::thread _thread{};
    int _id;
    int _port;
    char _nbSlots;
    bool _gameRunning;
    std::unique_ptr<Game> _game;
    std::unique_ptr<UdpSocketInput> _udpSocketInput;
};

#endif //RTYPE_LOBBY_HPP
