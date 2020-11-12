//
// Created by mathi on 03/11/2020.
//

#include "sceneManagement/AEntityGroup.hpp"

Engine::AEntityGroup::AEntityGroup()
= default;

Engine::AEntityGroup::~AEntityGroup()
{
    this->_entities.clear();
}

std::vector<std::shared_ptr<Engine::Entity>> Engine::AEntityGroup::getEntities() const
{
    return this->_entities;
}

void Engine::AEntityGroup::addEntities(const std::vector<std::shared_ptr<Engine::Entity>> &entities)
{
    for (auto &e : entities) {
        this->_entities.push_back(e);
    }
}

void Engine::AEntityGroup::addEntity(std::shared_ptr<Engine::Entity> &entity)
{
    this->_entities.push_back(entity);
}

/*!
 * \brief Freezes some components
 * This function is called whenever a scene containing this EntityGroup is switched off
 */
void Engine::AEntityGroup::freeze() {}

/*!
 * \brief Unfreezes some components
 * This function is called whenever a scene containing this EntityGroup is switched on
 */
void Engine::AEntityGroup::unFreeze() {}