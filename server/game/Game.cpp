//
// Created by mathi on 06/11/2020.
//

#include "Game.hpp"

#include <memory>
#include "tools/Geometry.hpp"
#include "systems/AnimationSystem.hpp"
#include "systems/ParallaxSystem.hpp"
#include "systems/PhysicSystem.hpp"
#include "systems/MoveSystem.hpp"
#include "systems/PlayerSystem.hpp"
#include "systems/ServerNetworkSystem.hpp"
#include "components/NetworkComponent.hpp"

Game::Game(std::vector<Client> &players, std::unique_ptr<UdpSocketInput> &reception) : _players(players), _reception(reception), _idIncrement(0)
{
    this->_timer = std::make_unique<Engine::Timer>();
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
    auto player = new Player(0, Engine::Point<int>{50, 50});

    this->spawn(std::shared_ptr<Player>(player), true);
}

void Game::initGameSystems()
{
    auto move = std::make_unique<Engine::MoveSystem>();
    auto network = std::make_unique<ServerNetworkSystem>(this->_players, this->_reception);
    auto animation = std::make_unique<Engine::AnimationSystem>();
    auto physic = std::make_unique<Engine::PhysicSystem>();
    auto players = std::make_unique<PlayerSystem>();

    this->_systems.push_back(std::move(move));
    this->_systems.push_back(std::move(animation));
    this->_systems.push_back(std::move(physic));
    this->_systems.push_back(std::move(players));
    this->_systems.push_back(std::move(network));
}

void Game::spawn(std::shared_ptr<Engine::Entity> entity, bool addToNetwork)
{
    auto network = entity->getComponent<Engine::NetworkComponent>();

    if (network) {
        network->setNetworkId(this->_idIncrement);
        this->_idIncrement++;
    } else if (addToNetwork) {
        entity->addComponent<Engine::NetworkComponent>(this->_idIncrement);
        this->_idIncrement++;
    }
    this->_entities.push_back(std::move(entity));
    for (auto &sys : this->_systems) {
        if (this->_entities.back()->hasComponents(sys->getDependencies()))
            sys->addEntity(this->_entities.back());
    }
}

void Game::update()
{
    for (auto &sys : this->_systems) {
        sys->setDeltatime(this->_timer->deltatime(10));
        sys->update();
    }
}