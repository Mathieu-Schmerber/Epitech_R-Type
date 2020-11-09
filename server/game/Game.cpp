//
// Created by mathi on 06/11/2020.
//

#include "Game.hpp"

#include <memory>
#include "tools/Geometry.hpp"
#include "entities/ParallaxSlide.hpp"
#include "systems/AnimationSystem.hpp"
#include "systems/ParallaxSystem.hpp"
#include "systems/PhysicSystem.hpp"
#include "systems/MoveSystem.hpp"
#include "systems/PlayerSystem.hpp"
#include "systems/ServerNetworkSystem.hpp"
#include "components/NetworkComponent.hpp"

Game::Game(std::vector<Client> &players, std::unique_ptr<UdpSocketInput> &reception)
: _players(players), _reception(reception), _idIncrement(0), _running(true)
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
    std::unique_ptr<Engine::ASprite> menuParralaxA = std::make_unique<DataSprite>("../../client/assets/images/parallax/parallax_2_3840_1080.png",
                                                                                  Engine::Box<int>{0, 3840, 0, 1080});
    std::unique_ptr<Engine::ASprite> menuParralaxB = std::make_unique<DataSprite>("../../client/assets/images/parallax/parallax_2_3840_1080.png",
                                                                                  Engine::Box<int>{0, 3840, 0, 1080});
    std::shared_ptr<Engine::Entity> slideA = std::make_shared<Engine::ParallaxSlide>(Engine::Point<int>{0, 0}, Engine::Point<int>{-3840, 0}, Engine::Vector<double>{-10, 0}, std::move(menuParralaxA));
    std::shared_ptr<Engine::Entity> slideB = std::make_shared<Engine::ParallaxSlide>(Engine::Point<int>{3840, 0}, Engine::Point<int>{0, 0}, Engine::Vector<double>{-10, 0}, std::move(menuParralaxB));
    std::shared_ptr<Engine::Entity> player = std::make_shared<Player>(0, Engine::Point<int>{50, 50});

    std::cout << slideA->getComponent<Engine::SpriteComponent>()->getSprite()->getRect().size.x << std::endl;
    this->spawn(player, true);
    //this->spawn(slideA, true);
    //this->spawn(slideB, true);
}

void Game::initGameSystems()
{
    auto move = std::make_unique<Engine::MoveSystem>();
    auto parallax = std::make_unique<Engine::ParallaxSystem>();
    auto network = std::make_unique<ServerNetworkSystem>(this->_players, this->_reception);
    auto animation = std::make_unique<Engine::AnimationSystem>();
    auto physic = std::make_unique<Engine::PhysicSystem>();
    auto players = std::make_unique<PlayerSystem>();

    this->_systems.push_back(std::move(move));
    this->_systems.push_back(std::move(parallax));
    this->_systems.push_back(std::move(animation));
    this->_systems.push_back(std::move(physic));
    this->_systems.push_back(std::move(players));
    this->_systems.push_back(std::move(network));
}

void Game::spawn(std::shared_ptr<Engine::Entity> &entity, bool addToNetwork)
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

bool Game::isGameRunning() const
{
    return _running;
}

void Game::update()
{
    for (auto &sys : this->_systems) {
        sys->setDeltatime(this->_timer->deltatime(0.1));
        sys->update();
    }
}