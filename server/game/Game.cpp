//
// Created by mathi on 06/11/2020.
//

#include "Game.hpp"
#include "systems/MoveSystem.hpp"
#include "systems/ServerNetworkSystem.hpp"

Game::Game(std::vector<Client> &players, std::unique_ptr<UdpSocketInput> &reception) : _players(players), _reception(reception)
{
    this->initGameSystems();
    this->initGameEntities();
}

Game::~Game()
{
    this->_systems.clear();
    this->_entities.clear();
    this->_players.clear();
}

void Game::initGameEntities()
{

}

void Game::initGameSystems()
{
    auto move = std::make_unique<Engine::MoveSystem>();
    auto network = std::make_unique<ServerNetworkSystem>();

    this->_systems.push_back(std::move(move));
    this->_systems.push_back(std::move(network));
}

void Game::update()
{

}