/*
** EPITECH PROJECT, 2020
** RType
** File description:
** Created by Cyprien
*/


#include "entities/Ground.hpp"
#include "components/EnemySpawnerComponent.hpp"
#include "SpawnerSystem.hpp"
#include "components/ColliderComponent.hpp"

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
        auto enemies = spawner->getComponent<EnemySpawnerComponent>()->getLibs();
        std::shared_ptr<Enemy> e = std::shared_ptr<Enemy>(spawner->getComponent<EnemySpawnerComponent>()->getEntity(enemies.at(0)));
        e->getComponent<Engine::TransformComponent>()->setPos(spawner->getComponent<Engine::TransformComponent>()->getPos());
        _game->spawn(e, true);
    }
}

void SpawnerSystem::handleMove(std::shared_ptr<Engine::Entity> &spawner)
{
    if (spawner->getComponent<Engine::TransformComponent>()->getPos().y >= 1080 - (GROUND_HEIGHT * 4) ||
    spawner->getComponent<Engine::TransformComponent>()->getPos().y <= (GROUND_HEIGHT * 4)) {
        spawner->getComponent<Engine::VelocityComponent>()->setSpeed(spawner->getComponent<Engine::VelocityComponent>()->getSpeed() * Engine::Vector<double>({0, -1}));
    }
}

void SpawnerSystem::update()
{
    for (auto &e : _entities) {
        handleSpawn(e);
        handleMove(e);
    }
}
