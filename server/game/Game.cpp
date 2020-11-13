//
// Created by mathi on 06/11/2020.
//

#include <memory>
#include "systems/SpawnerSystem.hpp"
#include "Game.hpp"
#include "systems/AutomaticWeaponSystem.hpp"
#include "systems/EnemySystem.hpp"
#include "systems/ChildrenSystem.hpp"
#include "entities/ParallaxSlide.hpp"
#include "entities/Spawner.hpp"
#include "systems/ProjectileSystem.hpp"
#include "systems/AnimationSystem.hpp"
#include "systems/ParallaxSystem.hpp"
#include "systems/PhysicSystem.hpp"
#include "systems/MoveSystem.hpp"
#include "systems/PlayerSystem.hpp"
#include "systems/ServerNetworkSystem.hpp"
#include "systems/LifetimeSystem.hpp"
#include "systems/GroundSystem.hpp"
#include "components/NetworkComponent.hpp"
#include "entities/Collectible.hpp"

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
    std::shared_ptr<Engine::Entity> player = std::make_shared<Player>(0, Engine::Point<double>{500, 500});

    auto parallaxA = std::make_unique<DataSprite>("../../client/assets/images/parallax/parallax_2_3840_1080.png");
    auto parallaxB = std::make_unique<DataSprite>("../../client/assets/images/parallax/parallax_2_3840_1080.png");
    parallaxA->setRect({{0, 0}, {3840, 1080}});
    parallaxB->setRect({{0, 0}, {3840, 1080}});
    std::shared_ptr<Engine::Entity> slideA = std::make_shared<Engine::ParallaxSlide>(Engine::Point<double>{0, 0}, Engine::Point<double>{-3840, 0}, Engine::Point<double>{-15, 0}, std::move(parallaxA));
    std::shared_ptr<Engine::Entity> slideB = std::make_shared<Engine::ParallaxSlide>(Engine::Point<double>{3840, 0}, Engine::Point<double>{0, 0}, Engine::Point<double>{-15, 0}, std::move(parallaxB));
    std::shared_ptr<Engine::Entity> bonusTest = std::make_shared<Collectible>(Engine::Point<double>{1000, 500}, CollectibleComponent::SENTINEL);

    auto spawner = std::make_shared<Spawner>();

    this->spawn(player, true);
    this->spawn(slideA, true);
    this->spawn(slideB, true);
    this->spawn(bonusTest, true);
    //this->spawn(spawner, false);
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
    auto enemy = std::make_unique<EnemySystem>(game);
    auto autoWeapon = std::make_unique<AutomaticWeaponSystem>(game);
    auto lifetime = std::make_unique<LifetimeSystem>(game);
    auto children = std::make_unique<Engine::ChildrenSystem>();
    auto spawner = std::make_unique<SpawnerSystem>(game);

    this->_systems.push_back(std::move(move));
    this->_systems.push_back(std::move(ground));
    this->_systems.push_back(std::move(parallax));
    this->_systems.push_back(std::move(animation));
    this->_systems.push_back(std::move(physic));
    this->_systems.push_back(std::move(players));
    this->_systems.push_back(std::move(projectiles));
    this->_systems.push_back(std::move(enemy));
    this->_systems.push_back(std::move(autoWeapon));
    this->_systems.push_back(std::move(lifetime));
    this->_systems.push_back(std::move(children));
    this->_systems.push_back(std::move(network));
    this->_systems.push_back(std::move(spawner));
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

    if (Engine::Timer::hasElapsed(this->_timer->getLastPoint(), 1.0 / serverTicks)) {
        time = this->_timer->deltatime();
        for (auto &sys : this->_systems) {
            sys->setDeltatime(time);
            sys->update();
        }
    }
}