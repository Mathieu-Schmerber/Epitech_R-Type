//
// Created by mathi on 06/11/2020.
//

#include <memory>
#include "Game.hpp"
#include "systems/HealthSystem.hpp"
#include "systems/SpawnerSystem.hpp"
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
#include "systems/PlayerMovementSystem.hpp"
#include "systems/PlayerCollisionSystem.hpp"
#include "systems/PlayerWeaponSystem.hpp"
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
    auto parallaxC = std::make_unique<DataSprite>("../../client/assets/images/platform/bottom_platform_full_3940x71.png");
    auto parallaxD = std::make_unique<DataSprite>("../../client/assets/images/platform/bottom_platform_full_3940x71.png");
    parallaxA->setRect({{0, 0}, {3840, 1080}});
    parallaxB->setRect({{0, 0}, {3840, 1080}});
    parallaxC->setRect({{0, 0}, {3940, 71}});
    parallaxD->setRect({{0, 0}, {3940, 71}});
    std::shared_ptr<Engine::Entity> slideA = std::make_shared<Engine::ParallaxSlide>(Engine::Point<double>{0, 0}, Engine::Point<double>{-3840, 0}, Engine::Point<double>{-15, 0}, std::move(parallaxA));
    std::shared_ptr<Engine::Entity> slideB = std::make_shared<Engine::ParallaxSlide>(Engine::Point<double>{3840, 0}, Engine::Point<double>{0, 0}, Engine::Point<double>{-15, 0}, std::move(parallaxB));
    std::shared_ptr<Engine::Entity> groundA = std::make_shared<Engine::ParallaxSlide>(Engine::Point<double>{0, 1010}, Engine::Point<double>{-3940, 1010}, Engine::Point<double>{-20, 0}, std::move(parallaxC));
    std::shared_ptr<Engine::Entity> groundB = std::make_shared<Engine::ParallaxSlide>(Engine::Point<double>{3940, 1010}, Engine::Point<double>{0, 1010}, Engine::Point<double>{-20, 0}, std::move(parallaxD));
    std::shared_ptr<Engine::Entity> bonusTest = std::make_shared<Collectible>(Engine::Point<double>{1000, 500}, CollectibleComponent::SENTINEL);
    std::shared_ptr<Engine::Entity> bonusTest2 = std::make_shared<Collectible>(Engine::Point<double>{800, 500}, CollectibleComponent::SENTINEL);

    auto spawner = std::make_shared<Spawner>();
    auto test = std::make_shared<Ground>(Engine::Point<double>{1000, 600}, Engine::Point<double>{0, 0}, Engine::Point<double>{0, 0});

    this->spawn(player, true);
    this->spawn(slideA, true);
    this->spawn(slideB, true);
    this->spawn(groundA, true);
    this->spawn(groundB, true);
    this->spawn(bonusTest, true);
    this->spawn(bonusTest2, true);
    this->spawn(test, true);
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
    auto playerMove = std::make_unique<PlayerMovementSystem>();
    auto playerCollide = std::make_unique<PlayerCollisionSystem>(game);
    auto playerWeapon = std::make_unique<PlayerWeaponSystem>(game);
    auto projectiles = std::make_unique<ProjectileSystem>(game);
    //auto ground = std::make_unique<GroundSystem>(game);
    auto enemy = std::make_unique<EnemySystem>(game);
    auto autoWeapon = std::make_unique<AutomaticWeaponSystem>(game);
    auto lifetime = std::make_unique<LifetimeSystem>(game);
    auto children = std::make_unique<Engine::ChildrenSystem>();
    auto spawner = std::make_unique<SpawnerSystem>(game);
    auto life = std::make_unique<HealthSystem>(game);

    this->_systems.push_back(std::move(move));
    //this->_systems.push_back(std::move(ground));
    this->_systems.push_back(std::move(parallax));
    this->_systems.push_back(std::move(animation));
    this->_systems.push_back(std::move(physic));
    this->_systems.push_back(std::move(playerMove));
    this->_systems.push_back(std::move(playerCollide));
    this->_systems.push_back(std::move(playerWeapon));
    this->_systems.push_back(std::move(projectiles));
    this->_systems.push_back(std::move(enemy));
    this->_systems.push_back(std::move(autoWeapon));
    this->_systems.push_back(std::move(lifetime));
    this->_systems.push_back(std::move(children));
    this->_systems.push_back(std::move(network));
    this->_systems.push_back(std::move(spawner));
    this->_systems.push_back(std::move(life));
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