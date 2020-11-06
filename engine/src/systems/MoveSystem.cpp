//
// Created by mathi on 06/11/2020.
//

#include "systems/MoveSystem.hpp"
#include "components/TransformComponent.hpp"
#include "components/VelocityComponent.hpp"

Engine::MoveSystem::MoveSystem()
{
    this->addDependency<TransformComponent>();
    this->addDependency<VelocityComponent>();
}

void Engine::MoveSystem::update()
{
    VelocityComponent *velocity = nullptr;
    TransformComponent *transform = nullptr;

    for (auto &e : this->_entities) {
        velocity = e->getComponent<VelocityComponent>();
        transform = e->getComponent<TransformComponent>();
        transform->movePos({static_cast<int>(velocity->getSpeed().x * this->deltatime()),
                            static_cast<int>(velocity->getSpeed().y * this->deltatime())});
    }
}