/*
** EPITECH PROJECT, 2020
** RType
** File description:
** Created by Cyprien
*/


#include "components/PatternComponent.hpp"
#include "EnemySystem.hpp"

EnemySystem::EnemySystem(std::shared_ptr<Game> &game) : _game(game), Engine::System()
{
    this->addDependency<Engine::ControllerComponent>();
    this->addDependency<Engine::TransformComponent>();
    this->addDependency<Engine::VelocityComponent>();
    this->addDependency<Engine::SpriteComponent>();
    this->addDependency<Engine::AnimationComponent>();
    this->addDependency<Engine::ColliderComponent>();
    this->addDependency<PatternComponent>();
}

void EnemySystem::handleMovements(std::shared_ptr<Engine::Entity> &enemy)
{
    const double speed = 0.2f;
    Engine::Vector<double> dir = {0, 0};

    enemy->getComponent<PatternComponent>()->move(enemy);
}

void EnemySystem::update()
{
    auto tmp = _entities;

    for (auto &e : tmp)
        if (e->getComponent<Engine::TransformComponent>()->getPos().x < 0)
            _game->despawn(e);
    for (auto &e : this->_entities) {
        handleMovements(e);
    }
}