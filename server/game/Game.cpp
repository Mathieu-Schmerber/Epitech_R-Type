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
#include "systems/BorderLimitSystem.hpp"
#include "components/NetworkComponent.hpp"
#include "systems/TargetSystem.hpp"
#include "entities/Collectible.hpp"

Game::Game(std::vector<std::shared_ptr<Client>> &players, std::unique_ptr<UdpSocketInput> &reception)
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

void Game::spawnPlayers()
{
    std::shared_ptr<Engine::Entity> player;

    std::cout << "[GAME] >> Player number: " << this->_players.size() << std::endl;
    for (int i = 0; i < this->_players.size(); ++i) {
        player = std::make_shared<Player>(i, Engine::Point<double>{500, 500.0 + (50.0 * i)});
        this->spawn(player, true);
        _playersSpaceShips.push_back(player);
    }
}

void Game::initGameEntities()
{
    auto parallaxA = std::make_unique<DataSprite>("../../client/assets/images/parallax/parallax_2_3840_1080.png");
    auto parallaxB = std::make_unique<DataSprite>("../../client/assets/images/parallax/parallax_2_3840_1080.png");
    parallaxA->setRect({{0, 0}, {3840, 1080}});
    parallaxB->setRect({{0, 0}, {3840, 1080}});
    std::shared_ptr<Engine::Entity> slideA = std::make_shared<Engine::ParallaxSlide>(Engine::Point<double>{0, 0}, Engine::Point<double>{-3840, 0}, Engine::Point<double>{-15, 0}, std::move(parallaxA));
    std::shared_ptr<Engine::Entity> slideB = std::make_shared<Engine::ParallaxSlide>(Engine::Point<double>{3840, 0}, Engine::Point<double>{0, 0}, Engine::Point<double>{-15, 0}, std::move(parallaxB));
    auto spawner = std::make_shared<Spawner>();

    this->spawnPlayers();
    this->spawn(slideA, true);
    this->spawn(slideB, true);
    this->spawn(spawner, true);

    auto sentinel1 = std::make_shared<Collectible>(Engine::Point<double>{600, 700}, CollectibleComponent::Type::SENTINEL);
    auto sentinel2 = std::make_shared<Collectible>(Engine::Point<double>{700, 700}, CollectibleComponent::Type::SENTINEL);
    auto dmg1 = std::make_shared<Collectible>(Engine::Point<double>{600, 600}, CollectibleComponent::Type::DAMAGE);
    auto dmg2 = std::make_shared<Collectible>(Engine::Point<double>{700, 600}, CollectibleComponent::Type::DAMAGE);
    auto dmg3 = std::make_shared<Collectible>(Engine::Point<double>{600, 500}, CollectibleComponent::Type::DAMAGE);
    auto dmg4 = std::make_shared<Collectible>(Engine::Point<double>{700, 500}, CollectibleComponent::Type::DAMAGE);
    auto bounce1 = std::make_shared<Collectible>(Engine::Point<double>{600, 400}, CollectibleComponent::Type::BOUNCE);
    auto bounce2 = std::make_shared<Collectible>(Engine::Point<double>{700, 400}, CollectibleComponent::Type::BOUNCE);
    auto missile1 = std::make_shared<Collectible>(Engine::Point<double>{600, 300}, CollectibleComponent::Type::MISSILE);
    auto missile2 = std::make_shared<Collectible>(Engine::Point<double>{700, 300}, CollectibleComponent::Type::MISSILE);
    this->spawn(sentinel1, true);
    this->spawn(sentinel2, true);
    this->spawn(dmg1, true);
    this->spawn(dmg2, true);
    this->spawn(dmg3, true);
    this->spawn(dmg4, true);
    this->spawn(bounce1, true);
    this->spawn(bounce2, true);
    this->spawn(missile1, true);
    this->spawn(missile2, true);
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
    auto ground = std::make_unique<GroundSystem>(game);
    auto enemy = std::make_unique<EnemySystem>(game);
    auto autoWeapon = std::make_unique<AutomaticWeaponSystem>(game);
    auto lifetime = std::make_unique<LifetimeSystem>(game);
    auto children = std::make_unique<Engine::ChildrenSystem>();
    auto spawner = std::make_unique<SpawnerSystem>(game);
    auto life = std::make_unique<HealthSystem>(game);
    auto target = std::make_unique<Engine::TargetSystem>();
    auto borderLimit = std::make_unique<BorderLimitSystem>(game);

    this->_systems.push_back(std::move(move));
    this->_systems.push_back(std::move(ground));
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
    this->_systems.push_back(std::move(spawner));
    this->_systems.push_back(std::move(life));
    this->_systems.push_back(std::move(target));
    this->_systems.push_back(std::move(borderLimit));
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

void Game::despawn(std::shared_ptr<Engine::Entity> &entity)
{
    for (auto &sys : this->_systems)
        sys->deleteEntity(entity); // On passe dans tous les systèmes à cause de target FIXME
    Engine::Utils::removeFromVector(this->_entities, entity);
    if (Engine::Utils::isInVector(this->_playersSpaceShips, entity))
        Engine::Utils::removeFromVector(this->_playersSpaceShips, entity);
}

bool Game::isGameRunning() const
{
    return this->_running;
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
        if (_players.empty()) {
            _running = false;
            std::cout << "End of the game" << std::endl;
        }
    }
    this->_running = !(this->_playersSpaceShips.empty());
}

void Game::removeClientInGame(const std::shared_ptr<Client> &cli)
{
    for (auto a = _players.begin(); a != _players.end(); ++a) {
        std::cout << cli->getId() << " && " << a->get()->getId() << std::endl;
        if (cli->getId() == a->get()->getId()) {
            this->_players.erase(a);
            std::cout << "Player remove game " << _players.size() << std::endl;
            return;
        }
    }
}
