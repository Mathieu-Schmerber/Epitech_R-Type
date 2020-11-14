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
    enemy->getComponent<PatternComponent>()->move(enemy);
}

bool EnemySystem::didCollide(std::shared_ptr<Engine::Entity> &enemy)
{
    bool willBeDestroyed = false;
    auto collider = enemy->getComponent<Engine::ColliderComponent>();
    auto collided = Collision::removeIgnored(static_cast<Collision::Mask>(collider->getCollisionMask()), collider->getCollisions());

    for (auto &c : collided) {
        if (c->getComponent<HealthComponent>()) {
            c->getComponent<HealthComponent>()->setCurrentHealth(0);
            willBeDestroyed = true;
        }
    }
    return willBeDestroyed;
}

void EnemySystem::update()
{
    auto tmp = _entities;

    for (auto &e : tmp)
        if (e->getComponent<Engine::TransformComponent>()->getPos().x < -100 || didCollide(e))
            _game->despawn(e);
    for (auto &e : this->_entities) {
        handleMovements(e);
    }
}