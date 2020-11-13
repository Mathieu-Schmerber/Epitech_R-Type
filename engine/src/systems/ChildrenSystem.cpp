//
// Created by mathi on 13/11/2020.
//

#include "components/ChildrenComponent.hpp"
#include "components/TransformComponent.hpp"
#include "systems/ChildrenSystem.hpp"

Engine::ChildrenSystem::ChildrenSystem() : Engine::System ()
{
    this->addDependency<TransformComponent>();
    this->addDependency<ChildrenComponent>();
}

void Engine::ChildrenSystem::deleteEntity(std::shared_ptr<Engine::Entity> &entity)
{
    for (auto &e : this->_entities)
        e->getComponent<ChildrenComponent>()->removeChildIfExists(entity);
    Utils::removeFromVector(this->_entities, entity);
}