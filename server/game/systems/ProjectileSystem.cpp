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
    bool willBeDestroyed = false;
    auto proj = projectile->getComponent<ProjectileComponent>();
    std::vector<std::shared_ptr<Engine::Entity>> list = proj->getHit();
    auto collider = projectile->getComponent<Engine::ColliderComponent>();
    auto collided = Collision::removeIgnored(static_cast<Collision::Mask>(collider->getCollisionMask()), collider->getCollisions());

    for (auto &c : collided) {
        if (c->getComponent<HealthComponent>() && !Engine::Utils::isInVector(list, c)) {
            c->getComponent<HealthComponent>()->loseHealth(projectile->getComponent<ProjectileComponent>()->getDamage());
            proj->addHit(c);
            list = proj->getHit();
        } else if (!c->getComponent<HealthComponent>())
            willBeDestroyed = true;
    }
    return (proj->getHit().size() >= proj->getNbHit() || willBeDestroyed);
}

void ProjectileSystem::update()
{
    auto copy = this->_entities;

    for (auto &e : copy) {
        if (this->didCollide(e))
            _game->despawn(e);
    }
}