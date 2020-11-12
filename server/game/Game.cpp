//
// Created by mathi on 06/11/2020.
//

#include <memory>
#include "tools/Geometry.hpp"
#include "entities/ParallaxSlide.hpp"
#include "systems/ProjectileSystem.hpp"
#include "systems/AnimationSystem.hpp"
#include "systems/ParallaxSystem.hpp"
#include "systems/PhysicSystem.hpp"
#include "systems/MoveSystem.hpp"
#include "systems/PlayerSystem.hpp"
#include "systems/ServerNetworkSystem.hpp"
#include "systems/GroundSystem.hpp"
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
    std::shared_ptr<Engine::Entity> player = std::make_shared<Player>(0, Engine::Point<int>{50, 50});

    auto parallaxA = std::make_unique<DataSprite>("../../client/assets/images/parallax/parallax_2_3840_1080.png");
    auto parallaxB = std::make_unique<DataSprite>("../../client/assets/images/parallax/parallax_2_3840_1080.png");
    //auto parallaxC = std::make_unique<DataSprite>("../../client/assets/images/platform/bottom_platform_full.png");
    //auto parallaxD = std::make_unique<DataSprite>("../../client/assets/images/platform/bottom_platform_full.png");
    parallaxA->setRect({{0, 0}, {3840, 1080}});
    parallaxB->setRect({{0, 0}, {3840, 1080}});
    //parallaxC->setRect({{0, 0}, {3940, 70}});
    //parallaxD->setRect({{0, 0}, {3940, 70}});
    std::shared_ptr<Engine::Entity> slideA = std::make_shared<Engine::ParallaxSlide>(Engine::Point<int>{0, 0}, Engine::Point<int>{-3840, 0}, Engine::Point<double>{-10, 0}, std::move(parallaxA));
    std::shared_ptr<Engine::Entity> slideB = std::make_shared<Engine::ParallaxSlide>(Engine::Point<int>{3840, 0}, Engine::Point<int>{0, 0}, Engine::Point<double>{-10, 0}, std::move(parallaxB));
    //std::shared_ptr<Engine::Entity> groundA = std::make_shared<Engine::ParallaxSlide>(Engine::Point<int>{0, 1010}, Engine::Point<int>{-3940, 1010}, Engine::Point<double>{-20, 0}, std::move(parallaxC));
    //std::shared_ptr<Engine::Entity> groundB = std::make_shared<Engine::ParallaxSlide>(Engine::Point<int>{3940, 1010}, Engine::Point<int>{0, 1010}, Engine::Point<double>{-20, 0}, std::move(parallaxD));
    std::shared_ptr<Engine::Entity> ground = std::make_shared<Ground>(Engine::Point<int>{200, 200}, Engine::Point<int>{0, 0}, Engine::Vector<double>{0, 0});

    this->spawn(player, true);
    this->spawn(slideA, true);
    this->spawn(slideB, true);
    //this->spawn(groundA, true);
    //this->spawn(groundB, true);
}

void Game::initGameSystems()
{
    auto game = std::shared_ptr<Game>(this);
    auto move = std::make_unique<Engine::MoveSystem>();
    auto parallax = std::make_unique<Engine::ParallaxSystem>();
    auto network = std::make_unique<ServerNetworkSystem>(this->_players, this->_reception);
    auto animation = std::make_unique<Engine::AnimationSystem>();
    auto physic = std::make_unique<Engine::PhysicSystem>();
    auto players = std::make_unique<PlayerSystem>(game);
    auto projectiles = std::make_unique<ProjectileSystem>(game);
    auto ground = std::make_unique<GroundSystem>(game);

    this->_systems.push_back(std::move(move));
    this->_systems.push_back(std::move(ground));
    this->_systems.push_back(std::move(parallax));
    this->_systems.push_back(std::move(animation));
    this->_systems.push_back(std::move(physic));
    this->_systems.push_back(std::move(players));
    this->_systems.push_back(std::move(projectiles));
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

void Game::despawn(std::shared_ptr<Engine::Entity> &entity)
{
    for (auto &sys : this->_systems) {
        if (entity->hasComponents(sys->getDependencies()))
            sys->deleteEntity(entity);
    }
    Engine::Utils::removeFromVector(this->_entities, entity);
}

bool Game::isGameRunning() const
{
    return _running;
}

void Game::update()
{
    int serverTicks = 60;
    double time;

    std::cout << "Game entities " << this->_entities.size() << std::endl;
    if (Engine::Timer::hasElapsed(this->_timer->getLastPoint(), 1.0 / serverTicks)) {
        time = this->_timer->deltatime();
        for (auto &sys : this->_systems) {
            sys->setDeltatime(time);
            sys->update();
        }
    }
}