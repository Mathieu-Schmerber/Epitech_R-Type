//
// Created by mathi on 10/11/2020.
//

#include "ProjectileSystem.hpp"
#include "components/ProjectileComponent.hpp"
#include "components/ColliderComponent.hpp"
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

    for (auto &c : collided) {
        //TODO: Apply damage here
    }
    return (!collided.empty());
}

void ProjectileSystem::update()
{
    auto copy = this->_entities;

    for (auto &e : copy) {
        if (e->getComponent<ProjectileComponent>()->isLifetimeOver() || this->didCollide(e))
            _game->despawn(e);
    }
}