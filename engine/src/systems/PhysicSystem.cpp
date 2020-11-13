//
// Created by mathi on 01/11/2020.
//

#include "components/TransformComponent.hpp"
#include "components/SpriteComponent.hpp"
#include "components/ColliderComponent.hpp"
#include "systems/PhysicSystem.hpp"
#include "tools/Utils.hpp"

Engine::PhysicSystem::PhysicSystem() : Engine::System()
{
    this->addDependency<TransformComponent>();
    this->addDependency<SpriteComponent>();
    this->addDependency<ColliderComponent>();
}

void Engine::PhysicSystem::update()
{
    for (auto &a : this->_entities) {
        auto colliderA = a->getComponent<ColliderComponent>();
        auto transform = a->getComponent<TransformComponent>();
        auto original = colliderA->getBaseHitBox();
        auto current = colliderA->getHitBox();
        colliderA->clearCollisions();
        colliderA->setBaseHitBox({transform->getPos(), original.size});
        colliderA->setHitBox({transform->getPos(), current.size});
        for (auto &b : this->_entities) {
            if (b == a)
                continue;
            auto colliderB = b->getComponent<ColliderComponent>();
            if (Geometry::doOverlap(colliderA->getHitBox(), colliderB->getHitBox()) &&
            colliderA->getCollisionMask() != colliderB->getCollisionMask()) {
                auto collisions = colliderA->getCollisions();
                if (!Utils::isInVector(collisions, b))
                    colliderA->collide(b);
                collisions = colliderB->getCollisions();
                if (!Utils::isInVector(collisions, a))
                    colliderB->collide(a);
            }
        }
    }
}