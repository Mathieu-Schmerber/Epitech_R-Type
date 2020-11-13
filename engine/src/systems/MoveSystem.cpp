//
// Created by mathi on 06/11/2020.
//

#include "systems/MoveSystem.hpp"
#include "components/TransformComponent.hpp"
#include "components/VelocityComponent.hpp"
#include "components/ChildrenComponent.hpp"

Engine::MoveSystem::MoveSystem()
{
    this->addDependency<TransformComponent>();
    this->addDependency<VelocityComponent>();
}

void Engine::MoveSystem::update()
{
    VelocityComponent *velocity = nullptr;
    TransformComponent *transform = nullptr;
    ChildrenComponent *children = nullptr;

    for (auto &e : this->_entities) {
        velocity = e->getComponent<VelocityComponent>();
        velocity->setSpeed(velocity->getSpeed() + velocity->getAcceleration());
        transform = e->getComponent<TransformComponent>();
        transform->movePos({(velocity->getSpeed().x * this->deltatime()),
                            (velocity->getSpeed().y * this->deltatime())});
        children = e->getComponent<ChildrenComponent>();
        if (children != nullptr) {
            for (auto &c : children->getChildren()) {
                c->getComponent<TransformComponent>()->movePos({(velocity->getSpeed().x * this->deltatime()),
                                                                (velocity->getSpeed().y * this->deltatime())});
            }
        }
    }
}