//
// Created by mathi on 29/10/2020.
//

#include "System.hpp"

template<typename T> void Engine::System::addDependency() {
    this->_dependencies.push_back(std::make_unique<T>());
}

void Engine::System::addEntity(std::unique_ptr<Engine::Entity> &entity)
{
    this->_entities.emplace_back(entity);
}

std::vector<std::unique_ptr<Engine::Component>> &Engine::System::getDependencies()
{
    return this->_dependencies;
}

std::vector<std::reference_wrapper<std::unique_ptr<Engine::Entity>>> &Engine::System::getEntities()
{
    return this->_entities;
}