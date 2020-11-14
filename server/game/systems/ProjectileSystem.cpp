//
// Created by mathi on 10/11/2020.
//

#include "ProjectileSystem.hpp"
#include "CollisionMasks.hpp"

ProjectileSystem::ProjectileSystem(std::shared_ptr<Game> &game) : _game(game), Engine::System()
{
    this->addDependency<ProjectileComponent>();
    this->addDependency<Engine::ColliderComponent>();
    this->addDependency<Engine::VelocityComponent>();
}

void ProjectileSystem::bounce(std::shared_ptr<Engine::Entity> &projectile, std::shared_ptr<Engine::Entity> &collision)
{
    auto velocity = projectile->getComponent<Engine::VelocityComponent>();
    Engine::Point<double> speed = Engine::Geometry::normalizeVector(velocity->getSpeed());
    auto box1 = projectile->getComponent<Engine::ColliderComponent>()->getHitBox();
    auto box2 = collision->getComponent<Engine::ColliderComponent>()->getHitBox();
    Engine::Point<double> normal = Engine::Geometry::getCollisionNormal(box2, box1);
    Engine::Point<double> reflection = Engine::Geometry::getReflection(speed, normal);

    std::cout << "reflection " << reflection << std::endl;
    velocity->setSpeed(reflection);
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
            std::cout << "player life " << c->getComponent<HealthComponent>()->getCurrentHealth() << std::endl;
            list = proj->getHit();
        } else if (!c->getComponent<HealthComponent>()) {
            willBeDestroyed = !proj->canBounce();
            if (proj->canBounce())
                ProjectileSystem::bounce(projectile, c);
        }
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