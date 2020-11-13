//
// Created by mathi on 10/11/2020.
//

#include "ProjectileSystem.hpp"
#include "components/ProjectileComponent.hpp"
#include "CollisionMasks.hpp"

ProjectileSystem::ProjectileSystem(std::shared_ptr<Game> &game) : _game(game), Engine::System()
{
    this->addDependency<ProjectileComponent>();
    this->addDependency<Engine::ColliderComponent>();
}

bool ProjectileSystem::didCollide(std::shared_ptr<Engine::Entity> &projectile)
{
    auto collider = projectile->getComponent<Engine::ColliderComponent>();
    auto collided = Collision::removeIgnored(static_cast<Collision::Mask>(collider->getCollisionMask()), collider->getCollisions());

    for (auto &c : collider->getCollisions()) {
        if (c->getComponent<HealthComponent>()) {
            c->getComponent<HealthComponent>()->loseHealth(projectile->getComponent<ProjectileComponent>()->getDamage());
        }
    }
    return (!collided.empty());
}

void ProjectileSystem::update()
{
    auto copy = this->_entities;

    for (auto &e : copy) {
        if (this->didCollide(e))
            _game->despawn(e);
    }
}