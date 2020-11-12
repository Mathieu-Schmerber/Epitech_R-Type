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
    for (auto &a : this->_entities) {
        auto colliderA = a->getComponent<ColliderComponent>();
        auto transform = a->getComponent<TransformComponent>();
        if (transform->getPos().x != colliderA->getHitBox().x1 || transform->getPos().y != (int)colliderA->getHitBox().x2) {
            auto original = colliderA->getBaseHitBox();
            auto current = colliderA->getHitBox();
            colliderA->setBaseHitBox({{(double)transform->getPos().x, (double)transform->getPos().y}, original.size});
            colliderA->setHitBox({{(double)transform->getPos().x, (double)transform->getPos().y}, current.size});
        }
        for (auto &b : this->_entities) {
            auto colliderB = b->getComponent<ColliderComponent>();
            colliderB->clearCollisions();
            if (Geometry::doOverlap(colliderA->getHitBox(), colliderB->getHitBox()))
                colliderB->collide(a);
        }
    }
}