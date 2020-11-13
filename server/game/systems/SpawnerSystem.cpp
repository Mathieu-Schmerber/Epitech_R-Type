/*
** EPITECH PROJECT, 2020
** RType
** File description:
** Created by Cyprien
*/


#include "components/EnemySpawnerComponent.hpp"
#include "SpawnerSystem.hpp"

SpawnerSystem::SpawnerSystem(std::shared_ptr<Game> &game) : _game(game)
{
    this->addDependency<Engine::TransformComponent>();
    this->addDependency<Engine::VelocityComponent>();
    this->addDependency<Engine::ColliderComponent>();
    this->addDependency<EnemySpawnerComponent>();
}

void SpawnerSystem::handleSpawn(std::shared_ptr<Engine::Entity> &spawner)
{
    if (spawner->getComponent<EnemySpawnerComponent>()->canSpawn()) {
        std::shared_ptr<Enemy> e = std::shared_ptr<Enemy>(spawner->getComponent<EnemySpawnerComponent>()->getEntity("../lib/libfloatingRobot.so"));
        std::cout << "hihi" << std::endl;
        _game->spawn(e, true);
    }
}

void SpawnerSystem::update()
{
    for (auto &e : _entities) {
        handleSpawn(e);
    }
}
