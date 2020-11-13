/*
** EPITECH PROJECT, 2020
** RType
** File description:
** Created by Emilien
*/

#include "Lobby.hpp"
#include "Client.hpp"
#include "Game.hpp"

Lobby::Lobby(int id, char nbSlots, int port) : _id(id), _nbSlots(nbSlots), _gameRunning(false), _port(port)
{
    _udpSocketInput = std::make_unique<UdpSocketInput>(port);
}

void Lobby::run()
{
    std::cout << "Lobby::run" << std::endl;
    std::vector<std::shared_ptr<Client>> cli;
    //cli.push_back(this->_players.front());
    _game = std::make_unique<Game>(cli, _udpSocketInput);
    _gameRunning = true;
    std::cout << "Start game" << std::endl;
    _thread = std::thread([&] { while (_game->isGameRunning()) { _game->update(); } });
    std::cout << "wtf" << std::endl;
}

void Lobby::join(const std::shared_ptr<Client> &cli)
{
    std::cout << "Client " << cli->getId() << " join lobby " << _id << std::endl;
    _players.push_back(cli);
}

void Lobby::leave(const std::shared_ptr<Client>& cli)
{
}

int Lobby::getId() const
{
    return this->_id;
}

bool Lobby::isInGame() const
{
    return this->_gameRunning;
}

char Lobby::getSlots() const
{
    return this->_nbSlots;
}

char Lobby::getNbPlayers() const
{
    return (char)this->_players.size();
}

int Lobby::getPort() const
{
    return _port;
}