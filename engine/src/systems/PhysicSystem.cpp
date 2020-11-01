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
    Box<int> boxA(0, 0, 0, 0);
    Box<int> boxB(0, 0, 0, 0);

    for (auto &a : this->_entities) {
        colliderA = a->getComponent<ColliderComponent>();
        boxA = Box<int>(a->getComponent<TransformComponent>()->getPos(),
                        a->getComponent<SpriteComponent>()->getSprite()->getSize());
        for (auto &b : this->_entities) {
            colliderB = b->getComponent<ColliderComponent>();
            boxB = Box<int>(b->getComponent<TransformComponent>()->getPos(),
                            b->getComponent<SpriteComponent>()->getSprite()->getSize());
            colliderB->clearCollisions();
            if (Geometry::doOverlap(boxA, boxB))
                colliderB->collide(a);
        }
    }
}