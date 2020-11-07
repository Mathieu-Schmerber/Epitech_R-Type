//
// Created by mathi on 01/11/2020.
//

#include "components/TransformComponent.hpp"
#include "components/SpriteComponent.hpp"
#include "components/ColliderComponent.hpp"
#include "systems/PhysicSystem.hpp"

Engine::PhysicSystem::PhysicSystem() : Engine::System()
{
    this->addDependency<TransformComponent>();
    this->addDependency<SpriteComponent>();
    this->addDependency<ColliderComponent>();
}

void Engine::PhysicSystem::update()
{
    ColliderComponent *colliderA = nullptr;
    ColliderComponent *colliderB = nullptr;

    for (auto &a : this->_entities) {
        colliderA = a->getComponent<ColliderComponent>();
        for (auto &b : this->_entities) {
            colliderB = b->getComponent<ColliderComponent>();
            colliderB->clearCollisions();
            if (Geometry::doOverlap(colliderA->getHitBox(), colliderB->getHitBox()))
                colliderB->collide(a);
        }
    }
}