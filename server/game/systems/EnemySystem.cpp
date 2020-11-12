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
    const float speed = 0.2;
    Engine::Vector<float> dir = {0, 0};

    dir.x += 1;
    dir.y += 1;
    dir = {dir.x * speed, dir.y * speed};
    enemy->getComponent<Engine::VelocityComponent>()->setSpeed(dir);
}

void EnemySystem::update()
{
    for (auto &e : this->_entities) {
        handleMovements(e);
    }
}
