/*
** EPITECH PROJECT, 2020
** RType
** File description:
** Created by Emilien
*/

#include "Lobby.hpp"

Lobby::Lobby(int id, char nbSlots) : _id(id), _nbSlots(nbSlots), _gameRunning(false)
{
}

void Lobby::run()
{
}

void Lobby::join(Client *cli)
{
}

void Lobby::leave(Client *cli)
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

char Lobby::getEmptySlots() const
{
    return (char)(this->_nbSlots - (char)this->_players.size());
}
