//
// Created by mathi on 13/11/2020.
//

#include "components/ChildrenComponent.hpp"
#include "components/TransformComponent.hpp"
#include "systems/TargetSystem.hpp"
#include "components/TargetComponent.hpp"

Engine::TargetSystem::TargetSystem() : Engine::System ()
{
    this->addDependency<Engine::TargetComponent>();
}

void Engine::TargetSystem::deleteEntity(std::shared_ptr<Engine::Entity> &entity)
{
    for (auto &e : this->_entities)
        e->getComponent<Engine::TargetComponent>()->removeTargetIfExists(entity);
    Utils::removeFromVector(this->_entities, entity);
}