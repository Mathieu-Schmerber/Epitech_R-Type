/*
** EPITECH PROJECT, 2020
** RType
** File description:
** Created by Cyprien
*/

#include "components/PatternComponent.hpp"
#include "entities/Collectible.hpp"
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
    auto collider = enemy->getComponent<Engine::ColliderComponent>();
    auto collided = Collision::removeIgnored(static_cast<Collision::Mask>(collider->getCollisionMask()), collider->getCollisions());

    for (auto &c : collided) {
        if (c->getComponent<Engine::ColliderComponent>()->getCollisionMask() == Collision::Mask::WALL) {
            return true;
        }
    }
    return false;
}

void EnemySystem::deleteEntity(std::shared_ptr<Engine::Entity> &entity)
{
    const double bonusSpawnRate = BONUS_RATE;
    auto rdm = Engine::RandomETU::randETU<double>(0, 100);
    bool spawnBonus = (rdm <= bonusSpawnRate);
    std::shared_ptr<Engine::Entity> bonus;

    if (Engine::Utils::isInVector(this->_entities, entity)) {
        if (spawnBonus) {
            bonus = std::make_shared<Collectible>(entity->getComponent<Engine::TransformComponent>()->getPos(),
                                                  static_cast<CollectibleComponent::Type>(Engine::RandomETU::randETU<int>(0, 3)));
            this->_game->spawn(bonus, true);
        }
        Engine::Utils::removeFromVector(this->_entities, entity);
    }
}

void EnemySystem::update()
{
    auto cpy = _entities;

    for (auto &e : cpy)
        if (didCollide(e))
            _game->despawn(e);
    for (auto &e : this->_entities)
        handleMovements(e);
}